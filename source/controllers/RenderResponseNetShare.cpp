#include "RenderResponseNetShare.h"

#include <QDir>

RenderResponseNetShare::RenderResponseNetShare(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseNetShare::~RenderResponseNetShare() {
}

void RenderResponseNetShare::preRender() {

    if(!m_pReq)
        return;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_MODULE_GET_INFO:
        generateModuleGetInfo(doc);
        break;
    case CMD_GET_ADS_INFO:
        generateGetAdsInfo(doc);
        break;
    case CMD_GET_SESSION:
        generateGetSession(doc);
        break;
    case CMD_GET_ISO_SHARE:
        generateGetIsoShare(doc);
        break;
    case CMD_GET_AFP_INFO:
        generateGetAfpInfo(doc);
        break;
    case CMD_GET_NFS_INFO:
        generateGetNfsInfo(doc);
        break;
    case CMD_ISO_PERCENTAGE:
        generateIsoPrecentage(str);
        break;
    case CMD_CLEAR_ISO_CREATE:
        generateClearIsoCreate();
        break;
    case CMD_USER_LIST:
        generateUserList(doc);
        break;
    case CMD_GROUP_LIST:
        generateGroupList(doc);
        break;
    case CMD_GET_ALL_ISO_SHARE:
        generateGetAllIsoShare(doc);
        break;
    case CMD_OPEN_TREE:
        generateOpenTree(str);
        break;
    case CMD_OPEN_NEW_FOLDER:
        generateOpenNewFolder(doc);
        break;
    case CMD_ADD_SESSION:
        generateAddSession();
        break;
    case CMD_SET_NFS_SHARE:
        generateSetNfsShare();
        break;
    case CMD_GET_MODIFY_SESSION:
        generateGetModifySession(doc);
        break;
    case CMD_MODIFY_SESSION:
        generateModifySession();
        break;
    case CMD_MODIFY_NFS_SHARE:
        generateModifyNfsShare();
        break;
    case CMD_WEBDAV_ACCOUNT_ADD:
        generateWebdavAccountAdd(doc);
        break;
    case CMD_DEL_SESSION:
        generateDeleteSession();
        break;
    case CMD_WEBDAV_ACCOUNT_DEL:
        generateWebdavAccountDel(doc);
        break;
    case CMD_RESET_SESSION:
        generateResetSession(str);
        break;
    case CMD_GET_SHARE_INFO:
        generateGetShareInfo(doc);
        break;
    case CMD_GET_FTP:
        generateGetFtp(doc);
        break;
    case CMD_WEBDAV_ACCOUNT_INFO:
        generateWebdavAccountInfo(doc);
        break;

    case CMD_SET_ISO_SHARE:
        generateSetIsoShare(doc);
        break;
    case CMD_GET_ISO_SHARE_DETAIL:
        generateGetIsoShareDetail(doc);
        break;
    case CMD_GET_NFS_SHARE_INFO:
        generateGetNfsShareInfo(doc);
        break;
    case CMD_GET_MODIFY_ISO_INFO:
        generateGetModifyIsoInfo(doc);
        break;
    case CMD_MODIFY_ISO_SHARE:
        generateModifyIsoShare();
        break;
    case CMD_DEL_ISO_SHARE:
        generateDelIsoShare(doc);
        break;
    case CMD_CHK_IMG_NAME:
        generateChkImgName(str);
        break;
    case CMD_CHK_HD_SIZE:
        generateChkHDSize(str);
        break;
    case CMD_ISO_CREATE_PATH:
        generateIsoCreatePath();
        break;
    case CMD_ISO_SIZE:
        generateIsoSize(str);
        break;
    case CMD_ISO_CREATE_IMAGE:
        generateIsoCreateImage();
        break;

    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

}

/* todo: need API */
void RenderResponseNetShare::generateModuleGetInfo(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);


    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement apkgElement = doc.createElement("apkg");
    root.appendChild(apkgElement);

    //for(int i=0; i < apiOut.size(); i++) {
//        if(apiOut.at(i).isEmpty())
//            continue;
//        if(apiOut.at(i).split(",").size() < 2)
//            continue;

        QDomElement itemElement = doc.createElement("Item");
        apkgElement.appendChild(itemElement);
        QDomElement nameElement = doc.createElement("Name");
        itemElement.appendChild(nameElement);
        nameElement.appendChild(doc.createTextNode("Transmission"));
        QDomElement showNameElement = doc.createElement("ShowName");
        itemElement.appendChild(showNameElement);
        showNameElement.appendChild(doc.createTextNode("Transmission"));

        QDomElement enableElement = doc.createElement("Enable");
        itemElement.appendChild(enableElement);
        enableElement.appendChild(doc.createTextNode("1"));
        QDomElement urlElement = doc.createElement("URL");
        itemElement.appendChild(urlElement);
        urlElement.appendChild(doc.createTextNode("index.html"));
        QDomElement userElement = doc.createElement("User");
        itemElement.appendChild(userElement);
        userElement.appendChild(doc.createTextNode("0"));

        QDomElement centerElement = doc.createElement("Center");
        itemElement.appendChild(centerElement);
        centerElement.appendChild(doc.createTextNode("0"));
        QDomElement userControlElement = doc.createElement("user_control");
        itemElement.appendChild(userControlElement);
        userControlElement.appendChild(doc.createTextNode("0"));

        QDomElement versionElement = doc.createElement("version");
        itemElement.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode("1.00"));

        QDomElement dateElement = doc.createElement("date");
        itemElement.appendChild(dateElement);
        dateElement.appendChild(doc.createTextNode("20150515"));

        QDomElement pathElement = doc.createElement("path");
        itemElement.appendChild(pathElement);
        pathElement.appendChild(doc.createTextNode("/mnt/HD/HD_a2/Nas_Prog/Transmission"));
    //}

        QDomElement p2pEnableElement = doc.createElement("p2p_enable");
        root.appendChild(p2pEnableElement);
        p2pEnableElement.appendChild(doc.createTextNode("0"));

}

