#include "RenderResponseFtp.h"
#include "AppDefine.h"

RenderResponseFtp::RenderResponseFtp(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseFtp::~RenderResponseFtp() {
}

void RenderResponseFtp::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
/*    case CMD_GUI_CODEPAGE_GET_LIST:
        codepagegetlist(doc);
        m_renderType = RENDER_TYPE_XML;
        break;*/
    case CMD_FTP_SERVER_GET_CONFIG:
        servergetconfig();
        break;
    case CMD_FTP_SERVER_EXIP_RENEW:
        serverexiprenew();
        break;
/*    case CMD_GUI_CODE_ADD:
        codepageadd(doc);
        break;*/
    case CMD_P2P_GET_PORT:
        p2pgetport();
        break;
    case CMD_FTP_SERVER_BLOCKIP_LIST:
        serverblockiplist();
        break;
    case CMD_FTP_SERVER_BLOCKIP_ADD:
        serverblockipadd();
        break;
    case CMD_FTP_SERVER_ENABLE:
        serverenable();
        break;

    case CMD_NONE:
    default:
        break;
    }

}

/*/ todo API
void RenderResponseFtp::codepagegetlist(QDomDocument &doc) {
//QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_APPAPI_FTP + " -g codepage", true, ";");

    QVector<QString> vlang;
    QVector<QString> vdesc;

    vlang << "UTF-8" << "ISO-8859-1" << "CP865" << "ISO-8859-2"<< "CP1250"<< "BIG5"<< "GB2312"<< "CP1251"<< "ISO-8859-9"<< "EUC-KR"<< "ISO-8859-8";
    vdesc << "Unicode 8bit" << "Western European" << "MS-DOS Northern European" << "Slavic/Central European"<< "MS Windows Central European"<< "Traditional Chinese"<< "Simplified Chinese"<< "MS Windows Cyrillic"<< "Turkish"<< "Korean"<< "Hebrew";

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
    for (int i = 0; i < vlang.size(); i++)
    {
        QDomElement itemElement = doc.createElement("item");
        root.appendChild(itemElement);
        QDomElement langElement = doc.createElement("lang");
        itemElement.appendChild(langElement);
        langElement.appendChild(doc.createTextNode(vlang[i]));
        QDomElement descElement = doc.createElement("desc");
        itemElement.appendChild(descElement);
        descElement.appendChild(doc.createTextNode(vdesc[i]));
    }
}*/

// todo API
void RenderResponseFtp::servergetconfig() {
    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_APPAPI_FTP + " config", true, ",");

    QVector<QString> vparam;
        vparam << "maxclientsnumber" << "maxidletime" << "port" << "flowcontrol"<< "filesystemcharset"<< "clientcharset"<< "passiveportrange"<< "exip"<< "externalip"<< "state"<< "tlsencryption"<< "forcepasvmode"<< "connect_per_ip"<< "fxpaccess";

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    for (int i = 0; i < vparam.size(); i++)
    {
        QDomElement maxclientsnumberElement = doc.createElement(vparam[i]);
        root.appendChild(maxclientsnumberElement);
        maxclientsnumberElement.appendChild(doc.createTextNode(apiOut.value(i)));
    }
    m_var = doc.toString();

}

// todo API
void RenderResponseFtp::serverexiprenew() {

    QDomDocument doc;

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
    QDomElement exipElement = doc.createElement("exip");
    root.appendChild(exipElement);
    exipElement.appendChild(doc.createTextNode("0"));

    m_var = doc.toString();

}

/*
// todo API
void RenderResponseFtp::codepageadd(QDomDocument &doc) {

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
}
*/

// todo API
void RenderResponseFtp::p2pgetport() {

    QDomDocument doc;

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

// todo API
void RenderResponseFtp::serverblockiplist() {

    QDomDocument doc;

    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qyupe").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_APPAPI_FTP + " blkiplist", false, ";");

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
        cellElement2.appendChild(doc.createTextNode(data.value(1)));
        QDomElement cellElement3 = doc.createElement("cell");
        rowElement1.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode(data.value(2)));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement1.appendChild(cellElement4);
        cellElement4.appendChild(doc.createTextNode(data.value(3)));
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement1.appendChild(cellElement5);
        cellElement5.appendChild(doc.createTextNode(data.value(4)));


        rowElement1.setAttribute("id", QString::number(i+1));
    }

    QDomElement pageElement1 = doc.createElement("page");
    root.appendChild(pageElement1);
    pageElement1.appendChild(doc.createTextNode("1"));
    QDomElement totalElement1 = doc.createElement("total");
    root.appendChild(totalElement1);
    totalElement1.appendChild(doc.createTextNode(QString::number(apiOut.size())));
    m_var = doc.toString();

}

//todo API
void RenderResponseFtp::serverblockipadd() {

    QDomDocument doc;

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
    m_var = doc.toString();

}

//todo API
void RenderResponseFtp::serverenable() {

    QDomDocument doc;

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}


