#ifndef CGICONTROLLER_H
#define CGICONTROLLER_H

#include "applicationcontroller.h"
#include "RenderResponse.h"
#include "CommandDefine.h"
#include "ParseCmd.h"

class T_CONTROLLER_EXPORT CgiController : public ApplicationController
{
    Q_OBJECT

public:
    CgiController();
    //CgiController(const CgiController &other);
    virtual ~CgiController();

public slots:
    void process();
    void processGoogleDrive();
    void renderTypeChanged(RENDER_TYPE);

private:
    void cgiInit(int group = CMD_GRP_NONE);
    void cgiResponse();
    void getSessionTime();
    void resetSessionTime();
    RenderResponse *getRenderResponseBaseInstance(THttpRequest &, CGI_COMMAND);
    bool isValidClient(bool bCookiesOnly = false);
    QMap<QString, QList<QDateTime>> map;

    ParseCmd *m_pParseCmd;
};

T_DECLARE_CONTROLLER(CgiController, cgicontroller);

#endif // CGICONTROLLER_H
