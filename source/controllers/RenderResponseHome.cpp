#include <QDir>
#include <TAppSettings>

#include "RenderResponseHome.h"

static QMap<QString, QString> lang_map {

    { "zh-tw",  "TC"    },
    { "de",     "DE"    },
    { "en-us",  "EN"    },
    { "es",     "ES-DI" },
    { "es-es",  "ES-EU" },
    { "fr",     "FR"    },
    { "it",     "IT"    },
    { "pt",     "PT"    },
    { "ru",     "RU"    },
    { "zh-cn",  "SC"    },

};

RenderResponseHome::RenderResponseHome(THttpRequest &req, CGI_COMMAND cmd)
    : m_bRedirect2Ssl(false)
    , m_bRemMe(false)
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

    QStringList arg = QStringList() << "service_home_api" << "build_in_language";
    QStringList val = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

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

    QStringList arg = QStringList() << "service_home_api" << "cgi_get_user_language";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QString ret = apiOut.value(0);
    QString retFormat = "%1,%2.xml";
    bool bFound = true;
    QString langCode = apiOut.value(0).split(",").value(0);
    if(langCode == "Auto") {
        bFound = false;
        /* eg. zh-TW,zh;q=0.8,en-US;q=0.6,en;q=0.4 */
        QString detectedLang(m_pReq->header().rawHeader("Accept-Language").split(';').value(0).split(',').value(0));
        tDebug("RenderResponseHome::generateGetUserLanguage() detectedLang: %s", detectedLang.toLocal8Bit().data());

        QMapIterator<QString, QString> i(lang_map);
        while (i.hasNext()) {
            i.next();
            if(detectedLang.startsWith(i.key(), Qt::CaseInsensitive)) {
                ret = retFormat.arg(langCode, i.value());
                bFound = true;
                break;
            }
        }
    }

    if(!bFound)
        ret = retFormat.arg(langCode, "EN");

    QDomElement root = doc.createElement("language");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(ret));
    m_var = doc.toString();

}

void RenderResponseHome::generateGetSslInfo() {
    QDomDocument doc;
    QStringList arg = QStringList() << "service_home_api" << "ssl_info";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

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
    m_var = isValidUser() ? "success" : "fail";
}

void RenderResponseHome::generateFWStatus() {
    QStringList arg = QStringList() << "service_home_api" << "cgi_get_fw_status";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
    m_var = apiOut.value(0);
}

void RenderResponseHome::generateLogin() {
    QString paraUsername = m_pReq->parameter("username");
    QString paraPwd = QUrl::fromPercentEncoding(m_pReq->parameter("pwd").toLocal8Bit());
    QString paraPort = m_pReq->parameter("port");
    QString paraType = m_pReq->parameter("f_type");
    QString paraFUsername = m_pReq->parameter("f_username");
    QString paraPrePwd = m_pReq->parameter("pre_pwd");
    QString paraSsl = m_pReq->parameter("ssl");
    QString paraC1 = m_pReq->parameter("C1");
    QString paraSslPort = m_pReq->parameter("ssl_port");
    QString paraLPage = m_pReq->parameter("lpage");
    QString paraLPagePortHttp = m_pReq->parameter("lpage_port_http");

    QString loginPara = "login#" + allParametersToString();
    QStringList arg = QStringList() << "service_home_api" << loginPara;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    if(!paraSsl.isEmpty() && !paraSslPort.isEmpty()) {
        QMap<QString, QString> map;
        map.insert("ssl_enable", paraSsl);
        map.insert("ssl_port", paraSslPort);

        if(setNasCfg("web", map)) {
            if(paraSsl.compare("1") == 0) {
#ifndef SIMULATOR_MODE
                //todo: restart.
#endif
            }
        }
    }

    if(paraC1.compare("ON") == 0 && !paraSsl.compare("1") == 0) {
        m_bRemMe = true;
    }

    if(apiOut.value(0).compare("1") == 0 || apiOut.value(0).compare("2") == 0) {
        if(paraSsl.compare("1") == 0)
            m_bRedirect2Ssl = true;

        //m_loginUser = User::create(paraUsername, paraPwd);
        TCookie cookie("username", paraUsername.toLocal8Bit());
        cookie.setPath("/");
        m_cookies.append(cookie);
        m_pSession->insert("user", paraUsername);
        m_pSession->insert("time", QDateTime::currentDateTime());

        if(apiOut.value(0).compare("1") == 0) {
            if(paraLPage.isEmpty())
                m_var = "/web/home.html?v=8401878";
            else {
                if(paraLPage == "2")
                    m_var = "/photo_center/index.html?v=4389165&lpage_port_http=" + paraLPagePortHttp;
                else if(paraLPage == "3")
                    m_var = "/MyMusic/index.html?v=4745396&lpage_port_http=" + paraLPagePortHttp;
                else if(paraLPage == "4")
                    m_var = "/web/web_file/web_file_server.html?v=1529718&lpage_port_http=" + paraLPagePortHttp;
                else if(paraLPage == "5")
                    m_var = "/web/download_mgr/p2p_main.html?v=9476204&lpage_port_http=" + paraLPagePortHttp;
            }
        }
        else
            m_var = "/web/set_passwd.html";
    }
    else /*if(apiOut.value(0).compare("0") == 0)*/ {
        m_var = "/web/relogin.html";
    }

}

