#include <QDir>
#include <QCryptographicHash>

#include <unistd.h>
#include <pwd.h>
#include <grp.h>

#include "RenderResponseFileStation.h"
#include "FileSuffixDescription.h"

bool copyDirRecursive(QString fromDir, QString toDir, bool replaceOnConflit = true)
{
    QDir dir;
    dir.setPath(fromDir);

    fromDir += QDir::separator();
    toDir += QDir::separator();

    foreach(QString copyFile, dir.entryList(QDir::Files)) {
        QString from = fromDir + copyFile;
        QString to = toDir + copyFile;

        if (QFile::exists(to)) {
            if (replaceOnConflit) {
                if (!QFile::remove(to))
                    return false;
            }
            else
                continue;
        }
        if (!QFile::copy(from, to)) {
            tDebug("Copy file fail: %s", from.toLocal8Bit().data());
            return false;
        }
        else {
            QFileInfo fromInfo = QFileInfo(from);
            if(chown(to.toLocal8Bit().data(), fromInfo.ownerId(), fromInfo.groupId()) != 0) {
                tDebug("chwon failed: %s", to.toLocal8Bit().data());
                return false;
            }
        }
    }

    foreach(QString copyDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString from = fromDir + copyDir;
        QString to = toDir + copyDir;

        if (dir.mkpath(to)) {
            QFile::setPermissions(to, (QFileDevice::Permission)0x0777);
            QFileInfo fromInfo = QFileInfo(from);
            if(chown(to.toLocal8Bit().data(), fromInfo.ownerId(), fromInfo.groupId()) != 0) {
                tDebug("chwon failed: %s", to.toLocal8Bit().data());
                return false;
            }
        }
        else
            return false;

        if (!copyDirRecursive(from, to, replaceOnConflit))
            return false;
    }

    return true;
}

bool getUid(const char *username, uint &uid) {
    struct passwd pwd;
    struct passwd *result;
    char *buf;
    long bufsize;

    bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
    if (bufsize == -1)          /* Value was indeterminate */
        bufsize = 16384;        /* Should be more than enough */

    buf = (char *)malloc(bufsize);
    if (buf == NULL) {
        //perror("malloc");
        return false;
    }

    getpwnam_r(username, &pwd, buf, bufsize, &result);
    if (result != NULL) {
        uid = pwd.pw_uid;
        return true;
    }

    return false;
}

bool getGid(const char *groupName, uint &gid) {
    struct group gwd;
    struct group *result;
    char *buf;
    long bufsize;

    bufsize = sysconf(_SC_GETGR_R_SIZE_MAX);
    if (bufsize == -1)          /* Value was indeterminate */
        bufsize = 16384;        /* Should be more than enough */

    buf = (char *)malloc(bufsize);
    if (buf == NULL) {
        //perror("malloc");
        return false;
    }

    getgrnam_r(groupName, &gwd, buf, bufsize, &result);
    if (result != NULL) {
        gid = gwd.gr_gid;
        return true;
    }

    return false;
}

RenderResponseFileStation::RenderResponseFileStation(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseFileStation::~RenderResponseFileStation() {
}

void RenderResponseFileStation::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_OPEN_TREE:
        generateOpenTree();
        break;
    case CMD_OPEN_NEW_FOLDER:
        generateOpenNewFolder();
        break;
    case CMD_FOLDER_CONTENT:
        generateFolderContent();
        break;
    case CMD_EMPTY_FOLDER:
        generateEmptyFolder();
        break;
    case CMD_GET_USER_QUOTA:
        generateGetUserQuota();
        break;
    case CMD_CHK_FILE:
        generateChkFile();
        break;
    case CMD_COMPRESS:
        generateCompress();
        break;
    case CMD_DOWNLOAD:
        generateDownload();
        break;
    case CMD_CP:
        generateCp();
        break;
    case CMD_MOVE:
        generateMove();
        break;
    case CMD_DEL:
        generateDel();
        break;
    case CMD_RENAME:
        generateRename();
        break;
    case CMD_GET_PROPERTIES:
        generateGetProperties();
        break;
    case CMD_CHANGE_PERMISSIONS:
        generateChangePermissions();
        break;
    case CMD_ADD_ZIP:
        generateAddZip();
        break;
    case CMD_UNZIP:
        generateUnzip();
        break;
    case CMD_UNTAR:
        generateUntar();
        break;
    case CMD_GET_SECDOWNLOAD_URL:
        generateGetSecDownloadUrl();
        break;
    case CMD_GET_COOLIRIS_RSS:
        generateGetCoolirisRss();
        break;
    
    default:
        break;
    }

}

