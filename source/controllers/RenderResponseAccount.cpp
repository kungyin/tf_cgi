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

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_CHANGE_ADMIN_PWD:
        generateChangeAdminPwd(doc);
        break;
    case CMD_GET_USER_LIST:
        generateGetUserList(doc);
        break;
    case CMD_GET_USER_INFO:
        generateGetUserInfo(doc);
        break;
    case CMD_GET_SMB_LIST:
        generateGetSmbList(doc);
        break;
    case CMD_USER_ADD:
        generateUserAdd(doc);
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
        generateWebdavAccountMerge(doc);
        break;
    case CMD_USER_BATCH_CREATE:
        generateUserBatchCreate();
        break;
    case CMD_GET_MODIFY_USER_INFO:
        generateGetModifyUserInfo(doc);
        break;
    case CMD_USER_MODIFY:
        generateUserModify(doc);
        break;
    case CMD_USER_DEL:
        generateUserDel();
        break;
    case CMD_MYFAVORITE_DEL_USER:
        generateMyFavDelUser(doc);
        break;
    case CMD_DWONLOAD_IMPORT_SAMPLE:
        generateDownloadImportSample(str);
        break;
    case CMD_GET_ALL_SESSION:
        generateGetAllSession(doc);
        break;
    case CMD_GET_IMPORT_USERS:
        generateGetImportUsers(doc);
        break;
    case CMD_ADDUSER_GET_USER_QUOTA_MAXSIZE:
        generateAddUserGetUserQuotaMaxsize(doc);
        break;
    case CMD_CREATE_IMPORT_USERS:
        generateCreateImportUsers();
        break;
    case CMD_GET_CREATE_STATUS:
        generateCreateStatus(doc);
        break;
    case CMD_GET_GROUP_LIST:
        generateGetGroupList(doc);
        break;
    case CMD_GET_GROUP_INFO:
        generateGetGroupInfo(doc);
        break;
    case CMD_GROUP_ADD:
        generateGroupAdd();
        break;
    case CMD_ADDGROUP_GET_GROUP_QUOTA_MINSIZE:
        generateAddGroupGetGroupQuotaMinsize(doc);
        break;
    case CMD_GROUP_SET_QUOTA:
        generateGroupSetQuota();
        break;
    case CMD_GET_MODIFY_GROUP_INFO:
        generateGetModifyGroupInfo(doc);
        break;
    case CMD_GROUP_MODIFY:
        generateGroupModify();
        break;
    case CMD_GROUP_DEL:
        generateGroupDel();
        break;
    case CMD_GET_QUOTA_INFO:
        generateGetQuotaInfo(doc);
        break;
    case CMD_GET_HD_MAPPING_INFO:
        generateGetHDMappingInfo(doc);
        break;
    case CMD_GET_USER_QUOTA_LIST:
        generateGetUserQuotaList(doc);
        break;
    case CMD_GET_GROUP_QUOTA_LIST:
        generateGetGroupQuotaList(doc);
        break;
    case CMD_GET_USER_QUOTA_MAXSIZE:
        generateGetUserQuotaMaxSize(doc);
        break;
    case CMD_GET_GROUP_QUOTA_MINSIZE:
        generateGetGroupQuotaMinSize(doc);
        break;
    case CMD_SET_QUOTA_ONOFF:
        generateSetQuotaOnOff();
        break;
    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

}

void RenderResponseAccount::generateChangeAdminPwd(QDomDocument &doc) {
    QString paraPwd = m_pReq->allParameters().value("pw").toString();
    QString paraOldPwd = m_pReq->allParameters().value("old_pw").toString();
    //QByteArray pwd = QByteArray::fromBase64(paraPwd.toLocal8Bit());
    //QByteArray oldPwd = QByteArray::fromBase64(paraOldPwd.toLocal8Bit());

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR + " admin " + paraOldPwd  + " " + paraPwd, true);

    QDomElement root = doc.createElement("modify_info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.isEmpty() ? "0" : apiOut.at(0)));
}

