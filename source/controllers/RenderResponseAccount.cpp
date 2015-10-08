#include <QFileInfo>

#include "RenderResponseAccount.h"

RenderResponseAccount::RenderResponseAccount(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseAccount::~RenderResponseAccount() {
}

void RenderResponseAccount::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_CHANGE_ADMIN_PWD:
        generateChangeAdminPwd();
        break;
    case CMD_GET_USER_LIST:
        generateGetUserList();
        break;
    case CMD_GET_USER_INFO:
        generateGetUserInfo();
        break;
    case CMD_GET_SMB_LIST:
        generateGetSmbList();
        break;
    case CMD_USER_ADD:
        generateUserAdd();
        break;
    case CMD_RESTART_SERVICE:
        generateRestartService();
        break;
    case CMD_USER_SET_QUOTA:
        generateUserSetQuota();
        break;
    case CMD_ADDUSER_TO_SESSION:
        generateAddUserToSession();
        break;
    case CMD_CREATE_FTP_LINK:
        generateCreateFtpLink();
        break;
    case CMD_FTP_SERVICE:
        generateFtpService();
        break;
    case CMD_WEBDAV_ACCOUNT_MERGE:
        generateWebdavAccountMerge();
        break;
    case CMD_USER_BATCH_CREATE:
        generateUserBatchCreate();
        break;
    case CMD_GET_MODIFY_USER_INFO:
        generateGetModifyUserInfo();
        break;
    case CMD_USER_MODIFY:
        generateUserModify();
        break;
    case CMD_USER_DEL:
        generateUserDel();
        break;
    case CMD_MYFAVORITE_DEL_USER:
        generateMyFavDelUser();
        break;
    case CMD_DWONLOAD_IMPORT_SAMPLE:
        generateDownloadImportSample();
        break;
    case CMD_GET_ALL_SESSION:
        generateGetAllSession();
        break;
    case CMD_GET_IMPORT_USERS:
        generateGetImportUsers();
        break;
    case CMD_ADDUSER_GET_USER_QUOTA_MAXSIZE:
        generateAddUserGetUserQuotaMaxsize();
        break;
    case CMD_CREATE_IMPORT_USERS:
        generateCreateImportUsers();
        break;
    case CMD_GET_CREATE_STATUS:
        generateCreateStatus();
        break;
    case CMD_GET_GROUP_LIST:
        generateGetGroupList();
        break;
    case CMD_GET_GROUP_INFO:
        generateGetGroupInfo();
        break;
    case CMD_GROUP_ADD:
        generateGroupAdd();
        break;
    case CMD_ADDGROUP_GET_GROUP_QUOTA_MINSIZE:
        generateAddGroupGetGroupQuotaMinsize();
        break;
    case CMD_GROUP_SET_QUOTA:
        generateGroupSetQuota();
        break;
    case CMD_GET_MODIFY_GROUP_INFO:
        generateGetModifyGroupInfo();
        break;
    case CMD_GROUP_MODIFY:
        generateGroupModify();
        break;
    case CMD_GROUP_DEL:
        generateGroupDel();
        break;
    case CMD_GET_QUOTA_INFO:
        generateGetQuotaInfo();
        break;
    case CMD_GET_HD_MAPPING_INFO:
        generateGetHDMappingInfo();
        break;
    case CMD_GET_USER_QUOTA_LIST:
        generateGetUserQuotaList();
        break;
    case CMD_GET_GROUP_QUOTA_LIST:
        generateGetGroupQuotaList();
        break;
    case CMD_GET_USER_QUOTA_MAXSIZE:
        generateGetUserQuotaMaxSize();
        break;
    case CMD_GET_GROUP_QUOTA_MINSIZE:
        generateGetGroupQuotaMinSize();
        break;
    case CMD_SET_QUOTA_ONOFF:
        generateSetQuotaOnOff();
        break;

    default:
        break;
    }

}

