#ifndef RENDERRESPONSE_H
#define RENDERRESPONSE_H

#include "applicationcontroller.h"
#include "CommandDefine.h"

enum RENDER_TYPE {
    RENDER_TYPE_UNKNOWN,
    RENDER_TYPE_NULL,
    RENDER_TYPE_STRING,
    RENDER_TYPE_XML,
    RENDER_TYPE_JOSEN,
    RENDER_TYPE_FILE,
    RENDER_TYPE_HTML
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

protected:

    QStringList getAPIStdOut(QString, bool bOneLine = false, QString splitChar = ",");
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

#endif // RENDERRESPONSE_H
