#ifndef RENDERRESPONSEDROPBOX_H
#define RENDERRESPONSEDROPBOX_H


#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseDropbox : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseDropbox(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseDropbox();

    virtual void preRender();

private:
    void generateDropboxRefreshStatus();
    void generateDropboxGetInfo();
    void generateDropboxAPIChangePath();
    void generateDropboxGetAccessUrl();
    void generateDropboxEnable();
    void generateDropboxNewFolderEncode();
    void generateDropboxCheckFolderExist();
    void generateDropboxSetInterval();
    void generateDropboxSyncNow();
    void generateDropboxUnlink();
};

#endif // RENDERRESPONSEDROPBOX_H
