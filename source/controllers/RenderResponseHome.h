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
    QStringList &getSession() { return m_session; }
    QString &getUserLogout() { return m_userLogout; }

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
    QStringList m_session;
    QString m_userLogout;
    //User m_loginUser;

};

#endif // RENDERRESPONSEHOME_H
