#include "CgiController.h"
#include "ParseCmd.h"
#include "RenderResponse.h"

const QString CGI_PARA_CMD_NAME = "cmd";

CgiController::CgiController(const CgiController &other)
    : ApplicationController()
{}

void CgiController::index()
{
    if(!httpRequest().header().path().startsWith("/cgi-bin/login_mgr.cgi")) {
        //std::string user = my_cookie.value();
        if(httpRequest().cookie("username").isEmpty()) {
            renderErrorResponse(Tf::NotFound);
            return;
        }
    }

    QVariantMap parasMap = httpRequest().allParameters();
    if(parasMap.contains(CGI_PARA_CMD_NAME)) {
        QString paraCmd = parasMap[CGI_PARA_CMD_NAME].toString();
        tDebug("command: %s", paraCmd.toLocal8Bit().data());

        ParseCmd c(paraCmd);
        CGI_COMMAND cmd = c.getCGICmd();

        RenderResponse rrep(parasMap, cmd);
        RENDER_TYPE type = rrep.preRender();

        if(paraCmd.compare("login") == 0) {
            QString name = rrep.getUsername();
            QDateTime age = QDateTime::currentDateTime();;
            if(!name.isEmpty())
                age = age.addSecs(31536000);

            if(parasMap.contains("username"))
                addCookie("uname", parasMap["username"].toByteArray(), age, "/");
            addCookie("rembMe", "checked", age, "/");
            if(parasMap.contains("pwd"))
                addCookie("password", parasMap["pwd"].toByteArray(), age, "/");

            int status = rrep.getLoginStatus();
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
            renderText(rrep.getStr());
            break;
        case RENDER_TYPE_XML:
            renderXml(rrep.getDoc());
            break;
        case RENDER_TYPE_JOSEN:
            // todo: renderJson();
            break;
        default:
            break;
        }

        tDebug("GGG: %s", httpRequest().header().path().data());
    }
}

T_REGISTER_CONTROLLER(cgicontroller);
