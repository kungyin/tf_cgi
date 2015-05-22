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

    void generateLogSystem(QString &);
    void generateGetLogInfo(QDomDocument &);
    void generateLogServer();
    void generateSendLogTest();
    void generateLogBackup(QString &);
    void generateLogClear();

};


#endif // RENDERRESPONSESYSMNGM_H
