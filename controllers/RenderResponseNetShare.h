#ifndef RENDERRESPONSENETSHARE_H
#define RENDERRESPONSENETSHARE_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseNetShare : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseNetShare(QVariantMap &, CGI_COMMAND);
    virtual ~RenderResponseNetShare();

    virtual RENDER_TYPE preRender();

private:

    void generateModuleGetInfo(QDomDocument &);
    void generateGetAdsInfo(QDomDocument &);
    void generateGetSession(QDomDocument &);
    void generateGetIsoShare(QDomDocument &);
    void generateGetAfpInfo(QDomDocument &);
    void generateGetNfsInfo(QDomDocument &);
    void generateIsoPrecentage(QString &);
    void generateClearIsoCreate();
    void generateUserList(QDomDocument &);
    void generateGroupList(QDomDocument &);
    void generateGetAllIsoShare(QDomDocument &);
    void generateOpenTree(QString &);
    void generateOpenNewFolder(QDomDocument &);
    void generateAddSession();
    void generateSetNfsShare();
    void generateGetModifySession(QDomDocument &);
    void generateModifySession();
    void generateModifyNfsShare();
    void generateWebdavAccountAdd(QDomDocument &);
    void generateDeleteSession();
    void generateWebdavAccountDel(QDomDocument &);
    void generateResetSession(QString &);
    void generateGetShareInfo(QDomDocument &);
    void generateGetFtp(QDomDocument &);
    void generateWebdavAccountInfo(QDomDocument &);

};

#endif // RENDERRESPONSENETSHARE_H