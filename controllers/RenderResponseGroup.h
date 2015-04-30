#ifndef RENDERRESPONSEGROUP_H
#define RENDERRESPONSEGROUP_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseGroup : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseGroup(QVariantMap &, CGI_COMMAND);
    RenderResponseGroup(const RenderResponseGroup &other) {}
    virtual ~RenderResponseGroup();

    virtual RENDER_TYPE preRender();

private:

    void generateGetGroupList(QDomDocument &);
    void generateGetGroupInfo(QDomDocument &);
    void generateGroupAdd();
    void generateAddGroupGetGroupQuotaMinsize(QDomDocument &);
    void generateGroupSetQuota();
    void generateGetModifyGroupInfo(QDomDocument &);
    void generateGroupModify();
    void generateGroupDel();
};

#endif // RENDERRESPONSEGROUP_H
