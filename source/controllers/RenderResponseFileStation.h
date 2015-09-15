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
    QString getFileDescription(QString &);
    bool copy(QString &, QString &);
    bool unArchive(QString &, QString &, QString);
    QString getSecretPath(QString);

    void generateOpenTree();
    void generateOpenNewFolder();
    void generateFolderContent();
    void generateEmptyFolder();
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
