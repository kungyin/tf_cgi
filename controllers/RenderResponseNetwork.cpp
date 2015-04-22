#include "RenderResponseNetwork.h"
#include "AppDefine.h"

RenderResponseNetwork::RenderResponseNetwork(QVariantMap &map, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_renderType = RENDER_TYPE_UNKNOWN;
    m_pMap = &map;
}

RenderResponseNetwork::~RenderResponseNetwork() {
}

RENDER_TYPE RenderResponseNetwork::preRender() {

    if(!m_pMap)
        return RENDER_TYPE_UNKNOWN;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_LLTD:
        generateLLTD(doc);
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

void RenderResponseNetwork::generateLLTD(QDomDocument &doc) {
    QDomElement root = doc.createElement("lltd");
    doc.appendChild(root);
    QDomElement enable = doc.createElement("enable");
    root.appendChild(enable);
    QDomText text = doc.createTextNode("0");
    enable.appendChild(text);
}

