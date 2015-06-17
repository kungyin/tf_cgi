#include "RenderResponseTimeMachine.h"

RenderResponseTimeMachine::RenderResponseTimeMachine(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseTimeMachine::~RenderResponseTimeMachine() {
}

void RenderResponseTimeMachine::preRender() {

    if(!m_pReq)
        return;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_TM_GET_INFO:
        generateTmGetInfo(doc);
        break;
    case CMD_TM_GET_LIST:
        generateTmGetList(doc);
        break;
    case CMD_TM_GET_SMB_LIST:
        generateTmGetSmbList(doc);
        break;
    case CMD_TM_SET:
        generateTmSet(str);
        break;
    case CMD_TM_GET_SHARENAME:
        generateTmGetShareName(doc);
        break;
    case CMD_TM_SET_SHARE:
        generateTmSetShare(doc);
        break;
    case CMD_TM_DEL_SHARE:
        generateTmDelShare(str);
        break;
    case CMD_TM_DEL_ALL_SHARE:
        generateTmDelAllShare(str);
        break;
    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

}

void RenderResponseTimeMachine::generateTmGetInfo(QDomDocument &doc) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_tm_info", true, ";");

    QDomElement root = doc.createElement("tm_info");
    doc.appendChild(root);

    QDomElement tm_enableElement = doc.createElement("tm_enable");
    root.appendChild(tm_enableElement);
    tm_enableElement.appendChild(doc.createTextNode(apiOut.value(0)));

    QDomElement ads_enableElement = doc.createElement("ads_enable");
    root.appendChild(ads_enableElement);
    ads_enableElement.appendChild(doc.createTextNode(apiOut.value(1)));

}

void RenderResponseTimeMachine::generateTmGetList(QDomDocument &doc) {

    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qyupe").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_tm_info");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);
    
    for(int i=0; i < apiOut.size(); i++) {
        QStringList data = apiOut.value(i).split(";");

        QDomElement rowElement1 = doc.createElement("row");
        root.appendChild(rowElement1);

        QDomElement cellElement1 = doc.createElement("cell");
        rowElement1.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(data.value(0)));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement1.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode(data.value(1)));

        rowElement1.setAttribute("id", QString::number(i+1));
    }
    
    QDomElement pageElement1 = doc.createElement("page");
    root.appendChild(pageElement1);
    pageElement1.appendChild(doc.createTextNode(paraPage));
    QDomElement totalElement1 = doc.createElement("total");
    root.appendChild(totalElement1);
    totalElement1.appendChild(doc.createTextNode(QString::number(apiOut.size())));

}

void RenderResponseTimeMachine::generateTmGetSmbList(QDomDocument &doc) {
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qyupe").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_samba_list");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    for(int i=0; i < apiOut.size(); i++) {
        QStringList data = apiOut.value(i).split(";");

        QDomElement rowElement1 = doc.createElement("row");
        root.appendChild(rowElement1);

        QDomElement cellElement1 = doc.createElement("cell");
        rowElement1.appendChild(cellElement1);
        /* todo */
        cellElement1.appendChild(doc.createTextNode("&lt;input type=&quot;checkbox&quot; "
            "name=&quot;share_box&quot; id=&quot;share_box&quot; value=&quot;" + data.value(0) +
            "&quot; onclick=&quot;sel_box(this)&quot; rel=&quot;" + data.value(1) + "&quot;&gt;"));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement1.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode(data.value(0)));
        QDomElement cellElement3 = doc.createElement("cell");
        rowElement1.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode(data.value(1)));

        rowElement1.setAttribute("id", QString::number(i+1));
    }

    QDomElement pageElement1 = doc.createElement("page");
    root.appendChild(pageElement1);
    pageElement1.appendChild(doc.createTextNode(paraPage));
    QDomElement totalElement1 = doc.createElement("total");
    root.appendChild(totalElement1);
    totalElement1.appendChild(doc.createTextNode(QString::number(apiOut.size())));

}

void RenderResponseTimeMachine::generateTmSet(QString &str) {

    QString paraEnable = m_pReq->parameter("enable");

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_tm_status enable="
                                      + paraEnable, true);
    str = "N/A";

}

/* todo */
void RenderResponseTimeMachine::generateTmGetShareName(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_tm_status", true);

    QDomElement root = doc.createElement("tm_share");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(""));

}

/* todo */
void RenderResponseTimeMachine::generateTmSetShare(QDomDocument &doc) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
            " service_set_add_tm_share " + allParametersToString(), true);

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

void RenderResponseTimeMachine::generateTmDelShare(QString &str) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
            " service_set_del_tm_share " + allParametersToString(), true);
    str = "N/A";
}

void RenderResponseTimeMachine::generateTmDelAllShare(QString &str) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
            " service_set_del_all_share", true);
    str = "N/A";
}