void RenderResponseAccount::generateChangeAdminPwd() {
    QDomDocument doc;

    QString paraPwd = m_pReq->allParameters().value("pw").toString();
    QString paraOldPwd = m_pReq->allParameters().value("old_pw").toString();
    //QByteArray pwd = QByteArray::fromBase64(paraPwd.toLocal8Bit());
    //QByteArray oldPwd = QByteArray::fromBase64(paraOldPwd.toLocal8Bit());

    QStringList arg = QStringList() << "admin" << paraOldPwd << paraPwd;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR, arg, true);

    QDomElement root = doc.createElement("modify_info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.isEmpty() ? "0" : apiOut.at(0)));

    m_var = doc.toString();

}

void RenderResponseAccount::generateGetUserList() {
    QDomDocument doc;

    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList arg = QStringList() << "system_user_get_user_list";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QStringList userInfoList(apiOut);
    int rp = paraRp.toInt();
    if(userInfoList.size() > rp)
        userInfoList = apiOut.mid((paraPage.toInt()-1) * rp, rp);

    int i = 0;
    for(QString e : userInfoList) {
        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);

        for(QString cellEntry : e.split(";")) {
            QDomElement cellElement = doc.createElement("cell");
            rowElement.appendChild(cellElement);
            cellElement.appendChild(doc.createTextNode(cellEntry));
        }

        rowElement.setAttribute("id", QString::number(i+1));
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

void RenderResponseAccount::generateGetUserInfo() {
    QDomDocument doc;

    QStringList arg = QStringList() << "system_user_get_user_info";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");
    QDomElement root = doc.createElement("user_info");
    doc.appendChild(root);

    QStringList infoTagNames(QStringList()
        << "total" << "all_user" << "all_group" << "hddnum" << "hddsize" << "v_name");

    if( infoTagNames.size() == apiOut.size() ) {
        for(int i = 0; i < apiOut.size(); i++) {
            if(i == 5) {
                for(QString e : apiOut.value(i).split(",")) {
                    QDomElement element = doc.createElement(infoTagNames.value(i));
                    root.appendChild(element);
                    element.appendChild(doc.createTextNode(e));
                }
            }
            else {
                QDomElement element = doc.createElement(infoTagNames.value(i));
                root.appendChild(element);
                element.appendChild(doc.createTextNode(apiOut.value(i)));
            }
        }
    }
    else {
        //assert(0);
        tError("RenderResponseAccount::generateGetUserInfo() :"
               "infoTagNames size is not equal to apiOut size.");
    }

    m_var = doc.toString();

}

void RenderResponseAccount::generateGetSmbList() {

    QDomDocument doc;

    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList arg = QStringList() << "system_user_get_smb_share_list";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QStringList userInfoList(apiOut);
    int rp = paraRp.toInt();
    if(userInfoList.size() > rp)
        userInfoList = apiOut.mid((paraPage.toInt()-1) * rp, rp);

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QString cellContent = "<input type=\"checkbox\" name=\"C_%1\" value=\"%2\" rel=\"%3\">";
    for(int i=0; i < userInfoList.size(); i++) {

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        rowElement.setAttribute("id", QString::number(i+1));

        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(userInfoList.at(i)));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createCDATASection(cellContent.arg(QString::number(i)).arg("r").arg(userInfoList.value(i))));
        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createCDATASection(cellContent.arg(QString::number(i)).arg("w").arg(userInfoList.value(i))));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createCDATASection(cellContent.arg(QString::number(i)).arg("d").arg(userInfoList.value(i))));
    }
    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

    m_var = doc.toString();

}

void RenderResponseAccount::generateUserAdd() {

    QStringList arg = QStringList() << "system_user_add_user" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

}

/* todo: restart specified service*/
void RenderResponseAccount::generateRestartService() {
    QStringList arg = QStringList() << "system_user_set_service_restart";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
}

void RenderResponseAccount::generateUserSetQuota() {
    QStringList arg = QStringList() << "system_user_set_user_quota" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

}

void RenderResponseAccount::generateAddUserToSession() {
//    QString paraName = m_pReq->allParameters().value("s_name").toString();
//    QString paraFtp = m_pReq->allParameters().value("ftp").toString();
//    QString paraReadList = m_pReq->allParameters().value("read_list").toString();
//    QString paraWriteList = m_pReq->allParameters().value("write_list").toString();
//    QString paraDeclineList = m_pReq->allParameters().value("decline_list").toString();
//    QString paraUsername = m_pReq->allParameters().value("username").toString();

    QStringList arg = QStringList() << "system_user_set_user_add_session" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
}