void RenderResponseAccount::generateGetUserList(QDomDocument &doc) {
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR + " userlist");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);
    for(int i=0; i < apiOut.size(); i++) {
        if(apiOut.at(i).isEmpty())
            continue;
//        if(apiOut.at(i).split(",").size() < 2)
//            continue;

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);

        for(int j=0; j < 2; j++) {
            QString content = apiOut.at(i).split(",").value(j);
            QDomElement cellElement1 = doc.createElement("cell");
            rowElement.appendChild(cellElement1);
            cellElement1.appendChild(doc.createTextNode(content));
        }

        rowElement.setAttribute("id", QString::number(i+1));
    }
    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));
}

void RenderResponseAccount::generateGetUserInfo(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR + " userinfo", true, ";");

    QDomElement root = doc.createElement("user_info");
    doc.appendChild(root);

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(apiOut.value(0)));

    QDomElement allUserElement = doc.createElement("all_user");
    root.appendChild(allUserElement);
    allUserElement.appendChild(doc.createTextNode(apiOut.value(1)));

    QDomElement allGroupElement = doc.createElement("all_group");
    root.appendChild(allGroupElement);
    allGroupElement.appendChild(doc.createTextNode(apiOut.value(2)));

    QDomElement hddNumElement = doc.createElement("hddnum");
    root.appendChild(hddNumElement);
    hddNumElement.appendChild(doc.createTextNode(apiOut.value(3)));

    QDomElement hddSizeElement = doc.createElement("hddsize");
    root.appendChild(hddSizeElement);
    hddSizeElement.appendChild(doc.createTextNode(apiOut.value(4)));

    QDomElement volumeNameElement1 = doc.createElement("v_name");
    root.appendChild(volumeNameElement1);
    volumeNameElement1.appendChild(doc.createTextNode(apiOut.value(5)));

    QDomElement volumeNameElement2 = doc.createElement("v_name");
    root.appendChild(volumeNameElement2);
    volumeNameElement2.appendChild(doc.createTextNode(apiOut.value(6)));
}

void RenderResponseAccount::generateGetSmbList(QDomDocument &doc) {
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR + " sharelist");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QString cellContent = "<input type=\"checkbox\" name=\"C_%1\" value=\"%2\" rel=\"%3\">";
    for(int i=0; i < apiOut.size(); i++) {

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        rowElement.setAttribute("id", QString::number(i+1));

        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(apiOut.at(i)));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createCDATASection(cellContent.arg(QString::number(i)).arg("r").arg(apiOut.value(i))));
        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createCDATASection(cellContent.arg(QString::number(i)).arg("w").arg(apiOut.value(i))));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createCDATASection(cellContent.arg(QString::number(i)).arg("d").arg(apiOut.value(i))));
    }
    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));
}

void RenderResponseAccount::generateUserAdd(QDomDocument &doc) {
    QString paraName = m_pReq->allParameters().value("name").toString();
    QString paraPw = m_pReq->allParameters().value("pw").toString();
    QString paraGroup = QUrl::fromPercentEncoding(m_pReq->allParameters().value("group").toByteArray()).remove("#");

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR +
                                      " add " + paraName + " " + paraPw + " " + paraGroup, true);
}

/* todo: restart specified service*/
void RenderResponseAccount::generateRestartService() {
    QString paraNfs = m_pReq->allParameters().value("nfs").toString();
    QString paraWebdav = m_pReq->allParameters().value("webdav").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_SERVICE_API + " restart", true);
}