QString RenderResponseFileStation::getFileDescription(QString &suffix) {

    QString ret;
    int iSize = sizeof(SUFFIX_DESCRIPTION_TABLE)/sizeof(SUFFIX_DESCRIPTION_TABLE[0]);
    for(int i = 0; i < iSize; i++) {
        if(QString(SUFFIX_DESCRIPTION_TABLE[i][0]) == suffix) {
            ret = SUFFIX_DESCRIPTION_TABLE[i][1];
            break;
        }
    }

    return ret;

}

void RenderResponseFileStation::generateOpenTree() {
    QString paraDir = QUrl::fromPercentEncoding(m_pReq->parameter("dir").toLocal8Bit());
    QString paraShowFile = m_pReq->parameter("show_file");
    QString paraChkFlag = m_pReq->parameter("chk_flag");
    QString paraFileType = m_pReq->parameter("file_type");
    QString paraFuncId = m_pReq->parameter("function_id");
//    QString paraFilterFile = m_pReq->parameter("filter_file");
//    QString paraRootPath = m_pReq->parameter("root_path");

    QString cssUlClass = "<ul class=\"jqueryFileTree\" style=\"display: none;\">\n"
                            "%1"
                         "</ul>";
    QString cssLiClass =        "    <li class=\"directory collapsed%1\">\n"
                                "%2%3"
                                "    </li>\n";
    /* todo */
    QString cssLiClassWithID =  "    <li id=\"eve_test_456\" class=\"file ext_zip\">\n"
                                "%1%2"
                                "    </li>\n";
    QString checkboxLine = "        <input type='checkbox' name='folder_name' value=\"%1\" %2rel=\"%3\">\n";
    QString checkboxSrc = "src=\"%1\" ";
    QString hrefLine = "        <a href=\"#\" rel=\"%1\">%2</a>\n";

    QDir dir(paraDir);
    QDir::Filters filters = QDir::NoDotAndDotDot | QDir::Dirs;
    if(paraShowFile.compare("1") == 0)
        filters |= QDir::AllEntries;
    QFileInfoList fileList = dir.entryInfoList(filters);

    QListIterator<QFileInfo> iter(fileList);
    while (iter.hasNext()) {
        QFileInfo entry = iter.next();

        if(            entry.fileName() == "lost+found"
                    || entry.fileName() == "Nas_Prog"
                    || entry.fileName() == "aMule"
                    || entry.fileName() == "ShareCenter_Sync") {
            fileList.removeOne(entry);
            continue;
        }

        if(paraShowFile == "0") {
            if(!entry.isDir()) {
                fileList.removeOne(entry);
                continue;
            }
        }
        else if(paraShowFile == "1") {
            if(paraFuncId == "iso_mount") {
                if(entry.isDir() || entry.suffix().compare("iso", Qt::CaseInsensitive) == 0)
                    continue;
                fileList.removeOne(entry);
                continue;
            }
        }

    }

    QString content;
    QStringList shareInfo = getAPIFileOut(SHARE_INFO_FILE);
    for(QFileInfo e : fileList) {
        QString fileName = e.fileName();

        for(QString shareEntry : shareInfo) {
            if(e.absoluteFilePath().compare(shareEntry.split(":").value(1)) == 0) {
                fileName = shareEntry.split(":").value(0);
                break;
            }
        }

        if(e.absoluteDir().absolutePath() == "/mnt/HD" && !fileName.startsWith("Volume_"))
            break;

        QString line2 = hrefLine.arg(e.absoluteFilePath() + QDir::separator()).arg(fileName);
        if(e.isDir()) {
            QString line1 = (paraChkFlag.compare("1") == 0) ?
                        checkboxLine.arg(e.absoluteFilePath()).arg(checkboxSrc.arg(fileName)).arg(fileName) : QString::null;
            content += cssLiClass.arg("").arg(line1).arg(line2);
        }
        else {
            QString fileVolumePath = e.absoluteFilePath();
            if(fileVolumePath.startsWith("/mnt/HD/HD_")) {
                for(QString shareEntry : shareInfo) {
                    if(fileVolumePath.startsWith(shareEntry.split(":").value(1))) {
                        fileVolumePath.replace(shareEntry.split(":").value(1), shareEntry.split(":").value(0));
                        break;
                    }
                }
            }
            QString line1 = (paraChkFlag.compare("1") == 0) ?
                        checkboxLine.arg(e.absoluteFilePath()).arg(QString::null).arg(fileVolumePath) : QString::null;
            content += cssLiClassWithID.arg(line1).arg(line2);
        }
    }

    /* If it was not rooted path, we can add folder. */
    QString dirAbsolutePath(dir.absolutePath());
    if(     !(dirAbsolutePath.compare("/mnt/HD") == 0 ||
             dirAbsolutePath.compare("/mnt/USB") == 0)) {
        QString line2 = hrefLine.arg(dirAbsolutePath + "/new/").arg("New");
        content += cssLiClass.arg(" add").arg("").arg(line2);
    }

    m_var = cssUlClass.arg(content);
}

