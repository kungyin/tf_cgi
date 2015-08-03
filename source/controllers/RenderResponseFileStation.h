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

    void generateFolderContent(QDomDocument &);
    void generateGetUserQuota(QDomDocument &);
    void generateChkFile(QString &);
    void generateCompress(QDomDocument &);
    void generateDownload(QString &);
    void generateCp(QDomDocument &);
    void generateMove(QDomDocument &);
    void generateDel(QDomDocument &);
    void generateRename(QDomDocument &);
    void generateGetProperties(QDomDocument &);
    void generateChangePermissions(QDomDocument &);
    void generateAddZip(QDomDocument &);
    void generateUnzip(QDomDocument &);
    void generateUntar(QDomDocument &);
    void generateGetSecDownloadUrl(QDomDocument &);
    void generateGetCoolirisRss(QString &);

};


#endif // RENDERRESPONSEFILESTATION_H
