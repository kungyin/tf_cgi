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

    QVariant &getVar() { return m_var; }

signals:
    void typeChanged(RENDER_TYPE);

protected:

    QStringList getAPIStdOut(QString, bool bOneLine = false, QString splitChar = ",", bool bUseSh = false);
    bool startDetached(QString, QStringList&);
    QStringList getAPIFileOut(QString, bool bOneLine = false, QString splitChar = ",");
    bool setNasCfg(QString, QString, QString);
    bool setNasCfg(QString, QMap<QString, QString> &);
    bool setNasCfg(QMap<QString, QMap<QString, QString>> &);
    QMap<QString, QString> getNasCfg(QString);
    QString allParametersToString(bool bDecode = true, QString before = QString::null, QString after = QString::null);
    QString sizeHuman(qint64);
    void replaceVoltoRealPath(QString &);

    inline int getTotalPages(int, int);

    CGI_COMMAND m_cmd;
    QVariant m_var;

    THttpRequest *m_pReq;

private:

};

#endif // RENDERRESPONSE_H
