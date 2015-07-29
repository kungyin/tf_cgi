#ifndef RENDERRESPONSEAPPMNGM_H
#define RENDERRESPONSEAPPMNGM_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseAppMngm : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseAppMngm(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseAppMngm();

    virtual void preRender();

private:

    void generateSetAfp();
    void generateNfsEnable(QDomDocument &);
    void generateCheckDb();
    void generateUpnpAvServerPathList(QDomDocument &);
    void generateUpnpAvServerGetConfig(QDomDocument &);
    void generateUpnpAvServer(QDomDocument &);
    void generateUpnpAvServerGetSqldbState(QDomDocument &);
    void generateGuiCodepageGetList(QDomDocument &);
    void generateItunesServerGetXml(QDomDocument &);
    void generateItunesServerReady(QDomDocument &);
    void generateUpnpAvServerCheckPath(QDomDocument &);
    void generateUpnpAvServerPathSetting(QDomDocument &);
    void generateSqldbStopFinish(QDomDocument &);
    void generateUpnpAvServerPrescan(QDomDocument &);
    void generateUpnpAvServerPathDel(QDomDocument &);
    void generateUpnpAvServerSetting();
    void generateGuiCodepageAdd(QDomDocument &);
    void generateItunesServerSetting(QDomDocument &);
    void generateItunesServerCheckPs(QDomDocument &);
    void generateItunesServerRefresh(QDomDocument &);
    void generateItunesServerRefreshState(QDomDocument &);

    void generateSyslogSearch(QDomDocument &);
    void generateGetVolumeInfo(QDomDocument &);
    void generateSyslogGetLogFileOption(QDomDocument &);
    void generateSyslogGetConfig(QDomDocument &);
    void generateSyslogGetSelectOption(QDomDocument &);
    void generateSyslogSetConfig(QString &);
    void generateSyslogExport(QString &);
    void generateSyslogGetExportStatus(QDomDocument &);
    void generateSyslogClear();

    void generateLocalBackupNow(QDomDocument &);
    void generateLocalBackupList(QDomDocument &);
    void generateLocalBackupSambaFormat(QDomDocument &);
    void generateLocalBackupAdd(QString &);
    void generateLocalBackupInfo(QDomDocument &);
    void generateLocalBackupRenew(QString &);
    void generateLocalBackupDel(QDomDocument &);
    void generateLocalBackupTest(QDomDocument &);

    void generateGetRsyncInfo(QDomDocument &);
    void generateSetRsyncServer(QString &);

    void generateGetBackupList(QDomDocument &);
    void generateGetAllTaskName(QDomDocument &);
    void generateServerTest(QDomDocument &);
    void generateCheckRsyncRw(QDomDocument &);
    void generateSetSchedule(QString &);
    void generateGetModifyInfo(QDomDocument &);
    void generateDelSchedule(QString &);
    void generateEnableDisableSchedule(QString &);
    void generateBackupNow(QString &);

    void generateMtpInfoGet(QDomDocument &);
    void generateUsbBackupInfoGet(QDomDocument &);
    void generateMtpInfoSet(QDomDocument &);
    void generateUsbBackupInfoSet(QDomDocument &);
    void generateGetUsbMappingInfo(QDomDocument &);

private:
    void renewOrAdd(bool);
    QString getIcon(QString);

};


#endif // RENDERRESPONSEAPPMNGM_H
