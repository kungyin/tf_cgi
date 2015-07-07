#include <QFileInfo>
#include <QCryptographicHash>

#include "AppDefine.h"
#include "CgiController.h"
#include "ParseCmd.h"

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

//#include <TAppSettings>

const QString CGI_PARA_CMD_NAME = "cmd";

const char VALID_CLIENT_ID[][255] = {
    "CURIOSITY_SUW",
    "CURIOSITY_FDR",
    "CURIOSITY_MBA"
};

CgiController::CgiController(const CgiController &other)
    : ApplicationController()
{}

void CgiController::index()
{

/* Parse command */
    QVariantMap parasMap = httpRequest().allParameters();
    QString paraCmd = parasMap.value(CGI_PARA_CMD_NAME).toString();
    tDebug("CgiController::index() -- command: %s", paraCmd.toLocal8Bit().data());

    ParseCmd parseCmd(paraCmd);
    CGI_COMMAND cmd = static_cast<CGI_COMMAND>(parseCmd.getCGICmd());
    if(cmd == CMD_NONE) {
        tError("CgiController::index() -- command: %s is an invalided command", paraCmd.toLocal8Bit().data());
        return;
    }

/* Verify client which ia valid */

#ifdef SIMULATOR_MODE
    tDebug("SIMULATOR_MODE is enabled.");
#else
    if(parseCmd.getFilterType() == COOKIE_REQ_CMDS) {
        if(!isValidClient()) {
            renderErrorResponse(Tf::NotFound);
            return;
        }
    }
#endif

//    QString key = Tf::appSettings()->value(Tf::SessionCsrfProtectionKey).toString();

//    tDebug("key -- %s", key.toLocal8Bit().data());

//    QByteArray csrfId = session().value(key).toByteArray();
//    tDebug("csrf id -- %s", csrfId.data());

//    QByteArray id = session().id();
//    tDebug("id -- %s", id.data());

//    tDebug("CgiController::index() -- %s", authenticityToken().data());

//    tDebug("size -- %d", httpRequest().multipartFormData().size("file"));
//    tDebug("size -- %d", httpRequest().multipartFormData().entity("name").fileSize());

    RenderResponse *pRrep = NULL;
    pRrep = getRenderResponseBaseInstance(httpRequest(), cmd);
    if(!pRrep) {
        tError("CgiController::index() -- could not create render instance.");
        return;
    }
    pRrep->preRender();

    /* render */
    switch(parseCmd.getRenderType()) {
    case RENDER_TYPE_NULL:
        renderErrorResponse(Tf::OK);
        break;
    case RENDER_TYPE_STRING:
        renderText(pRrep->getStr());
        break;
    case RENDER_TYPE_XML:
        renderXml(pRrep->getDoc());
        break;
    case RENDER_TYPE_JOSEN:
        // todo: renderJson();
        break;
    case RENDER_TYPE_FILE:
    {
        QFileInfo file(pRrep->getStr());
        if(file.exists() && file.isFile())
            sendFile(pRrep->getStr(), "application/octet-stream", file.fileName());
        else
            tDebug("file %s doesn't exist.", pRrep->getStr().toLocal8Bit().data());
    }
        break;
    case RENDER_TYPE_HTML:
        //render("index");
        renderText(pRrep->getStr());
        break;
    case RENDER_TYPE_REDIRECT:
        redirect(QUrl(pRrep->getStr()));
        break;
    case RENDER_TYPE_REDIRECT_WITH_COOKIE:
    {
        QList<TCookie> cookies = pRrep->getCookies();
        for(auto e : cookies)
            addCookie(e);
        redirect(QUrl(pRrep->getStr()));
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
    if(cmd <= CMD_NONE)
        return NULL;

    RenderResponse *pRrep = NULL;
    if(cmd < CMD_DISK_END)
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
    else
        bValidClient = true;

    return bValidClient;
}

T_REGISTER_CONTROLLER(cgicontroller);
