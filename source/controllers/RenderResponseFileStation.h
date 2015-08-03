#ifndef RENDERRESPONSEFILESTATION_H
#define RENDERRESPONSEFILESTATION_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseFileStation : public RenderResponse {
    Q_OBJECT

public:
    RenderResponseFileStation(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseFileStation();

    virtual void preRender();

private:
    inline QString getTempPath(const QString &);
    bool copy(QString &, QString &);
    bool unArchive(QString &, QString &, QString);
    QString getSecretPath(QString);

    void generateFolderContent();
    void generateGetUserQuota();
    void generateChkFile();
    void generateCompress();
    void generateDownload();
    void generateCp();
    void generateMove();
    void generateDel();
    void generateRename();
    void generateGetProperties();
    void generateChangePermissions();
    void generateAddZip();
    void generateUnzip();
    void generateUntar();
    void generateGetSecDownloadUrl();
    void generateGetCoolirisRss();

};


#endif // RENDERRESPONSEFILESTATION_H
