#ifndef RENDERRESPONSEMYDLINKACCOUNT_H
#define RENDERRESPONSEMYDLINKACCOUNT_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseMyDlinkAccount : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseMyDlinkAccount(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseMyDlinkAccount();

    virtual void preRender();

private:
    void generateMydlinkAcc();

};


#endif // RENDERRESPONSEMYDLINKACCOUNT_H
