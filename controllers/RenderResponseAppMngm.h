#ifndef RENDERRESPONSEAPPMNGM_H
#define RENDERRESPONSEAPPMNGM_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseAppMngm : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseAppMngm(QVariantMap &, CGI_COMMAND);
    virtual ~RenderResponseAppMngm();

    virtual RENDER_TYPE preRender();

private:

    void generateSetAfp();
    void generateNfsEnable(QDomDocument &);

};


#endif // RENDERRESPONSEAPPMNGM_H
