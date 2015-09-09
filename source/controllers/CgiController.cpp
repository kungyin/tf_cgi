#include <QFileInfo>
#include <QCryptographicHash>
#include <QProcess>

#include "AppDefine.h"
#include "CgiController.h"
//#include "user.h"

#include "RenderResponseDisk.h"
#include "RenderResponseHome.h"
#include "RenderResponseNetwork.h"
#include "RenderResponseAccount.h"
#include "RenderResponseNetShare.h"
#include "RenderResponseAppMngm.h"
#include "RenderResponseSysMngm.h"
#include "RenderResponseSysStatus.h"
#include "RenderResponseFtp.h"
#include "RenderResponseTimeMachine.h"
#include "RenderResponseSetupWizard.h"
#include "RenderResponseAppDownloads.h"
#include "RenderResponseAddOn.h"
#include "RenderResponseDashboard.h"
#include "RenderResponseFileStation.h"
#include "RenderResponseP2pDownloads.h"
#include "RenderResponseS3.h"
#include "RenderResponseGoogleDrive.h"
#include "RenderResponseDropbox.h"
#include "RenderResponseAirplay.h"
#include "RenderResponseMyDlink.h"

#include <TAppSettings>
#include <TWebApplication>

const QString CGI_PARA_CMD_NAME = "cmd";

const char VALID_CLIENT_ID[][255] = {
    "CURIOSITY_SUW",
    "CURIOSITY_FDR",
    "CURIOSITY_MBA"
};

CgiController::CgiController(/*const CgiController &other*/)
    //: ApplicationController()
    : m_pParseCmd(NULL)
{
    tDebug("\n  --------------------------- start -----------------------------------");
#ifdef SIMULATOR_MODE
    tDebug("** SIMULATOR_MODE is enabled. **");
#endif
}


CgiController::~CgiController()
{
    if(m_pParseCmd)
        delete m_pParseCmd;

    tDebug("\n  ---------------------------- end -------------------------------------\n");
}

void CgiController::process()
{
    cgiInit();
    cgiResponse();
}

void CgiController::processGoogleDrive() {
    cgiInit(CMD_GRP_GOOGLE_DRIVE);
    cgiResponse();
}

void CgiController::cgiInit(int group) {
    /* Parse command */
    QVariantMap parasMap = httpRequest().allParameters();
    QString paraCmd = parasMap.value(CGI_PARA_CMD_NAME).toString();
    tDebug("<< %s >>", paraCmd.toLocal8Bit().data());

    m_pParseCmd = new ParseCmd(paraCmd, group);

    /* Verify client which ia valid */

#ifndef SIMULATOR_MODE
    if(m_pParseCmd->getFilterType() == COOKIE_REQ_CMDS) {
        if(!isValidClient()) {
            renderErrorResponse(Tf::NotFound);
            return;
        }
    }
#endif

}

