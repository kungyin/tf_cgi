#ifndef RENDERRESPONSESYSSTATUS_H
#define RENDERRESPONSESYSSTATUS_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseSysStatus : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseSysStatus(QVariantMap &, CGI_COMMAND);
    virtual ~RenderResponseSysStatus();

    virtual RENDER_TYPE preRender();

private:
    void generateGetStatus(QDomDocument &);
    void generateStatusVolumeInfo(QDomDocument &);
    void generateUsbStorageInfo(QDomDocument &);
    void generateMtpInfo(QDomDocument &);
    void generateUsbPrinterInfo(QDomDocument &);
    void generateUpsInfo2(QDomDocument &);

};

#endif // RENDERRESPONSESYSSTATUS_H