void RenderResponseFileStation::generateOpenNewFolder() {

    QDomDocument doc;

    QString paraDir = QUrl::fromPercentEncoding(m_pReq->parameter("dir").toLocal8Bit());
    QString paraFileName = m_pReq->parameter("filename");
    QString paraShowFile = m_pReq->parameter("show_file");
    QString paraChkFlag = m_pReq->parameter("chk_flag");
    //QString paraFileType = m_pReq->parameter("file_type");
    QString paraFuncId = m_pReq->parameter("function_id");
    QString paraFilterFile = m_pReq->parameter("filter_file");
    QString paraRootPath = m_pReq->parameter("root_path");

    QDir dir(paraDir);
    bool bMkdir = dir.mkdir(paraFileName);
    if(bMkdir) {
        QFileInfo fileInfo = QFileInfo(dir.absolutePath() + QDir::separator() + paraFileName);
        QFile(fileInfo.absoluteFilePath()).setPermissions((QFileDevice::Permission)0x0777);

        uint gid, uid;
        if(getGid("allaccount", gid) && getUid("nobody", uid)) {
            if(chown(fileInfo.absoluteFilePath().toLocal8Bit().data(), uid, gid) != 0)
                tDebug("chwon failed: %s", fileInfo.absolutePath().toLocal8Bit().data());
        }
        else
            tDebug("UID or GID is not found.");
    }
    QString ret = bMkdir ? "ok" : "error";

    QDomElement root = doc.createElement("mkdir");
    doc.appendChild(root);

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(ret));

    m_var = doc.toString();

}

