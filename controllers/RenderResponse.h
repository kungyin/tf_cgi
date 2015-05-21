#ifndef RENDERRESPONSE_H
#define RENDERRESPONSE_H

#include "applicationcontroller.h"
#include "CommandDefine.h"
#include "AppDefine.h"

enum RENDER_TYPE {
    RENDER_TYPE_UNKNOWN,
    RENDER_TYPE_NULL,
    RENDER_TYPE_STRING,
    RENDER_TYPE_XML,
    RENDER_TYPE_JOSEN,
    RENDER_TYPE_FILE,
    RENDER_TYPE_HTML,
    RENDER_TYPE_REDIRECT,
    RENDER_TYPE_REDIRECT_WITH_COOKIE,
};

//const int CGI_COMMANDS[][2] = {
//    {2,  3}
//};

class T_CONTROLLER_EXPORT RenderResponse : public QObject {
    Q_OBJECT
public:

    virtual RENDER_TYPE preRender() = 0;
    virtual ~RenderResponse() {}

    QDomDocument &getDoc() { return m_doc; }
    QString &getStr() { return m_str; }
    QString &getFile() { return m_file; }
    QList<TCookie> &getCookies() { return m_cookies; }

protected:

    QStringList getAPIStdOut(QString, bool bOneLine = false, QString splitChar = ",");
    bool setNasCfg(QString, QString, QString);
    bool setNasCfg(QString, QMap<QString, QString> &);
    QMap<QString, QString> getNasCfg(QString);

    CGI_COMMAND m_cmd;
    RENDER_TYPE m_renderType;
    QDomDocument m_doc;
    QString m_str;
    QString m_file;
    QList<TCookie> m_cookies;

    THttpRequest *m_pReq;

private:

};

#endif // RENDERRESPONSE_H
