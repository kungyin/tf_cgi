#ifndef PARSECMD_H
#define PARSECMD_H

#include "CommandDefine.h"
#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT ParseCmd : public QObject {
    Q_OBJECT
public:
    ParseCmd(QString);
    virtual ~ParseCmd();

    CGI_COMMAND getCGICmd();
    int getCmdNumber() { return iCmdNumber; }

private:

    int iCmdNumber;
};

#endif // PARSECMD_H
