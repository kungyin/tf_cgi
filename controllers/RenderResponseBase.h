#ifndef RESPONSEBODYBASE_H
#define RESPONSEBODYBASE_H

#include "applicationcontroller.h"
#include "CommandDefine.h"

enum RENDER_TYPE {
    RENDER_TYPE_UNKNOWN,
    RENDER_TYPE_STRING,
    RENDER_TYPE_XML,
    RENDER_TYPE_JOSEN
};

class T_CONTROLLER_EXPORT RenderResponseBase : public QObject {
    Q_OBJECT
public:

    virtual RENDER_TYPE preRender() = 0;
    virtual ~RenderResponseBase() {}

    QDomDocument &getDoc() { return m_doc; }
    QString &getStr() { return m_str; }

protected:

    QStringList getAPIStdOut(QString, bool bOneLine = false);
    bool setNasCfg(QString, QString, QString);
    bool setNasCfg(QString, QMap<QString, QString> &);
    QMap<QString, QString> getNasCfg(QString);

    CGI_COMMAND m_cmd;
    RENDER_TYPE m_renderType;
    QDomDocument m_doc;
    QString m_str;

    QVariantMap *m_pMap;

private:

};

#endif // RESPONSEBODYBASE_H