void RenderResponseFileStation::generateFolderContent() {
    QDomDocument doc;

    QString paraPage = m_pReq->parameter("page");
    QString paraRp = m_pReq->parameter("rp");
    QString paraQuery = m_pReq->parameter("query");
    QString paraType = m_pReq->parameter("qtype");
    QString paraField = m_pReq->parameter("f_field");
    QString paraUsedDir = QUrl::fromPercentEncoding(m_pReq->parameter("used_dir").toLocal8Bit());

    QString itemContent =   "<span style='display:none'>%1</span>"
                            "<span class='%2'><span>%3</span></span>"
                            ;

    QDir dir(paraUsedDir);
    QDir::Filters filters = QDir::NoDotAndDotDot | QDir::AllEntries;
    QFileInfoList fileList= dir.entryInfoList(filters);

    QListIterator<QFileInfo> iter(fileList);
    while (iter.hasNext()) {
        QFileInfo entry = iter.next();
        if(            entry.fileName() == "lost+found"
                    || entry.fileName() == "Nas_Prog"
                    || entry.fileName() == "aMule"
                    || entry.fileName() == "ShareCenter_Sync") {
            fileList.removeOne(entry);
            continue;
        }

        if(paraType == "name" && !paraQuery.isEmpty())
            if(!entry.fileName().contains(paraQuery))
                fileList.removeOne(entry);
    }

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    int start = (paraPage.toInt()-1) * paraRp.toInt();
    int end = start + paraRp.toInt();
    if(end > fileList.size())
        end = fileList.size();

    for(int i = start; i < end; i++) {
        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);

        QString fileDescription;
        if(fileList.value(i).isDir())
            fileDescription = "Folder";
        else {
            QString suffix = fileList.value(i).suffix();
            fileDescription = getFileDescription(suffix);
            if(fileDescription.isEmpty()) {
                if(suffix.size() >= 7)
                    fileDescription = "File";
                else
                    fileDescription = suffix.toUpper() + " File";
            }
        }

        QString fileSize;
        if(!fileList.value(i).isDir())
            fileSize = sizeHuman(fileList.value(i).size());

        QString table = fileList.value(i).isDir() ? "table_folder" : "table_file";

        QStringList cellContent(QStringList() <<
            itemContent.arg(fileList.value(i).absoluteFilePath()).arg(table).arg(fileList.value(i).fileName()) <<
            fileSize <<
            fileDescription <<
            fileList.value(i).lastModified().toString("yyyy-MM-dd hh:mm:ss"));

        for(QString e : cellContent) {
            QDomElement cellElement = doc.createElement("cell");
            rowElement.appendChild(cellElement);
            if(e == cellContent.value(0))
                cellElement.appendChild(doc.createCDATASection(e));
            else
                cellElement.appendChild(doc.createTextNode(e));
        }

        rowElement.setAttribute("id", i - start + 1);
    }

//    int total = 1;
//    if(paraRp.toInt() != 0)
//        total = fileList.size() / paraRp.toInt() + (fileList.size() % paraRp.toInt() != 0);

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(fileList.size())));
    m_var = doc.toString();

}

/* status= -1 | -2 | -3 | 0 (int)
 * //0=ok (empty folder),
 * -1=To sync with Google Drive, please select an empty folder on your NAS or clean the data in the folder you selected. ,
 * -2=Folder not exist. ,
 * -3=Selected folder is invalid, please select a sub-folder or create a new folder. */

void RenderResponseFileStation::generateEmptyFolder() {
    QDomDocument doc;
    QString paraDir = QUrl::fromPercentEncoding(m_pReq->parameter("dir").toLocal8Bit());

    QString ret = "-3";
    if(paraDir.startsWith("Volume_")) {
        QString dirPath = paraDir;
        replaceVoltoRealPath(dirPath);

        QFileInfo dirInfo(dirPath);
        if(dirInfo.isDir() && dirInfo.exists()) {
            QDir dir(dirPath);
            QDir::Filters filters = QDir::NoDotAndDotDot | QDir::AllEntries;
            if(dir.entryInfoList(filters).isEmpty())
                ret = "0";
            else
                ret = "-1";
        }
        else ret = "-2";
    }
    else ret = "-3";

    QDomElement root = doc.createElement("result");
    doc.appendChild(root);

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(ret));

    m_var = doc.toString();

}

/* todo */
void RenderResponseFileStation::generateGetUserQuota() {
    QDomDocument doc;
    QStringList configContentElement(QStringList()
        << "used_size" << "g_used_size" << "limit_size" << "g_limit_size" << "hdd_free_size" << "enable");

    QStringList valusElement(QStringList()
        << "0" << "0" << "0" << "0" << "2863845948" << "0");

    QDomElement root = doc.createElement("quota");
    doc.appendChild(root);

    for(int i=0; i<configContentElement.size(); i++) {
        QDomElement element = doc.createElement(configContentElement.value(i));
        root.appendChild(element);
        element.appendChild(doc.createTextNode(valusElement.value(i)));
    }
    m_var = doc.toString();

}

