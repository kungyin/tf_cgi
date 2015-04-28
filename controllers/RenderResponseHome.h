#ifndef RENDERRESPONSEHOME_H
#define RENDERRESPONSEHOME_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseHome : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseHome(QVariantMap &, CGI_COMMAND);
    RenderResponseHome(const RenderResponseHome &other) {}
    virtual ~RenderResponseHome();

    virtual RENDER_TYPE preRender();

    QString getUsername() { return m_session; }
    int getLoginStatus() { return m_loginStatus; }

private:

    void generateIsBuildInLanguage(QDomDocument &);
    void generateGetUserLanguage(QDomDocument &);
    void generateGetSslInfo(QDomDocument &);
    void generateUICheckWto(QString &);
    void generateFWStatus(QString &);
    void generateLogin(QString &);
    void generateLogout(QString &);

    QString m_session;
    int m_loginStatus;

};

#endif // RENDERRESPONSEHOME_H
