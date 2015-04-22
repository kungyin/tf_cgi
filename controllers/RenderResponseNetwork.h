#ifndef RENDERRESPONSENETWORK_H
#define RENDERRESPONSENETWORK_H

#include "RenderResponseBase.h"

class T_CONTROLLER_EXPORT RenderResponseNetwork : public RenderResponseBase {
    Q_OBJECT
public:
    RenderResponseNetwork(QVariantMap &, CGI_COMMAND);
    RenderResponseNetwork(const RenderResponseNetwork &other) {}
    virtual ~RenderResponseNetwork();

    virtual RENDER_TYPE preRender();

private:

    void generateLLTD(QDomDocument &);


};

#endif // RENDERRESPONSENETWORK_H