/* todo: need API */
void RenderResponseNetShare::generateGetAdsInfo(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("ads");
    doc.appendChild(root);

    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode("0"));
    QDomElement workgroupElement = doc.createElement("workgroup");
    root.appendChild(workgroupElement);
    //workgroupElement.appendChild(doc.createTextNode(""));
    QDomElement nameElement = doc.createElement("u_name");
    root.appendChild(nameElement);
    QDomElement upwdElement = doc.createElement("u_pwd");
    root.appendChild(upwdElement);
    QDomElement realmElement = doc.createElement("realm");
    root.appendChild(realmElement);
    QDomElement spwdElement = doc.createElement("s_pwd");
    root.appendChild(spwdElement);

    QDomElement dns1Element = doc.createElement("dns1");
    root.appendChild(dns1Element);
    dns1Element.appendChild(doc.createTextNode("192.168.100.5"));
    QDomElement dns2Element = doc.createElement("dns2");
    root.appendChild(dns2Element);
    dns2Element.appendChild(doc.createTextNode("8.8.8.8"));

}

/* todo: need API */
void RenderResponseNetShare::generateGetSession(QDomDocument &doc) {

    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QString cellContentCifs =
            "<img src='../images/detail.png' onclick='show_cifs_detail(\"%1\");'>";
    QString cellContentFtp =
            "<img src='../images/detail.png' onclick='show_ftp_detail(\"%1\",\"#flex1\");'>";
    // prefix "-"
    QString cellContentNfsPart1 =
            "<img src='../images/detail.png' onclick='show_nfs_detail(\"%1\",\"#flex1\")'>";
    QString cellContentNfsPart2 =
            "<input type='hidden' name=\"%1\" id=\"%1\" value=\"%2:%3\">";
    QString cellContentWebdav =
            "<img src='../images/detail.png' onclick='show_webdav_detail(\"%1\",\"#flex1\")'>"
            "<input type=\"hidden\" name=\"%2\" id=\"%2\" value=\"%3:%4\">";

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    //for(int i=0; i < apiOut.size(); i++) {
//        if(apiOut.at(i).isEmpty())
//            continue;
//        if(apiOut.at(i).split(",").size() < 2)
//            continue;

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode("Volume_1"));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode("Volume_1"));

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createCDATASection(cellContentCifs.arg("0")));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createCDATASection(cellContentFtp.arg("0")));
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createCDATASection(cellContentNfsPart1.arg("0") +
                                                    cellContentNfsPart2.arg("nfs_0").arg("*").arg("/mnt/USB/USB2_b1")));

        QDomElement cellElement6 = doc.createElement("cell");
        rowElement.appendChild(cellElement6);
        cellElement6.appendChild(doc.createCDATASection(cellContentWebdav.arg("0")
                                                    .arg("webdav_0").arg("/mnt/HD/HD_a2").arg("Volume_1")));
        QDomElement cellElement7 = doc.createElement("cell");
        rowElement.appendChild(cellElement7);
        cellElement7.appendChild(doc.createTextNode("-"));

        rowElement.setAttribute("id", "1");
    //}

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("3"));
}

