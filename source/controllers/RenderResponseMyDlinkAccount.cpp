#include "RenderResponseMyDlinkAccount.h"


RenderResponseMyDlinkAccount::RenderResponseMyDlinkAccount(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseMyDlinkAccount::~RenderResponseMyDlinkAccount() {
}

void RenderResponseMyDlinkAccount::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_MYDLINK_ACC_1:
    case CMD_MYDLINK_ACC_2:
    case CMD_MYDLINK_ACC_3:
    case CMD_MYDLINK_ACC_4:
    case CMD_MYDLINK_ACC_5:
    case CMD_MYDLINK_ACC_6:
        generateMydlinkAcc("res");
        break;
    case CMD_MYDLINK_ACC_7:
        generateMydlinkAcc("status");
        break;
    default:
        break;
    }

}

void RenderResponseMyDlinkAccount::generateMydlinkAcc(QString tagName) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " mydlink_account " + allParametersToString());

    QDomDocument doc;
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement(tagName);
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}


