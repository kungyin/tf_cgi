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
#include "RenderResponseMyDlink.h"


//#include <TAppSettings>

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
    pRrep = getRenderResponseBaseInstance(httpRequest(), static_cast<CGI_COMMAND>(m_pParseCmd->getCGICmd()));
    if(!pRrep) {
        tError("CgiController::index() -- could not create render instance.");
        return;
    }
    pRrep->preRender();

    /* render */
    switch(m_pParseCmd->getRenderType()) {
    case RENDER_TYPE_NULL:
        renderErrorResponse(Tf::OK);
        break;
    case RENDER_TYPE_STRING:
        renderText(pRrep->getVar().toString());
        break;
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
        QStringList s = pRrepHome->getSession();
        if(!s.isEmpty())
            session().insert(s.value(0), s.value(1));
        //User user = pRrepHome->getUser();
        //bool islogin = userLogin(&user);
        //tDebug("sss %d", islogin);
        redirect(QUrl(pRrep->getVar().toString()));
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
    else if(cmd < CMD_DASHBOARD_END)
        pRrep = new RenderResponseDashboard(req, cmd);
    else if(cmd < CMD_FILE_END)
        pRrep = new RenderResponseFileStation(req, cmd);
    else if(cmd < CMD_P2P_END)
        pRrep = new RenderResponseP2pDownloads(req, cmd);
    else if(cmd < CMD_S3_END)
        pRrep = new RenderResponseS3(req, cmd);
    else if(cmd < CMD_GD_END)
        pRrep = new RenderResponseGoogleDrive(req, cmd);

    return pRrep;

}

bool CgiController::isValidClient() {
    bool bValidClient = false;

    if(httpRequest().cookie("username").isEmpty()) {
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
        for(TCookie c : httpRequest().cookies())
            if(c.name() == "username")
                if(session().value(c.value()).toString() == "1")
                    bValidClient = true;
    }

    return bValidClient;
}

T_REGISTER_CONTROLLER(cgicontroller);
