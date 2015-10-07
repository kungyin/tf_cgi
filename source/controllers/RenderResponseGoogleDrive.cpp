#include "RenderResponseGoogleDrive.h"

RenderResponseGoogleDrive::RenderResponseGoogleDrive(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseGoogleDrive::~RenderResponseGoogleDrive() {
}

void RenderResponseGoogleDrive::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_GD_1:
        generateGd1();
        break;
    case CMD_GD_2:
        generateGd2();
        break;
    case CMD_GD_3:
        generateGd3();
        break;
    case CMD_GD_4:
        generateGd4();
        break;

    default:
        break;
    }

}

void RenderResponseGoogleDrive::generateGd1() {

    QDomDocument doc;

    QStringList arg = QStringList() << "service_add_gdrive_account" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    QDomElement root = doc.createElement("status");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseGoogleDrive::generateGd2() {

    QDomDocument doc;

    QStringList arg = QStringList() << "service_mod_gdrive_account" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    QDomElement root = doc.createElement("status");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseGoogleDrive::generateGd3() {

    QDomDocument doc;

    QStringList arg = QStringList() << "service_del_gdrive_account" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    QDomElement root = doc.createElement("status");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseGoogleDrive::generateGd4() {

    QDomDocument doc;

    QStringList arg = QStringList() << "service_sync_now_gdrive" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    QDomElement root = doc.createElement("status");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

