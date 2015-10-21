#include <QDir>
#include <QCryptographicHash>

#include <unistd.h>
#include <pwd.h>
#include <grp.h>

#include "RenderResponseFileOpBase.h"

bool copyDirRecursive(QString fromDir, QString toDir, bool replaceOnConflit = true)
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

quint64 dirSize(const QString &str)
{
    quint64 sizex = 0;
    QFileInfo parentInfo(str);
    if (parentInfo.isDir()) {
        QDir dir(str);
        QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs
                        | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        for(auto e : list) {
            if(e.isDir())
                sizex += dirSize(e.absoluteFilePath());
            else
                sizex += e.size();
        }
    }
    else
        sizex = parentInfo.size();

    return sizex;
}

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
            QString compressCmd = "zip -FSr \"%1%2%3\" \"%3\"";
            /* "sh -c" */
            getAPIStdOut(compressCmd.arg(tmpPath).arg(QDir::separator()).arg(name), false, "", 1);
            QDir::setCurrent(currentPath);
        }

        QFileInfo zipFileInfo(tmpPath + QDir::separator() + outFileName);
        if(zipFileInfo.exists())
            bCompress = true;

    }

    return bCompress;

}

QString RenderResponseFileOpBase::compressTgz(const QString &path, const QString &names) {

    QString ret;
    QDir dir(path);
    if(dir.exists()) {

        QString fileList(names);
        fileList.replace("*", " ");

        QString outFileName = dir.dirName() + ".tgz";
        QFileInfo targetFileInfo(dir.absolutePath() + QDir::separator() + outFileName);
        QFile::remove(targetFileInfo.absoluteFilePath());

        QString compressCmd = "tar zcf %1%2%3 -C %1 %4";
        /* "sh -c" */
        getAPIStdOut(compressCmd.arg(dir.absolutePath())
                     .arg(QDir::separator())
                     .arg(outFileName)
                     .arg(fileList), false, "", 1);

        if(targetFileInfo.exists())
            ret = targetFileInfo.absoluteFilePath();

    }

    return ret;

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

bool RenderResponseFileOpBase::mkdir(const QString &path, const QString &dirName) {
    QDir dir(path);
    bool bMkdir = dir.mkdir(dirName);
    if(bMkdir) {
        QFileInfo fileInfo = QFileInfo(dir.absolutePath() + QDir::separator() + dirName);
        QFile(fileInfo.absoluteFilePath()).setPermissions((QFileDevice::Permission)0x0777);

        uint gid, uid;
        if(getGid("allaccount", gid) && getUid("nobody", uid)) {
            if(chown(fileInfo.absoluteFilePath().toLocal8Bit().data(), uid, gid) != 0)
                tDebug("chwon failed: %s", fileInfo.absolutePath().toLocal8Bit().data());
        }
        else
            tDebug("UID or GID is not found.");
    }

    return bMkdir;
}

quint64 RenderResponseFileOpBase::getSize(const QString &path) {
    return dirSize(path);
}

/* lighttpd secret dwonload:
 * 1. a secret string (user supplied)
 * 2. <rel-path> (starts with /)
 * 3. <timestamp-in-hex>
 */
QString RenderResponseFileOpBase::getSecretPath(QString filePath) {
    QString secDownloadPath;

    if(QFileInfo(filePath).exists()) {
        filePath.remove("/mnt");
        QByteArray hexTime = QByteArray::number(QDateTime::currentDateTime().toTime_t(), 16);
        QByteArray hashResult = QCryptographicHash::hash("TNo5FFCWt1gT" +
                                                         filePath.toLocal8Bit() +
                                                         hexTime,
                                                         QCryptographicHash::Md5)
                                                        .toHex();

        secDownloadPath = QString("/sdownload/%1/%2%3")
                .arg(QString(hashResult))
                .arg(QString(hexTime))
                .arg(filePath);
    }

    return secDownloadPath;
}
