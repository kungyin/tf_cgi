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

    switch(m_cmd) {
    case CMD_MODULE_GET_INFO:
        generateModuleGetInfo();
        break;
    case CMD_GET_ADS_INFO:
        generateGetAdsInfo();
        break;
    case CMD_GET_SESSION:
        generateGetSession();
        break;
    case CMD_GET_ISO_SHARE:
        generateGetIsoShare();
        break;
    case CMD_GET_AFP_INFO:
        generateGetAfpInfo();
        break;
    case CMD_GET_NFS_INFO:
        generateGetNfsInfo();
        break;
    case CMD_ISO_PERCENTAGE:
        generateIsoPrecentage();
        break;
    case CMD_CLEAR_ISO_CREATE:
        generateClearIsoCreate();
        break;
    case CMD_USER_LIST:
        generateUserList();
        break;
    case CMD_GROUP_LIST:
        generateGroupList();
        break;
    case CMD_GET_ALL_ISO_SHARE:
        generateGetAllIsoShare();
        break;
    case CMD_ADD_SESSION:
        generateAddSession();
        break;
    case CMD_SET_NFS_SHARE:
        generateSetNfsShare();
        break;
    case CMD_GET_MODIFY_SESSION:
        generateGetModifySession();
        break;
    case CMD_MODIFY_SESSION:
        generateModifySession();
        break;
    case CMD_MODIFY_NFS_SHARE:
        generateModifyNfsShare();
        break;
    case CMD_WEBDAV_ACCOUNT_ADD:
        generateWebdavAccountAdd();
        break;
    case CMD_DEL_SESSION:
        generateDeleteSession();
        break;
    case CMD_WEBDAV_ACCOUNT_DEL:
        generateWebdavAccountDel();
        break;
    case CMD_RESET_SESSION:
        generateResetSession();
        break;
    case CMD_GET_SHARE_INFO:
        generateGetShareInfo();
        break;
    case CMD_GET_FTP:
        generateGetFtp();
        break;
    case CMD_WEBDAV_ACCOUNT_INFO:
        generateWebdavAccountInfo();
        break;

    case CMD_SET_ISO_SHARE:
        generateSetIsoShare();
        break;
    case CMD_GET_ISO_SHARE_DETAIL:
        generateGetIsoShareDetail();
        break;
    case CMD_GET_NFS_SHARE_INFO:
        generateGetNfsShareInfo();
        break;
    case CMD_GET_MODIFY_ISO_INFO:
        generateGetModifyIsoInfo();
        break;
    case CMD_MODIFY_ISO_SHARE:
        generateModifyIsoShare();
        break;
    case CMD_DEL_ISO_SHARE:
        generateDelIsoShare();
        break;
    case CMD_CHK_IMG_NAME:
        generateChkImgName();
        break;
    case CMD_CHK_HD_SIZE:
        generateChkHDSize();
        break;
    case CMD_ISO_CONFIG:
        generateIsoConfig();
        break;
    case CMD_ISO_CREATE_PATH:
        generateIsoCreatePath();
        break;
    case CMD_ISO_SIZE:
        generateIsoSize();
        break;
    case CMD_ISO_CREATE_IMAGE:
        generateIsoCreateImage();
        break;

    default:
        break;
    }

}

void RenderResponseNetShare::generateModuleGetInfo() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " Module_Get_Info");
    QStringList apkgList = apiOut;
    apkgList.removeFirst();

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QStringList itemTagNames(QStringList()
        << "Name" << "ShowName" << "Enable" << "URL" << "User" << "Center"
        << "user_control" << "version" << "date" << "path");

    QDomElement apkgElement = doc.createElement("apkg");
    root.appendChild(apkgElement);

    for(QString e : apkgList) {
        if( itemTagNames.size() == e.split(";").size() ) {
            QDomElement itemElement = doc.createElement("Item");
            apkgElement.appendChild(itemElement);
            for(int i = 0; i < e.split(";").size(); i++) {
                QDomElement element = doc.createElement(itemTagNames.value(i));
                itemElement.appendChild(element);
                element.appendChild(doc.createTextNode(e.split(";").value(i)));
            }
        }
        else {
            //assert(0);
            tError("RenderResponseNetShare::generateModuleGetInfo() :"
                   "itemTagNames size is not equal to apiOut size.");
        }
    }

    QDomElement p2pEnableElement = doc.createElement("p2p_enable");
    root.appendChild(p2pEnableElement);
    p2pEnableElement.appendChild(doc.createTextNode(apiOut.value(0).split(";").value(0)));

    m_var = doc.toString();

}