void RenderResponseAccount::generateCreateFtpLink() {
    QStringList arg = QStringList() << "service_ftp_modify_share_config" << "adduser";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
}

void RenderResponseAccount::generateFtpService() {
    QString paraStart = m_pReq->allParameters().value("type").toString();
    QString action = (paraStart == "1") ? "start" : "stop";

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " " + action, true);
}

/* For user, group and network share. */
void RenderResponseAccount::generateWebdavAccountMerge() {
    QDomDocument doc;

//    QString paraShareName = m_pReq->allParameters().value("f_share_name").toString();
//    QString paraRw = m_pReq->allParameters().value("f_rw").toString();
//    QString paraUser = m_pReq->allParameters().value("f_user").toString();
//    QString paraWebdav = m_pReq->allParameters().value("webdav").toString();
//    QString paraPath = m_pReq->allParameters().value("f_path").toString();

    QStringList arg = QStringList() << "system_user_set_webdav_service" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAccount::generateUserBatchCreate() {
//    QString paraPrefix = m_pReq->allParameters().value("f_prefix").toString();
//    QString paraStart = m_pReq->allParameters().value("f_start").toString();
//    QString paraNumber = m_pReq->allParameters().value("f_number").toString();
//    QString paraBatchPw = m_pReq->allParameters().value("f_batch_pw").toString();
//    QString paraRList = m_pReq->allParameters().value("r_list").toString();
//    QString paraWList = m_pReq->allParameters().value("w_list").toString();
//    QString paraDList = m_pReq->allParameters().value("d_list").toString();
//    QString paraGroupList = QUrl::fromPercentEncoding(m_pReq->allParameters().value("group_list").toByteArray()).replace(":", ",");
//    QString paraApp = m_pReq->allParameters().value("app").toString();
//    QString paraQuota = m_pReq->allParameters().value("quota").toString();
//    QString paraOverWrite = m_pReq->allParameters().value("f_overwrite").toString();

    QStringList arg = QStringList() << "system_user_multi_add_user" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

}

void RenderResponseAccount::generateGetModifyUserInfo() {
    QDomDocument doc;

    QString paraName = m_pReq->allParameters().value("name").toString();

    QStringList arg = QStringList() << "modinfo" << paraName;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR, arg, true, ";");
    QDomElement root = doc.createElement("user_info");
    doc.appendChild(root);

    if(!apiOut.value(0).isEmpty()) {
        QStringList quotaInfoItems = apiOut.value(0).split("#");

        for(auto e : quotaInfoItems) {
            if(!e.isEmpty()) {
                QDomElement quotaInfoElement1 = doc.createElement("quota_info");
                root.appendChild(quotaInfoElement1);
                QDomElement vnameElement = doc.createElement("v_name");
                quotaInfoElement1.appendChild(vnameElement);
                vnameElement.appendChild(doc.createTextNode(e.split(",").value(0)));
                QDomElement quotaElement = doc.createElement("quota");
                quotaInfoElement1.appendChild(quotaElement);
                quotaElement.appendChild(doc.createTextNode(e.split(",").value(1)));
                QDomElement maxQuotaElement = doc.createElement("max_quota");
                quotaInfoElement1.appendChild(maxQuotaElement);
                maxQuotaElement.appendChild(doc.createTextNode(e.split(",").value(2)));
            }
        }
    }

    QDomElement groupElement = doc.createElement("group");
    root.appendChild(groupElement);
    groupElement.appendChild(doc.createTextNode(apiOut.value(1)));

    QDomElement hddnumElement = doc.createElement("hddnum");
    root.appendChild(hddnumElement);
    hddnumElement.appendChild(doc.createTextNode(apiOut.value(2)));

    QDomElement hddsizeElement = doc.createElement("hddsize");
    root.appendChild(hddsizeElement);
    hddsizeElement.appendChild(doc.createTextNode(apiOut.value(3)));

    QDomElement mainGroupElement = doc.createElement("main_group");
    root.appendChild(mainGroupElement);
    mainGroupElement.appendChild(doc.createTextNode(apiOut.value(4)));

    QDomElement smbInfoElement = doc.createElement("smb_info");
    root.appendChild(smbInfoElement);

    if(!apiOut.value(5).isEmpty()) {
        QStringList quotaInfoItems = apiOut.value(5).split("#");

        for(auto e : quotaInfoItems) {
            if(!e.isEmpty()) {
                QDomElement itemElement = doc.createElement("item");
                smbInfoElement.appendChild(itemElement);

                QDomElement shareNameElement = doc.createElement("share_name");
                itemElement.appendChild(shareNameElement);
                shareNameElement.appendChild(doc.createTextNode(e.split(",").value(0)));
                QDomElement privilegesElement = doc.createElement("privileges");
                itemElement.appendChild(privilegesElement);
                privilegesElement.appendChild(doc.createTextNode(e.split(",").value(1)));
            }
        }
    }

    QDomElement ftpElement = doc.createElement("ftp");
    root.appendChild(ftpElement);
    ftpElement.appendChild(doc.createTextNode(apiOut.value(6)));
    QDomElement webdavInfoElement = doc.createElement("webdav_info");
    root.appendChild(webdavInfoElement);

    if(!apiOut.value(7).isEmpty()) {
        QStringList quotaInfoItems = apiOut.value(7).split("#");

        for(auto e : quotaInfoItems) {
            if(!e.isEmpty()) {
                QDomElement itemElement = doc.createElement("item");
                webdavInfoElement.appendChild(itemElement);
                itemElement.appendChild(doc.createTextNode(e.split(",").value(0)));
            }
        }
    }

    m_var = doc.toString();

}