/* todo: need API */
void RenderResponseNetShare::generateGetIsoShare(QDomDocument &doc) {
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("0"));

}

void RenderResponseNetShare::generateGetAfpInfo(QDomDocument &doc) {
    QMap<QString, QString> afpInfo = getNasCfg("afp");

    QDomElement root = doc.createElement("afp_info");
    doc.appendChild(root);

    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode(afpInfo.value("enable")));
}

/* todo: need API */
void RenderResponseNetShare::generateGetNfsInfo(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("nfs_info");
    doc.appendChild(root);

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("0"));
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode("1"));
}

/* todo: need API */
void RenderResponseNetShare::generateIsoPrecentage(QString &str) {
    QString paraFileName = m_pReq->allParameters().value("fileName").toString();
    QString paraUpIsoRootPath = m_pReq->allParameters().value("upIsoRootPath").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    str = "-1";
}

/* todo: need API */
void RenderResponseNetShare::generateClearIsoCreate() {
    QString paraFileName = m_pReq->allParameters().value("fileName").toString();
    QString paraUpIsoRootPath = m_pReq->allParameters().value("upIsoRootPath").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseNetShare::generateUserList(QDomDocument &doc) {
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    QString cellContent("<input type='checkbox' name='C_%1' value='%2&' rel='%3'>");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);
//    if(!apiOut.isEmpty()) {
//        for(int i=0; i < apiOut.size(); i++) {
//            if(apiOut.at(i).isEmpty())
//                continue;
            QDomElement rowElement = doc.createElement("row");
            root.appendChild(rowElement);
            rowElement.setAttribute("id", QString::number(1));

            QDomElement cellElement1 = doc.createElement("cell");
            rowElement.appendChild(cellElement1);
            //cellElement1.appendChild(doc.createTextNode(apiOut.at(i)));
            QDomElement cellElement2 = doc.createElement("cell");
            rowElement.appendChild(cellElement2);
            //cellElement2.appendChild(doc.createTextNode(cellContent.arg(QString::number(i)).arg("r").arg(apiOut.at(i))));
            QDomElement cellElement3 = doc.createElement("cell");
            rowElement.appendChild(cellElement3);
            //cellElement3.appendChild(doc.createTextNode(cellContent.arg(QString::number(i)).arg("w").arg(apiOut.at(i))));
            QDomElement cellElement4 = doc.createElement("cell");
            rowElement.appendChild(cellElement4);
            //cellElement4.appendChild(doc.createTextNode(cellContent.arg(QString::number(i)).arg("d").arg(apiOut.at(i))));
//        }
//    }

            QDomElement pageElement = doc.createElement("page");
            root.appendChild(pageElement);
            pageElement.appendChild(doc.createTextNode("1"));
            QDomElement totalElement = doc.createElement("total");
            root.appendChild(totalElement);
            totalElement.appendChild(doc.createTextNode("2"));

}

/* todo: need API */
void RenderResponseNetShare::generateGroupList(QDomDocument &doc) {
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    QString cellContent("<input type='checkbox' name='C_%1' value='%2' rel='%3'>");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);
//    if(!apiOut.isEmpty()) {
//        for(int i=0; i < apiOut.size(); i++) {
//            if(apiOut.at(i).isEmpty())
//                continue;
            QDomElement rowElement = doc.createElement("row");
            root.appendChild(rowElement);
            rowElement.setAttribute("id", QString::number(1));

            QDomElement cellElement1 = doc.createElement("cell");
            rowElement.appendChild(cellElement1);
            //cellElement1.appendChild(doc.createTextNode(apiOut.at(i)));
            QDomElement cellElement2 = doc.createElement("cell");
            rowElement.appendChild(cellElement2);
            //cellElement2.appendChild(doc.createTextNode(cellContent.arg(QString::number(i)).arg("r").arg(apiOut.at(i))));
            QDomElement cellElement3 = doc.createElement("cell");
            rowElement.appendChild(cellElement3);
            //cellElement3.appendChild(doc.createTextNode(cellContent.arg(QString::number(i)).arg("w").arg(apiOut.at(i))));
            QDomElement cellElement4 = doc.createElement("cell");
            rowElement.appendChild(cellElement4);
            //cellElement4.appendChild(doc.createTextNode(cellContent.arg(QString::number(i)).arg("d").arg(apiOut.at(i))));
