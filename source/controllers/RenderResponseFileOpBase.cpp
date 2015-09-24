#include <QDir>

#include <unistd.h>
#include <pwd.h>
#include <grp.h>

#include "RenderResponseFileOpBase.h"


bool RenderResponseFileOpBase::getUid(const char *username, uint &uid) {
    struct passwd pwd;
    struct passwd *result;
    char *buf;
    long bufsize;

    bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
    if (bufsize == -1)          /* Value was indeterminate */
        bufsize = 16384;        /* Should be more than enough */

    buf = (char *)malloc(bufsize);
    if (buf == NULL) {
        //perror("malloc");
        return false;
    }

    getpwnam_r(username, &pwd, buf, bufsize, &result);
    if (result != NULL) {
        uid = pwd.pw_uid;
        return true;
    }

    return false;
}

bool RenderResponseFileOpBase::getGid(const char *groupName, uint &gid) {
    struct group gwd;
    struct group *result;
    char *buf;
    long bufsize;

    bufsize = sysconf(_SC_GETGR_R_SIZE_MAX);
    if (bufsize == -1)          /* Value was indeterminate */
        bufsize = 16384;        /* Should be more than enough */

    buf = (char *)malloc(bufsize);
    if (buf == NULL) {
        //perror("malloc");
        return false;
    }

    getgrnam_r(groupName, &gwd, buf, bufsize, &result);
    if (result != NULL) {
        gid = gwd.gr_gid;
        return true;
    }

    return false;
}

bool RenderResponseFileOpBase::copyDirRecursive(QString fromDir, QString toDir, bool replaceOnConflit)
{
    QDir dir;
    dir.setPath(fromDir);

    fromDir += QDir::separator();
    toDir += QDir::separator();

    foreach(QString copyFile, dir.entryList(QDir::Files)) {
        QString from = fromDir + copyFile;
        QString to = toDir + copyFile;

        if (QFile::exists(to)) {
            if (replaceOnConflit) {
                if (!QFile::remove(to))
                    return false;
            }
            else
                continue;
        }
        if (!QFile::copy(from, to)) {
            tDebug("Copy file fail: %s", from.toLocal8Bit().data());
            return false;
        }
        else {
            QFileInfo fromInfo = QFileInfo(from);
            if(chown(to.toLocal8Bit().data(), fromInfo.ownerId(), fromInfo.groupId()) != 0) {
                tDebug("chwon failed: %s", to.toLocal8Bit().data());
                return false;
            }
        }
    }

    foreach(QString copyDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString from = fromDir + copyDir;
        QString to = toDir + copyDir;

        if (dir.mkpath(to)) {
            QFile::setPermissions(to, (QFileDevice::Permission)0x0777);
            QFileInfo fromInfo = QFileInfo(from);
            if(chown(to.toLocal8Bit().data(), fromInfo.ownerId(), fromInfo.groupId()) != 0) {
                tDebug("chwon failed: %s", to.toLocal8Bit().data());
                return false;
            }
        }
        else
            return false;

        if (!copyDirRecursive(from, to, replaceOnConflit))
            return false;
    }

    return true;
}


bool RenderResponseFileOpBase::compress(const QString &path, const QString &name) {

    bool bCompress = false;
    QString tmpPath(FILE_TMP_PATH);
    if(QDir(tmpPath).exists()) {

        //QFile::setPermissions(tmpPath, (QFileDevice::Permission)0x0777);
        QString outFileName;

        if(!QFileInfo(QDir(path).absolutePath() + QDir::separator() + name).isDir()) {
            outFileName = name;
            QString dest = tmpPath + QDir::separator() + outFileName;
            if(QFile::exists(dest))
                QFile::remove(dest);
            QFile::copy(QDir(path).absolutePath() + QDir::separator() + outFileName,
                        dest);
        }
        else {
            outFileName = name + ".zip";
            QString currentPath = QDir::currentPath();
            QDir::setCurrent(path);
            QString compressCmd = "zip -FSr \"%1/%2\" \"%2\"";
            getAPIStdOut(compressCmd.arg(tmpPath).arg(name), false, "", true);
            QDir::setCurrent(currentPath);
        }

        QFileInfo zipFileInfo(tmpPath + QDir::separator() + outFileName);
        if(zipFileInfo.exists())
            bCompress = true;

    }

    return bCompress;

}

bool RenderResponseFileOpBase::copy(const QString &sourcePath, const QString &destPath) {

    QString source = sourcePath;
    QString dest = destPath;

    QFileInfo sourceInfo(source);
    if(!dest.endsWith(QDir::separator()))
        dest += QDir::separator();
    dest += sourceInfo.fileName();
    if(sourceInfo.isDir()) {
        if (QDir().mkpath(dest)) {
            QFile::setPermissions(dest, (QFileDevice::Permission)0x0777);
            QFileInfo sourceInfo = QFileInfo(source);
            if(chown(dest.toLocal8Bit().data(), sourceInfo.ownerId(), sourceInfo.groupId()) != 0) {
                tDebug("chwon failed: %s", dest.toLocal8Bit().data());
                return false;
            }
            return copyDirRecursive(source, dest);
        }
    }
    else {
        bool bCopy = QFile::copy(source, dest);
        tDebug("%s, %s", source.toLocal8Bit().data(), dest.toLocal8Bit().data());
        QFileInfo sourceInfo = QFileInfo(source);
        if(chown(dest.toLocal8Bit().data(), sourceInfo.ownerId(), sourceInfo.groupId()) != 0) {
            tDebug("chwon failed: %s", dest.toLocal8Bit().data());
            bCopy = false;
        }
        return bCopy;
    }

    return false;
}

bool RenderResponseFileOpBase::move(const QString &sourcePath, const QString &destPath) {
    QString source = sourcePath;
    QString dest = destPath;

    bool bMove = false;
    if(copy(source, dest))
        bMove = remove(source);

    return bMove;
}

bool RenderResponseFileOpBase::remove(const QString &sourcePath) {
    QString source = sourcePath;

    bool bRemove = false;
    QFileInfo fileInfo(source);
    if(fileInfo.isDir())
        bRemove = QDir(source).removeRecursively();
    else
        bRemove = QFile(source).remove();

    return bRemove;
}
