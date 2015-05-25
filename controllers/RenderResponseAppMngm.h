#ifndef RENDERRESPONSEAPPMNGM_H
#define RENDERRESPONSEAPPMNGM_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseAppMngm : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseAppMngm(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseAppMngm();

    virtual void preRender();

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

    void generateSyslogSearch(QDomDocument &);
    void generateGetVolumeInfo(QDomDocument &);
    void generateSyslogGetLogFileOption(QDomDocument &);
    void generateSyslogGetConfig(QDomDocument &);
    void generateSyslogGetSelectOption(QDomDocument &);
    void generateSyslogSetConfig(QString &);
    void generateSyslogExport();
    void generateSyslogGetExportStatus(QDomDocument &);
    void generateSyslogClear();

};


#endif // RENDERRESPONSEAPPMNGM_H
