#ifndef RENDERRESPONSEDASHBOARD_H
#define RENDERRESPONSEDASHBOARD_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseDashboard : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseDashboard(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseDashboard();

    virtual void preRender();
    void setSession(TSession &session) { m_pSession = &session; }

private:
    void generateGetDeviceDetailInfo();
    TSession *m_pSession;
};

#endif // RENDERRESPONSEDASHBOARD_H
