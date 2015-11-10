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
    void generateModuleGetOneInfo();
    void generateMyFavSet();
    void generateMyFavGetSortInfo();
    void generateMyFavCompareApkg();

    void generateIcePlaylist();
    void generateIceIsPlaylistFull();
    void generateIcePlaylistName();
    void generateIceHasPlaylistName();
    void generateIcePlaylistNew();
    void generateIcePlaylistDel();
    void generateIceModInfo();
    void generateIcePlaylistRenew();
    void generateIceIsActiveFull();
    void generateIcePlaylistEnable();
    void generateIcePlaylistDisable();
    void generateIceGet();
    void generateIceSet();

};

#endif // RENDERRESPONSEADDON_H
