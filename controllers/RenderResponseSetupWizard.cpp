#include "RenderResponseSetupWizard.h"

RenderResponseSetupWizard::RenderResponseSetupWizard(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseSetupWizard::~RenderResponseSetupWizard() {
}

void RenderResponseSetupWizard::preRender() {

    if(!m_pReq)
        return;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_CHK_ADMIN_PW:
        generateChkAdminPw(doc);
        break;
    case CMD_SET_LED:
        generateSetLed();
        break;
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

}

/* todo: need API */
void RenderResponseSetupWizard::generateChkAdminPw(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");

    QDomElement root = doc.createElement("chk_info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode("1"));

}

void RenderResponseSetupWizard::generateSetLed() {
    QString paraLed = m_pReq->parameter("led");
    QString paraStatus = m_pReq->parameter("status");


    QString led = "power blue";

    if(paraLed.compare("0") == 0)
        led = "power blue";
    else if(paraLed.compare("1-0") == 0)
        led = "usb red";
    else if(paraLed.compare("1-1") == 0)
        led = "usb blue";
    else if(paraLed.compare("2-0") == 0)
        led = "hd0 red";
    else if(paraLed.compare("2-1") == 0)
        led = "hd0 blue";
    else if(paraLed.compare("3-0") == 0)
        led = "hd1 red";
    else if(paraLed.compare("3-1") == 0)
        led = "hd1 blue";

    QString status = "on";

    if(paraStatus.compare("0") == 0)
        status = "off";
    else if(paraStatus.compare("1") == 0)
        status = "on";
    else if(paraStatus.compare("2") == 0)
        status = "blinking";

    QStringList apiOut = getAPIStdOut(ENV_PATH + SCRIPT_LED_API + " " + led + " " + status, true);

}


