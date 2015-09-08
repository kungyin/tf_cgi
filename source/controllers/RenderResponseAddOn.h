#ifndef RENDERRESPONSEADDON_H
#define RENDERRESPONSEADDON_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseAddOn : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseAddOn(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseAddOn();

    virtual void preRender();

private:
    void generateModuleShowInstallStatus();
    void generateGetAllApps();
    void generateGetApkgDetail();
    void generateMyFavCheckImg();
    void generateChkHddFreeSize();
    void generateDownloadInstallAddOn();
    void generateClearAddOnFiles();
    void generateModuleReInstall();
    void generateInstall3PartyApkg();
    void generateUninstallAddOn();
    void generateModuleEnableDisable();
    void generateModuleUninstall();
    void generateApp();
    void generateApplication1st();
	void generateMyFavSet();
    void generateMyFavGetSortInfo();

};

#endif // RENDERRESPONSEADDON_H
