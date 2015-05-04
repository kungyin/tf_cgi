#include "RenderResponseAccount.h"
#include "AppDefine.h"

RenderResponseAccount::RenderResponseAccount(QVariantMap &map, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_renderType = RENDER_TYPE_UNKNOWN;
    m_pMap = &map;
}

RenderResponseAccount::~RenderResponseAccount() {
}

RENDER_TYPE RenderResponseAccount::preRender() {

    if(!m_pMap)
        return RENDER_TYPE_UNKNOWN;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_CHANGE_ADMIN_PWD:
        generateChangeAdminPwd(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_USER_LIST:
        generateGetUserList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_USER_INFO:
        generateGetUserInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_SMB_LIST:
        generateGetSmbList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_USER_ADD:
        generateUserAdd(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_RESTART_SERVICE:
        generateRestartService();
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_USER_SET_QUOTA:
        generateUserSetQuota();
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_ADDUSER_TO_SESSION:
        generateAddUserToSession();
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_CREATE_FTP_LINK:
        generateCreateFtpLink();
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_FTP_SERVICE:
        generateFtpService();
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_WEBDAV_ACCOUNT_MERGE:
        generateWebdavAccountMerge(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_USER_BATCH_CREATE:
        generateUserBatchCreate();
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_GET_MODIFY_USER_INFO:
        generateGetModifyUserInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_USER_MODIFY:
        generateUserModify(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_USER_DEL:
        generateUserDel();
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_MYFAVORITE_DEL_USER:
        generateMyFavDelUser(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_DWONLOAD_IMPORT_SAMPLE:
        generateDownloadImportSample();
        //m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_ALL_SESSION:
        generateGetAllSession(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_IMPORT_USERS:
        generateGetImportUsers(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_ADDUSER_GET_USER_QUOTA_MAXSIZE:
        generateAddUserGetUserQuotaMaxsize(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_CREATE_IMPORT_USERS:
        generateCreateImportUsers();
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_GET_CREATE_STATUS:
        generateCreateStatus(doc);
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_GET_GROUP_LIST:
        generateGetGroupList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_GROUP_INFO:
        generateGetGroupInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GROUP_ADD:
        generateGroupAdd();
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_ADDGROUP_GET_GROUP_QUOTA_MINSIZE:
        generateAddGroupGetGroupQuotaMinsize(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GROUP_SET_QUOTA:
        generateGroupSetQuota();
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_GET_MODIFY_GROUP_INFO:
        generateGetModifyGroupInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GROUP_MODIFY:
        generateGroupModify();
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_GROUP_DEL:
        generateGroupDel();
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_GET_QUOTA_INFO:
        generateGetQuotaInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_HD_MAPPING_INFO:
        generateGetHDMappingInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_USER_QUOTA_LIST:
        generateGetUserQuotaList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_GROUP_QUOTA_LIST:
        generateGetGroupQuotaList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_USER_QUOTA_MAXSIZE:
        generateGetUserQuotaMaxSize(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_GROUP_QUOTA_MINSIZE:
        generateGetGroupQuotaMinSize(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SET_QUOTA_ONOFF:
        generateSetQuotaOnOff();
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;

    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

    return m_renderType;
}

void RenderResponseAccount::generateChangeAdminPwd(QDomDocument &doc) {
    QString paraPwd = m_pMap->value("pw").toString();
    QString paraOldPwd = m_pMap->value("old_pw").toString();
    //QByteArray pwd = QByteArray::fromBase64(paraPwd.toLocal8Bit());
    //QByteArray oldPwd = QByteArray::fromBase64(paraOldPwd.toLocal8Bit());

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR + " admin " + paraOldPwd  + " " + paraPwd, true);

    QDomElement root = doc.createElement("modify_info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.isEmpty() ? "0" : apiOut.at(0)));
}

/* todo: need API */
void RenderResponseAccount::generateGetUserList(QDomDocument &doc) {
    QString paraPage = m_pMap->value("page").toString();
    QString paraRp = m_pMap->value("rp").toString();
    QString paraQuery = m_pMap->value("query").toString();
    QString paraQType = m_pMap->value("qtype").toString();
    QString paraField = m_pMap->value("f_field").toString();
    QString paraUser = m_pMap->value("user").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -g get_user_list");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);
    for(int i=0; i < apiOut.size(); i++) {
        if(apiOut.at(i).isEmpty())
            continue;
        if(apiOut.at(i).split(",").size() < 2)
            continue;

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(apiOut.at(i).split(",").at(0)));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode(apiOut.at(i).split(",").at(1)));

        rowElement.setAttribute("id", QString::number(i+1));
    }
    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));
}

/* todo: need API */
void RenderResponseAccount::generateGetUserInfo(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -g get_user_info");

    QDomElement root = doc.createElement("user_info");
    doc.appendChild(root);

    QSet<QString> groupSet;
    for(int i=0; i < apiOut.size(); i++) {
        if(apiOut.at(i).isEmpty())
            continue;
        if(apiOut.at(i).split(",").size() < 2)
            continue;

        groupSet.insert(apiOut.at(i).split(",").at(1));
    }
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

    QDomElement allUserElement = doc.createElement("all_user");
    root.appendChild(allUserElement);
    allUserElement.appendChild(doc.createTextNode("jerry#bnbbb#test1#adb#josen"));

    QDomElement allGroupElement = doc.createElement("all_group");
    root.appendChild(allGroupElement);
    allGroupElement.appendChild(doc.createTextNode("group1"));

    QDomElement hddNumElement = doc.createElement("hddnum");
    root.appendChild(hddNumElement);
    hddNumElement.appendChild(doc.createTextNode("2"));

    QDomElement hddSizeElement = doc.createElement("hddsize");
    root.appendChild(hddSizeElement);
    hddSizeElement.appendChild(doc.createTextNode("1997,4726642"));

    QDomElement volumeNameElement1 = doc.createElement("v_name");
    root.appendChild(volumeNameElement1);
    volumeNameElement1.appendChild(doc.createTextNode("Volume_1"));

    QDomElement volumeNameElement2 = doc.createElement("v_name");
    root.appendChild(volumeNameElement2);
    volumeNameElement2.appendChild(doc.createTextNode("Volume_2"));
}

/* todo: need API */
void RenderResponseAccount::generateGetSmbList(QDomDocument &doc) {
    QString paraPage = m_pMap->value("page").toString();
    QString paraRp = m_pMap->value("rp").toString();
    QString paraQuery = m_pMap->value("query").toString();
    QString paraQType = m_pMap->value("qtype").toString();
    QString paraField = m_pMap->value("f_field").toString();
    QString paraUser = m_pMap->value("user").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -g get_smb_list", true);

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QString cellContent = "&lt;input type=&quot;checkbox&quot; name=&quot;C_%1\
                            &quot; value=&quot;%2&quot; rel=&quot;%3&quot;&gt;";
    if(!apiOut.isEmpty()) {
        for(int i=0; i < apiOut.size(); i++) {
            if(apiOut.at(i).isEmpty())
                continue;
            QDomElement rowElement = doc.createElement("row");
            root.appendChild(rowElement);
            rowElement.setAttribute("id", QString::number(i+1));

            QDomElement cellElement1 = doc.createElement("cell");
            rowElement.appendChild(cellElement1);
            cellElement1.appendChild(doc.createTextNode(apiOut.at(i)));
            QDomElement cellElement2 = doc.createElement("cell");
            rowElement.appendChild(cellElement2);
            cellElement2.appendChild(doc.createTextNode(cellContent.arg(QString::number(i)).arg("r").arg(apiOut.at(i))));
            QDomElement cellElement3 = doc.createElement("cell");
            rowElement.appendChild(cellElement3);
            cellElement3.appendChild(doc.createTextNode(cellContent.arg(QString::number(i)).arg("w").arg(apiOut.at(i))));
            QDomElement cellElement4 = doc.createElement("cell");
            rowElement.appendChild(cellElement4);
            cellElement4.appendChild(doc.createTextNode(cellContent.arg(QString::number(i)).arg("d").arg(apiOut.at(i))));
        }
    }
    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));
}

/* todo: need API */
void RenderResponseAccount::generateUserAdd(QDomDocument &doc) {
    QString paraName = m_pMap->value("name").toString();
    QString paraPw = m_pMap->value("pw").toString();
    QString paraGroup = m_pMap->value("group").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QString cellContent = "&lt;input type=&quot;checkbox&quot; name=&quot;C_%1\
                            &quot; value=&quot;%2&quot; rel=&quot;%3&quot;&gt;";
    if(!apiOut.isEmpty()) {
        //for(int i=0; i < apiOut.size(); i++) {
            if(!apiOut.at(0).isEmpty()) {
                QDomElement rowElement = doc.createElement("row");
                root.appendChild(rowElement);
                rowElement.setAttribute("id", "1");

                QDomElement cellElement1 = doc.createElement("cell");
                rowElement.appendChild(cellElement1);
                cellElement1.appendChild(doc.createTextNode(apiOut.at(0)));
                QDomElement cellElement2 = doc.createElement("cell");
                rowElement.appendChild(cellElement2);
                cellElement2.appendChild(doc.createTextNode(cellContent.arg("0").arg("r").arg(apiOut.at(0))));
                QDomElement cellElement3 = doc.createElement("cell");
                rowElement.appendChild(cellElement3);
                cellElement3.appendChild(doc.createTextNode(cellContent.arg("0").arg("w").arg(apiOut.at(0))));
                QDomElement cellElement4 = doc.createElement("cell");
                rowElement.appendChild(cellElement4);
                cellElement4.appendChild(doc.createTextNode(cellContent.arg("0").arg("d").arg(apiOut.at(0))));
            }
        //}
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));
}

/* todo */
void RenderResponseAccount::generateRestartService() {
    QString paraNfs = m_pMap->value("nfs").toString();
    QString paraWebdav = m_pMap->value("webdav").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseAccount::generateUserSetQuota() {
    QString paraName = m_pMap->value("name").toString();
    QString paraAva1 = m_pMap->value("available1").toString();
    QString paraAva2 = m_pMap->value("available2").toString();
    QString paraAva3 = m_pMap->value("available3").toString();
    QString paraAva4 = m_pMap->value("available4").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseAccount::generateAddUserToSession() {
    QString paraName = m_pMap->value("s_name").toString();
    QString paraFtp = m_pMap->value("ftp").toString();
    QString paraReadList = m_pMap->value("read_list").toString();
    QString paraWriteList = m_pMap->value("write_list").toString();
    QString paraDeclineList = m_pMap->value("decline_list").toString();
    QString paraUsername = m_pMap->value("username").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo */
void RenderResponseAccount::generateCreateFtpLink() {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseAccount::generateFtpService() {
    QString paraStart = m_pMap->value("type").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseAccount::generateWebdavAccountMerge(QDomDocument &doc) {
    QString paraShareName = m_pMap->value("f_share_name").toString();
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
void RenderResponseAccount::generateUserBatchCreate() {
    QString paraPrefix = m_pMap->value("f_prefix").toString();
    QString paraStart = m_pMap->value("f_start").toString();
    QString paraNumber = m_pMap->value("f_number").toString();
    QString paraBatchPw = m_pMap->value("f_batch_pw").toString();
    QString paraRList = m_pMap->value("r_list").toString();
    QString paraWList = m_pMap->value("w_list").toString();
    QString paraDList = m_pMap->value("d_list").toString();
    QString paraGroupList = m_pMap->value("group_list").toString();
    QString paraApp = m_pMap->value("app").toString();
    QString paraQuota = m_pMap->value("quota").toString();
    QString paraOverWrite = m_pMap->value("f_overwrite").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

}

/* todo: need API */
void RenderResponseAccount::generateGetModifyUserInfo(QDomDocument &doc) {
    QString paraName = m_pMap->value("name").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    QDomElement root = doc.createElement("user_info");
    doc.appendChild(root);

    QDomElement quotaInfoElement1 = doc.createElement("quota_info");
    root.appendChild(quotaInfoElement1);
    QDomElement vnameElement = doc.createElement("v_name");
    quotaInfoElement1.appendChild(vnameElement);
    vnameElement.appendChild(doc.createTextNode("Volume_1"));
    QDomElement quotaElement = doc.createElement("quota");
    quotaInfoElement1.appendChild(quotaElement);
    quotaElement.appendChild(doc.createTextNode("0"));
    QDomElement maxQuotaElement = doc.createElement("max_quota");
    quotaInfoElement1.appendChild(maxQuotaElement);
    maxQuotaElement.appendChild(doc.createTextNode("1977"));

    QDomElement groupElement = doc.createElement("group");
    root.appendChild(groupElement);

    QDomElement hddnumElement = doc.createElement("hddnum");
    root.appendChild(hddnumElement);
    hddnumElement.appendChild(doc.createTextNode("1"));

    QDomElement hddsizeElement = doc.createElement("hddsize");
    root.appendChild(hddsizeElement);
    hddsizeElement.appendChild(doc.createTextNode("1977"));

    QDomElement mainGroupElement = doc.createElement("main_group");
    root.appendChild(mainGroupElement);
    mainGroupElement.appendChild(doc.createTextNode("allaccount"));

    QDomElement quotaInfoElement2 = doc.createElement("quota_info");
    root.appendChild(quotaInfoElement2);
    QDomElement itemElement = doc.createElement("item");
    quotaInfoElement2.appendChild(itemElement);
    QDomElement shareNameElement = doc.createElement("share_name");
    itemElement.appendChild(shareNameElement);
    shareNameElement.appendChild(doc.createTextNode("Volume_1"));
    QDomElement privilegesElement = doc.createElement("privileges");
    itemElement.appendChild(privilegesElement);
    privilegesElement.appendChild(doc.createTextNode("w"));

    QDomElement ftpElement = doc.createElement("ftp");
    root.appendChild(ftpElement);
    ftpElement.appendChild(doc.createTextNode("1"));
    QDomElement webdavInfoElement = doc.createElement("webdav_info");
    itemElement.appendChild(webdavInfoElement);
    //webdavInfoElement.appendChild(doc.createTextNode(""));
}

/* todo: need API */
void RenderResponseAccount::generateUserModify(QDomDocument &doc) {
    QString paraName = m_pMap->value("name").toString();
    QString paraPw = m_pMap->value("pw").toString();
    QString paraFtp = m_pMap->value("ftp").toString();
    QString paraGroup = m_pMap->value("group").toString();
    QString paraAva1 = m_pMap->value("available1").toString();
    QString paraAva2 = m_pMap->value("available2").toString();
    QString paraAva3 = m_pMap->value("available3").toString();
    QString paraAva4 = m_pMap->value("available4").toString();
    QString paraReadList = m_pMap->value("read_list").toString();
    QString paraWriteList = m_pMap->value("write_list").toString();
    QString paraDeclineList = m_pMap->value("decline_list").toString();
    QString paraUncheckList = m_pMap->value("uncheck_list").toString();
    QString paraMPw = m_pMap->value("m_pw").toString();
    QString paraMGroup = m_pMap->value("m_group").toString();
    QString paraMQuota = m_pMap->value("m_quota").toString();
    QString paraMShare = m_pMap->value("m_share").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode("1"));
}

/* todo: need API */
void RenderResponseAccount::generateUserDel() {
    QString paraName = m_pMap->value("name").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseAccount::generateMyFavDelUser(QDomDocument &doc) {
    QString paraUserList = m_pMap->value("f_user_lst").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
}

/* todo: need API */
void RenderResponseAccount::generateDownloadImportSample() {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    //sendfile()
}


/* todo: need API */
void RenderResponseAccount::generateGetAllSession(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    QDomElement root = doc.createElement("session");
    doc.appendChild(root);
    //for
    QDomElement shareElement = doc.createElement("share");
    root.appendChild(shareElement);
    QDomElement nameElement = doc.createElement("name");
    shareElement.appendChild(nameElement);
    nameElement.appendChild(doc.createTextNode("Volume_1"));
    QDomElement pathElement = doc.createElement("path");
    shareElement.appendChild(pathElement);
    pathElement.appendChild(doc.createTextNode("/mnt/HD/HD_a2"));

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
    QString paraName = m_pMap->value("name").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
    QDomElement root = doc.createElement("quota_info");
    doc.appendChild(root);
    QDomElement maxSizeElement = doc.createElement("max_size");
    root.appendChild(maxSizeElement);
    maxSizeElement.appendChild(doc.createTextNode("0:0:0:0"));
}

/* todo: need API */
void RenderResponseAccount::generateCreateImportUsers() {
    QString paraApp = m_pMap->value("app").toString();
    QString paraOverwrite = m_pMap->value("overwrite").toString();
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
    QString paraPage = m_pMap->value("page").toString();
    QString paraRp = m_pMap->value("rp").toString();
    QString paraQuery = m_pMap->value("query").toString();
    QString paraQType = m_pMap->value("qtype").toString();
    QString paraField = m_pMap->value("f_field").toString();
    QString paraUser = m_pMap->value("user").toString();

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
    QString paraGroup = m_pMap->value("group").toString();
    QString paraMember = m_pMap->value("member").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}


/* todo: need API */
void RenderResponseAccount::generateAddGroupGetGroupQuotaMinsize(QDomDocument &doc) {
    QString paraName = m_pMap->value("name").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("group_info");
    doc.appendChild(root);

    QDomElement memberElement = doc.createElement("member");
    root.appendChild(memberElement);
    QDomElement minSizeElement = doc.createElement("min_size");
    root.appendChild(minSizeElement);
    minSizeElement.appendChild(doc.createTextNode("102400:0:0:0"));
}

/* todo: need API */
void RenderResponseAccount::generateGroupSetQuota() {
    QString paraName = m_pMap->value("name").toString();
    QString paraAva1 = m_pMap->value("available1").toString();
    QString paraAva2 = m_pMap->value("available2").toString();
    QString paraAva3 = m_pMap->value("available3").toString();
    QString paraAva4 = m_pMap->value("available4").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseAccount::generateGetModifyGroupInfo(QDomDocument &doc) {
    QString paraGroup = m_pMap->value("group").toString();
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
    QString paraGroup = m_pMap->value("group").toString();
    QString paraAva1 = m_pMap->value("available1").toString();
    QString paraAva2 = m_pMap->value("available2").toString();
    QString paraAva3 = m_pMap->value("available3").toString();
    QString paraAva4 = m_pMap->value("available4").toString();
    QString paraReadList = m_pMap->value("read_list").toString();
    QString paraWriteList = m_pMap->value("write_list").toString();
    QString paraDeclineList = m_pMap->value("decline_list").toString();
    QString paraUncheckList = m_pMap->value("uncheck_list").toString();
    QString paraFtp = m_pMap->value("ftp").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseAccount::generateGroupDel() {
    QString paraGroup = m_pMap->value("group").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseAccount::generateGetQuotaInfo(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("quota_info");
    doc.appendChild(root);

    QDomElement hddNumElement = doc.createElement("hddnum");
    root.appendChild(hddNumElement);
    hddNumElement.appendChild(doc.createTextNode("2"));
    QDomElement hddSizeElement = doc.createElement("hddsize");
    root.appendChild(hddSizeElement);
    hddSizeElement.appendChild(doc.createTextNode("2814059,1875257"));
    QDomElement userNumElement = doc.createElement("usernum");
    root.appendChild(userNumElement);
    userNumElement.appendChild(doc.createTextNode("2"));
    QDomElement groupNumElement = doc.createElement("groupnum");
    root.appendChild(groupNumElement);
    groupNumElement.appendChild(doc.createTextNode("1"));
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode("1"));
    QDomElement vnameElement = doc.createElement("v_name");
    root.appendChild(vnameElement);
    vnameElement.appendChild(doc.createTextNode("Volume_1:Volume_2"));
}

/* todo: need API */
void RenderResponseAccount::generateGetHDMappingInfo(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("mapping_info");
    doc.appendChild(root);

    //for
    QDomElement itemElement = doc.createElement("item");
    root.appendChild(itemElement);
    QDomElement dataElement = doc.createElement("data");
    root.appendChild(dataElement);
    dataElement.appendChild(doc.createTextNode("Volume_1:/mnt/HD/HD_a2"));

}

/* todo: need API */
void RenderResponseAccount::generateGetUserQuotaList(QDomDocument &doc) {
    QString paraPage = m_pMap->value("page").toString();
    QString paraRp = m_pMap->value("rp").toString();
    QString paraQuery = m_pMap->value("query").toString();
    QString paraQType = m_pMap->value("qyupe").toString();
    QString paraField = m_pMap->value("f_field").toString();
    QString paraUser = m_pMap->value("user").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

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
        cellElement1.appendChild(doc.createTextNode("test"));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode("0 MB"));

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode("Unlimited"));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createTextNode("0 MB"));
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createTextNode("Unlimited"));

        QDomElement cellElement6 = doc.createElement("cell");
        rowElement.appendChild(cellElement6);
        cellElement6.appendChild(doc.createTextNode("-"));
        QDomElement cellElement7 = doc.createElement("cell");
        rowElement.appendChild(cellElement7);
        cellElement7.appendChild(doc.createTextNode("-"));
        QDomElement cellElement8 = doc.createElement("cell");
        rowElement.appendChild(cellElement8);
        cellElement8.appendChild(doc.createTextNode("-"));
        QDomElement cellElement9 = doc.createElement("cell");
        rowElement.appendChild(cellElement9);
        cellElement9.appendChild(doc.createTextNode("-"));

        rowElement.setAttribute("id", "1");
    //}

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("1"));

}

/* todo: need API */
void RenderResponseAccount::generateGetGroupQuotaList(QDomDocument &doc) {
    QString paraPage = m_pMap->value("page").toString();
    QString paraRp = m_pMap->value("rp").toString();
    QString paraQuery = m_pMap->value("query").toString();
    QString paraQType = m_pMap->value("qyupe").toString();
    QString paraField = m_pMap->value("f_field").toString();
    QString paraUser = m_pMap->value("user").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

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
        cellElement1.appendChild(doc.createTextNode("staff"));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode("0 MB"));

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode("100 MB"));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createTextNode("0 MB"));
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createTextNode("Unlimited"));

        QDomElement cellElement6 = doc.createElement("cell");
        rowElement.appendChild(cellElement6);
        cellElement6.appendChild(doc.createTextNode("-"));
        QDomElement cellElement7 = doc.createElement("cell");
        rowElement.appendChild(cellElement7);
        cellElement7.appendChild(doc.createTextNode("-"));
        QDomElement cellElement8 = doc.createElement("cell");
        rowElement.appendChild(cellElement8);
        cellElement8.appendChild(doc.createTextNode("-"));
        QDomElement cellElement9 = doc.createElement("cell");
        rowElement.appendChild(cellElement9);
        cellElement9.appendChild(doc.createTextNode("-"));

        rowElement.setAttribute("id", "1");
    //}

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("1"));

}

/* todo: need API */
void RenderResponseAccount::generateGetUserQuotaMaxSize(QDomDocument &doc) {
    QString paraName = m_pMap->value("name").toString();
    QString paraHdd = m_pMap->value("hdd").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("quota_info");
    doc.appendChild(root);
    QDomElement maxSizeElement = doc.createElement("max_size");
    root.appendChild(maxSizeElement);
    maxSizeElement.appendChild(doc.createTextNode("102400"));

}

/* todo: need API */
void RenderResponseAccount::generateGetGroupQuotaMinSize(QDomDocument &doc) {
    QString paraName = m_pMap->value("name").toString();
    QString paraHdd = m_pMap->value("hdd").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("quota_info");
    doc.appendChild(root);
    QDomElement maxSizeElement = doc.createElement("max_size");
    //min_size??
    root.appendChild(maxSizeElement);
    maxSizeElement.appendChild(doc.createTextNode("102400"));

}

/* todo: need API */
void RenderResponseAccount::generateSetQuotaOnOff() {
    QString paraOnoff = m_pMap->value("onoff").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}
