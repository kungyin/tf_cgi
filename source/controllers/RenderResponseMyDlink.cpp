#include "RenderResponseMyDlink.h"

RenderResponseMyDlink::RenderResponseMyDlink(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseMyDlink::~RenderResponseMyDlink() {
}

void RenderResponseMyDlink::preRender() {

    if(!m_pReq)
        return;

    if(m_pReq->header().path().contains("info.cgi"))
        generateInfo();
    else {

    }

}

/* todo */
void RenderResponseMyDlink::generateInfo() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_lan_mac_info", true, ";");
    QString fmtOut = "Product=dlink-8B21F7\n"
            "Model=DNS-320L-B\n"
            "Version=1.01.0905.2014\n"
            "Build=\n"
            "Macaddr=%1\n"
            "Wireless=NO\n"
            "Ptz=";

    QString ret = fmtOut.arg(apiOut.value(0));
    m_var = ret;

}