void RenderResponseAccount::generateUserSetQuota() {
    QString paraName = m_pReq->allParameters().value("name").toString();
    QString paraAva1 = m_pReq->allParameters().value("available1").toString();
    QString paraAva2 = m_pReq->allParameters().value("available2").toString();
    QString paraAva3 = m_pReq->allParameters().value("available3").toString();
    QString paraAva4 = m_pReq->allParameters().value("available4").toString();

    if(paraAva1.compare("null") != 0)
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " userset " + paraName + " 1 " + paraAva1, true);
    if(paraAva2.compare("null") != 0)
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " userset " + paraName + " 2 " + paraAva2, true);
    if(paraAva1.compare("null") != 0)
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " userset " + paraName + " 3 " + paraAva3, true);
    if(paraAva1.compare("null") != 0)
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " userset " + paraName + " 4 " + paraAva4, true);
}

/* todo: ftp */
void RenderResponseAccount::generateAddUserToSession() {
    QString paraName = m_pReq->allParameters().value("s_name").toString();
    QString paraFtp = m_pReq->allParameters().value("ftp").toString();
    QString paraReadList = m_pReq->allParameters().value("read_list").toString();
    QString paraWriteList = m_pReq->allParameters().value("write_list").toString();
    QString paraDeclineList = m_pReq->allParameters().value("decline_list").toString();
    QString paraUsername = m_pReq->allParameters().value("username").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_SMB_API + " access "
                + paraName + " " + paraReadList + " " + paraWriteList + " " + paraDeclineList, true);
}

/* todo */
void RenderResponseAccount::generateCreateFtpLink() {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

void RenderResponseAccount::generateFtpService() {
    QString paraStart = m_pReq->allParameters().value("type").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API2 + " " + paraStart, true);
}

/* todo: need API */
/* For user, group and network share. */
void RenderResponseAccount::generateWebdavAccountMerge(QDomDocument &doc) {
    QString paraShareName = m_pReq->allParameters().value("f_share_name").toString();
    QString paraRw = m_pReq->allParameters().value("f_rw").toString();
    QString paraUser = m_pReq->allParameters().value("f_user").toString();
    QString paraWebdav = m_pReq->allParameters().value("webdav").toString();
    QString paraPath = m_pReq->allParameters().value("f_path").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
}

void RenderResponseAccount::generateUserBatchCreate() {
    QString paraPrefix = m_pReq->allParameters().value("f_prefix").toString();
    QString paraStart = m_pReq->allParameters().value("f_start").toString();
    QString paraNumber = m_pReq->allParameters().value("f_number").toString();
    QString paraBatchPw = m_pReq->allParameters().value("f_batch_pw").toString();
//    QString paraRList = m_pReq->allParameters().value("r_list").toString();
//    QString paraWList = m_pReq->allParameters().value("w_list").toString();
//    QString paraDList = m_pReq->allParameters().value("d_list").toString();
    QString paraGroupList = QUrl::fromPercentEncoding(m_pReq->allParameters().value("group_list").toByteArray()).replace(":", ",");
    QString paraApp = m_pReq->allParameters().value("app").toString();
    QString paraQuota = m_pReq->allParameters().value("quota").toString();
    QString paraOverWrite = m_pReq->allParameters().value("f_overwrite").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR +
                                      " multiadd " + paraPrefix + " " + paraStart + " " + paraNumber +
                                      " " + paraBatchPw + " " + paraGroupList + " " + paraOverWrite, true);

}

void RenderResponseAccount::generateGetModifyUserInfo(QDomDocument &doc) {
    QString paraName = m_pReq->allParameters().value("name").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR + " modinfo " + paraName, true, ";");
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
}

