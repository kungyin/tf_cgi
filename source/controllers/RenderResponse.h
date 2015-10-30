#ifndef RENDERRESPONSE_H
#define RENDERRESPONSE_H

#include "applicationcontroller.h"
#include "CommandDefine.h"
#include "AppDefine.h"

class T_CONTROLLER_EXPORT RenderResponse : public QObject {
    Q_OBJECT

public:

    RenderResponse();
    virtual void preRender() = 0;
    virtual ~RenderResponse() {}

    QVariant &getVar() { return m_var; }
//    int getSessionDiff() { return m_diffTime; }
//    void setSessionDiff(int diff) { m_diffTime = diff; }
    void setSession(TSession &session) { m_pSession = &session; }

signals:
    void typeChanged(RENDER_TYPE);

protected:

    QStringList getAPIStdOut(QString, bool bOneLine = false, QString splitChar = ",", int iUseSh = 0, bool bBackground = false);
    QStringList getAPIStdOut(QString, QStringList, bool bOneLine = false, QString splitChar = ",", bool bUseSh = false);
    bool startDetached(QString, QStringList&);
    QStringList getAPIFileOut(QString, bool bOneLine = false, QString splitChar = ",");
    bool setNasCfg(QString, QString, QString, QString configFile = SYS_CONFIG_FILE, QString space = " ");
    bool setNasCfg(QString, QMap<QString, QString> &);
    bool setNasCfg(QMap<QString, QMap<QString, QString>> &);
    QMap<QString, QString> getNasCfg(QString);
    bool readXml(const QString &, QDomDocument &);

    QString allParametersToString(bool bDecode = true, QString before = QString::null, QString after = QString::null);
    QString addPoundSign(QString, QString splitSign = ",");
    QString sizeHuman(qint64);
    bool replaceVoltoRealPath(QString &, bool reverse = false);
    TSession findSession(const QByteArray &);
    QString sessionDirPath();

    int getTotalPages(int, int);

    CGI_COMMAND m_cmd;
    QVariant m_var;

    THttpRequest *m_pReq;
    TSession *m_pSession;

private:

    int m_diffTime;

};

#endif // RENDERRESPONSE_H
