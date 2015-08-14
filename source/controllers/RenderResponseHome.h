#ifndef RENDERRESPONSEHOME_H
#define RENDERRESPONSEHOME_H

#include "RenderResponse.h"
//#include "user.h"

class T_CONTROLLER_EXPORT RenderResponseHome : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseHome(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseHome();

    virtual void preRender();

    QList<TCookie> &getCookies() { return m_cookies; }
    //User &getUser() { return m_loginUser; }

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

    QList<TCookie> m_cookies;
    //User m_loginUser;

};

#endif // RENDERRESPONSEHOME_H
