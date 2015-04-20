#ifndef CGICONTROLLER_H
#define CGICONTROLLER_H

#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT CgiController : public ApplicationController
{
    Q_OBJECT
public:
    CgiController(){}
    CgiController(const CgiController &other);

public slots:
    void index();
};

T_DECLARE_CONTROLLER(CgiController, cgicontroller);

#endif // CGICONTROLLER_H
