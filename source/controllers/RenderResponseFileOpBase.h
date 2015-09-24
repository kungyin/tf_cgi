#ifndef RENDERRESPONSEFILEOPBASE_H
#define RENDERRESPONSEFILEOPBASE_H

#include "RenderResponse.h"

class T_CONTROLLER_EXPORT RenderResponseFileOpBase : public RenderResponse {
    Q_OBJECT

public:

    virtual void preRender() = 0;

protected:
    bool getUid(const char *, uint &);
    bool getGid(const char *, uint &);

    bool compress(const QString &, const QString &);
    bool copy(const QString &, const QString &);
    bool move(const QString &, const QString &);
    bool remove(const QString &);

private:
    bool copyDirRecursive(QString, QString, bool replaceOnConflit = true);

};

#endif // RENDERRESPONSEFILEOPBASE_H
