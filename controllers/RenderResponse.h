#ifndef RENDERRESPONSE_H
#define RENDERRESPONSE_H

#include "applicationcontroller.h"
#include "CommandDefine.h"
#include "AppDefine.h"

class T_CONTROLLER_EXPORT RenderResponse : public QObject {
    Q_OBJECT
public:

    virtual void preRender() = 0;
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
    QDomDocument m_doc;
    QString m_str;
    QString m_file;
    QList<TCookie> m_cookies;

    THttpRequest *m_pReq;

private:

};

#endif // RENDERRESPONSE_H
