#include "RenderResponseHome.h"
#include "AppDefine.h"

RenderResponseHome::RenderResponseHome(QVariantMap &map, CGI_COMMAND cmd)
    : m_session("")
    , m_loginStatus(0)
{
    m_cmd = cmd;
    m_renderType = RENDER_TYPE_UNKNOWN;
    m_pMap = &map;
}

RenderResponseHome::~RenderResponseHome() {
}

RENDER_TYPE RenderResponseHome::preRender() {

    if(!m_pMap)
        return RENDER_TYPE_UNKNOWN;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_CGI_IS_BUILD_IN_LANGUAGE:
        generateIsBuildInLanguage(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SET_USER_LANGUAGE:
        generateSetUserLanguage(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_USER_LANGUAGE:
        generateGetUserLanguage(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_CGI_GET_SSL_INFO:
        generateGetSslInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_UI_CHECK_WTO:
        generateUICheckWto(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_FW_STATUS:
        generateFWStatus(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_LOGIN:
        generateLogin(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_LOGOUT:
        generateLogout(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

    return m_renderType;
}

void RenderResponseHome::generateIsBuildInLanguage(QDomDocument &doc) {

    QDomElement root = doc.createElement("flag");
    doc.appendChild(root);

    QStringList val = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g build_in_language", true);

    root.appendChild(doc.createTextNode(val.isEmpty() ? "" : val.at(0)));
}

void RenderResponseHome::generateSetUserLanguage(QDomDocument &doc) {
    QString paraLang = m_pMap->value("language").toString();
    QString ret = setNasCfg("web", "language", paraLang) ? "1" : "0";

    QDomElement root = doc.createElement("status");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(ret));
}

void RenderResponseHome::generateGetUserLanguage(QDomDocument &doc) {

    QMap<QString, QString> webInfo = getNasCfg("web");
    QString ret = webInfo.value("language").isEmpty() ? "" : QString("%1,%1.xml").arg(webInfo.value("language"));

    QDomElement root = doc.createElement("language");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(ret));
}

void RenderResponseHome::generateGetSslInfo(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);
    if(apiOut.size() < 2)
        return;

    QDomElement root = doc.createElement("ssl_info");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode(apiOut.at(0)));
    QDomElement portElement = doc.createElement("port");
    root.appendChild(portElement);
    portElement.appendChild(doc.createTextNode(apiOut.at(1)));
}

void RenderResponseHome::generateUICheckWto(QString &str) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ui_check_wto", true);
    str = apiOut.isEmpty() ? "fail" : apiOut.at(0);
}

void RenderResponseHome::generateFWStatus(QString &str) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g fw_status", true);
    str = apiOut.isEmpty() ? "" : apiOut.at(0);
}

void RenderResponseHome::generateLogin(QString &str) {
    if(!m_pMap)
        return;

    QString paraUsername;
    QString paraPwd;
    QString paraPort;
    QString paraType;
    QString paraFUsername;
    QString paraPrePwd;
    QString paraSsl;
    QString paraC1;
    QString paraSslPort;

    if(m_pMap->contains("username"))
        paraUsername = m_pMap->value("username").toString();
    if(m_pMap->contains("pwd"))
        paraPwd = m_pMap->value("pwd").toString();
    if(m_pMap->contains("port"))
        paraPort = m_pMap->value("port").toString();
    if(m_pMap->contains("f_type"))
        paraType = m_pMap->value("f_type").toString();
    if(m_pMap->contains("f_username"))
        paraFUsername = m_pMap->value("f_username").toString();
    if(m_pMap->contains("pre_pwd"))
        paraPrePwd = m_pMap->value("pre_pwd").toString();
    if(m_pMap->contains("ssl"))
        paraSsl = m_pMap->value("ssl").toString();
    if(m_pMap->contains("C1"))
        paraC1 = m_pMap->value("C1").toString();
    if(m_pMap->contains("ssl_port"))
        paraSslPort = m_pMap->value("ssl_port").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g login " + paraUsername + " " + paraPwd, true);

    QMap<QString, QString> map;
    map.insert("ssl_enable", paraSsl);
    map.insert("ssl_port", paraSslPort);

    if(setNasCfg("web", map)) {
        //if(paraSsl.compare("1") == 0) {
#ifndef SIMULATOR_MODE
        //todo: restart.
#endif
        //}
    }

    if(paraC1.compare("ON") == 0) {
        m_session = paraUsername;
    }

    QString status = apiOut.isEmpty() ? "0" : apiOut.at(0);
    if(status.compare("1") == 0) {
        m_loginStatus = 1;
    }
}

void RenderResponseHome::generateLogout(QString &str) {
    if(!m_pMap)
        return;

    QString paraUsername;
    QString paraOS;

    if(m_pMap->contains("name"))
        paraUsername = m_pMap->value("name").toString();
    if(m_pMap->contains("os"))
        paraOS = m_pMap->value("os").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -s logout " + paraUsername, true);
    m_loginStatus = -1;

}
