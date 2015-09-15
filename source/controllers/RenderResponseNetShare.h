#ifndef RENDERRESPONSENETSHARE_H
#define RENDERRESPONSENETSHARE_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseNetShare : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseNetShare(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseNetShare();

    virtual void preRender();

private:

    void generateModuleGetInfo();
    void generateGetAdsInfo();
    void generateGetSession();
    void generateGetIsoShare();
    void generateGetAfpInfo();
    void generateGetNfsInfo();
    void generateIsoPrecentage();
    void generateClearIsoCreate();
    void generateUserList();
    void generateGroupList();
    void generateGetAllIsoShare();
    void generateAddSession();
    void generateSetNfsShare();
    void generateGetModifySession();
    void generateModifySession();
    void generateModifyNfsShare();
    void generateWebdavAccountAdd();
    void generateDeleteSession();
    void generateWebdavAccountDel();
    void generateResetSession();
    void generateGetShareInfo();
    void generateGetFtp();
    void generateWebdavAccountInfo();

    void generateSetIsoShare();
    void generateGetIsoShareDetail();
    void generateGetNfsShareInfo();
    void generateGetModifyIsoInfo();
    void generateModifyIsoShare();
    void generateDelIsoShare();
    void generateChkImgName();
    void generateChkHDSize();
    void generateIsoConfig();
    void generateIsoCreatePath();
    void generateIsoSize();
    void generateIsoCreateImage();

};

#endif // RENDERRESPONSENETSHARE_H