//        }
//    }

            QDomElement pageElement = doc.createElement("page");
            root.appendChild(pageElement);
            pageElement.appendChild(doc.createTextNode("1"));
            QDomElement totalElement = doc.createElement("total");
            root.appendChild(totalElement);
            totalElement.appendChild(doc.createTextNode("2"));

}

/* todo: need API */
void RenderResponseNetShare::generateGetAllIsoShare(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("iso_mount");
    doc.appendChild(root);

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("0"));
}

void RenderResponseNetShare::generateOpenTree(QString &str) {
    QString paraDir = QUrl::fromPercentEncoding(m_pReq->parameter("dir").toLocal8Bit());
    QString paraShowFile = m_pReq->parameter("show_file");
    QString paraChkFlag = m_pReq->parameter("chk_flag");
    QString paraFileType = m_pReq->parameter("file_type");
//    QString paraFuncId = m_pReq->parameter("function_id");
//    QString paraFilterFile = m_pReq->parameter("filter_file");
//    QString paraRootPath = m_pReq->parameter("root_path");

    QString cssUlClass = "<ul class=\"jqueryFileTree\" style=\"display: none;\">\n"
                            "%1"
                         "</ul>";
    QString cssLiClass =        "    <li class=\"directory collapsed %1\">\n"
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

    for(QFileInfo e : fileList) {
        if(!paraFileType.isEmpty())
            if(!e.isDir() && e.suffix() != paraFileType)
                fileList.removeOne(e);
        if(        e.fileName() == "lost+found"
                || e.fileName() == "Nas_Prog"
                || e.fileName() == "aMule"
                || e.fileName() == "ShareCenter_Sync")
            fileList.removeOne(e);
    }

    QString content;
    for(QFileInfo e : fileList) {
        QString fileName = e.fileName();
        if(e.absoluteFilePath().compare("/mnt/HD/HD_a2") == 0)
            fileName = "Volume_1";
        if(e.absoluteFilePath().compare("/mnt/HD/HD_b2") == 0)
            fileName = "Volume_2";

        QString line2 = hrefLine.arg(e.absoluteFilePath() + QDir::separator()).arg(fileName);
        if(e.isDir()) {
            QString line1 = (paraChkFlag.compare("1") == 0) ?
                        checkboxLine.arg(e.absoluteFilePath()).arg(checkboxSrc.arg(fileName)).arg(fileName) : QString::null;
            content += cssLiClass.arg("").arg(line1).arg(line2);
        }
        else {
            QString fileVolumePath = e.absoluteFilePath();
            fileVolumePath.replace("/mnt/HD/HD_a2", "Volume_1");
            fileVolumePath.replace( "/mnt/HD/HD_b2", "Volume_2");

            QString line1 = (paraChkFlag.compare("1") == 0) ?
                        checkboxLine.arg(e.absoluteFilePath()).arg(QString::null).arg(fileVolumePath) : QString::null;
            content += cssLiClassWithID.arg(line1).arg(line2);
        }
    }

    /* If it was not rooted path, we can add folder. */
    if(dir.absolutePath().compare("/mnt/HD") != 0) {
        QString line2 = hrefLine.arg(dir.absolutePath() + "/new/").arg("New");
        content += cssLiClass.arg("add").arg("").arg(line2);
    }

    str = cssUlClass.arg(content);
}

void RenderResponseNetShare::generateOpenNewFolder(QDomDocument &doc) {
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
    if(bMkdir)
        QFile(paraDir).setPermissions((QFileDevice::Permission)0x0775);
    QString ret = bMkdir ? "ok" : "error";

    QDomElement root = doc.createElement("mkdir");
    doc.appendChild(root);

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(ret));
}

