#ifndef RENDERRESPONSEDASHBOARD_H
#define RENDERRESPONSEDASHBOARD_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseDashboard : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseDashboard(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseDashboard();

    virtual void preRender();

private:
    void generateGetDeviceDetailInfo();

};

#endif // RENDERRESPONSEDASHBOARD_H
