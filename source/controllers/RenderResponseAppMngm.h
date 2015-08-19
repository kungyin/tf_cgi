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
    void generateNfsEnable();
    void generateCheckDb();
    void generateUpnpAvServerPathList();
    void generateUpnpAvServerGetConfig();
    void generateUpnpAvServer();
    void generateUpnpAvServerGetSqldbState();
    void generateGuiCodepageGetList();
    void generateItunesServerGetXml();
    void generateItunesServerReady();
    void generateUpnpAvServerCheckPath();
    void generateUpnpAvServerPathSetting();
    void generateSqldbStopFinish();
    void generateUpnpAvServerPrescan();
    void generateUpnpAvServerPathDel();
    void generateUpnpAvServerSetting();
    void generateGuiCodepageAdd();
    void generateItunesServerSetting();
    void generateItunesServerCheckPs();
    void generateItunesServerRefresh();
    void generateItunesServerRefreshState();

    void generateSyslogSearch();
    void generateGetVolumeInfo();
    void generateSyslogGetLogFileOption();
    void generateSyslogGetConfig();
    void generateSyslogGetSelectOption();
    void generateSyslogSetConfig();
    void generateSyslogExport();
    void generateSyslogGetExportStatus();
    void generateSyslogClear();

    void generateLocalBackupNow();
    void generateLocalBackupList();
    void generateLocalBackupSambaFormat();
    void generateLocalBackupAdd();
    void generateLocalBackupInfo();
    void generateLocalBackupRenew();
    void generateLocalBackupDel();
    void generateLocalBackupTest();
    void generateLocalBackupStart();
    void generateLocalBackupStop();

    void generateGetRsyncInfo();
    void generateSetRsyncServer();

    void generateGetBackupList();
    void generateGetAllTaskName();
    void generateServerTest();
    void generateCheckRsyncRw();
    void generateSetSchedule();
    void generateGetModifyInfo();
    void generateDelSchedule();
    void generateEnableDisableSchedule();
    void generateBackupNow();

    void generateMtpInfoGet();
    void generateUsbBackupInfoGet();
    void generateMtpInfoSet();
    void generateUsbBackupInfoSet();
    void generateGetUsbMappingInfo();

private:
    void renewOrAdd(bool);
    QString getIcon(QString);

};


#endif // RENDERRESPONSEAPPMNGM_H
