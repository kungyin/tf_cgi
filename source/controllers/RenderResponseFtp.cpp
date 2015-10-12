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
    case CMD_FTP_SERVER_GET_CONFIG:
        generateFtpServerGetConfig();
        break;
    case CMD_FTP_SERVER_EXIP_RENEW:
        generateFtpServerExipRenew();
        break;
    case CMD_P2P_GET_PORT:
        generateP2pGetPort();
        break;
    case CMD_FTP_SERVER_BLOCKIP_LIST:
        generateFtpServerBlockIPList();
        break;
    case CMD_FTP_SERVER_BLOCKIP_ADD:
        generateFtpServerBlockIPAdd();
        break;
    case CMD_FTP_SERVER_BLOCKIP_DEL:
        generateFtpServerBlockIPDel();
        break;
    case CMD_FTP_SERVER_ENABLE:
        generateFtpServerEnable();
        break;
    case CMD_FTP_SERVER_SET_CONFIG:
        generateFtpServerSetConfig();
        break;
    
    default:
        break;
    }

}

void RenderResponseFtp::generateFtpServerGetConfig() {
    QDomDocument doc;
    QStringList arg = QStringList() << "service_get_ftp_server_config";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QStringList configTagsElement(QStringList()
         << "maxclientsnumber" << "maxidletime" << "port" << "flowcontrol"
         << "filesystemcharset" << "clientcharset" << "passiveportrange"
         << "exip" << "externalip" << "state" << "tlsencryption"
         << "forcepasvmode"<< "connect_per_ip"<< "fxpaccess");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    if( configTagsElement.size() == apiOut.size() ) {

        for(int i=0; i < apiOut.size(); i++) {
            QDomElement element = doc.createElement(configTagsElement.value(i));
            root.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(i)));
        }

    }
    else {
        //assert(0);
        tError("RenderResponseFtp::generateFtpServerGetConfig() :"
               "configTagsElement size is not equal to apiOut size.");

        tDebug(" %d", apiOut.size());
        tDebug(" %d", configTagsElement.size());

    }

    m_var = doc.toString();

}

void RenderResponseFtp::generateFtpServerExipRenew() {

    QDomDocument doc;

    QStringList arg = QStringList() << "service_get_ftp_server_exip";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement exipElement = doc.createElement("exip");
    root.appendChild(exipElement);
    exipElement.appendChild(doc.createTextNode(apiOut.value(1)));

    m_var = doc.toString();

}

void RenderResponseFtp::generateP2pGetPort() {

    QDomDocument doc;

    QStringList arg = QStringList() << "service_check_ftp_port";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseFtp::generateFtpServerBlockIPList() {

    QDomDocument doc;

    QString paraPage = m_pReq->allParameters().value("page").toString();
//    QString paraRp = m_pReq->allParameters().value("rp").toString();
//    QString paraQuery = m_pReq->allParameters().value("query").toString();
//    QString paraQType = m_pReq->allParameters().value("qyupe").toString();
//    QString paraField = m_pReq->allParameters().value("f_field").toString();
//    QString paraUser = m_pReq->allParameters().value("user").toString();

    QStringList arg = QStringList() << "service_get_ftp_blockip_list";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    for(int i=0; i < apiOut.size(); i++) {
        QStringList data = apiOut.value(i).split(";");

        QDomElement rowElement1 = doc.createElement("row");
        root.appendChild(rowElement1);

        for(QString e : data) {
            QDomElement cellElement1 = doc.createElement("cell");
            rowElement1.appendChild(cellElement1);
            cellElement1.appendChild(doc.createTextNode(e));
        }

        rowElement1.setAttribute("id", i+1);
    }

    QDomElement pageElement1 = doc.createElement("page");
    root.appendChild(pageElement1);
    pageElement1.appendChild(doc.createTextNode(paraPage));
    QDomElement totalElement1 = doc.createElement("total");
    root.appendChild(totalElement1);
    totalElement1.appendChild(doc.createTextNode(QString::number(apiOut.size())));

    m_var = doc.toString();

}

void RenderResponseFtp::generateFtpServerBlockIPAdd() {

    QDomDocument doc;

    QStringList arg = QStringList() << "service_set_ftp_blockip" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("result");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseFtp::generateFtpServerBlockIPDel() {

    QDomDocument doc;

    QStringList arg = QStringList() << "FTP_Server_BlockIP_Del" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("result");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseFtp::generateFtpServerEnable() {

    QString paraStatus = m_pReq->parameter("f_state");

    QDomDocument doc;

    QStringList arg = QStringList() << "service_set_ftp_server_state" << paraStatus;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseFtp::generateFtpServerSetConfig() {

    QMap<QString, QString> map;
    map.insert("maxclientsnumber", m_pReq->parameter("f_maxuser"));
    map.insert("maxidletime", m_pReq->parameter("f_idle_time"));
    map.insert("port", m_pReq->parameter("f_port"));
    map.insert("flowcontrol", m_pReq->parameter("f_flow_value"));
    map.insert("filesystemcharset", m_pReq->parameter("f_client_char_defult"));
    map.insert("clientcharset", m_pReq->parameter("f_client_char"));
    QString passivePort = QUrl::fromPercentEncoding(m_pReq->parameter("f_passive").toLocal8Bit());
    if(passivePort.isEmpty())
        passivePort = QUrl::fromPercentEncoding(m_pReq->parameter("f_passive_port").toLocal8Bit());
    map.insert("passiveportrange", passivePort);
    map.insert("externalip", m_pReq->parameter("f_external_ip"));
    map.insert("state", m_pReq->parameter("f_flow"));
    map.insert("tlsencryption", m_pReq->parameter("f_tls_status"));
    map.insert("forcepasvmode", m_pReq->parameter("forcepasvmod"));
    map.insert("anonymous_access", m_pReq->parameter("f_mode"));
    map.insert("fxpaccess", m_pReq->parameter("f_fxp"));

    if(!setNasCfg("ftp", map))
        tDebug("setNasCfg ftp failed");

    QStringList arg = QStringList() << "service_set_modify_ftp_config";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    m_var = "<script>location.href='/web/app_mgr/ftp_setting.html?id=8401878'</script>";

}