void RenderResponseNetShare::generateGetAdsInfo() {

    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_ads_info", true, ";");

    QDomElement root = doc.createElement("ads");
    doc.appendChild(root);

    QStringList adsTagNames(QStringList()
        << "enable" << "workgroup" << "u_name" << "u_pwd" << "realm" << "s_pwd" << "dns1" << "dns2");

    if( adsTagNames.size() == apiOut.size() ) {
        for(int i = 0; i < apiOut.size(); i++) {
            QDomElement element = doc.createElement(adsTagNames.value(i));
            root.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseNetShare::generateGetAdsInfo() :"
               "adsTagNames size is not equal to apiOut size.");
    }

    m_var = doc.toString();
}

void RenderResponseNetShare::generateGetSession() {

    QDomDocument doc;

    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_session_list");

    QString cellContentCifs =
            "<img src='../images/detail.png' onclick='show_cifs_detail(\"%1\");'>";
    QString cellContentFtp =
            "<img src='../images/detail.png' onclick='show_ftp_detail(\"%1\",\"#flex1\");'>";
    // todo: 2 sessions.
    QString cellContentNfs =
            "<img src='../images/detail.png' onclick='show_nfs_detail(\"%1\",\"#flex1\")'>"
            "<input type='hidden' name=\"nfs_%2\" id=\"nfs_%2\" value=\"%3\">";
    QString cellContentNfsEmpty =
            "-<input type='hidden' name=\"nfs_%1\" id=\"nfs_%1\" value=\"null:null\">";
    QString cellContentWebdav =
            "<img src='../images/detail.png' onclick='show_webdav_detail(\"%1\",\"#flex1\")'>"
            "<input type=\"hidden\" name=\"webdav_%2\" id=\"webdav_%2\" value=\"%3\">";

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    int i = 0;
    for(QString e : apiOut) {

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(e.split(";").value(0).isEmpty() ? "-" : e.split(";").value(0)));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode(e.split(";").value(1).isEmpty() ? "-" : e.split(";").value(1)));

        QString cell3 = e.split(";").value(2).isEmpty() ? "-" : cellContentCifs.arg(QString::number(i));
        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createCDATASection(cell3));

        QString cell4 = e.split(";").value(3) == "1" ? cellContentFtp.arg(QString::number(i)) : "-";
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createCDATASection(cell4));

        QString nfsInfo = e.split(";").value(4);
        QString cell5 = nfsInfo.isEmpty() ? cellContentNfsEmpty.arg(QString::number(i))
                                          : cellContentNfs.arg(QString::number(i), QString::number(i), nfsInfo);
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createCDATASection(cell5));

        QString webdavInfo = e.split(";").value(5);
        QString cell6 = webdavInfo.isEmpty() ? "-" : cellContentWebdav.arg(
                 QString::number(i), QString::number(i), webdavInfo);
        QDomElement cellElement6 = doc.createElement("cell");
        rowElement.appendChild(cellElement6);
        cellElement6.appendChild(doc.createCDATASection(cell6));

        QDomElement cellElement7 = doc.createElement("cell");
        rowElement.appendChild(cellElement7);
        cellElement7.appendChild(doc.createTextNode("-"));

        rowElement.setAttribute("id", i+1);
        i++;
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

    m_var = doc.toString();

}

