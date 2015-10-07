#ifndef RENDERRESPONSEFILESTATION_H
#define RENDERRESPONSEFILESTATION_H

#include "RenderResponseFileOpBase.h"

class T_CONTROLLER_EXPORT RenderResponseFileStation : public RenderResponseFileOpBase {
    Q_OBJECT

public:
    RenderResponseFileStation(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseFileStation();

    virtual void preRender();

private:
    QString getFileDescription(QString &);
    bool unArchive(QString &, QString &, QString);
    bool convUnzipUniFmtToString(QString &);

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
