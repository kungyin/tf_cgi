#ifndef RENDERRESPONSEAIRPLAY_H
#define RENDERRESPONSEAIRPLAY_H


#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseAirplay : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseAirplay(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseAirplay();

    virtual void preRender();

private:

    void generateGetAirplayDevice();
    void generateSetAirplayDevice();
    void generateChkAirplayStatus();
    void generateSetAirplaySource();
    void generateAirplayStop();

};

#endif // RENDERRESPONSEDROPBOX_H