/* todo */
void RenderResponseAccount::generateUserModify(QDomDocument &doc) {
    QString paraName = m_pReq->allParameters().value("name").toString();
    QString paraPw = m_pReq->allParameters().value("pw").toString();
    QString paraFtp = m_pReq->allParameters().value("ftp").toString();
    QString paraGroup = m_pReq->allParameters().value("group").toString();
    QString paraAva1 = m_pReq->allParameters().value("available1").toString();
    QString paraAva2 = m_pReq->allParameters().value("available2").toString();
    QString paraAva3 = m_pReq->allParameters().value("available3").toString();
    QString paraAva4 = m_pReq->allParameters().value("available4").toString();
    QString paraReadList = m_pReq->allParameters().value("read_list").toString();
    QString paraWriteList = m_pReq->allParameters().value("write_list").toString();
    QString paraDeclineList = m_pReq->allParameters().value("decline_list").toString();
    QString paraUncheckList = m_pReq->allParameters().value("uncheck_list").toString();
    QString paraMPw = m_pReq->allParameters().value("m_pw").toString();
    QString paraMGroup = QUrl::fromPercentEncoding(m_pReq->allParameters().value("m_group").toByteArray()).remove("#");
    QString paraMQuota = m_pReq->allParameters().value("m_quota").toString();
    QString paraMShare = m_pReq->allParameters().value("m_share").toString();

//    QVector<QString> available;
//    if(paraAva1.compare("null") != 0)
//        available.insert("volume_1");
//    if(paraAva2.compare("null") != 0)
//        available.insert("volume_2");
//    if(paraAva3.compare("null") != 0)
//        available.insert("volume_3");
//    if(paraAva4.compare("null") != 0)
//        available.insert("volume_4");

    QStringList apiOutUser = getAPIStdOut(API_PATH + SCRIPT_USER_MGR +
                                      " modify " + paraName + " " + paraPw + " " + paraMGroup, true);
//    for(auto e : available) {
//        getAPIStdOut(API_PATH + SCRIPT_SMB_API + " access " + e + " " +
//                     paraPw + " " + paraMGroup, true);
//    }
    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOutUser.value(0)));
}

void RenderResponseAccount::generateUserDel() {
    QString paraName = QUrl::fromPercentEncoding(m_pReq->allParameters().value("name").toByteArray());
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR + " del " + paraName, true);
}

/* the same API ?? */
void RenderResponseAccount::generateMyFavDelUser(QDomDocument &doc) {
    QString paraUserList = m_pReq->allParameters().value("f_user_lst").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " del " + paraUserList, true);
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
}

/* todo */
void RenderResponseAccount::generateDownloadImportSample(QString &str) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_IMPORTUSER_API + " get");
    str = "import_file.txt";
    //sendfile()
}


void RenderResponseAccount::generateGetAllSession(QDomDocument &doc) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR + " session");
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
}

/* todo: need API */
void RenderResponseAccount::generateGetImportUsers(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement itemElement = doc.createElement("item");
    root.appendChild(itemElement);
    itemElement.appendChild(doc.createTextNode("staff3/staff3//Volume1///100"));

}

/* todo: need API */
void RenderResponseAccount::generateAddUserGetUserQuotaMaxsize(QDomDocument &doc) {
    QString paraName = m_pReq->allParameters().value("name").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    QDomElement root = doc.createElement("quota_info");
    doc.appendChild(root);
    QDomElement maxSizeElement = doc.createElement("max_size");
    root.appendChild(maxSizeElement);
    maxSizeElement.appendChild(doc.createTextNode("0:0:0:0"));
}

/* todo: need API */
void RenderResponseAccount::generateCreateImportUsers() {
    QString paraApp = m_pReq->allParameters().value("app").toString();
    QString paraOverwrite = m_pReq->allParameters().value("overwrite").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseAccount::generateCreateStatus(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode("1"));
}

/* todo: need API */
void RenderResponseAccount::generateGetGroupList(QDomDocument &doc) {
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

//    for(int i=0; i < apiOut.size(); i++) {
//        if(apiOut.at(i).isEmpty())
//            continue;
//        if(apiOut.at(i).split(",").size() < 2)
//            continue;

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        //cellElement1.appendChild(doc.createTextNode(apiOut.at(i).split(",").at(0)));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        //cellElement2.appendChild(doc.createTextNode(apiOut.at(i).split(",").at(1)));

        //rowElement.setAttribute("id", QString::number(i+1));
    //}

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("0"));

}


