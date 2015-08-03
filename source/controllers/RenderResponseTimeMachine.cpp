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

    switch(m_cmd) {
    case CMD_TM_GET_INFO:
        generateTmGetInfo();
        break;
    case CMD_TM_GET_LIST:
        generateTmGetList();
        break;
    case CMD_TM_GET_SMB_LIST:
        generateTmGetSmbList();
        break;
    case CMD_TM_SET:
        generateTmSet();
        break;
    case CMD_TM_GET_SHARENAME:
        generateTmGetShareName();
        break;
    case CMD_TM_SET_SHARE:
        generateTmSetShare();
        break;
    case CMD_TM_DEL_SHARE:
        generateTmDelShare();
        break;
    case CMD_TM_DEL_ALL_SHARE:
        generateTmDelAllShare();
        break;
    case CMD_NONE:
    default:
        break;
    }

}

void RenderResponseTimeMachine::generateTmGetInfo() {

    QDomDocument doc;

    QMap<QString, QString> tmInfo = getNasCfg("time_machine");
    QMap<QString, QString> sambaInfo = getNasCfg("samba");

    QDomElement root = doc.createElement("tm_info");
    doc.appendChild(root);

    QDomElement tm_enableElement = doc.createElement("tm_enable");
    root.appendChild(tm_enableElement);
    tm_enableElement.appendChild(doc.createTextNode(tmInfo.value("enable")));

    QDomElement ads_enableElement = doc.createElement("ads_enable");
    root.appendChild(ads_enableElement);
    ads_enableElement.appendChild(doc.createTextNode(sambaInfo.value("ads_enable")));

    m_var = doc.toString();

}

void RenderResponseTimeMachine::generateTmGetList() {

    QDomDocument doc;
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

    m_var = doc.toString();

}

void RenderResponseTimeMachine::generateTmGetSmbList() {

    QDomDocument doc;
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
        cellElement1.appendChild(doc.createCDATASection(
            QString("<input type=\"checkbox\" name=\"share_box\" id=\"share_box\" value=\"%1\" "
                    "onclick=\"sel_box(this)\" rel=\"%2\">").arg(data.value(0).arg(data.value(1)))));
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

    m_var = doc.toString();

}

void RenderResponseTimeMachine::generateTmSet() {

    QString paraEnable = m_pReq->parameter("enable");

    if(setNasCfg("time_machine", "enable", paraEnable))
        getAPIStdOut(API_PATH + SCRIPT_AFP_CTL + " restart", true);
    else
        tDebug("RenderResponseTimeMachine::generateTmSet(): setNasCfg time_machine failed");

    m_var = "N/A";

}

void RenderResponseTimeMachine::generateTmGetShareName() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_tm_share_name", true, ";");

    QDomElement root = doc.createElement("tm_share");
    doc.appendChild(root);

    for(QString e : apiOut) {
        QDomElement itemElement = doc.createElement("item");
        root.appendChild(itemElement);
        QDomElement nameElement = doc.createElement("name");
        itemElement.appendChild(nameElement);
        nameElement.appendChild(doc.createTextNode(e));
    }

    m_var = doc.toString();

}

void RenderResponseTimeMachine::generateTmSetShare() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
            " service_set_add_tm_share " + allParametersToString(), true);

    m_var = "N/A";
}

void RenderResponseTimeMachine::generateTmDelShare() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
            " service_set_del_tm_share " + allParametersToString(), true);
    m_var = "N/A";
}

void RenderResponseTimeMachine::generateTmDelAllShare() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
            " service_set_del_all_share", true);
    m_var = "N/A";
}


