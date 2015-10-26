#ifndef RENDERRESPONSEFILEOPBASE_H
#define RENDERRESPONSEFILEOPBASE_H

#include <QDir>

#include "RenderResponse.h"

static QSet<QString> No_Display_File_Set {
    { "lost+found" },
    { "Nas_Prog" },
    { "aMule" },
    { "ShareCenter_Sync" }
};

class T_CONTROLLER_EXPORT RenderResponseFileOpBase : public RenderResponse {
    Q_OBJECT

public:

    virtual void preRender() = 0;

protected:
    bool getUid(const char *, uint &);
    bool getGid(const char *, uint &);

    bool compress(const QString &, const QString &);
    QString compressTgz(const QString &, const QString &);
    bool copy(const QString &, const QString &);
    bool move(const QString &, const QString &);
    bool remove(const QString &);
    bool mkdir(const QString &, const QString &);

    QString getSecretPath(QString);
    quint64 getSize(const QString &);
    bool recursiveSearch(const QString&, QFileInfoList &);


private:

};

#endif // RENDERRESPONSEFILEOPBASE_H