/* todo: need API */
void RenderResponseNetShare::generateAddSession() {
    QString paraPath = m_pReq->allParameters().value("path").toString();
    QString paraName = m_pReq->allParameters().value("name").toString();
    QString paraOplocks = m_pReq->allParameters().value("oplocks").toString();
    QString paraMapArchive = m_pReq->allParameters().value("map_archive").toString();
    QString paraComment = m_pReq->allParameters().value("comment").toString();
    QString paraFtp = m_pReq->allParameters().value("ftp").toString();
    QString paraReadList = m_pReq->allParameters().value("read_list").toString();
    QString paraWriteList = m_pReq->allParameters().value("write_list").toString();
    QString paraDeclineList = m_pReq->allParameters().value("decline_list").toString();
    QString paraRecycle = m_pReq->allParameters().value("recycle").toString();
    QString paraFtpAnonymous = m_pReq->allParameters().value("ftp_anonymous").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

}

/* todo: need API */
void RenderResponseNetShare::generateSetNfsShare() {
    QString paraHost = m_pReq->allParameters().value("host").toString();
    QString paraPath = m_pReq->allParameters().value("path").toString();
    QString paraRw = m_pReq->allParameters().value("rw").toString();
    QString paraRootsquash = m_pReq->allParameters().value("rootsquash").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

}

/* todo: need API */
void RenderResponseNetShare::generateGetModifySession(QDomDocument &doc) {
    QString paraName = m_pReq->allParameters().value("name").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("session");
    doc.appendChild(root);

    QDomElement nameElement = doc.createElement("name");
    root.appendChild(nameElement);
    nameElement.appendChild(doc.createTextNode("111222555"));

    QDomElement pathElement = doc.createElement("path");
    root.appendChild(pathElement);
    pathElement.appendChild(doc.createTextNode("/mnt/HD/HD_a2/111222555"));

    QDomElement oplocksElement = doc.createElement("oplocks");
    root.appendChild(oplocksElement);
    oplocksElement.appendChild(doc.createTextNode("no"));

    QDomElement mapArchiveElement = doc.createElement("map_archive");
    root.appendChild(mapArchiveElement);
    mapArchiveElement.appendChild(doc.createTextNode("yes"));

    QDomElement commentElement = doc.createElement("comment");
    root.appendChild(commentElement);
    commentElement.appendChild(doc.createTextNode("ffff"));

    QDomElement readListElement = doc.createElement("read_list");
    root.appendChild(readListElement);
    readListElement.appendChild(doc.createTextNode("ffff"));

    QDomElement writeListElement = doc.createElement("write_list");
    root.appendChild(writeListElement);
    writeListElement.appendChild(doc.createTextNode("#jerry#,#test#"));

    QDomElement invalidUsersElement = doc.createElement("invalid_users");
    root.appendChild(invalidUsersElement);
    invalidUsersElement.appendChild(doc.createTextNode("#nobody#"));



    QDomElement recycleElement = doc.createElement("recycle");
    root.appendChild(recycleElement);
    recycleElement.appendChild(doc.createTextNode("0"));

    QDomElement recycleTreeElement = doc.createElement("recycle_tree");
    root.appendChild(recycleTreeElement);
    recycleTreeElement.appendChild(doc.createTextNode("1"));

    QDomElement ftpElement = doc.createElement("ftp");
    root.appendChild(ftpElement);
    ftpElement.appendChild(doc.createTextNode("1"));

    QDomElement ftpAnonymousElement = doc.createElement("ftp_anonymous");
    root.appendChild(ftpAnonymousElement);
    ftpAnonymousElement.appendChild(doc.createTextNode("n"));

    QDomElement nfsElement = doc.createElement("nfs");
    root.appendChild(nfsElement);
    QDomElement statusElement = doc.createElement("status");
    nfsElement.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode("1"));
    QDomElement realPathElement = doc.createElement("real_path");
    nfsElement.appendChild(realPathElement);
    realPathElement.appendChild(doc.createTextNode("/mnt/HD/HD_a2/111222555"));
    QDomElement rootSquashElement = doc.createElement("root_squash");
    nfsElement.appendChild(rootSquashElement);
    rootSquashElement.appendChild(doc.createTextNode("No"));
    QDomElement writeElement = doc.createElement("write");
    nfsElement.appendChild(writeElement);
    writeElement.appendChild(doc.createTextNode("No"));
    QDomElement hostElement = doc.createElement("host");
    nfsElement.appendChild(hostElement);
    hostElement.appendChild(doc.createTextNode("gggg"));

    QDomElement webdavElement = doc.createElement("webdav");
    root.appendChild(webdavElement);
    webdavElement.appendChild(doc.createTextNode("1"));
    QDomElement webdavRwElement = doc.createElement("webdav_rw");
    root.appendChild(webdavRwElement);
    webdavRwElement.appendChild(doc.createTextNode("1"));
    QDomElement webdavUserElement = doc.createElement("webdav_user");
    root.appendChild(webdavUserElement);
    webdavUserElement.appendChild(doc.createTextNode("#jerry#,#test#"));
    QDomElement mycloudElement = doc.createElement("mycloud");
    root.appendChild(mycloudElement);
    mycloudElement.appendChild(doc.createTextNode("0"));
}


