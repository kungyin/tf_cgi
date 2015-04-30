#include "RenderResponseGroup.h"
#include "AppDefine.h"

RenderResponseGroup::RenderResponseGroup(QVariantMap &map, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_renderType = RENDER_TYPE_UNKNOWN;
    m_pMap = &map;
}

RenderResponseGroup::~RenderResponseGroup() {
}

RENDER_TYPE RenderResponseGroup::preRender() {

    if(!m_pMap)
        return RENDER_TYPE_UNKNOWN;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
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
    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

    return m_renderType;
}


/* todo: need API */
void RenderResponseGroup::generateGetGroupList(QDomDocument &doc) {
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
void RenderResponseGroup::generateGetGroupInfo(QDomDocument &doc) {
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
void RenderResponseGroup::generateGroupAdd() {
    QString paraGroup = m_pMap->value("group").toString();
    QString paraMember = m_pMap->value("member").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}


/* todo: need API */
void RenderResponseGroup::generateAddGroupGetGroupQuotaMinsize(QDomDocument &doc) {
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
void RenderResponseGroup::generateGroupSetQuota() {
    QString paraName = m_pMap->value("name").toString();
    QString paraAva1 = m_pMap->value("available1").toString();
    QString paraAva2 = m_pMap->value("available2").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

/* todo: need API */
void RenderResponseGroup::generateGetModifyGroupInfo(QDomDocument &doc) {
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
void RenderResponseGroup::generateGroupModify() {
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
void RenderResponseGroup::generateGroupDel() {
    QString paraGroup = m_pMap->value("group").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);
}

