#ifndef RENDERRESPONSEACCOUNT_H
#define RENDERRESPONSEACCOUNT_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseAccount : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseAccount(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseAccount();

    virtual RENDER_TYPE preRender();

private:
    bool isQuotaNumber(QString);

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
    void generateDownloadImportSample(QString &);
    void generateGetAllSession(QDomDocument &);
    void generateGetImportUsers(QDomDocument &);
    void generateAddUserGetUserQuotaMaxsize(QDomDocument &);
    void generateCreateImportUsers();
    void generateCreateStatus(QDomDocument &);

    void generateGetGroupList(QDomDocument &);
    void generateGetGroupInfo(QDomDocument &);
    void generateGroupAdd();
    void generateAddGroupGetGroupQuotaMinsize(QDomDocument &);
    void generateGroupSetQuota();
    void generateGetModifyGroupInfo(QDomDocument &);
    void generateGroupModify();
    void generateGroupDel();

    void generateGetQuotaInfo(QDomDocument &);
    void generateGetHDMappingInfo(QDomDocument &);
    void generateGetUserQuotaList(QDomDocument &);
    void generateGetGroupQuotaList(QDomDocument &);
    void generateGetUserQuotaMaxSize(QDomDocument &);
    void generateGetGroupQuotaMinSize(QDomDocument &);
    void generateSetQuotaOnOff();

    void generateModuleGetInfo(QDomDocument &);
    void generateGetAdsInfo(QDomDocument &);
    void generateGetSession(QDomDocument &);
    void generateGetIsoShare(QDomDocument &);
    void generateGetAfpInfo(QDomDocument &);
    void generateGetNfsInfo(QDomDocument &);
    void generateIsoPrecentage(QString &);
    void generateUserList(QDomDocument &);

};

#endif // RENDERRESPONSEACCOUNT_H
