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

    void generateGetTime(QDomDocument &);
    void generateManualTime();
    void generateTimezone();
    void generateNtpTime();
    void generateGetTimeStatus(QDomDocument &);
    void generateGetDeviceInfo(QDomDocument &);
    void generateDevice();

    void generateDetectDangerous(QDomDocument &);
    void generateGetIdle(QString &);
    void generateGetTemperature(QDomDocument &);
    void generateGetRestoreStatus(QString &);
    void generateRestart(QString &);
    void generateRestore(QString &);
    void generateShutdown();
    void generateIdle();
    void generateTemperature();
    void generateBackupConf(QString &);
    void generateRestoreConf(QString &);

    void generateGetPowerMgr(QDomDocument &);
    void generatePowerManagement(QString &);
    void generatePowerRecovery();
    void generateFan();
    void generatePowerOffSchedule();

    void generateGetEmailXml(QDomDocument &);
    void generateGetEventXml(QDomDocument &);
    void generateEmailEvent(QString &);
    void generateEmail(QString &);
    void generateEmailTest();
    void generateEmailTestResult(QDomDocument &);
    void generateEmailClear(QString &);

    void generateLogSystem(QString &);
    void generateGetLogInfo(QDomDocument &);
    void generateLogServer();
    void generateSendLogTest();
    void generateLogBackup(QString &);
    void generateLogClear();

    void generateUpsInfo(QDomDocument &);
    void generateUpsSlaveSetting(QDomDocument &);
    void generateUpsPs(QDomDocument &);
    void generateUsbStorageUmount(QDomDocument &);
    void generateUsbPrinterClear(QDomDocument &);

    void generateFirmVXml(QDomDocument &);
    void generateCheckPowerSch(QString &);
    void generateFirmwareInitUpload(QString &);
    void generateFirmwareUpload(QString &);
    void generateGetPercentage(QString &);
    void generateGetFirmwareVerify(QString &);
    void generateGetUpFw(QString &);
    void generateReboot(QString &);

};


#endif // RENDERRESPONSESYSMNGM_H