void RenderResponseNetShare::generateGetIsoShare() {

    QDomDocument doc;

    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_iso_get_iso_share", true);

    QString cellContentCifs =
            "<img src='../images/detail.png' onclick='show_iso_detail(\"%1\");'>";
    QString cellContentFtp =
            "<img src='../images/detail.png' onclick='show_ftp_detail(\"%1\",\"#iso_tb\");'>";
    // todo: 2 sessions.
    QString cellContentNfs =
            "<img src='../images/detail.png' onclick='show_iso_nfs_detail(\"%1\",\"#iso_tb\")'>"
            "<input type=\"hidden\" name=\"nfs_%2\" id=\"nfs_%2\" value=\"%3\">";
    QString cellContentWebdav =
            "<img src='../images/detail.png' onclick='show_webdav_detail(\"%1\",\"#iso_tb\")'>"
            "<input type=\"hidden\" name=\"webdav_%2\" id=\"webdav_%2\" value=\"%3\">";

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    int i = 0;
    for(QString e : apiOut) {

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(e.split(";").value(0).isEmpty() ? "-" : e.split(";").value(0)));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode(e.split(";").value(1).isEmpty() ? "-" : e.split(";").value(1)));

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createCDATASection(cellContentCifs.arg("1")));

        QString cell4 = e.split(";").value(2) == "1" ? cellContentFtp.arg("1") : "-";
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createCDATASection(cell4));

        QString nfsInfo = e.split(";").value(3);
        QString cell5 = (nfsInfo == "-") ? nfsInfo : cellContentNfs.arg(
                 "1", QString::number(i), nfsInfo);
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createCDATASection(cell5));

        QString webdavInfo = e.split(";").value(4);
        QString cell6 = (webdavInfo == "-") ? "-" : cellContentWebdav.arg(
                 "1", QString::number(i), webdavInfo);
        QDomElement cellElement6 = doc.createElement("cell");
        rowElement.appendChild(cellElement6);
        cellElement6.appendChild(doc.createCDATASection(cell6));

        rowElement.setAttribute("id", i+1);
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

    m_var = doc.toString();

}

void RenderResponseNetShare::generateGetAfpInfo() {

    QDomDocument doc;

    QMap<QString, QString> afpInfo = getNasCfg("afp");

    QDomElement root = doc.createElement("afp_info");
    doc.appendChild(root);

    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode(afpInfo.value("enable")));
    m_var = doc.toString();

}

void RenderResponseNetShare::generateGetNfsInfo() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_nfs_info", true);

    QDomElement root = doc.createElement("nfs_info");
    doc.appendChild(root);

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode(apiOut.value(1)));
    m_var = doc.toString();

}

void RenderResponseNetShare::generateIsoPrecentage() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " service_iso_get_iso_percentage " + allParametersToString(), true);
    m_var = apiOut.value(0);
}

void RenderResponseNetShare::generateClearIsoCreate() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " service_clear_iso_create " + allParametersToString(), true);
}

void RenderResponseNetShare::generateUserList() {

    QDomDocument doc;

    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_iso_get_user_list");
    QString cellContent("<input type='checkbox' name='C_%1' value='%2' rel='%3'>");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    int i = 0;
    for(QString e : apiOut) {
        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        rowElement.setAttribute("id", i+1);

        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(e));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createCDATASection(cellContent.arg(QString::number(i)).arg("r").arg(e)));
        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createCDATASection(cellContent.arg(QString::number(i)).arg("w").arg(e)));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createCDATASection(cellContent.arg(QString::number(i)).arg("d").arg(e)));
        i++;
    }
    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

    m_var = doc.toString();

}

void RenderResponseNetShare::generateGroupList() {

    QDomDocument doc;

    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_iso_get_group_list");
    QString cellContent("<input type='checkbox' name='C_%1' value='%2' rel='%3'>");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);
    int i = 0;
    for(QString e : apiOut) {
        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        rowElement.setAttribute("id", i+1);

        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(e));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createCDATASection(cellContent.arg(QString::number(i)).arg("r").arg(e)));
        if(paraField == "false") {
            QDomElement cellElement4 = doc.createElement("cell");
            rowElement.appendChild(cellElement4);
            cellElement4.appendChild(doc.createCDATASection(cellContent.arg(QString::number(i)).arg("w").arg(e)));
        }
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createCDATASection(cellContent.arg(QString::number(i)).arg("d").arg(e)));

        i++;
    }
    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

    m_var = doc.toString();

}

