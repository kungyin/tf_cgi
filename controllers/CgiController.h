#ifndef CGICONTROLLER_H
#define CGICONTROLLER_H

#include "applicationcontroller.h"
#include "RenderResponse.h"
#include "CommandDefine.h"

class T_CONTROLLER_EXPORT CgiController : public ApplicationController
{
    Q_OBJECT
public:
    CgiController(){}
    CgiController(const CgiController &other);

public slots:
    void index();

private:
    RenderResponse *getRenderResponseBaseInstance(THttpRequest &, CGI_COMMAND);
};

T_DECLARE_CONTROLLER(CgiController, cgicontroller);

#endif // CGICONTROLLER_H
