#ifndef RENDERRESPONSE_H
#define RENDERRESPONSE_H

#include "RenderResponseBase.h"

class T_CONTROLLER_EXPORT RenderResponse : public RenderResponseBase {
    Q_OBJECT
public:
    RenderResponse(QVariantMap &, CGI_COMMAND);
    RenderResponse(const RenderResponse &other) {}
    virtual ~RenderResponse();

    virtual RENDER_TYPE preRender();

    QString getUsername() { return m_session; }
    int getLoginStatus() { return m_loginStatus; }


private:

    QStringList getAPIStdOut(QString);
    QString getAPIStdOutOneLine(QString);

    void generateVolumeStatus(QDomDocument &);
    void generateFMTGetSyncState(QDomDocument &);
    void generateFMTGetAutoRebuildInfo(QDomDocument &);
    void generateAJAXPlorerStop(QDomDocument &);
    void generateFMTCreateDiskMGR(QDomDocument &);
    void generateSmartHDList(QDomDocument &);
    void generateCreateTestList(QDomDocument &);
    void generateSmartScheduleList(QDomDocument &);
    void generateGetTestStatus(QDomDocument &);
    void generateSmartSetSchedule(QDomDocument &);
    void generateSmartDelSchedule(QDomDocument &);
    void generateSmartTestStart(QDomDocument &);
    void generateScanDiskInfo(QDomDocument &);
    void generateCheckDiskRemountState(QDomDocument &);
    void generateScanDiskRunE2fsck(QDomDocument &);
    void generateScanDiskFinish(QDomDocument &);

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

#endif // RENDERRESPONSE_H
