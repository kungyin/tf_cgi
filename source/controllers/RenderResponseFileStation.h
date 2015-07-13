#ifndef RENDERRESPONSEFILESTATION_H
#define RENDERRESPONSEFILESTATION_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseFileStation : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseFileStation(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseFileStation();

    virtual void preRender();

private:
    void generateFolderContent(QDomDocument &);

};


#endif // RENDERRESPONSEFILESTATION_H