void CgiController::cgiResponse() {

    if(!m_pParseCmd)
        return;

    //    QString key = Tf::appSettings()->value(Tf::SessionCsrfProtectionKey).toString();
    RenderResponse *pRrep = NULL;
    CGI_COMMAND cmd = static_cast<CGI_COMMAND>(m_pParseCmd->getCGICmd());
    pRrep = getRenderResponseBaseInstance(httpRequest(), cmd);
    if(!pRrep) {
        tError("CgiController::index() %d -- could not create render instance.", cmd);
        return;
    }
    pRrep->preRender();

    /* render */
    switch(m_pParseCmd->getRenderType()) {
    case RENDER_TYPE_NULL:
        renderErrorResponse(Tf::OK);
        break;
    case RENDER_TYPE_STRING: {
        QString str = pRrep->getVar().toString();
        if(cmd == CMD_UI_CHECK_WTO)
            str = isValidClient(true) ? "success" : "fail";
        renderText(str);
        break;
    }
    case RENDER_TYPE_XML:
    {
        QDomDocument doc;
        QString str = pRrep->getVar().toString();
        doc.setContent(str);
        renderXml(doc);
    }
        break;
    case RENDER_TYPE_JOSEN:
        renderJson(pRrep->getVar().toJsonDocument());
        break;
    case RENDER_TYPE_FILE:
    {
        bool bRemoveFile = false;
        if(m_pParseCmd->getCGICmd() == CMD_DOWNLOAD)
            bRemoveFile = true;
        QFileInfo file(pRrep->getVar().toString());
        contentType();
        if(file.exists() && file.isFile())
            sendFile(pRrep->getVar().toString(), "application/octet-stream", file.fileName(), bRemoveFile);
        else
            tDebug("file %s doesn't exist.", pRrep->getVar().toByteArray().data());
    }
        break;
    case RENDER_TYPE_HTML:
        //render("index");
        renderText(pRrep->getVar().toString());
        break;
    case RENDER_TYPE_REDIRECT:
        redirect(QUrl(pRrep->getVar().toString()));
        break;
    case RENDER_TYPE_USER_LOGIN:
    {
        RenderResponseHome *pRrepHome = qobject_cast<RenderResponseHome *>(pRrep);
        QList<TCookie> cookies = pRrepHome->getCookies();
        for(auto e : cookies)
            addCookie(e);

        QDateTime expire = QDateTime::currentDateTime();
        expire = expire.addSecs(31536000);    // 1 year in seconds.
        for(TCookie e : httpRequest().cookies()) {
            bool add = false;
            if(QString(e.name()) == QString("rembMe") && pRrepHome->getRemMe())
                add = true;
            else if(e.name() == QString("password") || e.name() == QString("uname"))
                add = true;
            
            if(add) {
                e.setExpirationDate(expire);
                e.setPath("/");
                addCookie(e);
                tDebug("addCookie: %s", e.name().data());
            }
        }

        QPair<QString, uint> s = pRrepHome->getSession();
        if(!s.first.isEmpty()) {
            if(session().contains(s.first))
                session().remove(s.first);
            session().insert(s.first, s.second);
        }
        //User user = pRrepHome->getUser();
        //bool islogin = userLogin(&user);
        //tDebug("sss %d", islogin);

        QString redirectUrl;
        QString protocol = "http://";
        if(pRrepHome->getIfRedirectSsl())
            protocol = "https://";
        redirectUrl = protocol + httpRequest().header().rawHeader("host") + pRrep->getVar().toString();

        redirect(QUrl(redirectUrl));
    }
        break;
    case RENDER_TYPE_USER_LOGOUT:
    {
        RenderResponseHome *pRrepHome = qobject_cast<RenderResponseHome *>(pRrep);
        session().remove(pRrepHome->getUserLogout());
        redirect(QUrl(pRrep->getVar().toString()));
        break;
    }
    case RENDER_TYPE_FILE_REMOVE:
    {
        bool isSendOK = false;
        QFile::remove("/tmp/syslogsendok");
        QFileInfo file(pRrep->getVar().toString());
        if(file.exists() && file.isFile())
            isSendOK = sendFile(pRrep->getVar().toString(), "application/octet-stream", file.fileName(), true);
        else
            tDebug("file %s doesn't exist.", pRrep->getVar().toByteArray().data());
        if (isSendOK)
        {
            QProcess process;
            process.setStandardOutputFile("/tmp/syslogsendok");
            process.start("echo 1");
            process.waitForFinished();
        }
    }
        break;
    default:
        break;
    }

    if(pRrep)
        delete pRrep;

}

