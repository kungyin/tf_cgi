#include "RenderResponseAppMngm.h"
#include "AppDefine.h"

RenderResponseAppMngm::RenderResponseAppMngm(QVariantMap &map, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_renderType = RENDER_TYPE_UNKNOWN;
    m_pMap = &map;
}

RenderResponseAppMngm::~RenderResponseAppMngm() {
}

RENDER_TYPE RenderResponseAppMngm::preRender() {

    if(!m_pMap)
        return RENDER_TYPE_UNKNOWN;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_SET_AFP:
        generateSetAfp();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_NFS_ENABLE:
        generateNfsEnable(doc);
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

void RenderResponseAppMngm::generateSetAfp() {
    QString paraAfp = m_pMap->value("afp").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR + " admin " + paraOldPwd  + " " + paraPwd, true);
}

void RenderResponseAppMngm::generateNfsEnable(QDomDocument &doc) {
    QString paraNfsStatus = m_pMap->value("nfs_status").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_MGR + " admin " + paraOldPwd  + " " + paraPwd, true);

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode("1"));
}
