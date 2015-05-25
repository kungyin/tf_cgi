#ifndef RENDERRESPONSETIMEMACHINE_H
#define RENDERRESPONSETIMEMACHINE_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseTimeMachine : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseTimeMachine(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseTimeMachine();

    virtual RENDER_TYPE preRender();

private:

    void timeGetInfo(QDomDocument &);
    void timeGetList(QDomDocument &);
    void timeGetSmbList(QDomDocument &);
    void timeSet();
    void timeGetShareName(QDomDocument &);
    void timeSetShare(QDomDocument &);
    void timeDelShare();
    void timeDelAllShare();

};

#endif // RENDERRESPONSETIMEMACHINE_H
