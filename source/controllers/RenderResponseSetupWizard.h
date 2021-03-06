#ifndef RENDERRESPONSESETUPWIZARD_H
#define RENDERRESPONSESETUPWIZARD_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseSetupWizard : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseSetupWizard(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseSetupWizard();

    virtual void preRender();

private:
    void generateChkAdminPw();
    void generateSetLed();
    void generateGetWizard();

};

#endif // RENDERRESPONSESETUPWIZARD_H
