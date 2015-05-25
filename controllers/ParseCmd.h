#ifndef PARSECMD_H
#define PARSECMD_H

#include "CommandDefine.h"
#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT ParseCmd : public QObject {
    Q_OBJECT
public:
    ParseCmd(QString);
    virtual ~ParseCmd() {}

    inline int getCGICmd() { return m_iCommand; }
    inline int getRenderType() { return m_iRenderType; }
    inline int getFilterType() { return m_iFilterType; }

private:

    void parse(QString);

    int m_iCommand;
    int m_iRenderType;
    int m_iFilterType;
};

#endif // PARSECMD_H
