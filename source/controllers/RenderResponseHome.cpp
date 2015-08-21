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

    switch(m_cmd) {
    case CMD_CGI_IS_BUILD_IN_LANGUAGE:
        generateIsBuildInLanguage();
        break;
    case CMD_SET_USER_LANGUAGE:
        generateSetUserLanguage();
        break;
    case CMD_GET_USER_LANGUAGE:
        generateGetUserLanguage();
        break;
    case CMD_CGI_GET_SSL_INFO:
        generateGetSslInfo();
        break;
    case CMD_UI_CHECK_WTO:
        generateUICheckWto();
        break;
    case CMD_FW_STATUS:
        generateFWStatus();
        break;
    case CMD_LOGIN:
        generateLogin();
        break;
    case CMD_LOGOUT:
        generateLogout();
        break;
    case CMD_GET_LOG_ITEM:
        generateGetLogItem();
        break;
    
    default:
        break;
    }

}

void RenderResponseHome::generateIsBuildInLanguage() {

    QDomDocument doc;

    QDomElement root = doc.createElement("flag");
    doc.appendChild(root);

    QStringList val = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_home_api build_in_language");

    root.appendChild(doc.createTextNode(val.value(0)));
    m_var = doc.toString();

}

void RenderResponseHome::generateSetUserLanguage() {

    QDomDocument doc;

    QString paraLang = m_pReq->allParameters().value("language").toString();
    QString ret = setNasCfg("web", "language", paraLang) ? "1" : "0";

    QDomElement root = doc.createElement("status");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(ret));
    m_var = doc.toString();

}

void RenderResponseHome::generateGetUserLanguage() {

    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_home_api cgi_get_user_language", true, ";");

    QDomElement root = doc.createElement("language");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseHome::generateGetSslInfo() {
    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_home_api ssl_info", true);

    QDomElement root = doc.createElement("ssl_info");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement portElement = doc.createElement("port");
    root.appendChild(portElement);
    portElement.appendChild(doc.createTextNode(apiOut.value(1)));
    m_var = doc.toString();

}

void RenderResponseHome::generateUICheckWto() {
    /* Return value is not decided here */
    m_var = "success";
}

void RenderResponseHome::generateFWStatus() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_home_api cgi_get_fw_status", true);
    m_var = apiOut.value(0);
}

void RenderResponseHome::generateLogin() {
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

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_home_api login#" +
                                 allParametersToString(), true);
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
    if(paraC1.compare("ON") == 0 && !paraSsl.compare("1") == 0)
        m_cookies.append(cookieRemMe);
    m_cookies.append(cookiePwd);

    if(apiOut.value(0).compare("1") == 0) {
        //m_loginUser = User::create(paraUsername, paraPwd);
        TCookie cookie("username", paraUsername.toLocal8Bit());
        cookie.setPath("/");
        m_cookies.append(cookie);

        m_session << paraUsername << "1";

        m_var = "../web/home.html?v=8401878";
    }
    else if(apiOut.value(0).compare("0") == 0){
        m_var = "../web/relogin.html";
    }
    else if(apiOut.value(0).compare("2") == 0){
        m_var = "../web/set_passwd.html";
    }

}

void RenderResponseHome::generateLogout() {

    QString paraUsername;
    QString paraOS;

    if(m_pReq->allParameters().contains("name"))
        paraUsername = m_pReq->allParameters().value("name").toString();
    if(m_pReq->allParameters().contains("os"))
        paraOS = m_pReq->allParameters().value("os").toString();

    m_userLogout = paraUsername;
    m_var = "..";

}

/* todo */
void RenderResponseHome::generateGetLogItem() {

    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);

    QDomElement root = doc.createElement("log");
    doc.appendChild(root);

    //for
    QDomElement itemElement = doc.createElement("item");
    root.appendChild(itemElement);
    QStringList itemContent(QStringList() << "date" << "info");
    //if( itemContent.size() != apiOut.value(i).split(";").size() ) {

    //for(int j = 0; j < apiOut.value(i).split(";").size(); j++) {
    QDomElement element = doc.createElement(itemContent.value(0));
    itemElement.appendChild(element);
    element.appendChild(doc.createTextNode(""));
    //}
    m_var = doc.toString();

}

