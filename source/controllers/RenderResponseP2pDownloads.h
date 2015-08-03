#ifndef RENDERRESPONSEP2PDOWNLOADS_H
#define RENDERRESPONSEP2PDOWNLOADS_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseP2pDownloads : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseP2pDownloads(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseP2pDownloads();

    virtual void preRender();

private:
    void generateP2pGetListByPriority();

};

#endif // RENDERRESPONSEP2PDOWNLOADS_H