void RenderResponseNetShare::generateGetAllIsoShare() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_iso_get_all_iso_share");

    QDomElement root = doc.createElement("iso_mount");
    doc.appendChild(root);

    for(QString e : apiOut) {
        QDomElement shareElement = doc.createElement("share");
        root.appendChild(shareElement);

        QDomElement nameElement = doc.createElement("name");
        shareElement.appendChild(nameElement);
        nameElement.appendChild(doc.createTextNode(e.split(";").value(0)));
        QDomElement pathElement = doc.createElement("path");
        shareElement.appendChild(pathElement);
        pathElement.appendChild(doc.createTextNode(e.split(";").value(1)));
    }

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

    m_var = doc.toString();

}

void RenderResponseNetShare::generateAddSession() {
//    QString paraPath = m_pReq->allParameters().value("path").toString();
//    QString paraName = m_pReq->allParameters().value("name").toString();
//    QString paraOplocks = m_pReq->allParameters().value("oplocks").toString();
//    QString paraMapArchive = m_pReq->allParameters().value("map_archive").toString();
//    QString paraComment = m_pReq->allParameters().value("comment").toString();
//    QString paraFtp = m_pReq->allParameters().value("ftp").toString();
//    QString paraReadList = m_pReq->allParameters().value("read_list").toString();
//    QString paraWriteList = m_pReq->allParameters().value("write_list").toString();
//    QString paraDeclineList = m_pReq->allParameters().value("decline_list").toString();
//    QString paraRecycle = m_pReq->allParameters().value("recycle").toString();
//    QString paraFtpAnonymous = m_pReq->allParameters().value("ftp_anonymous").toString();

    //QStringList arg = QStringList() << "service_set_add_session" << allParametersToString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_add_session " +
                                      allParametersToString(), true);

}

void RenderResponseNetShare::generateSetNfsShare() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_add_nfs_share "
                                      + allParametersToString(), true);

}

void RenderResponseNetShare::generateGetModifySession() {

    QDomDocument doc;
    QString paraName = m_pReq->allParameters().value("name").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_modify_session " + paraName, true, ";");

    QDomElement root = doc.createElement("session");
    doc.appendChild(root);

    QStringList sessionTagNames(QStringList()
        << "Name" << "path" << "oplocks" << "map_archive" << "comment" << "read_list"
        << "write_list" << "invalid_users" << "recycle" << "recycle_tree" << "ftp"
        << "ftp_anonymous" << "nfs" << "webdav" << "webdav_rw" << "webdav_user" << "mycloud");

    for(int i = 0; i < apiOut.size(); i++) {
        if( sessionTagNames.size() == apiOut.size() ) {
            if(i == 12) {
                QStringList nfsInfoList = apiOut.value(i).split(",");
                QStringList nfsTagNames(QStringList()
                    << "status" << "real_path" << "root_squash" << "write" << "host");
                QDomElement nfsElement = doc.createElement("nfs");
                root.appendChild(nfsElement);
                for(int j = 0; j < nfsInfoList.size(); j++) {
                    QDomElement element = doc.createElement(nfsTagNames.value(j));
                    nfsElement.appendChild(element);
                    element.appendChild(doc.createTextNode(nfsInfoList.value(j)));
                }
            }
            else {
                QDomElement element = doc.createElement(sessionTagNames.value(i));
                root.appendChild(element);
                element.appendChild(doc.createTextNode(apiOut.value(i)));
            }
        }
        else {
            //assert(0);
            tError("RenderResponseNetShare::generateGetModifySession() :"
                   "sessionTagNames size is not equal to apiOut size.");
        }
    }

    m_var = doc.toString();

}

