#ifndef RENDERRESPONSETIMEMACHINE_H
#define RENDERRESPONSETIMEMACHINE_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseTimeMachine : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseTimeMachine(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseTimeMachine();

    virtual void preRender();

private:

    void generateTmGetInfo();
    void generateTmGetList();
    void generateTmGetSmbList();
    void generateTmSet();
    void generateTmGetShareName();
    void generateTmSetShare();
    void generateTmDelShare();
    void generateTmDelAllShare();

};

#endif // RENDERRESPONSETIMEMACHINE_H
