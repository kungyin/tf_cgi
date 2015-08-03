#ifndef RENDERRESPONSEHOME_H
#define RENDERRESPONSEHOME_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseHome : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseHome(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseHome();

    virtual void preRender();

private:

    void generateIsBuildInLanguage();
    void generateSetUserLanguage();
    void generateGetUserLanguage();
    void generateGetSslInfo();
    void generateUICheckWto();
    void generateFWStatus();
    void generateLogin();
    void generateLogout();
    void generateGetLogItem();

};

#endif // RENDERRESPONSEHOME_H