/* todo: need API */
void RenderResponseNetShare::generateModifySession() {
    QString paraPath = m_pReq->allParameters().value("path").toString();
    QString paraName = m_pReq->allParameters().value("name").toString();
    QString paraOplocks = m_pReq->allParameters().value("oplocks").toString();
    QString paraMapArchive = m_pReq->allParameters().value("map_archive").toString();
    QString paraComment = m_pReq->allParameters().value("comment").toString();
    QString paraFtp = m_pReq->allParameters().value("ftp").toString();
    QString paraReadList = m_pReq->allParameters().value("read_list").toString();
    QString paraWriteList = m_pReq->allParameters().value("write_list").toString();
    QString paraDeclineList = m_pReq->allParameters().value("decline_list").toString();
    QString paraRecycle = m_pReq->allParameters().value("recycle").toString();
    QString paraFtpAnonymous = m_pReq->allParameters().value("ftp_anonymous").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

}

/* todo: need API */
void RenderResponseNetShare::generateModifyNfsShare() {
    QString paraOldHost = m_pReq->allParameters().value("old_host").toString();
    QString paraHost = m_pReq->allParameters().value("host").toString();
    QString paraPath = m_pReq->allParameters().value("path").toString();
    QString paraRw = m_pReq->allParameters().value("rw").toString();
    QString paraRootSquash = m_pReq->allParameters().value("rootsquash").toString();
    QString paraNfsFlag = m_pReq->allParameters().value("nfs_flag").toString();
    QString paraNfs = m_pReq->allParameters().value("nfs").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

}

/* todo: need API */
void RenderResponseNetShare::generateWebdavAccountAdd(QDomDocument &doc) {
    QString paraShareName = m_pReq->allParameters().value("f_share_name").toString();
    QString paraPath = m_pReq->allParameters().value("f_path").toString();
    QString paraRw = m_pReq->allParameters().value("f_rw").toString();
    QString paraUser = m_pReq->allParameters().value("f_user").toString();
    QString paraWebdav = m_pReq->allParameters().value("webdav").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
}

/* todo: need API */
void RenderResponseNetShare::generateDeleteSession() {
    QString paraName = m_pReq->allParameters().value("name").toString();
    QString paraPath = m_pReq->allParameters().value("path").toString();
    QString paraHost = m_pReq->allParameters().value("host").toString();
    QString paraSmbPath = m_pReq->allParameters().value("smb_path").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseNetShare::generateWebdavAccountDel(QDomDocument &doc) {
    QString paraFlag = m_pReq->allParameters().value("f_flag").toString();
    QString paraPath = m_pReq->allParameters().value("f_path").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
}

/* todo: need API */
void RenderResponseNetShare::generateResetSession(QString &str) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    str = "ok";
}

