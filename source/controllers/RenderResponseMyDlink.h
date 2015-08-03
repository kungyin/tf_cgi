#ifndef RENDERRESPONSEMYDLINK_H
#define RENDERRESPONSEMYDLINK_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseMyDlink : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseMyDlink(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseMyDlink();

    virtual void preRender();

private:
    void generateInfo();

};

#endif // RENDERRESPONSEMYDLINK_H
