#include "CgiController.h"
#include "ParseCmd.h"
#include "RenderResponse.h"
#include "RenderResponseNetwork.h"

const QString CGI_PARA_CMD_NAME = "cmd";

CgiController::CgiController(const CgiController &other)
    : ApplicationController()
{}

void CgiController::index()
{

#ifdef SIMULATOR_MODE
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

        RenderResponseBase *pRrep = NULL;
        pRrep = getRenderResponseBaseInstance(parasMap, cmd);
        if(!pRrep)
            return;
        RENDER_TYPE type = pRrep->preRender();

        if(paraCmd.compare("login") == 0) {
            QString name = static_cast<RenderResponse *>(pRrep)->getUsername();
            QDateTime age = QDateTime::currentDateTime();;
            if(!name.isEmpty())
                age = age.addSecs(31536000);

            if(parasMap.contains("username"))
                addCookie("uname", parasMap["username"].toByteArray(), age, "/");
            addCookie("rembMe", "checked", age, "/");
            if(parasMap.contains("pwd"))
                addCookie("password", parasMap["pwd"].toByteArray(), age, "/");

            int status = static_cast<RenderResponse *>(pRrep)->getLoginStatus();
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
        case RENDER_TYPE_STRING:
            renderText(pRrep->getStr());
            break;
        case RENDER_TYPE_XML:
            renderXml(pRrep->getDoc());
            break;
        case RENDER_TYPE_JOSEN:
            // todo: renderJson();
            break;
        default:
            break;
        }

        if(pRrep)
            delete pRrep;
    }
}

RenderResponseBase *CgiController::getRenderResponseBaseInstance(QVariantMap &map, CGI_COMMAND cmd)
{
    if(cmd <= CMD_NONE)
        return NULL;

    RenderResponseBase *pRrep = NULL;
    if(cmd < CMD_DISK_END)
        pRrep = new RenderResponse(map, cmd);
    else if(cmd < CMD_LONGIN_END)
        pRrep = new RenderResponse(map, cmd);
    else if(cmd < CMD_NETWORK_END)
        pRrep = new RenderResponseNetwork(map, cmd);

    return pRrep;

}

T_REGISTER_CONTROLLER(cgicontroller);