void RenderResponseFileStation::generateChkFile() {
    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());
    QString paraName = m_pReq->parameter("name");

    QString ret = "1";
    QString source = FILE_TMP_PATH + QDir::separator() + paraName;
    QString dest = paraPath + QDir::separator() + paraName;

    if(QFile::copy(source, dest)) {

        QFileInfo fileInfo = QFileInfo(dest);
        QFile(fileInfo.absoluteFilePath()).setPermissions((QFileDevice::Permission)0x0666);

        QByteArray user = m_pReq->cookie("username");
        if(!user.isEmpty()) {
            uint uid;
            if(getUid(user.data(), uid)) {
                uint gid;
                bool bFound = false;
                if(uid == 0) {
                    gid = 0;
                    bFound = true;
                }
                else {
                    if(getGid("allaccount", gid))
                        bFound = true;
                }

                if(bFound) {
                    if(chown(dest.toLocal8Bit().data(), uid, gid) != 0)
                        tDebug("chwon failed: %s", dest.toLocal8Bit().data());
                }
            }
        }
        ret = "0";
    }

    if(QFile::exists(source))
        QFile::remove(source);

    QDir dir(paraPath);
    if(!dir.exists(paraName))
        ret = "1";

    m_var = ret;
}

void RenderResponseFileStation::generateCompress() {

    QDomDocument doc;

    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());
    QString paraName = m_pReq->parameter("name");

    QString ret = "error";

    QString tmpPath(FILE_TMP_PATH);
    if(QDir(tmpPath).exists()) {

        //QFile::setPermissions(tmpPath, (QFileDevice::Permission)0x0777);
        QString outFileName;

        if(!QFileInfo(QDir(paraPath).absolutePath() + QDir::separator() + paraName).isDir()) {
            outFileName = paraName;
            QString dest = tmpPath + QDir::separator() + outFileName;
            if(QFile::exists(dest))
                QFile::remove(dest);
            QFile::copy(QDir(paraPath).absolutePath() + QDir::separator() + outFileName,
                        dest);
        }
        else {
            outFileName = paraName + ".zip";
            QString currentPath = QDir::currentPath();
            QDir::setCurrent(paraPath);
            QString compressCmd = "zip -FSr \"%1/%2\" \"%2\"";
            getAPIStdOut(compressCmd.arg(tmpPath).arg(paraName), false, "", true);
            QDir::setCurrent(currentPath);
        }

        QFileInfo zipFileInfo(tmpPath + QDir::separator() + outFileName);
        if(zipFileInfo.exists())
            ret = "ok";

    }

    QDomElement root = doc.createElement("result");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(ret));
    m_var = doc.toString();

}


void RenderResponseFileStation::generateDownload() {

    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path1").toLocal8Bit());
    QString paraName = m_pReq->parameter("name");

    QString tmpPath(FILE_TMP_PATH);
    QString zipFileName = paraName;
    QFileInfo file(tmpPath + QDir::separator() + zipFileName);
    if(file.exists() && file.isFile()) {
        m_var = file.absoluteFilePath();
    }
    else {
        zipFileName += ".zip";
        file = QFileInfo(tmpPath + QDir::separator() + zipFileName);
        if(file.exists() && file.isFile())
            m_var = file.absoluteFilePath();
    }

}

bool RenderResponseFileStation::copy(QString &source, QString &dest) {

    QFileInfo sourceInfo(source);
    if(!dest.endsWith(QDir::separator()))
        dest += QDir::separator();
    dest += sourceInfo.fileName();
    if(sourceInfo.isDir()) {
        if (QDir().mkpath(dest)) {
            QFile::setPermissions(dest, (QFileDevice::Permission)0x0777);
            QFileInfo sourceInfo = QFileInfo(source);
            if(chown(dest.toLocal8Bit().data(), sourceInfo.ownerId(), sourceInfo.groupId()) != 0) {
                tDebug("chwon failed: %s", dest.toLocal8Bit().data());
                return false;
            }
            return copyDirRecursive(source, dest);
        }
    }
    else {
        bool bCopy = QFile::copy(source, dest);
        tDebug("%s, %s", source.toLocal8Bit().data(), dest.toLocal8Bit().data());
        QFileInfo sourceInfo = QFileInfo(source);
        if(chown(dest.toLocal8Bit().data(), sourceInfo.ownerId(), sourceInfo.groupId()) != 0) {
            tDebug("chwon failed: %s", dest.toLocal8Bit().data());
            bCopy = false;
        }
        return bCopy;
    }

    return false;
}

