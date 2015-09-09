#include "RenderResponseAirplay.h"

RenderResponseAirplay::RenderResponseAirplay(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseAirplay::~RenderResponseAirplay() {
}

void RenderResponseAirplay::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {

    case CMD_GET_AIRPLAY_DEVICE:
        generateGetAirplayDevice();
        break;
    case CMD_SET_AIRPLAY_DEVICE:
        generateSetAirplayDevice();
        break;
    case CMD_CHK_AIRPLAY_STATUS:
        generateChkAirplayStatus();
        break;
    case CMD_SET_AIRPLAY_SOURCE:
        generateSetAirplaySource();
        break;
    case CMD_AIRPLAY_STOP:
        generateAirplayStop();
        break;

    default:
        break;
    }

}

void RenderResponseAirplay::generateGetAirplayDevice() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " cgi_get_airplay_device", true, ";");

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);

    for(int i=0; i < apiOut.size(); i+=2) {
        QDomElement itmeElement = doc.createElement("item");
        root.appendChild(itmeElement);

        QDomElement nameElement = doc.createElement("name");
        itmeElement.appendChild(nameElement);
        nameElement.appendChild(doc.createTextNode(apiOut.value(i)));
        QDomElement typeElement = doc.createElement("type");
        itmeElement.appendChild(typeElement);
        typeElement.appendChild(doc.createTextNode(apiOut.value(i+1)));
    }

    m_var = doc.toString();

}

void RenderResponseAirplay::generateSetAirplayDevice() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " cgi_set_airplay_device " +
                                      allParametersToString());

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAirplay::generateChkAirplayStatus() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " cgi_chk_airplay_status");

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAirplay::generateSetAirplaySource() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " cgi_set_airplay_source " +
                                      allParametersToString());

}

void RenderResponseAirplay::generateAirplayStop() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " cgi_airplay_stop " +
                                      allParametersToString());

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}