RenderResponse *CgiController::getRenderResponseBaseInstance(THttpRequest &req, CGI_COMMAND cmd)
{
    if(cmd < CMD_NONE)
        return NULL;

    RenderResponse *pRrep = NULL;
    if(cmd == CMD_NONE) {
        if( req.header().path().contains("info.cgi") ||
            req.header().path().contains("mydlink.cgi"))
            pRrep = new RenderResponseMyDlink(req, cmd);
        else
            tError("CgiController::index() -- command: (null) is an invalided command");
    }
    else if(cmd < CMD_DISK_END)
        pRrep = new RenderResponseDisk(req, cmd);
    else if(cmd < CMD_LONGIN_END)
        pRrep = new RenderResponseHome(req, cmd);
    else if(cmd < CMD_NETWORK_END)
        pRrep = new RenderResponseNetwork(req, cmd);
    else if(cmd < CMD_ACCOUNT_END)
        pRrep = new RenderResponseAccount(req, cmd);
    else if(cmd < CMD_NETSHARE_END)
        pRrep = new RenderResponseNetShare(req, cmd);
    else if(cmd < CMD_APP_MNGM_END)
        pRrep = new RenderResponseAppMngm(req, cmd);
    else if(cmd < CMD_SYS_MNGM_END)
        pRrep = new RenderResponseSysMngm(req, cmd);
    else if(cmd < CMD_SYS_STATUS_END)
        pRrep = new RenderResponseSysStatus(req, cmd);
    else if(cmd < CMD_FTP_SERVER_END)
        pRrep = new RenderResponseFtp(req, cmd);
    else if(cmd < CMD_TIME_MACHINE_END)
        pRrep = new RenderResponseTimeMachine(req, cmd);
    else if(cmd < CMD_SETUP_WIZARD_END)
        pRrep = new RenderResponseSetupWizard(req, cmd);
    else if(cmd < CMD_APP_DOWNLOAD_END)
        pRrep = new RenderResponseAppDownloads(req, cmd);
    else if(cmd < CMD_ADD_ON_END)
        pRrep = new RenderResponseAddOn(req, cmd);
    else if(cmd < CMD_DASHBOARD_END) {
        RenderResponseDashboard *pDashboard = new RenderResponseDashboard(req, cmd);
        pDashboard->setSession(session());
        pRrep = pDashboard;
    }
    else if(cmd < CMD_FILE_END)
        pRrep = new RenderResponseFileStation(req, cmd);
    else if(cmd < CMD_P2P_END)
        pRrep = new RenderResponseP2pDownloads(req, cmd);
    else if(cmd < CMD_S3_END)
        pRrep = new RenderResponseS3(req, cmd);
    else if(cmd < CMD_GD_END)
        pRrep = new RenderResponseGoogleDrive(req, cmd);
    else if(cmd < CMD_DROPBOX_END)
        pRrep = new RenderResponseDropbox(req, cmd);
    else if(cmd < CMD_AIRPLAY_END)
        pRrep = new RenderResponseAirplay(req, cmd);

    return pRrep;

}

bool CgiController::isValidClient(bool bCookiesOnly) {

    bool bValidClient = false;

    if(!bCookiesOnly && httpRequest().cookie("username").isEmpty()) {
        if(     httpRequest().header().hasRawHeader("Security-Token")
             && httpRequest().header().hasRawHeader("Client-ID")
             && httpRequest().header().hasRawHeader("Time-Stamp")) {

            QByteArray securityTokenLine = httpRequest().header().rawHeader("Security-Token");
            QByteArray clientIdLine = httpRequest().header().rawHeader("Client-ID");
            QByteArray timeStampLine = httpRequest().header().rawHeader("Time-Stamp");

            QByteArray securityTokenValue = securityTokenLine.mid(securityTokenLine.indexOf(":") + 1);
            QByteArray clientIdValue = clientIdLine.mid(clientIdLine.indexOf(":") + 1);
            QByteArray timeStampValue = timeStampLine.mid(timeStampLine.indexOf(":") + 1);

            bool bValidClientId = false;
            int size = sizeof(VALID_CLIENT_ID)/sizeof(VALID_CLIENT_ID[0]);
            for(int i = 0; i < size; i++)
                if(clientIdValue == QByteArray(VALID_CLIENT_ID[i]))
                    bValidClientId = true;

            if(bValidClientId) {

                //key[0-10] + Client-ID + key[11-23] + Time-Stamp + key[24-31]
                QByteArray key = "23ee20abd0cc6add605da13f4c31d5e3";
                QByteArray token = key.insert(24, timeStampValue).insert(11, clientIdValue);
                QByteArray hash = QCryptographicHash::hash(token, QCryptographicHash::Sha1).toHex();

                if(hash == securityTokenValue) {
                    bValidClient = true;
                    tDebug("Valid client has been checked.");
                }
                else {
                    tDebug("securityTokenValue: %s, current hash: %s", securityTokenValue.data(), hash.data());
                }
            }
        }
    }
    else {

        /* clear expired sessions */
        QMapIterator<QString, QVariant> i(session());
        while (i.hasNext()) {
            i.next();
            int diff = i.value().toInt() - QDateTime::currentDateTime().toTime_t();
            if(diff <= 0) {
                if(i.key().compare(TAppSettings::instance()->value(Tf::SessionCsrfProtectionKey).toString()) != 0) {
                    session().remove(i.key());
                    tDebug("remove session: %s", i.key().toLocal8Bit().data());
                }
            }
        }

        for(TCookie c : httpRequest().cookies())
            if(c.name() == "username") {
                if(session().value(c.value()).toInt() > 0) {
                    session()[c.value()] = QDateTime::currentDateTime().toTime_t() + LOGIN_TIMOUT;
                    bValidClient = true;
                    break;
                }
            }

    }

    return bValidClient;
}

T_REGISTER_CONTROLLER(cgicontroller);