/* todo: need API */
void RenderResponseAccount::generateGetGroupInfo(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("group_info");
    doc.appendChild(root);

    QDomElement vnameElement1 = doc.createElement("v_name");
    root.appendChild(vnameElement1);
    vnameElement1.appendChild(doc.createTextNode("Volume_1"));
    QDomElement vnameElement2 = doc.createElement("v_name");
    root.appendChild(vnameElement2);
    vnameElement2.appendChild(doc.createTextNode("Volume_2"));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("0"));
    QDomElement allUserElement = doc.createElement("all_user");
    root.appendChild(allUserElement);
    QDomElement allGroupElement = doc.createElement("all_group");
    root.appendChild(allGroupElement);
    QDomElement hddnumElement = doc.createElement("hddnum");
    root.appendChild(hddnumElement);
    hddnumElement.appendChild(doc.createTextNode("2"));
    QDomElement hddSizeElement = doc.createElement("hddsize");
    root.appendChild(hddSizeElement);
    hddSizeElement.appendChild(doc.createTextNode("2814059,1875257"));
}

/* todo: need API */
void RenderResponseAccount::generateGroupAdd() {
    QString paraGroup = m_pReq->allParameters().value("group").toString();
    QString paraMember = m_pReq->allParameters().value("member").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}


/* todo: need API */
void RenderResponseAccount::generateAddGroupGetGroupQuotaMinsize(QDomDocument &doc) {
    QString paraName = m_pReq->allParameters().value("name").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("group_info");
    doc.appendChild(root);

    QDomElement memberElement = doc.createElement("member");
    root.appendChild(memberElement);
    QDomElement minSizeElement = doc.createElement("min_size");
    root.appendChild(minSizeElement);
    minSizeElement.appendChild(doc.createTextNode("102400:0:0:0"));
}

void RenderResponseAccount::generateGroupSetQuota() {
    QString paraName = m_pReq->allParameters().value("name").toString();
    QString paraAva1 = m_pReq->allParameters().value("available1").toString();
    QString paraAva2 = m_pReq->allParameters().value("available2").toString();
    QString paraAva3 = m_pReq->allParameters().value("available3").toString();
    QString paraAva4 = m_pReq->allParameters().value("available4").toString();
    if(paraAva1.compare("null") != 0)
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " groupset " + paraName + " 1 " + paraAva1, true);
    if(paraAva2.compare("null") != 0)
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " groupset " + paraName + " 2 " + paraAva2, true);
    if(paraAva1.compare("null") != 0)
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " groupset " + paraName + " 3 " + paraAva3, true);
    if(paraAva1.compare("null") != 0)
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " groupset " + paraName + " 4 " + paraAva4, true);
}

/* todo: need API */
void RenderResponseAccount::generateGetModifyGroupInfo(QDomDocument &doc) {
    QString paraGroup = m_pReq->allParameters().value("group").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("group_info");
    doc.appendChild(root);

    QDomElement memberElement = doc.createElement("member");
    root.appendChild(memberElement);
    QDomElement hddnumElement = doc.createElement("hddnum");
    root.appendChild(hddnumElement);
    hddnumElement.appendChild(doc.createTextNode("2"));
    QDomElement hddsizeElement = doc.createElement("hddsize");
    root.appendChild(hddsizeElement);
    hddsizeElement.appendChild(doc.createTextNode("2814059,1875257"));


    //for
    QDomElement quotaElement1 = doc.createElement("quota");
    root.appendChild(quotaElement1);
    QDomElement vnameElement1 = doc.createElement("v_name");
    quotaElement1.appendChild(vnameElement1);
    vnameElement1.appendChild(doc.createTextNode("Volume_1"));
    QDomElement sizeElement = doc.createElement("size");
    quotaElement1.appendChild(sizeElement);
    sizeElement.appendChild(doc.createTextNode("0"));


    QDomElement smbInfoElement = doc.createElement("smb_info");
    root.appendChild(smbInfoElement);
    //for
    QDomElement itemElement = doc.createElement("item");
    smbInfoElement.appendChild(itemElement);
    QDomElement shareNameElement = doc.createElement("share_name");
    itemElement.appendChild(shareNameElement);
    shareNameElement.appendChild(doc.createTextNode("Volume_2"));
    QDomElement privilegesElement = doc.createElement("privileges");
    itemElement.appendChild(privilegesElement);
    privilegesElement.appendChild(doc.createTextNode("w"));

    QDomElement ftpElement = doc.createElement("ftp");
    root.appendChild(ftpElement);
    ftpElement.appendChild(doc.createTextNode("1"));

    QDomElement webdavInfoElement = doc.createElement("webdav_info");
    root.appendChild(webdavInfoElement);
    //for
//    QDomElement itemElement = doc.createElement("item");
//    webdavInfoElement.appendChild(itemElement);
//    itemElement.appendChild(doc.createTextNode("Volume_1:RO"));

}


