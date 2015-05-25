#include "RenderResponseTimeMachine.h"
#include "AppDefine.h"

RenderResponseTimeMachine::RenderResponseTimeMachine(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_renderType = RENDER_TYPE_UNKNOWN;
    m_pReq = &req;
}

RenderResponseTimeMachine::~RenderResponseTimeMachine() {
}

RENDER_TYPE RenderResponseTimeMachine::preRender() {

    if(!m_pReq)
        return RENDER_TYPE_UNKNOWN;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_GET_TM_INFO:
        timeGetInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_TM_LIST:
        timeGetList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_TM_GET_SMB_LIST:
        timeGetSmbList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_TM_SET:
        timeSet();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_TM_GET_SHARENAME:
        timeGetShareName(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_TM_SET_SHARE:
        timeSetShare(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_TM_DEL_SHARE:
        timeDelShare();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_TM_DEL_ALL_SHARE:
        timeDelAllShare();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

    return m_renderType;
}

void RenderResponseTimeMachine::timeGetInfo(QDomDocument &doc) {

    QDomElement root = doc.createElement("tm_info");
    doc.appendChild(root);

    QDomElement tm_enableElement = doc.createElement("tm_enable");
    root.appendChild(tm_enableElement);
    tm_enableElement.appendChild(doc.createTextNode("0"));

    QDomElement ads_enableElement = doc.createElement("ads_enable");
    root.appendChild(ads_enableElement);
    ads_enableElement.appendChild(doc.createTextNode("0"));

}

void RenderResponseTimeMachine::timeGetList(QDomDocument &doc) {

    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qyupe").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_APPAPI_TMM + " sharename", false, ";");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);
    
    for(int i=0; i < apiOut.size(); i++) {
        QStringList data = apiOut.at(i).split(";");

        QDomElement rowElement1 = doc.createElement("row");
        root.appendChild(rowElement1);

        QDomElement cellElement1 = doc.createElement("cell");
        rowElement1.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(data.value(0)));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement1.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode(data.value(1) + "/" + data.value(0)));

        rowElement1.setAttribute("id", QString::number(i+1));
    }
    
    QDomElement pageElement1 = doc.createElement("page");
    root.appendChild(pageElement1);
    pageElement1.appendChild(doc.createTextNode("1"));
    QDomElement totalElement1 = doc.createElement("total");
    root.appendChild(totalElement1);
    totalElement1.appendChild(doc.createTextNode(QString::number(apiOut.size())));

}

void RenderResponseTimeMachine::timeGetSmbList(QDomDocument &doc) {
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qyupe").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_APPAPI_TMM + " sharename", false, ";");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    for(int i=0; i < apiOut.size(); i++) {
        QStringList data = apiOut.at(i).split(";");

        QDomElement rowElement1 = doc.createElement("row");
        root.appendChild(rowElement1);

        QDomElement cellElement1 = doc.createElement("cell");
        rowElement1.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode("&lt;input type=&quot;checkbox&quot; name=&quot;share_box&quot; id=&quot;share_box&quot; value=&quot;" + data.value(0) + "&quot; onclick=&quot;sel_box(this)&quot; rel=&quot;" + data.value(1) + "/" + data.value(0) + "&quot;&gt;"));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement1.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode(data.value(0)));
        QDomElement cellElement3 = doc.createElement("cell");
        rowElement1.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode(data.value(1) + "/" + data.value(0)));

        rowElement1.setAttribute("id", QString::number(i+1));
    }

    QDomElement pageElement1 = doc.createElement("page");
    root.appendChild(pageElement1);
    pageElement1.appendChild(doc.createTextNode("1"));
    QDomElement totalElement1 = doc.createElement("total");
    root.appendChild(totalElement1);
    totalElement1.appendChild(doc.createTextNode(QString::number(apiOut.size())));

}

void RenderResponseTimeMachine::timeSet() {

}

void RenderResponseTimeMachine::timeGetShareName(QDomDocument &doc) {

    QDomElement root = doc.createElement("tm_share");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(""));

}

void RenderResponseTimeMachine::timeSetShare(QDomDocument &doc) {

    QDomElement root = doc.createElement("service-group");
    doc.appendChild(root);

    QDomElement nameElement = doc.createElement("name");
    root.appendChild(nameElement);
    nameElement.setAttribute("replace-wildcards", "yes");
    nameElement.appendChild(doc.createTextNode("%h_AFP_ggg"));

    QDomElement serviceElement = doc.createElement("service");
    root.appendChild(serviceElement);

    QDomElement typeElement = doc.createElement("type");
    serviceElement.appendChild(typeElement);
    typeElement.appendChild(doc.createTextNode("_afpovertcp._tcp"));
    QDomElement portElement = doc.createElement("port");
    serviceElement.appendChild(portElement);
    portElement.appendChild(doc.createTextNode("548"));

    QDomElement serviceElement1 = doc.createElement("service");
    root.appendChild(serviceElement1);

    QDomElement typeElement1 = doc.createElement("type");
    serviceElement1.appendChild(typeElement1);
    typeElement1.appendChild(doc.createTextNode("_adisk._tcp"));
    QDomElement portElement1 = doc.createElement("port");
    serviceElement1.appendChild(portElement1);
    portElement1.appendChild(doc.createTextNode("9"));
    QDomElement txtrecordElement = doc.createElement("txt-record");
    serviceElement1.appendChild(txtrecordElement);
    txtrecordElement.appendChild(doc.createTextNode("sys=waMA=CC:B2:55:8B:21:F7"));
    QDomElement txtrecordElement1 = doc.createElement("txt-record");
    serviceElement1.appendChild(txtrecordElement1);
    txtrecordElement1.appendChild(doc.createTextNode("dk2=adVF=0x83,adVN=ggg,adVU=12345678-1234-1234-1234-CCB2558B21F7"));

}

void RenderResponseTimeMachine::timeDelShare() {

}

void RenderResponseTimeMachine::timeDelAllShare() {

}


