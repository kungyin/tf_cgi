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
    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

    return m_renderType;
}

/* todo: need API */
void RenderResponseAccount::generateChangeAdminPwd(QDomDocument &doc) {
    QString paraPwd = m_pMap->value("pw").toString();
    QString paraOldPwd = m_pMap->value("old_pw").toString();
    QByteArray pwd = QByteArray::fromBase64(paraPwd.toLocal8Bit());
    QByteArray oldPwd = QByteArray::fromBase64(paraOldPwd.toLocal8Bit());

    QDomElement root = doc.createElement("modify_info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode("0"));
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
    QDomElement pageElement = doc.createElement("total");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

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
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseAccount::generateUserSetQuota() {
    QString paraName = m_pMap->value("name").toString();
    QString paraAva1 = m_pMap->value("available1").toString();
    QString paraAva2 = m_pMap->value("available2").toString();

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