/* todo: need API */
void RenderResponseNetShare::generateGetShareInfo(QDomDocument &doc) {
    QString paraName = m_pReq->allParameters().value("name").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("session");
    doc.appendChild(root);

    QDomElement nameElement = doc.createElement("name");
    root.appendChild(nameElement);
    nameElement.appendChild(doc.createTextNode("Volume_1"));
    QDomElement pathElement = doc.createElement("path");
    root.appendChild(pathElement);
    pathElement.appendChild(doc.createTextNode("Volume_1"));
    QDomElement oplocksElement = doc.createElement("oplocks");
    root.appendChild(oplocksElement);
    oplocksElement.appendChild(doc.createTextNode("no"));
    QDomElement mapArchiveElement = doc.createElement("map_archive");
    root.appendChild(mapArchiveElement);
    mapArchiveElement.appendChild(doc.createTextNode("yes"));
    QDomElement commentElement = doc.createElement("comment");
    root.appendChild(commentElement);
    commentElement.appendChild(doc.createTextNode("test"));
    QDomElement readListElement = doc.createElement("read_list");
    root.appendChild(readListElement);
    readListElement.appendChild(doc.createTextNode("test"));
    QDomElement writeListElement = doc.createElement("write_list");
    root.appendChild(writeListElement);
    writeListElement.appendChild(doc.createTextNode("<b>aaaa</b><br>jerry"));
    QDomElement invalidUsersElement = doc.createElement("invalid_users");
    root.appendChild(invalidUsersElement);
    invalidUsersElement.appendChild(doc.createTextNode(" - "));
    QDomElement recycleElement = doc.createElement("recycle");
    root.appendChild(recycleElement);
    recycleElement.appendChild(doc.createTextNode("1"));
    QDomElement recycleTreeElement = doc.createElement("recycle_tree");
    root.appendChild(recycleTreeElement);
    recycleTreeElement.appendChild(doc.createTextNode("1"));
    QDomElement ftpElement = doc.createElement("ftp");
    root.appendChild(ftpElement);
    ftpElement.appendChild(doc.createTextNode("1"));

    QDomElement nfsElement = doc.createElement("nfs");
    root.appendChild(nfsElement);
    QDomElement statusElement = doc.createElement("status");
    nfsElement.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode("1"));
    QDomElement realPathElement = doc.createElement("real_path");
    nfsElement.appendChild(realPathElement);
    realPathElement.appendChild(doc.createTextNode("/mnt/HD/HD_a2"));
    QDomElement rootSquashElement = doc.createElement("root_squash");
    nfsElement.appendChild(rootSquashElement);
    rootSquashElement.appendChild(doc.createTextNode("Yes"));
    QDomElement writeElement = doc.createElement("write");
    nfsElement.appendChild(writeElement);
    writeElement.appendChild(doc.createTextNode("Yes"));
    QDomElement hostElement = doc.createElement("host");
    nfsElement.appendChild(hostElement);
    hostElement.appendChild(doc.createTextNode("gg"));
}

/* todo: need API */
void RenderResponseNetShare::generateGetFtp(QDomDocument &doc) {
    QString paraName = m_pReq->allParameters().value("name").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("session");
    doc.appendChild(root);

    QDomElement nameElement = doc.createElement("name");
    root.appendChild(nameElement);
    nameElement.appendChild(doc.createTextNode("Volume_1"));
    QDomElement pathElement = doc.createElement("path");
    root.appendChild(pathElement);
    pathElement.appendChild(doc.createTextNode("Volume_1"));
    QDomElement anonymousElement = doc.createElement("anonymous");
    root.appendChild(anonymousElement);
    anonymousElement.appendChild(doc.createTextNode("n"));

    QDomElement readListElement = doc.createElement("read_list");
    root.appendChild(readListElement);
    readListElement.appendChild(doc.createTextNode("test"));
    QDomElement writeListElement = doc.createElement("write_list");
    root.appendChild(writeListElement);
    writeListElement.appendChild(doc.createTextNode("<b>aaaa</b><br>jerry"));
    QDomElement denyAccessListElement = doc.createElement("deny_access_list");
    root.appendChild(denyAccessListElement);
    denyAccessListElement.appendChild(doc.createTextNode(" - "));
}

/* todo: need API */
void RenderResponseNetShare::generateWebdavAccountInfo(QDomDocument &doc) {
    QString paraPath = m_pReq->allParameters().value("f_path").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement webdavElement = doc.createElement("WebDAV");
    root.appendChild(webdavElement);
    QDomElement itemElement = doc.createElement("item");
    webdavElement.appendChild(itemElement);

    QDomElement sharedNameElement = doc.createElement("shared_name");
    itemElement.appendChild(sharedNameElement);
    sharedNameElement.appendChild(doc.createTextNode("Volume_1"));
    QDomElement pathElement = doc.createElement("path");
    itemElement.appendChild(pathElement);
    pathElement.appendChild(doc.createTextNode("/mnt/HD/HD_a2/"));
    QDomElement enableElement = doc.createElement("enable");
    itemElement.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode("1"));
    QDomElement rwElement = doc.createElement("RW");
    itemElement.appendChild(rwElement);
    rwElement.appendChild(doc.createTextNode("1"));
    QDomElement userElement = doc.createElement("user");
    itemElement.appendChild(userElement);
    userElement.appendChild(doc.createTextNode("#jerry#,#@aaaa#"));
}

