#ifndef RENDERRESPONSESYSSTATUS_H
#define RENDERRESPONSESYSSTATUS_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseSysStatus : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseSysStatus(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseSysStatus();

    virtual void preRender();

private:
    void generateGetStatus();
    void generateStatusVolumeInfo();
    void generateUsbStorageInfo();
    void generateMtpInfo();
    void generateUsbPrinterInfo();
    void generateUpsInfo2();

    void generateSmartXmlCreateDeviceList();
    void generateSmartXmlCreateSmartInfo();
    void generateResource();
    void generateGetService();
    void generateModuleList();

};

#endif // RENDERRESPONSESYSSTATUS_H