void RenderResponseFileStation::generateCp() {

    QDomDocument doc;

    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());
    QString paraSourcePath = QUrl::fromPercentEncoding(m_pReq->parameter("source_path").toLocal8Bit());

    QString dest = paraPath;
    replaceVoltoRealPath(dest);

    QString ret = copy(paraSourcePath, dest) ? "ok" : "error";

    QDomElement root = doc.createElement("result");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(ret));
    m_var = doc.toString();

}

void RenderResponseFileStation::generateMove() {

    QDomDocument doc;

    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());
    QString paraSourcePath = QUrl::fromPercentEncoding(m_pReq->parameter("source_path").toLocal8Bit());

    QString dest = paraPath;
    replaceVoltoRealPath(dest);

    bool bRemove = false;
    if(copy(paraSourcePath, dest)) {
        QFileInfo fileInfo(paraSourcePath);
        if(fileInfo.isDir())
            bRemove = QDir(paraSourcePath).removeRecursively();
        else
            bRemove = QFile(paraSourcePath).remove();
    }

    QString ret = bRemove ? "ok" : "error";

    QDomElement root = doc.createElement("result");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(ret));
    m_var = doc.toString();

}

void RenderResponseFileStation::generateDel() {

    QDomDocument doc;
    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());

    QFileInfo fileInfo(paraPath);
    bool bRemove = false;
    if(fileInfo.isDir())
        bRemove = QDir(paraPath).removeRecursively();
    else
        bRemove = QFile(paraPath).remove();

    QString ret = bRemove ? "ok" : "error";

    QDomElement root = doc.createElement("result");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(ret));
    m_var = doc.toString();

}

void RenderResponseFileStation::generateRename() {

    QDomDocument doc;

    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());
    QString paraSourcePath = QUrl::fromPercentEncoding(m_pReq->parameter("source_path").toLocal8Bit());

    QString ret = QDir().rename(paraSourcePath, paraPath) ? "ok" : "error";

    QDomElement root = doc.createElement("result");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(ret));
    m_var = doc.toString();

}

void RenderResponseFileStation::generateGetProperties() {

    QDomDocument doc;

    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());

    QStringList statusElement(QStringList()
        << "change_time" << "modify_time" << "access_time" << "owner" << "group" << "permission");
    QFileInfo fileInfo(paraPath);
    QString filePermission = "rwxrwxrwx";
    QFile::Permissions permissions = fileInfo.permissions();
    QList<QFileDevice::Permission> permissionList;
    permissionList << QFileDevice::ReadUser << QFileDevice::WriteUser << QFileDevice::ExeUser <<
                      QFileDevice::ReadGroup << QFileDevice::WriteGroup << QFileDevice::ExeGroup <<
                      QFileDevice::ReadOther << QFileDevice::WriteOther << QFileDevice::ExeOther;
    for(int i = permissionList.size(); i>=0; i--)
        if(!(permissions & permissionList.value(i)))
            filePermission[i] = QChar('-');

    QStringList contentElement(QStringList()
        << fileInfo.created().toString("yyyy-M-d h:m")
        << fileInfo.lastModified().toString("yyyy-M-d h:m")
        << fileInfo.lastRead().toString("yyyy-M-d h:m")
        << fileInfo.owner()
        << fileInfo.group()
        << filePermission);

    QDomElement root = doc.createElement("status");
    doc.appendChild(root);

    for(int i=0; i<statusElement.size(); i++) {
        QDomElement element = doc.createElement(statusElement.value(i));
        root.appendChild(element);
        element.appendChild(doc.createTextNode(contentElement.value(i)));
    }
    m_var = doc.toString();

}

void RenderResponseFileStation::generateChangePermissions() {

    QDomDocument doc;

    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());
    QString paraPermission = m_pReq->parameter("permission");

    bool ok = false;
    QString ret = QFile::setPermissions(paraPath,
                                        (QFileDevice::Permission)paraPermission.toInt(&ok, 16))
                            ? "ok" : "error";

    QDomElement root = doc.createElement("result");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(ret));

    m_var = doc.toString();

}

