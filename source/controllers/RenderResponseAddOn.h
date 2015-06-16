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
    void generateModuleShowInstallStatus(QDomDocument &);
    void generateGetAllApps(QDomDocument &);
    void generateGetApkgDetail(QDomDocument &);
    void generateMyFavCheckImg(QDomDocument &);
    void generateChkHddFreeSize(QDomDocument &);
    void generateDownloadInstallAddOn(QString &);
    void generateClearAddOnFiles(QDomDocument &);
    void generateModuleReInstall(QString &);
    void generateInstall3PartyApkg(QString &);
    void generateUninstallAddOn(QDomDocument &);
    void generateModuleEnableDisable(QDomDocument &);
    void generateModuleUninstall(QDomDocument &);

};

#endif // RENDERRESPONSEADDON_H
