#include <QFileInfo>

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

const QString CGI_PARA_CMD_NAME = "cmd";

CgiController::CgiController(const CgiController &other)
    : ApplicationController()
{}

void CgiController::index()
{

    QVariantMap parasMap = httpRequest().allParameters();
    QString paraCmd = parasMap.value(CGI_PARA_CMD_NAME).toString();
    tDebug("CgiController::index() -- command: %s", paraCmd.toLocal8Bit().data());

    ParseCmd parseCmd(paraCmd);
    CGI_COMMAND cmd = static_cast<CGI_COMMAND>(parseCmd.getCGICmd());
    if(cmd == CMD_NONE) {
        tError("CgiController::index() -- command: %s is an invalided command", paraCmd.toLocal8Bit().data());
        return;
    }

#ifndef SIMULATOR_MODE
//    if(parseCmd.getFilterType() == COOKIE_REQ_CMDS) {
//        if(httpRequest().cookie("username").isEmpty()) {
//            renderErrorResponse(Tf::NotFound);
//            return;
//        }
//    }
#endif


    //tDebug("CgiController::index() -- %s", authenticityToken().data());

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

    return pRrep;

}

T_REGISTER_CONTROLLER(cgicontroller);