/* todo: need API */
void RenderResponseNetShare::generateSetIsoShare(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("iso_info");
    doc.appendChild(root);

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode("1"));

}

/* todo: need API */
void RenderResponseNetShare::generateGetIsoShareDetail(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("iso_mount");
    doc.appendChild(root);

    QDomElement nameElement = doc.createElement("name");
    root.appendChild(nameElement);
    nameElement.appendChild(doc.createTextNode("uu"));
    QDomElement commentElement = doc.createElement("comment");
    root.appendChild(commentElement);
    commentElement.appendChild(doc.createTextNode(""));
    QDomElement pathElement = doc.createElement("path");
    root.appendChild(pathElement);
    pathElement.appendChild(doc.createTextNode("Volume_1/dddd.iso"));
    QDomElement readListElement = doc.createElement("read_list");
    root.appendChild(readListElement);
    readListElement.appendChild(doc.createTextNode("ALL"));
    QDomElement invalidUsersElement = doc.createElement("invalid_users");
    root.appendChild(invalidUsersElement);
    invalidUsersElement.appendChild(doc.createTextNode(" - "));
}

/* todo: need API */
void RenderResponseNetShare::generateGetNfsShareInfo(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("nfs_share");
    doc.appendChild(root);

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode("1"));

    QDomElement realPathElement = doc.createElement("real_path");
    root.appendChild(realPathElement);
    realPathElement.appendChild(doc.createTextNode("/mnt/isoMount/dddd"));

    QDomElement rootSquashElement = doc.createElement("root_squash");
    root.appendChild(rootSquashElement);
    rootSquashElement.appendChild(doc.createTextNode("No"));

    QDomElement writeElement = doc.createElement("write");
    root.appendChild(writeElement);
    writeElement.appendChild(doc.createTextNode("No"));

    QDomElement hostElement = doc.createElement("host");
    root.appendChild(hostElement);
    hostElement.appendChild(doc.createTextNode("123"));
}

/* todo: need API */
void RenderResponseNetShare::generateGetModifyIsoInfo(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("iso_mount");
    doc.appendChild(root);

    QDomElement commentElement = doc.createElement("comment");
    root.appendChild(commentElement);
    commentElement.appendChild(doc.createTextNode("ddd"));

    QDomElement pathElement = doc.createElement("path");
    root.appendChild(pathElement);
    pathElement.appendChild(doc.createTextNode("/mnt/HD/HD_a2/dddd.iso"));

    QDomElement readListElement = doc.createElement("read_list");
    root.appendChild(readListElement);
    readListElement.appendChild(doc.createTextNode("#jerry#"));

    QDomElement invalidUsersElement = doc.createElement("invalid_users");
    root.appendChild(invalidUsersElement);
    invalidUsersElement.appendChild(doc.createTextNode("#@staff#"));

    QDomElement ftpElement = doc.createElement("ftp");
    root.appendChild(ftpElement);
    ftpElement.appendChild(doc.createTextNode("1"));

    QDomElement nfsElement = doc.createElement("nfs");
    root.appendChild(nfsElement);
    nfsElement.appendChild(doc.createTextNode("1"));

    QDomElement nfsHostElement = doc.createElement("nfs_host");
    root.appendChild(nfsHostElement);
    nfsHostElement.appendChild(doc.createTextNode("acc"));

    QDomElement webdavElement = doc.createElement("webdav");
    root.appendChild(webdavElement);
    webdavElement.appendChild(doc.createTextNode("1"));
}

/* todo: need API */
void RenderResponseNetShare::generateModifyIsoShare() {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseNetShare::generateDelIsoShare(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("iso_mount");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode("0"));
}

/* todo: need API */
void RenderResponseNetShare::generateChkImgName(QString &str) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    str = "0";
}

/* todo: need API */
void RenderResponseNetShare::generateChkHDSize(QString &str) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    str = "ok";
}

/* todo: need API */
void RenderResponseNetShare::generateIsoCreatePath() {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseNetShare::generateIsoSize(QString &str) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    str = "874.0k";
}

/* todo: need API */
void RenderResponseNetShare::generateIsoCreateImage() {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}