/* todo: need API */
void RenderResponseAccount::generateGroupModify() {
    QString paraGroup = m_pReq->allParameters().value("group").toString();
    QString paraAva1 = m_pReq->allParameters().value("available1").toString();
    QString paraAva2 = m_pReq->allParameters().value("available2").toString();
    QString paraAva3 = m_pReq->allParameters().value("available3").toString();
    QString paraAva4 = m_pReq->allParameters().value("available4").toString();
    QString paraReadList = m_pReq->allParameters().value("read_list").toString();
    QString paraWriteList = m_pReq->allParameters().value("write_list").toString();
    QString paraDeclineList = m_pReq->allParameters().value("decline_list").toString();
    QString paraUncheckList = m_pReq->allParameters().value("uncheck_list").toString();
    QString paraFtp = m_pReq->allParameters().value("ftp").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseAccount::generateGroupDel() {
    QString paraGroup = m_pReq->allParameters().value("group").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

void RenderResponseAccount::generateGetQuotaInfo(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " quotainfo", true, ";");

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
}


void RenderResponseAccount::generateGetHDMappingInfo(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " remoteinfo", true, ";");

    QDomElement root = doc.createElement("mapping_info");
    doc.appendChild(root);

    for(auto e : apiOut) {
        QDomElement itemElement = doc.createElement("item");
        root.appendChild(itemElement);
        QDomElement dataElement = doc.createElement("data");
        itemElement.appendChild(dataElement);
        dataElement.appendChild(doc.createTextNode(e));
    }
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

void RenderResponseAccount::generateGetUserQuotaList(QDomDocument &doc) {
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qyupe").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " userlist", false, ";");

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

}

void RenderResponseAccount::generateGetGroupQuotaList(QDomDocument &doc) {
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qyupe").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " grouplist", false, ";");

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

}

void RenderResponseAccount::generateGetUserQuotaMaxSize(QDomDocument &doc) {
    QString paraName = m_pReq->allParameters().value("name").toString();
    QString paraHdd = m_pReq->allParameters().value("hdd").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " usersize " + paraName + " " + paraHdd, true);

    QDomElement root = doc.createElement("quota_info");
    doc.appendChild(root);
    QDomElement maxSizeElement = doc.createElement("max_size");
    root.appendChild(maxSizeElement);
    maxSizeElement.appendChild(doc.createTextNode(apiOut.value(0)));

}

void RenderResponseAccount::generateGetGroupQuotaMinSize(QDomDocument &doc) {
    QString paraName = m_pReq->allParameters().value("name").toString();
    QString paraHdd = m_pReq->allParameters().value("hdd").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " groupsize " + paraName + " " + paraHdd, true);

    QDomElement root = doc.createElement("quota_info");
    doc.appendChild(root);
    QDomElement maxSizeElement = doc.createElement("max_size");
    root.appendChild(maxSizeElement);
    maxSizeElement.appendChild(doc.createTextNode(apiOut.value(0)));

}

void RenderResponseAccount::generateSetQuotaOnOff() {
    QString paraOnoff = m_pReq->allParameters().value("onoff").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR + " enable " + paraOnoff, true);
}