void RenderResponseFileStation::generateAddZip() {

    QDomDocument doc;

    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());
    QString paraSelectName = m_pReq->parameter("select_name");
    QString paraName = QUrl::fromPercentEncoding(m_pReq->parameter("name").toLocal8Bit());
    //QString paraCommand = QUrl::fromPercentEncoding(m_pReq->parameter("command").toLocal8Bit());

    QString zipFileName = paraName;
    if(paraName.startsWith(QDir::separator())) {
        QFileInfo fileInfo(paraName);
        zipFileName = fileInfo.fileName();
    }

    QString ret = "error";
    QDir dir(paraPath);
    if(dir.exists()) {

        QString currentPath = QDir::currentPath();
        QDir::setCurrent(paraPath);
        QString compressCmd = "zip -r \"%1/%2\" \"%3\"";

        getAPIStdOut(compressCmd.arg(paraPath).arg(zipFileName).arg(paraSelectName.replace("*", " ")), false, "", true);
        QDir::setCurrent(currentPath);

        QFileInfo zipFileInfo(paraPath + QDir::separator() + zipFileName);
        if(zipFileInfo.exists())
            ret = "ok";

    }

    QDomElement root = doc.createElement("result");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(ret));
    m_var = doc.toString();

}

bool RenderResponseFileStation::unArchive(QString &path, QString &name, QString cmd) {
    QDir dir(path);
    if(dir.exists()) {
        QString currentPath = QDir::currentPath();
        QDir::setCurrent(path);
        QString uncompressCmd = "%1 \"%2\"";
        getAPIStdOut(uncompressCmd.arg(cmd).arg(name), false, "", true);
        QDir::setCurrent(currentPath);

        return true;
    }
    return false;
}

void RenderResponseFileStation::generateUnzip() {

    QDomDocument doc;

    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());
    QString paraName = QUrl::fromPercentEncoding(m_pReq->parameter("name").toLocal8Bit());

    QString ret = unArchive(paraPath, paraName, "unzip -o") ? "ok" : "error";

    QDomElement root = doc.createElement("result");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(ret));
    m_var = doc.toString();

}

void RenderResponseFileStation::generateUntar() {

    QDomDocument doc;

    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());
    QString paraName = QUrl::fromPercentEncoding(m_pReq->parameter("name").toLocal8Bit());

    QString cmd;
    QFileInfo fileInfo(paraPath + QDir::separator() + paraName);
    if(fileInfo.completeSuffix() == "tar.gz" || fileInfo.completeSuffix() == "tgz")
        cmd = "tar -zxvf";
    else if(fileInfo.completeSuffix() == "tar")
        cmd = "tar -xvf";

    QString ret = "error";
    if(!cmd.isEmpty())
        ret = unArchive(paraPath, paraName, cmd) ? "ok" : "error";

    QDomElement root = doc.createElement("result");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(ret));
    m_var = doc.toString();

}

/* lighttpd secret dwonload:
 * 1. a secret string (user supplied)
 * 2. <rel-path> (starts with /)
 * 3. <timestamp-in-hex>
 */
QString RenderResponseFileStation::getSecretPath(QString filePath) {
    QString secDownloadPath;

    if(QFileInfo(filePath).exists()) {
        filePath.remove("/mnt");
        QByteArray hexTime = QByteArray::number(QDateTime::currentDateTime().toTime_t(), 16);
        QByteArray hashResult = QCryptographicHash::hash("TNo5FFCWt1gT" +
                                                         filePath.toLocal8Bit() +
                                                         hexTime,
                                                         QCryptographicHash::Md5)
                                                        .toHex();

        secDownloadPath = QString("/sdownload/%1/%2%3")
                .arg(QString(hashResult))
                .arg(QString(hexTime))
                .arg(filePath);
    }

    return secDownloadPath;
}


void RenderResponseFileStation::generateGetSecDownloadUrl() {

    QDomDocument doc;
    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("f_path").toLocal8Bit());
    QString secDownloadPath = getSecretPath(paraPath);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(secDownloadPath.isEmpty() ? "0" : "1"));
    QDomElement myUrlElement = doc.createElement("my_url");
    root.appendChild(myUrlElement);
    myUrlElement.appendChild(doc.createTextNode(secDownloadPath));
    m_var = doc.toString();

}

void RenderResponseFileStation::generateGetCoolirisRss() {

    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());
    QString paraName = QUrl::fromPercentEncoding(m_pReq->parameter("name").toLocal8Bit());

    m_var = getSecretPath(paraPath + QDir::separator() + paraName);

}
