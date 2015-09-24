#ifndef RENDERRESPONSEMYDLINK_H
#define RENDERRESPONSEMYDLINK_H

#include "RenderResponseFileOpBase.h"

class T_CONTROLLER_EXPORT RenderResponseMyDlink : public RenderResponseFileOpBase {
    Q_OBJECT

public:
    RenderResponseMyDlink(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseMyDlink();

    virtual void preRender();

private:
    void generateInfo();
    void generateLogin();
    void generateSetDeviceName();
    void generateGetDeviceInfo();
    void generateListVolume();
    void generateListFolder();

    bool isLogin();
    void generatePrefix(QDomDocument &);
    bool m_bLoginStatus;

};

#endif // RENDERRESPONSEMYDLINK_H
