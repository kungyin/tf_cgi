#ifndef RENDERRESPONSES3_H
#define RENDERRESPONSES3_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseS3 : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseS3(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseS3();

    virtual void preRender();

private:
    void generateGetS3();
    void generateS3();
    void generateS3Modify();
    void generateS3GetModify();
    void generateS3Del();
    void generateS3Start();
    void generateS3Stop();
    void generateS3Backup();
    void generateS3AllName();
    void generateGetRecovery();
    void generateGetPercent();
    void generateClearPercent();

};

#endif // RENDERRESPONSES3_H
