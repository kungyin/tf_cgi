#include "RenderResponseFileStation.h"

RenderResponseFileStation::RenderResponseFileStation(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseFileStation::~RenderResponseFileStation() {
}

void RenderResponseFileStation::preRender() {

    if(!m_pReq)
        return;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_FOLDER_CONTENT:
        generateFolderContent(doc);
        break;

    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

}

/* todo */
void RenderResponseFileStation::generateFolderContent(QDomDocument &doc) {

    QString paraPage = m_pReq->parameter("page");
    QString paraRp = m_pReq->parameter("rp");
    QString paraQuery = m_pReq->parameter("query");
    QString paraType = m_pReq->parameter("qtype");
    QString paraField = m_pReq->parameter("f_field");
    QString paraUsedDir = m_pReq->parameter("used_dir");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("0"));

}


