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

    void generateIsBuildInLanguage(QDomDocument &);
    void generateSetUserLanguage(QDomDocument &);
    void generateGetUserLanguage(QDomDocument &);
    void generateGetSslInfo(QDomDocument &);
    void generateUICheckWto(QString &);
    void generateFWStatus(QString &);
    void generateLogin(QString &);
    void generateLogout(QString &);

};

#endif // RENDERRESPONSEHOME_H
