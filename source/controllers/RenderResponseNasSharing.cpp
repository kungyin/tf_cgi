#include <QDir>

#include "RenderResponseNasSharing.h"

RenderResponseNasSharing::RenderResponseNasSharing(THttpRequest &req, CGI_COMMAND cmd)
    : m_bLoginStatus(false)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseNasSharing::~RenderResponseNasSharing() {
}

void RenderResponseNasSharing::preRender() {

    if(!m_pReq)
        return;

    m_bLoginStatus = isLogin();

    switch(m_cmd) {
    case CMD_NAS_SHARING_1:
        generateLogin();
        break;
//    case CMD_2:
//        generateSetDeviceName();
//        break;
//    case CMD_4:
//        generateListVolume();
//        break;
//    case CMD_5:
//        generateListFolder();
//        break;
//    case CMD_6:
//        generateDownload();
//        break;
//    case CMD_7:
//        generateUpload();
//        break;
//    case CMD_9:
//        generateMove();
//        break;
//    case CMD_10:
//        generateCopy();
//        break;
//    case CMD_14:
//        generateMkdir();
//        break;

    default:
        break;
    }

}



bool RenderResponseNasSharing::isLogin() {

    QString paraUser = QUrl::fromPercentEncoding(m_pReq->parameter("user").toLocal8Bit());
    QString loginStr = paraUser.toLocal8Bit() +
            " " + QUrl::fromPercentEncoding(m_pReq->parameter("passwd").toLocal8Bit());

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_CHK_PWD + " " + loginStr, true);
    return apiOut.value(0) == "OK" ? true : false;

}

void RenderResponseNasSharing::generatePrefix(QDomDocument &doc) {

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement nasSharingElement = doc.createElement("nas_sharing");
    root.appendChild(nasSharingElement);
    QDomElement authStatusElement = doc.createElement("auth_status");
    nasSharingElement.appendChild(authStatusElement);
    authStatusElement.appendChild(doc.createTextNode(m_bLoginStatus ? "1" : "0"));

}

void RenderResponseNasSharing::generateLogin() {

    QDomDocument doc;
    generatePrefix(doc);
    QDomElement root = doc.documentElement();
    if(m_bLoginStatus) {
        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(NAS_SHARING_VERSION));

        QDomElement mediaFolderElement = doc.createElement("media_folder");
        root.appendChild(mediaFolderElement);
        mediaFolderElement.appendChild(doc.createTextNode("0"));
    }

    m_var = doc.toString();

}
