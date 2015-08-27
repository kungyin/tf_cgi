#ifndef RENDERRESPONSESYSMNGM_H
#define RENDERRESPONSESYSMNGM_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseSysMngm : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseSysMngm(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseSysMngm();

    virtual void preRender();

private:

    void generateGetTime();
    void generateManualTime();
    void generateTimezone();
    void generateNtpTime();
    void generateGetTimeStatus();
    void generateGetDeviceInfo();
    void generateDevice();

    void generateDetectDangerous();
    void generateGetIdle();
    void generateGetTemperature();
    void generateGetRestoreStatus();
    void generateRestart();
    void generateRestore();
    void generateShutdown();
    void generateIdle();
    void generateTemperature();
    void generateBackupConf();
    void generateRestoreConf();

    void generateGetPowerMgr();
    void generatePowerManagement();
    void generatePowerRecovery();
    void generateFan();
    void generatePowerOffSchedule();

    void generateGetEmailXml();
    void generateGetEventXml();
    void generateEmailEvent();
    void generateEmail();
    void generateEmailTest();
    void generateEmailTestResult();
    void generateEmailClear();

    void generateSmsAdd();
    void generateSmsModify();
    void generateSmsTest();
    void generateSmsTestResult();
    void generateSmsDel();

    void generateLogSystem();
    void generateGetLogInfo();
    void generateLogServer();
    void generateSendLogTest();
    void generateLogBackup();
    void generateLogClear();

    void generateUpsInfo();
    void generateUpsMaterList();
    void generateUpsSlaveSetting();
    void generateUpsPs();
    void generateUsbStorageUmount();
    void generateUsbPrinterClear();

    void generateFirmVXml();
    void generateCheckPowerSch();
    void generateFirmwareInitUpload();
    void generateFirmwareUpload();
    void generateGetPercentage();
    void generateGetFirmwareVerify();
    void generateGetUpFw();
    void generateReboot();

    void daemonize();

};


#endif // RENDERRESPONSESYSMNGM_H
