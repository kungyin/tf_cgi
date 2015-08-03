#ifndef RENDERRESPONSEACCOUNT_H
#define RENDERRESPONSEACCOUNT_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseAccount : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseAccount(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseAccount();

    virtual void preRender();

private:
    bool isQuotaNumber(QString);

    void generateChangeAdminPwd();
    void generateGetUserList();
    void generateGetUserInfo();
    void generateGetSmbList();
    void generateUserAdd();
    void generateRestartService();
    void generateUserSetQuota();
    void generateAddUserToSession();
    void generateCreateFtpLink();
    void generateFtpService();
    void generateWebdavAccountMerge();
    void generateUserBatchCreate();
    void generateGetModifyUserInfo();
    void generateUserModify();
    void generateUserDel();
    void generateMyFavDelUser();
    void generateDownloadImportSample();
    void generateGetAllSession();
    void generateGetImportUsers();
    void generateAddUserGetUserQuotaMaxsize();
    void generateCreateImportUsers();
    void generateCreateStatus();

    void generateGetGroupList();
    void generateGetGroupInfo();
    void generateGroupAdd();
    void generateAddGroupGetGroupQuotaMinsize();
    void generateGroupSetQuota();
    void generateGetModifyGroupInfo();
    void generateGroupModify();
    void generateGroupDel();

    void generateGetQuotaInfo();
    void generateGetHDMappingInfo();
    void generateGetUserQuotaList();
    void generateGetGroupQuotaList();
    void generateGetUserQuotaMaxSize();
    void generateGetGroupQuotaMinSize();
    void generateSetQuotaOnOff();

};

#endif // RENDERRESPONSEACCOUNT_H
