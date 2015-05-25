#ifndef RENDERRESPONSEFTP_H
#define RENDERRESPONSEFTP_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseFtp : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseFtp(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseFtp();

    virtual RENDER_TYPE preRender();

private:

    void servergetconfig(QDomDocument &);
    void serverexiprenew(QDomDocument &);
    void p2pgetport(QDomDocument &);
    void serverblockiplist(QDomDocument &);
    void serverblockipadd(QDomDocument &);
    void serverenable(QDomDocument &);
};

#endif // RENDERRESPONSEFTP_H