void RenderResponseAccount::generateUserModify() {
    QDomDocument doc;

//    QString paraName = m_pReq->allParameters().value("name").toString();
//    QString paraPw = m_pReq->allParameters().value("pw").toString();
//    QString paraFtp = m_pReq->allParameters().value("ftp").toString();
//    QString paraGroup = m_pReq->allParameters().value("group").toString();
//    QString paraAva1 = m_pReq->allParameters().value("available1").toString();
//    QString paraAva2 = m_pReq->allParameters().value("available2").toString();
//    QString paraAva3 = m_pReq->allParameters().value("available3").toString();
//    QString paraAva4 = m_pReq->allParameters().value("available4").toString();
//    QString paraReadList = m_pReq->allParameters().value("read_list").toString();
//    QString paraWriteList = m_pReq->allParameters().value("write_list").toString();
//    QString paraDeclineList = m_pReq->allParameters().value("decline_list").toString();
//    QString paraUncheckList = m_pReq->allParameters().value("uncheck_list").toString();
//    QString paraMPw = m_pReq->allParameters().value("m_pw").toString();
//    QString paraMGroup = QUrl::fromPercentEncoding(m_pReq->allParameters().value("m_group").toByteArray()).remove("#");
//    QString paraMQuota = m_pReq->allParameters().value("m_quota").toString();
//    QString paraMShare = m_pReq->allParameters().value("m_share").toString();

//    QVector<QString> available;
//    if(paraAva1.compare("null") != 0)
//        available.insert("volume_1");
//    if(paraAva2.compare("null") != 0)
//        available.insert("volume_2");
//    if(paraAva3.compare("null") != 0)
//        available.insert("volume_3");
//    if(paraAva4.compare("null") != 0)
//        available.insert("volume_4");

    QStringList arg = QStringList() << "modify" << allParametersToString();
    QStringList apiOutUser = getAPIStdOut(API_PATH + SCRIPT_USER_MGR, arg, true);

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOutUser.value(0)));

    m_var = doc.toString();

}

void RenderResponseAccount::generateUserDel() {
    QString paraName = QUrl::fromPercentEncoding(m_pReq->allParameters().value("name").toByteArray());
    QStringList arg = QStringList() << "del" << paraName;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR, arg, true);
}