void RenderResponseHome::generateLogout() {

    if(m_pSession) {
        QString user = m_pSession->value("user").toString();

        QDir dir(sessionDirPath());
        QDir::Filters filters = QDir::Files;
        QFileInfoList fileList = dir.entryInfoList(filters);

        QListIterator<QFileInfo> iter(fileList);
        while (iter.hasNext()) {
            QFileInfo entry = iter.next();
            if(entry.fileName().length() == 40) {
                TSession session = findSession(entry.fileName().toLocal8Bit());
                if(session.value("user").toString() == user
                        && m_pSession->id() != entry.fileName())
                {
                    QFile::remove(entry.absoluteFilePath());

                    tDebug("remove %s", entry.absoluteFilePath().toLocal8Bit().data());
                }
            }
        }

        m_pSession->reset();

    }

    m_var = "..";

}

void RenderResponseHome::generateGetLogItem() {

    QDomDocument doc;

    QStringList arg = QStringList() << "cgi_get_log_item" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("log");
    doc.appendChild(root);

    for(QString e : apiOut) {
        QDomElement itemElement = doc.createElement("item");
        root.appendChild(itemElement);
        //QStringList itemContent(QStringList() << "date" << "info");

        int diff = 0;
        if(e.indexOf("  ") == 3)
            diff = 1;
        QString logDateTime = e.section(" ", 0, 2 + diff);
        //QString logTime = e.section(" ", 2 + diff, 2 + diff);
        QString strLog = e.section(" ", 4 + diff);
        //QString logContent = strLog.right(strLog.length() - (strLog.indexOf(": ") + 2));

        QDomElement dateElement = doc.createElement("date");
        itemElement.appendChild(dateElement);
        dateElement.appendChild(doc.createTextNode(logDateTime));
        QDomElement infoElement = doc.createElement("info");
        itemElement.appendChild(infoElement);
        infoElement.appendChild(doc.createTextNode(strLog));
    }
    m_var = doc.toString();

}

bool RenderResponseHome::isValidUser() {

    if(!m_pSession) {
        tError("RenderResponseHome::isValidUser() m_pSession is NULL");
        return false;
    }

    bool bValidUser = false;

    for(TCookie c : m_pReq->cookies()) {
        if(c.name() == "username") {
            uint lifeTime = Tf::appSettings()->value(Tf::SessionLifeTime).toInt();
            tDebug("lifeTime: %d", lifeTime);
            if(m_pSession->value("user").toByteArray() == c.value()) {
                if(lifeTime > (QDateTime::currentDateTime().toTime_t()
                             - m_pSession->value("time").toDateTime().toTime_t())) {
                    m_pSession->insert("time", QDateTime::currentDateTime());
                    bValidUser = true;
                }
                break;
            }
            else {
                QDir dir(sessionDirPath());
                QDir::Filters filters = QDir::Files;
                QFileInfoList fileList = dir.entryInfoList(filters);

                QListIterator<QFileInfo> iter(fileList);
                while (iter.hasNext()) {
                    QFileInfo entry = iter.next();
                    if(entry.fileName().length() == 40) {
                        TSession session = findSession(entry.fileName().toLocal8Bit());
                        if(session.value("user").toByteArray() == c.value()
                                && (lifeTime > (QDateTime::currentDateTime().toTime_t()
                                    - session.value("time").toDateTime().toTime_t())))
                        {
                            m_pSession->insert("user", c.value());
                            m_pSession->insert("time", QDateTime::currentDateTime());
                            bValidUser = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    return bValidUser;
}
