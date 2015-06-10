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
    void generateGetStatus(QDomDocument &);
    void generateStatusVolumeInfo(QDomDocument &);
    void generateUsbStorageInfo(QDomDocument &);
    void generateMtpInfo(QDomDocument &);
    void generateUsbPrinterInfo(QDomDocument &);
    void generateUpsInfo2(QDomDocument &);

    void generateSmartXmlCreateDeviceList(QDomDocument &);
    void generateSmartXmlCreateSmartInfo(QDomDocument &);
    void generateResource(QDomDocument &);
    void generateGetService(QDomDocument &);
    void generateModuleList(QDomDocument &);

};

#endif // RENDERRESPONSESYSSTATUS_H