/* the same API ?? */
void RenderResponseAccount::generateMyFavDelUser() {
    QDomDocument doc;

    QString paraUserList = QUrl::fromPercentEncoding(m_pReq->allParameters().value("f_user_lst").toByteArray());

    QStringList arg = QStringList() << "del" << paraUserList;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR, arg, true);
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAccount::generateDownloadImportSample() {

    QString filePath = DWONLOAD_USER_IMPORT_FILE;
    tDebug("file: %s", filePath.toLocal8Bit().data());
    QFileInfo file(filePath);
    if(file.exists() && file.isFile())
        m_var = filePath;

}


void RenderResponseAccount::generateGetAllSession() {
    QDomDocument doc;

    QStringList arg = QStringList() << "service_get_tm_list";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);
    QDomElement root = doc.createElement("session");
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

void RenderResponseAccount::generateGetImportUsers() {
    QDomDocument doc;

    QStringList arg = QStringList() << "get_import_user";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR, arg);
    QDomElement root = doc.createElement("info");
    doc.appendChild(root);

    for(QString e : apiOut) {
        QDomElement itemElement = doc.createElement("item");
        root.appendChild(itemElement);
        itemElement.appendChild(doc.createTextNode(e));
    }

    m_var = doc.toString();

}

void RenderResponseAccount::generateAddUserGetUserQuotaMaxsize() {
    QDomDocument doc;

    QString paraName = m_pReq->allParameters().value("name").toString();
    QStringList arg = QStringList() << "system_user_get_user_quota_maxsize" << paraName;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR, arg, true);
    QDomElement root = doc.createElement("quota_info");
    doc.appendChild(root);
    QDomElement maxSizeElement = doc.createElement("max_size");
    root.appendChild(maxSizeElement);
    maxSizeElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAccount::generateCreateImportUsers() {
    QStringList arg = QStringList() << "create_import_user" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR, arg, true);
}

void RenderResponseAccount::generateCreateStatus() {
    QDomDocument doc;

    QStringList arg = QStringList() << "system_user_get_create_import_status";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseAccount::generateGetGroupList() {
    QDomDocument doc;
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList arg = QStringList() << "get_group_list";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_GROUP_MANAGER, arg);

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QStringList groupInfoList(apiOut);
    int rp = paraRp.toInt();
    if(groupInfoList.size() > rp)
        groupInfoList = apiOut.mid((paraPage.toInt()-1) * rp, rp);

    int i = 0;
    for(QString e : groupInfoList) {
        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);

        for(QString cellEntry : e.split(";")) {
            QDomElement cellElement = doc.createElement("cell");
            rowElement.appendChild(cellElement);
            cellElement.appendChild(doc.createTextNode(cellEntry));
        }

        rowElement.setAttribute("id", QString::number(i+1));
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


void RenderResponseAccount::generateGetGroupInfo() {
    QDomDocument doc;
    QStringList arg = QStringList() << "get_group_info";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_GROUP_MANAGER, arg, true, ";");

    QDomElement root = doc.createElement("group_info");
    doc.appendChild(root);

    QStringList infoTagNames(QStringList()
        << "v_name" << "total" << "all_user" << "all_group" << "hddnum" << "hddsize");

    if( infoTagNames.size() == apiOut.size() ) {
        for(int i = 0; i < apiOut.size(); i++) {
            if(i == 0) {
                for(QString e : apiOut.value(i).split(",")) {
                    QDomElement element = doc.createElement(infoTagNames.value(i));
                    root.appendChild(element);
                    element.appendChild(doc.createTextNode(e));
                }
            }
            else {
                QDomElement element = doc.createElement(infoTagNames.value(i));
                root.appendChild(element);
                element.appendChild(doc.createTextNode(apiOut.value(i)));
            }
        }
    }
    else {
        //assert(0);
        tError("RenderResponseAccount::generateGetGroupInfo() :"
               "infoTagNames size is not equal to apiOut size.");
    }

    m_var = doc.toString();

}

void RenderResponseAccount::generateGroupAdd() {
//    QString paraGroup = m_pReq->allParameters().value("group").toString();
//    QString paraMember = m_pReq->allParameters().value("member").toString();
    QStringList arg = QStringList() << "add" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_GROUP_MANAGER, arg, true);
}


