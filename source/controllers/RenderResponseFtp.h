#ifndef RENDERRESPONSEFTP_H
#define RENDERRESPONSEFTP_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseFtp : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseFtp(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseFtp();

    virtual void preRender();

private:

    void servergetconfig();
    void serverexiprenew();
    void p2pgetport();
    void serverblockiplist();
    void serverblockipadd();
    void serverenable();
};

#endif // RENDERRESPONSEFTP_H

