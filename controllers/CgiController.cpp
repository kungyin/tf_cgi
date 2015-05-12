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

const QString CGI_PARA_CMD_NAME = "cmd";

CgiController::CgiController(const CgiController &other)
    : ApplicationController()
{}

void CgiController::index()
{

#ifndef SIMULATOR_MODE
    if(!httpRequest().header().path().startsWith("/cgi-bin/login_mgr.cgi")) {
        //std::string user = my_cookie.value();
        if(httpRequest().cookie("username").isEmpty()) {
            renderErrorResponse(Tf::NotFound);
            return;
        }
    }
#endif   

    QVariantMap parasMap = httpRequest().allParameters();
    if(parasMap.contains(CGI_PARA_CMD_NAME)) {
        QString paraCmd = parasMap[CGI_PARA_CMD_NAME].toString();
        tDebug("CgiController::index(): command: %s", paraCmd.toLocal8Bit().data());

        ParseCmd c(paraCmd);
        CGI_COMMAND cmd = c.getCGICmd();
        if(cmd == CMD_NONE)
            return;

        RenderResponse *pRrep = NULL;
        pRrep = getRenderResponseBaseInstance(parasMap, cmd);
        if(!pRrep)
            return;
        RENDER_TYPE type = pRrep->preRender();

        if(paraCmd.compare("login") == 0) {
            QString name = static_cast<RenderResponseHome *>(pRrep)->getUsername();
            QDateTime age = QDateTime::currentDateTime();;
            if(!name.isEmpty())
                age = age.addSecs(31536000);    // 1 year in seconds.

            if(parasMap.contains("username"))
                addCookie("uname", parasMap["username"].toByteArray(), age, "/");
            addCookie("rembMe", "checked", age, "/");
            if(parasMap.contains("pwd"))
                addCookie("password", parasMap["pwd"].toByteArray(), age, "/");

            int status = static_cast<RenderResponseHome *>(pRrep)->getLoginStatus();
            if(status == 1) {
                if(parasMap.contains("username")) {
                    TCookie cookie("username", parasMap["username"].toByteArray());
                    cookie.setPath("/");
                    addCookie(cookie);
                }
                redirect(QUrl("../web/home.html?v=8401878"));
            }
            else if(status == 0){
                redirect(QUrl("../web/relogin.html"));
            }
        }
        else if(paraCmd.compare("logout") == 0) {
            redirect(QUrl(".."));
        }

        /* render */
        switch(type) {
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
        case RENDER_TYPE_HTML:
            //render("index");
            renderText(pRrep->getStr());
            break;
        default:
            break;
        }

        if(pRrep)
            delete pRrep;
    }
}

RenderResponse *CgiController::getRenderResponseBaseInstance(QVariantMap &map, CGI_COMMAND cmd)
{
    if(cmd <= CMD_NONE)
        return NULL;

    RenderResponse *pRrep = NULL;
    if(cmd < CMD_DISK_END)
        pRrep = new RenderResponseDisk(map, cmd);
    else if(cmd < CMD_LONGIN_END)
        pRrep = new RenderResponseHome(map, cmd);
    else if(cmd < CMD_NETWORK_END)
        pRrep = new RenderResponseNetwork(map, cmd);
    else if(cmd < CMD_ACCOUNT_END)
        pRrep = new RenderResponseAccount(map, cmd);
    else if(cmd < CMD_NETSHARE_END)
        pRrep = new RenderResponseNetShare(map, cmd);
    else if(cmd < CMD_APP_MNGM_END)
        pRrep = new RenderResponseAppMngm(map, cmd);
    else if(cmd < CMD_SYS_MNGM_END)
        pRrep = new RenderResponseSysMngm(map, cmd);

    return pRrep;

}

T_REGISTER_CONTROLLER(cgicontroller);
