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

    void generateTmGetInfo(QDomDocument &);
    void generateTmGetList(QDomDocument &);
    void generateTmGetSmbList(QDomDocument &);
    void generateTmSet(QString &);
    void generateTmGetShareName(QDomDocument &);
    void generateTmSetShare(QString &);
    void generateTmDelShare(QString &);
    void generateTmDelAllShare(QString &);

};

#endif // RENDERRESPONSETIMEMACHINE_H