void RenderResponseNetShare::generateModifySession() {
//    QString paraPath = m_pReq->allParameters().value("path").toString();
//    QString paraName = m_pReq->allParameters().value("name").toString();
//    QString paraOplocks = m_pReq->allParameters().value("oplocks").toString();
//    QString paraMapArchive = m_pReq->allParameters().value("map_archive").toString();
//    QString paraComment = m_pReq->allParameters().value("comment").toString();
//    QString paraFtp = m_pReq->allParameters().value("ftp").toString();
//    QString paraReadList = m_pReq->allParameters().value("read_list").toString();
//    QString paraWriteList = m_pReq->allParameters().value("write_list").toString();
//    QString paraDeclineList = m_pReq->allParameters().value("decline_list").toString();
//    QString paraRecycle = m_pReq->allParameters().value("recycle").toString();
//    QString paraFtpAnonymous = m_pReq->allParameters().value("ftp_anonymous").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_modify_session " +
                                      allParametersToString(), true);

}

void RenderResponseNetShare::generateModifyNfsShare() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_modify_nfs_share "
                                      + allParametersToString(), true);

}

void RenderResponseNetShare::generateWebdavAccountAdd() {

    QDomDocument doc;

//    QString paraShareName = m_pReq->allParameters().value("f_share_name").toString();
//    QString paraPath = m_pReq->allParameters().value("f_path").toString();
//    QString paraRw = m_pReq->allParameters().value("f_rw").toString();
//    QString paraUser = m_pReq->allParameters().value("f_user").toString();
//    QString paraWebdav = m_pReq->allParameters().value("webdav").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_share_webdav_account_add " +
                                      allParametersToString(), true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseNetShare::generateDeleteSession() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_del_session " +
                                      allParametersToString(), true);
}

void RenderResponseNetShare::generateWebdavAccountDel() {

    QDomDocument doc;

//    QString paraFlag = m_pReq->allParameters().value("f_flag").toString();
//    QString paraPath = m_pReq->allParameters().value("f_path").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_share_webdav_account_del " +
                                      allParametersToString(), true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseNetShare::generateResetSession() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_reset_session", true);
    m_var = apiOut.value(0);
}

void RenderResponseNetShare::generateGetShareInfo() {

    QDomDocument doc;
    QString paraName = m_pReq->parameter("name");

    /* todo */
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_modify_session " + paraName, true, ";");

    QDomElement root = doc.createElement("session");
    doc.appendChild(root);

    QStringList sessionTagNames(QStringList()
        << "Name" << "path" << "oplocks" << "map_archive" << "comment" << "read_list"
        << "write_list" << "invalid_users" << "recycle" << "recycle_tree" << "ftp"
        << "ftp_anonymous" << "nfs");

    for(int i = 0; i < apiOut.size(); i++) {
        if( sessionTagNames.size() == 13/*apiOut.size()*/ ) {
            if(i == 12) {
                QStringList nfsInfoList = apiOut.value(i).split(",");
                QStringList nfsTagNames(QStringList()
                    << "status" << "real_path" << "root_squash" << "write" << "host");
                QDomElement nfsElement = doc.createElement("nfs");
                root.appendChild(nfsElement);
                for(int j = 0; j < nfsInfoList.size(); j++) {
                    QDomElement element = doc.createElement(nfsTagNames.value(j));
                    nfsElement.appendChild(element);
                    element.appendChild(doc.createTextNode(nfsInfoList.value(j)));
                }
            }
            else {
                QDomElement element = doc.createElement(sessionTagNames.value(i));
                root.appendChild(element);
                element.appendChild(doc.createTextNode(apiOut.value(i)));
            }
        }
        else {
            //assert(0);
            tError("RenderResponseNetShare::generateGetShareInfo() :"
                   "sessionTagNames size is not equal to apiOut size.");
        }
    }

    m_var = doc.toString();

}

/* todo: need API */
void RenderResponseNetShare::generateGetFtp() {

    QDomDocument doc;
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

    m_var = doc.toString();

}

/* todo: need API */
void RenderResponseNetShare::generateWebdavAccountInfo() {

    QDomDocument doc;
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

    m_var = doc.toString();

}

