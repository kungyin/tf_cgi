#ifndef RENDERRESPONSEAPPMNGM_H
#define RENDERRESPONSEAPPMNGM_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseAppMngm : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseAppMngm(QVariantMap &, CGI_COMMAND);
    virtual ~RenderResponseAppMngm();

    virtual RENDER_TYPE preRender();

private:

    void generateSetAfp();
    void generateNfsEnable(QDomDocument &);
    void generateCheckDb();
    void generateUpnpAvServerPathList(QDomDocument &);
    void generateUpnpAvServerGetConfig(QDomDocument &);
    void generateUpnpAvServer(QDomDocument &);
    void generateUpnpAvServerGetSqldbState(QDomDocument &);
    void generateGuiCodepageGetList(QDomDocument &);
    void generateItunesServerGetXml(QDomDocument &);
    void generateItunesServerReady(QDomDocument &);
    void generateUpnpAvServerCheckPath(QDomDocument &);
    void generateUpnpAvServerPathSetting(QDomDocument &);
    void generateSqldbStopFinish(QDomDocument &);
    void generateUpnpAvServerPrescan(QDomDocument &);
    void generateUpnpAvServerPathDel(QDomDocument &);
    void generateUpnpAvServerSetting();
    void generateGuiCodepageAdd(QDomDocument &);
    void generateItunesServerSetting(QDomDocument &);
    void generateItunesServerCheckPs(QDomDocument &);
    void generateItunesServerRefresh(QDomDocument &);
    void generateItunesServerRefreshState(QDomDocument &);

};


#endif // RENDERRESPONSEAPPMNGM_H
