#ifndef RENDERRESPONSEACCOUNT_H
#define RENDERRESPONSEACCOUNT_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseAccount : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseAccount(QVariantMap &, CGI_COMMAND);
    RenderResponseAccount(const RenderResponseAccount &other) {}
    virtual ~RenderResponseAccount();

    virtual RENDER_TYPE preRender();

private:

    void generateChangeAdminPwd(QDomDocument &);
    void generateGetUserList(QDomDocument &);
    void generateGetUserInfo(QDomDocument &);
    void generateGetSmbList(QDomDocument &);
    void generateUserAdd(QDomDocument &);
    void generateRestartService();
    void generateUserSetQuota();
    void generateAddUserToSession();
    void generateCreateFtpLink();
    void generateFtpService();
    void generateWebdavAccountMerge(QDomDocument &);
    void generateUserBatchCreate();
    void generateGetModifyUserInfo(QDomDocument &);
    void generateUserModify(QDomDocument &);
    void generateUserDel();
    void generateMyFavDelUser(QDomDocument &);
    void generateDownloadImportSample();
    void generateGetAllSession(QDomDocument &);
    void generateGetImportUsers(QDomDocument &);
    void generateAddUserGetUserQuotaMaxsize(QDomDocument &);
    void generateCreateImportUsers();
    void generateCreateStatus(QDomDocument &);
};

#endif // RENDERRESPONSEACCOUNT_H