void RenderResponseNetShare::generateSetIsoShare() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " service_iso_set_iso_share " + allParametersToString(), true);

    QDomElement root = doc.createElement("iso_info");
    doc.appendChild(root);

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseNetShare::generateGetIsoShareDetail() {

    QDomDocument doc;

    QString paraName = m_pReq->allParameters().value("name").toString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_iso_get_iso_detail_info " + paraName, true, ";");

    QDomElement root = doc.createElement("iso_mount");
    doc.appendChild(root);

    QString contentReadList = "<b>%1</b><br>%2";
    QString contentInvalidUsers = "<b>%1</b><br>%2";

    QStringList isoMountTags(QStringList()
            << "name" << "comment" << "path" << "read_list" << "invalid_users");

    if( isoMountTags.size() == apiOut.size() ) {
        for(int i = 0; i < apiOut.size(); i++) {
            QString value = apiOut.value(i);
            if(i == 3 && value != "ALL")
                value = contentReadList.arg(value.split(";").value(0), value.split(";").value(1));
            if(i == 4 && value != "-")
                value = contentInvalidUsers.arg(value.split(";").value(0), value.split(";").value(1));
            QDomElement element = doc.createElement(isoMountTags.value(i));
            root.appendChild(element);
            element.appendChild(doc.createCDATASection(value));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseNetShare::generateGetIsoShareDetail() :"
               "isoMountTags size is not equal to apiOut size.");
    }

    m_var = doc.toString();

}

/* todo: need API */
void RenderResponseNetShare::generateGetNfsShareInfo() {

    QDomDocument doc;
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

    m_var = doc.toString();

}

void RenderResponseNetShare::generateGetModifyIsoInfo() {

    QDomDocument doc;

    QString paraName = m_pReq->allParameters().value("name").toString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " service_iso_modify_iso_info " + paraName, true, ";");

    QDomElement root = doc.createElement("iso_mount");
    doc.appendChild(root);

    QStringList isoMountTags(QStringList()
            << "comment" << "path" << "read_list" << "invalid_users" << "ftp" << "nfs"
            << "nfs_host" << "webdav");

    /* <nfs_host> */
    if(apiOut.size() == 7)
        apiOut.insert(6, "");

    if( isoMountTags.size() == apiOut.size()) {
        for(int i = 0; i < apiOut.size(); i++) {
            QString value = apiOut.value(i);
            /* for nfs_host */
            if(i == 6 && value.isEmpty())
                continue;
            QDomElement element = doc.createElement(isoMountTags.value(i));
            root.appendChild(element);
            element.appendChild(doc.createTextNode(value));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseNetShare::generateGetModifyIsoInfo() :"
               "isoMountTags size is not equal to apiOut size.");
    }

    m_var = doc.toString();

}

void RenderResponseNetShare::generateModifyIsoShare() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " service_iso_modify_iso_share " + allParametersToString(), true);
}

void RenderResponseNetShare::generateDelIsoShare() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " service_iso_del_iso_share " + allParametersToString(), true);

    QDomElement root = doc.createElement("iso_mount");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseNetShare::generateChkImgName() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " service_iso_chk_iso_name " + allParametersToString(), true);
    m_var = apiOut.value(0);
}

void RenderResponseNetShare::generateChkHDSize() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " service_iso_chk_hdd_size " + allParametersToString(), true);
    m_var = apiOut.value(0);
}

void RenderResponseNetShare::generateIsoConfig() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " service_iso_set_iso_config " + allParametersToString(), true, ";");

    QStringList isoMountTags(QStringList() << "status" << "name" << "path");

    QDomElement root = doc.createElement("iso");
    doc.appendChild(root);

    if( isoMountTags.size() == apiOut.size()) {
        for(int i = 0; i < apiOut.size(); i++) {
            QDomElement element = doc.createElement(isoMountTags.value(i));
            root.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseNetShare::generateIsoConfig() :"
               "isoMountTags size is not equal to apiOut size.");
    }

    m_var = doc.toString();
}

void RenderResponseNetShare::generateIsoCreatePath() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " service_iso_create_iso_path " + allParametersToString(), true);
}

void RenderResponseNetShare::generateIsoSize() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " service_iso_get_iso_use_size " + allParametersToString(), true);
    m_var = apiOut.value(0);
}

void RenderResponseNetShare::generateIsoCreateImage() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " service_iso_create_image " + allParametersToString(), true);
}
