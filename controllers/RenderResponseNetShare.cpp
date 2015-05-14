#include "RenderResponseNetShare.h"
#include "AppDefine.h"

#include <QDir>

RenderResponseNetShare::RenderResponseNetShare(QVariantMap &map, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_renderType = RENDER_TYPE_UNKNOWN;
    m_pMap = &map;
}

RenderResponseNetShare::~RenderResponseNetShare() {
}

RENDER_TYPE RenderResponseNetShare::preRender() {

    if(!m_pMap)
        return RENDER_TYPE_UNKNOWN;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_MODULE_GET_INFO:
        generateModuleGetInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_ADS_INFO:
        generateGetAdsInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_SESSION:
        generateGetSession(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_ISO_SHARE:
        generateGetIsoShare(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_AFP_INFO:
        generateGetAfpInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_NFS_INFO:
        generateGetNfsInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_ISO_PERCENTAGE:
        generateIsoPrecentage(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_CLEAR_ISO_CREATE:
        generateClearIsoCreate();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_USER_LIST:
        generateUserList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GROUP_LIST:
        generateGroupList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_ALL_ISO_SHARE:
        generateGetAllIsoShare(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_OPEN_TREE:
        generateOpenTree(str);
        m_renderType = RENDER_TYPE_HTML;
        break;
    case CMD_OPEN_NEW_FOLDER:
        generateOpenNewFolder(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_ADD_SESSION:
        generateAddSession();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_SET_NFS_SHARE:
        generateSetNfsShare();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_GET_MODIFY_SESSION:
        generateGetModifySession(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_MODIFY_SESSION:
        generateModifySession();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_MODIFY_NFS_SHARE:
        generateModifyNfsShare();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_WEBDAV_ACCOUNT_ADD:
        generateWebdavAccountAdd(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_DEL_SESSION:
        generateDeleteSession();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_WEBDAV_ACCOUNT_DEL:
        generateWebdavAccountDel(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_RESET_SESSION:
        generateResetSession(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_GET_SHARE_INFO:
        generateGetShareInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_FTP:
        generateGetFtp(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_WEBDAV_ACCOUNT_INFO:
        generateWebdavAccountInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

    return m_renderType;
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

    QString paraPage = m_pMap->value("page").toString();
    QString paraRp = m_pMap->value("rp").toString();
    QString paraQuery = m_pMap->value("query").toString();
    QString paraQType = m_pMap->value("qtype").toString();
    QString paraField = m_pMap->value("f_field").toString();
    QString paraUser = m_pMap->value("user").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QString cellContentCifs =
            "&lt;img src=&apos;../images/detail.png&apos; onclick=&apos;show_cifs_detail(&quot;%1&quot;);&apos;&gt;";
    QString cellContentFtp =
            "&lt;img src=&apos;../images/detail.png&apos; onclick=&apos;show_ftp_detail\
            (&quot;%1&quot;,&quot;#flex1&quot;);&apos;&gt;";
    // prefix "-"
    QString cellContentNfsPart1 =
            "&lt;img src=&apos;../images/detail.png&apos; onclick=&apos;show_nfs_detail\
            (&quot;%1&quot;,&quot;#flex1&quot;)&apos;&gt;";
    QString cellContentNfsPart2 =
            "&lt;input type=&quot;hidden&quot; \
            name=&quot;%1&quot; id=&quot;%1&quot; value=&quot;%2:%3&quot;&gt;";
    QString cellContentWebdav =
            "&lt;img src=&apos;../images/detail.png&apos; onclick=&apos;show_webdav_detail\
            (&quot;%1&quot;,&quot;#flex1&quot;)&apos;&gt;&lt;input type=&quot;hidden&quot; \
            name=&quot;%2&quot; id=&quot;%2&quot; value=&quot;%3:%4&quot;&gt;";

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
        cellElement3.appendChild(doc.createTextNode(cellContentCifs.arg("0")));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createTextNode(cellContentFtp.arg("0")));
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createTextNode(cellContentNfsPart1.arg("0") +
                                                    cellContentNfsPart2.arg("nfs_0").arg("*").arg("/mnt/USB/USB2_b1")));

        QDomElement cellElement6 = doc.createElement("cell");
        rowElement.appendChild(cellElement6);
        cellElement6.appendChild(doc.createTextNode(cellContentWebdav.arg("0")
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
    QString paraPage = m_pMap->value("page").toString();
    QString paraRp = m_pMap->value("rp").toString();
    QString paraQuery = m_pMap->value("query").toString();
    QString paraQType = m_pMap->value("qtype").toString();
    QString paraField = m_pMap->value("f_field").toString();
    QString paraUser = m_pMap->value("user").toString();
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

/* todo: need API */
void RenderResponseNetShare::generateGetAfpInfo(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("afp_info");
    doc.appendChild(root);

    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode("1"));
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
    QString paraFileName = m_pMap->value("fileName").toString();
    QString paraUpIsoRootPath = m_pMap->value("upIsoRootPath").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    str = "-1";
}

/* todo: need API */
void RenderResponseNetShare::generateClearIsoCreate() {
    QString paraFileName = m_pMap->value("fileName").toString();
    QString paraUpIsoRootPath = m_pMap->value("upIsoRootPath").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseNetShare::generateUserList(QDomDocument &doc) {
    QString paraPage = m_pMap->value("page").toString();
    QString paraRp = m_pMap->value("rp").toString();
    QString paraQuery = m_pMap->value("query").toString();
    QString paraQType = m_pMap->value("qtype").toString();
    QString paraField = m_pMap->value("f_field").toString();
    QString paraUser = m_pMap->value("user").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    QString cellContent("&lt;input type=&apos;checkbox&apos; name\
                        =&apos;C_%1&apos; value=&apos;%2&apos; rel=&apos;%3&apos;&gt;");

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
    QString paraPage = m_pMap->value("page").toString();
    QString paraRp = m_pMap->value("rp").toString();
    QString paraQuery = m_pMap->value("query").toString();
    QString paraQType = m_pMap->value("qtype").toString();
    QString paraField = m_pMap->value("f_field").toString();
    QString paraUser = m_pMap->value("user").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    QString cellContent("&lt;input type=&apos;checkbox&apos; name\
                        =&apos;C_%1&apos; value=&apos;%2&apos; rel=&apos;%3&apos;&gt;");

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
    QString paraDir = m_pMap->value("dir").toString();
    QString paraShowFile = m_pMap->value("show_file").toString();
    QString paraChkFlag = m_pMap->value("chk_flag").toString();
    QString paraFileType = m_pMap->value("file_type").toString();
    QString paraFuncId = m_pMap->value("function_id").toString();
    QString paraFilterFile = m_pMap->value("filter_file").toString();
    QString paraRootPath = m_pMap->value("root_path").toString();

    QString cssUlClass = "<ul class=\"jqueryFileTree\" style=\"display: none;\">\n\
                            %1\
                         </ul>";
    QString cssLiClass = "<li class=\"directory collapsed%1\">\n\
                         %2%3\
                         </li>\n";
    QString checkboxLine = "        <input type='checkbox' name='folder_name' value=\"%1\"  src=\"%2\" rel=\"%2\">\n";
    QString hrefLine = "        <a href=\"#\" rel=\"%1\">%2</a>\n";

    QDir dir(paraDir.replace("%2F", "/"));
    QDir::Filters filters = QDir::NoDotAndDotDot | QDir::Dirs;
    if(paraShowFile.compare("1") == 0)
        filters |= QDir::AllEntries;
    QFileInfoList fileList= dir.entryInfoList(filters);

    QString content;
    for(QFileInfo e : fileList) {
        QString fileName = e.fileName();
        if(e.absoluteFilePath().compare("/mnt/HD/HD_a2") == 0)
            fileName = "Volume_1";
        if(e.absoluteFilePath().compare("/mnt/HD/HD_b2") == 0)
            fileName = "Volume_2";
        QString line1 = (paraChkFlag.compare("1") == 0) ? checkboxLine.arg(e.absoluteFilePath()).arg(fileName) : QString::null;
        QString line2 = hrefLine.arg(e.absoluteFilePath()).arg(fileName);
        content += cssLiClass.arg("").arg(line1).arg(line2);
    }

    /* If it was not rooted path, we can add folder. */
    if(dir.absolutePath().compare("/mnt/HD") != 0) {
        QString line2 = hrefLine.arg(dir.absolutePath() + "/new/").arg("New");
        content += cssLiClass.arg(" add").arg("").arg(line2);
    }

    str = cssUlClass.arg(content);
}

void RenderResponseNetShare::generateOpenNewFolder(QDomDocument &doc) {
    QString paraDir = m_pMap->value("dir").toString();
    QString paraFileName = m_pMap->value("filename").toString();
    QString paraShowFile = m_pMap->value("show_file").toString();
    QString paraChkFlag = m_pMap->value("chk_flag").toString();
    //QString paraFileType = m_pMap->value("file_type").toString();
    QString paraFuncId = m_pMap->value("function_id").toString();
    QString paraFilterFile = m_pMap->value("filter_file").toString();
    QString paraRootPath = m_pMap->value("root_path").toString();

    QDir dir(paraDir.replace("%2F", "/"));
    QString ret = dir.mkdir(paraFileName) ? "ok" : "error";

    QDomElement root = doc.createElement("mkdir");
    doc.appendChild(root);

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(ret));
}

/* todo: need API */
void RenderResponseNetShare::generateAddSession() {
    QString paraPath = m_pMap->value("path").toString();
    QString paraName = m_pMap->value("name").toString();
    QString paraOplocks = m_pMap->value("oplocks").toString();
    QString paraMapArchive = m_pMap->value("map_archive").toString();
    QString paraComment = m_pMap->value("comment").toString();
    QString paraFtp = m_pMap->value("ftp").toString();
    QString paraReadList = m_pMap->value("read_list").toString();
    QString paraWriteList = m_pMap->value("write_list").toString();
    QString paraDeclineList = m_pMap->value("decline_list").toString();
    QString paraRecycle = m_pMap->value("recycle").toString();
    QString paraFtpAnonymous = m_pMap->value("ftp_anonymous").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

}

/* todo: need API */
void RenderResponseNetShare::generateSetNfsShare() {
    QString paraHost = m_pMap->value("host").toString();
    QString paraPath = m_pMap->value("path").toString();
    QString paraRw = m_pMap->value("rw").toString();
    QString paraRootsquash = m_pMap->value("rootsquash").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

}

/* todo: need API */
void RenderResponseNetShare::generateGetModifySession(QDomDocument &doc) {
    QString paraName = m_pMap->value("name").toString();

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
    QString paraPath = m_pMap->value("path").toString();
    QString paraName = m_pMap->value("name").toString();
    QString paraOplocks = m_pMap->value("oplocks").toString();
    QString paraMapArchive = m_pMap->value("map_archive").toString();
    QString paraComment = m_pMap->value("comment").toString();
    QString paraFtp = m_pMap->value("ftp").toString();
    QString paraReadList = m_pMap->value("read_list").toString();
    QString paraWriteList = m_pMap->value("write_list").toString();
    QString paraDeclineList = m_pMap->value("decline_list").toString();
    QString paraRecycle = m_pMap->value("recycle").toString();
    QString paraFtpAnonymous = m_pMap->value("ftp_anonymous").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

}

/* todo: need API */
void RenderResponseNetShare::generateModifyNfsShare() {
    QString paraOldHost = m_pMap->value("old_host").toString();
    QString paraHost = m_pMap->value("host").toString();
    QString paraPath = m_pMap->value("path").toString();
    QString paraRw = m_pMap->value("rw").toString();
    QString paraRootSquash = m_pMap->value("rootsquash").toString();
    QString paraNfsFlag = m_pMap->value("nfs_flag").toString();
    QString paraNfs = m_pMap->value("nfs").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

}

/* todo: need API */
void RenderResponseNetShare::generateWebdavAccountAdd(QDomDocument &doc) {
    QString paraShareName = m_pMap->value("f_share_name").toString();
    QString paraPath = m_pMap->value("f_path").toString();
    QString paraRw = m_pMap->value("f_rw").toString();
    QString paraUser = m_pMap->value("f_user").toString();
    QString paraWebdav = m_pMap->value("webdav").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
}

/* todo: need API */
void RenderResponseNetShare::generateDeleteSession() {
    QString paraName = m_pMap->value("name").toString();
    QString paraPath = m_pMap->value("path").toString();
    QString paraHost = m_pMap->value("host").toString();
    QString paraSmbPath = m_pMap->value("smb_path").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseNetShare::generateWebdavAccountDel(QDomDocument &doc) {
    QString paraFlag = m_pMap->value("f_flag").toString();
    QString paraPath = m_pMap->value("f_path").toString();

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
    QString paraName = m_pMap->value("name").toString();

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
    writeListElement.appendChild(doc.createTextNode("&lt;b&gt;aaaa&lt;/b&gt;&lt;br&gt;jerry"));
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
    QString paraName = m_pMap->value("name").toString();

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
    writeListElement.appendChild(doc.createTextNode("&lt;b&gt;aaaa&lt;/b&gt;&lt;br&gt;jerry"));
    QDomElement denyAccessListElement = doc.createElement("deny_access_list");
    root.appendChild(denyAccessListElement);
    denyAccessListElement.appendChild(doc.createTextNode(" - "));
}

/* todo: need API */
void RenderResponseNetShare::generateWebdavAccountInfo(QDomDocument &doc) {
    QString paraPath = m_pMap->value("f_path").toString();

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

