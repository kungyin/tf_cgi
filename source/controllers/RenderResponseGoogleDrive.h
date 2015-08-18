#ifndef RENDERRESPONSEGOOGLEDRIVE_H
#define RENDERRESPONSEGOOGLEDRIVE_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseGoogleDrive : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseGoogleDrive(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseGoogleDrive();

    virtual void preRender();

private:

    void generateGd1();
    void generateGd2();
    void generateGd3();
    void generateGd4();

};

#endif // RENDERRESPONSEGOOGLEDRIVE_H
