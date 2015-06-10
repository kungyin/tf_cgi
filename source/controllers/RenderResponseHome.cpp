#include "RenderResponseHome.h"

RenderResponseHome::RenderResponseHome(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseHome::~RenderResponseHome() {
}

void RenderResponseHome::preRender() {

    if(!m_pReq)
        return;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_CGI_IS_BUILD_IN_LANGUAGE:
        generateIsBuildInLanguage(doc);
        break;
    case CMD_SET_USER_LANGUAGE:
        generateSetUserLanguage(doc);
        break;
    case CMD_GET_USER_LANGUAGE:
        generateGetUserLanguage(doc);
        break;
    case CMD_CGI_GET_SSL_INFO:
        generateGetSslInfo(doc);
        break;
    case CMD_UI_CHECK_WTO:
        generateUICheckWto(str);
        break;
    case CMD_FW_STATUS:
        generateFWStatus(str);
        break;
    case CMD_LOGIN:
        generateLogin(str);
        break;
    case CMD_LOGOUT:
        generateLogout(str);
        break;
    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

}

void RenderResponseHome::generateIsBuildInLanguage(QDomDocument &doc) {

    QDomElement root = doc.createElement("flag");
    doc.appendChild(root);

    QStringList val = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g build_in_language", true);

    root.appendChild(doc.createTextNode(val.isEmpty() ? "" : val.at(0)));
}

void RenderResponseHome::generateSetUserLanguage(QDomDocument &doc) {
    QString paraLang = m_pReq->allParameters().value("language").toString();
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
    QString paraUsername;
    QString paraPwd;
    QString paraPort;
    QString paraType;
    QString paraFUsername;
    QString paraPrePwd;
    QString paraSsl;
    QString paraC1;
    QString paraSslPort;

    if(m_pReq->allParameters().contains("username"))
        paraUsername = m_pReq->allParameters().value("username").toString();
    if(m_pReq->allParameters().contains("pwd"))
        paraPwd = m_pReq->allParameters().value("pwd").toString();
    if(m_pReq->allParameters().contains("port"))
        paraPort = m_pReq->allParameters().value("port").toString();
    if(m_pReq->allParameters().contains("f_type"))
        paraType = m_pReq->allParameters().value("f_type").toString();
    if(m_pReq->allParameters().contains("f_username"))
        paraFUsername = m_pReq->allParameters().value("f_username").toString();
    if(m_pReq->allParameters().contains("pre_pwd"))
        paraPrePwd = m_pReq->allParameters().value("pre_pwd").toString();
    if(m_pReq->allParameters().contains("ssl"))
        paraSsl = m_pReq->allParameters().value("ssl").toString();
    if(m_pReq->allParameters().contains("C1"))
        paraC1 = m_pReq->allParameters().value("C1").toString();
    if(m_pReq->allParameters().contains("ssl_port"))
        paraSslPort = m_pReq->allParameters().value("ssl_port").toString();

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

    QDateTime expire = QDateTime::currentDateTime();
    if(paraC1.compare("ON") == 0)
        expire = expire.addSecs(31536000);    // 1 year in seconds.

    TCookie cookieName("uname", paraUsername.toLocal8Bit());
    cookieName.setExpirationDate(expire);
    cookieName.setPath("/");
    TCookie cookieRemMe("rembMe", "checked");
    cookieRemMe.setExpirationDate(expire);
    cookieRemMe.setPath("/");
    TCookie cookiePwd("password", paraPwd.toLocal8Bit());
    cookiePwd.setExpirationDate(expire);
    cookiePwd.setPath("/");
    m_cookies.append(cookieName);
    m_cookies.append(cookieRemMe);
    m_cookies.append(cookiePwd);

    if(apiOut.value(0).compare("1") == 0) {
        TCookie cookie("username", paraUsername.toLocal8Bit());
        cookie.setPath("/");
        m_cookies.append(cookie);
        str = "../web/home.html?v=8401878";
    }
    else if(apiOut.value(0).compare("0") == 0){
        str = "../web/relogin.html";
    }

}

void RenderResponseHome::generateLogout(QString &str) {

    QString paraUsername;
    QString paraOS;

    if(m_pReq->allParameters().contains("name"))
        paraUsername = m_pReq->allParameters().value("name").toString();
    if(m_pReq->allParameters().contains("os"))
        paraOS = m_pReq->allParameters().value("os").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -s logout " + paraUsername, true);
    str = "..";

}