void RenderResponseAccount::generateAddGroupGetGroupQuotaMinsize() {
    QDomDocument doc;
    QString paraName = QUrl::fromPercentEncoding(m_pReq->parameter("name").toLocal8Bit());
    QStringList arg = QStringList() << "get_group_quota_minsize" << paraName;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR, arg, true);

    QDomElement root = doc.createElement("quota_info");
    doc.appendChild(root);

    QDomElement minSizeElement = doc.createElement("min_size");
    root.appendChild(minSizeElement);
    minSizeElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAccount::generateGroupSetQuota() {
//    QString paraName = m_pReq->allParameters().value("name").toString();
//    QString paraAva1 = m_pReq->allParameters().value("available1").toString();
//    QString paraAva2 = m_pReq->allParameters().value("available2").toString();
//    QString paraAva3 = m_pReq->allParameters().value("available3").toString();
//    QString paraAva4 = m_pReq->allParameters().value("available4").toString();
    QStringList arg = QStringList() << "groupset" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_GROUP_MANAGER, arg, true);

}

void RenderResponseAccount::generateGetModifyGroupInfo() {
    QDomDocument doc;
    QString paraGroup = QUrl::fromPercentEncoding(m_pReq->allParameters().value("group").toByteArray());
    QStringList arg = QStringList() << "modify_group_info" << paraGroup;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_GROUP_MANAGER, arg, true, ";");

    QDomElement root = doc.createElement("group_info");
    doc.appendChild(root);

    QStringList infoTagNames(QStringList()
        << "member" << "hddnum" << "hddsize" << "quota" << "smb_info" << "ftp" << "webdav_info");

    if( infoTagNames.size() == apiOut.size() ) {
        for(int i = 0; i < apiOut.size(); i++) {

            switch(i) {
            case 3: //quota
            {
                for(int j = 0; j < apiOut.value(i).split("#").size(); j++) {
                    QDomElement element = doc.createElement(infoTagNames.value(i));
                    root.appendChild(element);
                    QStringList quotaTagNames(QStringList()
                                              << "v_name" << "size");
                    QString value = apiOut.value(i).split("#").value(j);
                    for(int k = 0; k < value.split(",").size(); k++) {
                        QDomElement quotaElement = doc.createElement(quotaTagNames.value(k));
                        element.appendChild(quotaElement);
                        quotaElement.appendChild(doc.createTextNode(value.split(",").value(k)));
                    }
                }
            }
                break;

            case 4: //smb_info
            {
                QDomElement element = doc.createElement(infoTagNames.value(i));
                root.appendChild(element);
                for(int j = 0; j < apiOut.value(i).split("#").size(); j++) {
                    QDomElement itemElement = doc.createElement("item");
                    element.appendChild(itemElement);
                    QStringList smbTagNames(QStringList()
                                            << "share_name" << "privileges");
                    QString value = apiOut.value(i).split("#").value(j);
                    for(int k = 0; k < value.split(",").size(); k++) {
                        QDomElement smbElement = doc.createElement(smbTagNames.value(k));
                        itemElement.appendChild(smbElement);
                        smbElement.appendChild(doc.createTextNode(value.split(",").value(k)));
                    }
                }
            }
                break;

            case 6: //webdav_info
            {
                QDomElement element = doc.createElement(infoTagNames.value(i));
                root.appendChild(element);

                if(!apiOut.value(i).isEmpty()) {
                    for(QString e : apiOut.value(i).split("#")) {
                        QDomElement webdavElement = doc.createElement("item");
                        element.appendChild(webdavElement);
                        webdavElement.appendChild(doc.createTextNode(e));
                    }
                }
                else
                    /* for sdupid web parser */
                    element.appendChild(doc.createTextNode(""));
            }
                break;

            default:
            {
                QDomElement element = doc.createElement(infoTagNames.value(i));
                root.appendChild(element);
                element.appendChild(doc.createTextNode(apiOut.value(i)));
            }
                break;
            }
        }
    }
    else {
        //assert(0);
        tError("RenderResponseAccount::generateGetModifyGroupInfo() :"
               "infoTagNames size is not equal to apiOut size.");
    }

    m_var = doc.toString();

}


