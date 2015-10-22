#ifndef RENDERRESPONSENASSHARING_H
#define RENDERRESPONSENASSHARING_H

#include "RenderResponseFileOpBase.h"

class T_CONTROLLER_EXPORT RenderResponseNasSharing : public RenderResponseFileOpBase {
    Q_OBJECT

public:
    RenderResponseNasSharing(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseNasSharing();

    virtual void preRender();

private:
    void generateLogin();

    bool isLogin();
    void generatePrefix(QDomDocument &);
    bool m_bLoginStatus;

};

#endif // RENDERRESPONSENASSHARING_H
