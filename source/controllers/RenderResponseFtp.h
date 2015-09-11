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

    void generateFtpServerGetConfig();
    void generateFtpServerExipRenew();
    void generateP2pGetPort();
    void generateFtpServerBlockIPList();
    void generateFtpServerBlockIPAdd();
    void generateFtpServerBlockIPDel();
    void generateFtpServerEnable();
    void generateFtpServerSetConfig();
};

#endif // RENDERRESPONSEFTP_H