void RenderResponseAccount::generateGroupModify() {
//    QString paraGroup = m_pReq->allParameters().value("group").toString();
//    QString paraAva1 = m_pReq->allParameters().value("available1").toString();
//    QString paraAva2 = m_pReq->allParameters().value("available2").toString();
//    QString paraAva3 = m_pReq->allParameters().value("available3").toString();
//    QString paraAva4 = m_pReq->allParameters().value("available4").toString();
//    QString paraReadList = m_pReq->allParameters().value("read_list").toString();
//    QString paraWriteList = m_pReq->allParameters().value("write_list").toString();
//    QString paraDeclineList = m_pReq->allParameters().value("decline_list").toString();
//    QString paraUncheckList = m_pReq->allParameters().value("uncheck_list").toString();
//    QString paraFtp = m_pReq->allParameters().value("ftp").toString();

    QStringList arg = QStringList() << "modify" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_GROUP_MANAGER, arg, true);
}

void RenderResponseAccount::generateGroupDel() {
    QString paraGroup = QUrl::fromPercentEncoding(m_pReq->allParameters().value("group").toByteArray());
    QStringList arg = QStringList() << "delete" << paraGroup;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_GROUP_MANAGER, arg, true);
}

void RenderResponseAccount::generateGetQuotaInfo() {
    QDomDocument doc;

    QStringList arg = QStringList() << "quotainfo";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR, arg, true, ";");

    QDomElement root = doc.createElement("quota_info");
    doc.appendChild(root);

    QDomElement hddNumElement = doc.createElement("hddnum");
    root.appendChild(hddNumElement);
    hddNumElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement hddSizeElement = doc.createElement("hddsize");
    root.appendChild(hddSizeElement);
    hddSizeElement.appendChild(doc.createTextNode(apiOut.value(1)));
    QDomElement userNumElement = doc.createElement("usernum");
    root.appendChild(userNumElement);
    userNumElement.appendChild(doc.createTextNode(apiOut.value(2)));
    QDomElement groupNumElement = doc.createElement("groupnum");
    root.appendChild(groupNumElement);
    groupNumElement.appendChild(doc.createTextNode(apiOut.value(3)));
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode(apiOut.value(4)));
    QDomElement vnameElement = doc.createElement("v_name");
    root.appendChild(vnameElement);
    vnameElement.appendChild(doc.createTextNode(apiOut.value(5)));
    m_var = doc.toString();

}


void RenderResponseAccount::generateGetHDMappingInfo() {
    QDomDocument doc;
    QStringList apiOut = getAPIFileOut(SHARE_INFO_FILE);

    QDomElement root = doc.createElement("mapping_info");
    doc.appendChild(root);

    for(auto e : apiOut) {
        QDomElement itemElement = doc.createElement("item");
        root.appendChild(itemElement);
        QDomElement dataElement = doc.createElement("data");
        itemElement.appendChild(dataElement);
        dataElement.appendChild(doc.createTextNode(e));
    }
    m_var = doc.toString();

}

bool RenderResponseAccount::isQuotaNumber(QString str) {

    if(str.isEmpty() || str.compare("Unlimited") == 0 || str.compare("-") == 0)
        return false;

    bool ok = false;
    str.toInt(&ok);
    if(!ok)
        return false;

    return true;
}

void RenderResponseAccount::generateGetUserQuotaList() {
    QDomDocument doc;
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qyupe").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList arg = QStringList() << "userlist";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR, arg, false, ";");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    for(int i=0; i < apiOut.size(); i++) {
        QStringList data = apiOut.at(i).split(";");

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(data.value(0)));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode(isQuotaNumber(data.value(1)) ? data.value(1) + " MB" : data.value(1)));

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode(isQuotaNumber(data.value(2)) ? data.value(2) + " MB" : data.value(2)));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createTextNode(isQuotaNumber(data.value(3)) ? data.value(3) + " MB" : data.value(3)));
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createTextNode(isQuotaNumber(data.value(4)) ? data.value(4) + " MB" : data.value(4)));

        QDomElement cellElement6 = doc.createElement("cell");
        rowElement.appendChild(cellElement6);
        cellElement6.appendChild(doc.createTextNode(isQuotaNumber(data.value(5)) ? data.value(5) + " MB" : data.value(5)));
        QDomElement cellElement7 = doc.createElement("cell");
        rowElement.appendChild(cellElement7);
        cellElement7.appendChild(doc.createTextNode(isQuotaNumber(data.value(6)) ? data.value(6) + " MB" : data.value(6)));
        QDomElement cellElement8 = doc.createElement("cell");
        rowElement.appendChild(cellElement8);
        cellElement8.appendChild(doc.createTextNode(isQuotaNumber(data.value(7)) ? data.value(7) + " MB" : data.value(7)));
        QDomElement cellElement9 = doc.createElement("cell");
        rowElement.appendChild(cellElement9);
        cellElement9.appendChild(doc.createTextNode(isQuotaNumber(data.value(8)) ? data.value(8) + " MB" : data.value(8)));

        rowElement.setAttribute("id", QString::number(i+1));
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));
    m_var = doc.toString();

}

void RenderResponseAccount::generateGetGroupQuotaList() {
    QDomDocument doc;
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qyupe").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList arg = QStringList() << "grouplist";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR, arg, false, ";");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    for(int i=0; i < apiOut.size(); i++) {
        QStringList data = apiOut.at(i).split(";");

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(data.value(0)));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode(isQuotaNumber(data.value(1)) ? data.value(1) + " MB" : data.value(1)));

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode(isQuotaNumber(data.value(2)) ? data.value(2) + " MB" : data.value(2)));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createTextNode(isQuotaNumber(data.value(3)) ? data.value(3) + " MB" : data.value(3)));
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createTextNode(isQuotaNumber(data.value(4)) ? data.value(4) + " MB" : data.value(4)));

        QDomElement cellElement6 = doc.createElement("cell");
        rowElement.appendChild(cellElement6);
        cellElement6.appendChild(doc.createTextNode(isQuotaNumber(data.value(5)) ? data.value(5) + " MB" : data.value(5)));
        QDomElement cellElement7 = doc.createElement("cell");
        rowElement.appendChild(cellElement7);
        cellElement7.appendChild(doc.createTextNode(isQuotaNumber(data.value(6)) ? data.value(6) + " MB" : data.value(6)));
        QDomElement cellElement8 = doc.createElement("cell");
        rowElement.appendChild(cellElement8);
        cellElement8.appendChild(doc.createTextNode(isQuotaNumber(data.value(7)) ? data.value(7) + " MB" : data.value(7)));
        QDomElement cellElement9 = doc.createElement("cell");
        rowElement.appendChild(cellElement9);
        cellElement9.appendChild(doc.createTextNode(isQuotaNumber(data.value(8)) ? data.value(8) + " MB" : data.value(8)));

        rowElement.setAttribute("id", QString::number(i+1));
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));
    m_var = doc.toString();

}

void RenderResponseAccount::generateGetUserQuotaMaxSize() {
    QDomDocument doc;
//    QString paraName = m_pReq->allParameters().value("name").toString();
//    QString paraHdd = m_pReq->allParameters().value("hdd").toString();

    QStringList arg = QStringList() << "get_user_quota_maxsize" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR, arg, true);

    QDomElement root = doc.createElement("quota_info");
    doc.appendChild(root);
    QDomElement maxSizeElement = doc.createElement("max_size");
    root.appendChild(maxSizeElement);
    maxSizeElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAccount::generateGetGroupQuotaMinSize() {
    QDomDocument doc;
//    QString paraName = m_pReq->allParameters().value("name").toString();
//    QString paraHdd = m_pReq->allParameters().value("hdd").toString();

    QStringList arg = QStringList() << "get_group_quota_minsize" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR, arg, true);

    QDomElement root = doc.createElement("quota_info");
    doc.appendChild(root);
    QDomElement maxSizeElement = doc.createElement("max_size");
    root.appendChild(maxSizeElement);
    maxSizeElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAccount::generateSetQuotaOnOff() {
    QString paraOnoff = m_pReq->allParameters().value("onoff").toString();

    QStringList arg = QStringList() << "set_quota_onoff" << paraOnoff;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR, arg, true);
    m_var = "/web/account_mgr/quota.html";
}

