#include <QProcess>
#include <QFileInfo>
#include <TWebApplication>
#include <QDir>
#include <QSettings>


#include "RenderResponse.h"

RenderResponse::RenderResponse()
    : m_pReq(NULL)
    , m_pSession(NULL)
{
}

/*
 * iUseSh
 * 0: null
 * 1: nohup sh -c
 * 2: nohup
 */

QStringList RenderResponse::getAPIStdOut(QString apiCmd, bool bOneLine, QString splitChar, int iUseSh, bool bBackground) {
    QStringList ret;
    QString fullCmd = apiCmd;

#ifndef SIMULATOR_MODE
    QString cmd;
    QString args;
    QString argsFmt = "\"%1\"";

    if(iUseSh > 0) {
        args = argsFmt.arg(apiCmd);
        cmd = "nohup";
        if(iUseSh == 1)
            cmd = "nohup sh -c";
        fullCmd = cmd + " " + args + " < /dev/null 2>&1 > /dev/null";
        if(bBackground)
            fullCmd += " &";
    }
#endif

    tDebug("Start command: %s", apiCmd.split(" ").value(0).toLocal8Bit().data());
    if(fullCmd.isEmpty())
        return ret;

    QProcess process;
    process.start(fullCmd);

    process.waitForFinished(-1);
    QString allOut = QString(process.readAllStandardOutput());
    ret = allOut.split("\n");
    tDebug("fullCmd: %s\napiOut: %s", fullCmd.toLocal8Bit().data(), allOut.toLocal8Bit().data());

    if(bOneLine) {
        if(!ret.isEmpty()) {
            ret = ret.at(0).split(splitChar);
            if(ret.size() == 1 && ret.at(0).isEmpty())
                ret = QStringList();
        }
        else
            ret = QStringList();
    }
    else {
        while(!ret.isEmpty() && ret.last().isEmpty())
            ret.removeLast();
    }

    return ret;
}

/*
 * Interface for base64 encoding
 */
QStringList RenderResponse::getAPIStdOut(QString apiCmd, QStringList paraList, bool bOneLine, QString splitChar, bool bUseSh) {
    QString paraB64, para;

    for(QString e : paraList) {
        QString blank;
        if(!para.isEmpty())
            blank = " ";
#ifdef SIMULATOR_MODE
        paraB64 += blank + e;
#else
        paraB64 += blank + e.toUtf8().toBase64();
#endif
        para += blank + e;
    }

    tDebug("RenderResponse::getAPIStdOut() (before base64) -- apiCmd: %s %s", apiCmd.toLocal8Bit().data(), para.toLocal8Bit().data());
    return getAPIStdOut(apiCmd + " " + paraB64, bOneLine, splitChar, bUseSh);

}

bool RenderResponse::startDetached(QString name, QStringList &arguments) {

    QString apiCmd = name;
    for(QString e : arguments)
        apiCmd += " " + e;

    tDebug("RenderResponse::startDetached() - apiCmd: %s", apiCmd.toLocal8Bit().data());
    if(!QProcess::startDetached(name, arguments))
        return false;

    return true;
}

QStringList RenderResponse::getAPIFileOut(QString filePath, bool bOneLine, QString splitChar) {
    QStringList ret;

    tDebug("RenderResponse::getAPIFileOut() -- filePath: %s", filePath.toLocal8Bit().data());

    QFileInfo fileInfo(filePath);
    if ( !fileInfo.exists() || !fileInfo.isFile() ) {
        tError("RenderResponse::getAPIFileOut() -- file %s does not exist", filePath.toLocal8Bit().data());
        return ret;
    }

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QString allOut = QString(file.readAll());
    ret = allOut.split("\n");
    tDebug("RenderResponse::getAPIFileOut() -- apiOut: %s", allOut.toLocal8Bit().data());

    if(bOneLine) {
        if(!ret.isEmpty()) {
            ret = ret.at(0).split(splitChar);
            if(ret.size() == 1 && ret.at(0).isEmpty())
                ret = QStringList();
        }
        else
            ret = QStringList();
    }
    else {
        while(!ret.isEmpty() && ret.last().isEmpty())
            ret.removeLast();
    }

    file.close();

    return ret;
}

bool RenderResponse::setNasCfg(QString title, QString key, QString value, QString configFile, QString space) {

    QByteArray data;
    QFile file(configFile);
    file.open(QIODevice::ReadWrite);
    data = file.readAll();
    QString fileData(data);
    fileData.remove(QChar('\r'));

    QString sectionTitle =  QString("[%1]").arg(title);
    int idxTitle = fileData.indexOf(sectionTitle);
    if(idxTitle == -1) {
        file.close();
        return false;
    }

    int idxBrackets = fileData.indexOf("[", idxTitle + 1);

    int idxKey = fileData.indexOf(key, idxTitle + 1);
    if(idxKey == -1 || (idxBrackets != -1 && idxKey > idxBrackets)) {
        file.close();
        return false;
    }

    int idxToSetValue = fileData.indexOf("=", idxKey + 1) + 1;
    fileData.replace(idxToSetValue, fileData.indexOf("\n", idxToSetValue) - idxToSetValue, space + value);

    file.reset();
    file.write(fileData.toUtf8());
    file.resize(file.pos());
    file.close();
    return true;
}

bool RenderResponse::setNasCfg(QString title, QMap<QString, QString> &map) {

    QByteArray data;
    QFile file(SYS_CONFIG_FILE);
    file.open(QIODevice::ReadWrite);
    data = file.readAll();
    QString fileData(data);
    fileData.remove(QChar('\r'));

    QString sectionTitle =  QString("[%1]").arg(title);
    int idxTitle = fileData.indexOf(sectionTitle);
    if(idxTitle == -1) {
        file.close();
        return false;
    }

    int idxBrackets = fileData.indexOf("[", idxTitle + 1);

    for ( auto/*QString*/ entry : map.keys() ) {
        int idxKey = fileData.indexOf(entry, idxTitle + 1);
        if(idxKey == -1 || (idxBrackets != -1 && idxKey > idxBrackets))
            continue;

        int idxToSetValue = fileData.indexOf("=", idxKey + 1) + 1;
        fileData.replace(idxToSetValue, fileData.indexOf("\n", idxToSetValue) - idxToSetValue, " " + map.value(entry));
    }

    file.reset();
    file.write(fileData.toUtf8());
    file.resize(file.pos());
    file.close();
    return true;
}

bool RenderResponse::setNasCfg(QMap<QString, QMap<QString, QString>> &map) {

    QByteArray data;
    QFile file(SYS_CONFIG_FILE);
    file.open(QIODevice::ReadWrite);
    data = file.readAll();
    QString fileData(data);
    fileData.remove(QChar('\r'));

    for( auto titleEntry : map.keys() ) {
        QString sectionTitle =  QString("[%1]").arg(titleEntry);
        int idxTitle = fileData.indexOf(sectionTitle);
        if(idxTitle == -1) {
            continue;
        }

        int idxBrackets = fileData.indexOf("[", idxTitle + 1);

        for ( auto entry : map.value(titleEntry).keys() ) {
            int idxKey = fileData.indexOf(entry, idxTitle + 1);
            if(idxKey == -1 || (idxBrackets != -1 && idxKey > idxBrackets)) {
                continue;
            }

            int idxToSetValue = fileData.indexOf("=", idxKey + 1) + 1;
            fileData.replace(idxToSetValue, fileData.indexOf("\n", idxToSetValue) - idxToSetValue, " " + map.value(titleEntry).value(entry));
        }
    }

    file.reset();
    file.write(fileData.toUtf8());
    file.resize(file.pos());
    file.close();
    return true;
}

QMap<QString, QString> RenderResponse::getNasCfg(QString title) {
    QMap<QString, QString> ret;
    QString sectionTitle =  QString("[%1]").arg(title);

    QByteArray data;
    QFile file(SYS_CONFIG_FILE);
    file.open(QIODevice::ReadOnly);
    data = file.readAll();

    QString fileData(data);
    int idxTitle = fileData.indexOf(sectionTitle);
    if(idxTitle == -1) {
        file.close();
        return ret;
    }
    file.seek(idxTitle);
    file.readLine();  // skip this line.

    while(!file.atEnd()) {
        QString line = QString(file.readLine());
        if(line.startsWith("["))
            break;
        QStringList fields = line.split("=");
        if(fields.size() == 2)
            ret.insert(fields.at(0).trimmed(), fields.at(1).trimmed());
    }
    file.close();

//    QSettings sysConfig(SYS_CONFIG_FILE, QSettings::NativeFormat);
//    sysConfig.beginGroup(title);

//    for(QString e : sysConfig.allKeys()) {
//        ret.insert(e, sysConfig.value(e).toString());
//        tDebug("UUUUU %s %s", e.toLocal8Bit().data(), sysConfig.value(e).toByteArray().data());
//    }
//    sysConfig.endGroup();

    return ret;
}

bool RenderResponse::readXml(const QString &filePath, QDomDocument &readFileDoc) {

    bool ret = false;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        if (!readFileDoc.setContent(&file)) {
            tError("RenderResponse::readXml: file %s is not XML.",
                   filePath.toLocal8Bit().data());
        }
        else ret = true;
        file.close();
    }
    else
        tError("RenderResponse::readXml: file %s does not exist.",
               filePath.toLocal8Bit().data());

    return ret;
}

QString RenderResponse::allParametersToString(bool bDecode, QString before, QString after) {

    QString ret;
    if(m_pReq) {
        for ( QString entryKey : m_pReq->allParameters().keys() ) {
            if(!ret.isEmpty())
                ret += "#";
            QString value = m_pReq->allParameters().value(entryKey).toString();
            if(bDecode)
                value = QUrl::fromPercentEncoding(m_pReq->allParameters().value(entryKey).toByteArray());
            if(!before.isEmpty())
                value.replace(before, after);
            else
                value.replace("#", QString::null);
            ret += entryKey + "=" + value.simplified();
        }
    }

    return ret;
}

QString RenderResponse::addPoundSign(QString before, QString splitSign) {

    QString ret;

    for(QString e : before.split(splitSign)) {
        if(!ret.isEmpty())
            ret += splitSign;
        ret += "#" + e.trimmed() + "#";
    }

    return ret;
}

int RenderResponse::getTotalPages(int perPage, int itemNumber) {
    int iTotals = 1;
    if(perPage > 0 && itemNumber > 0)
        iTotals = itemNumber / perPage + (itemNumber % perPage != 0);
    return iTotals;
}

QString RenderResponse::sizeHuman(qint64 size)
{
    double fileSize(size);
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("Bytes");

    while(fileSize >= 1024.0 && i.hasNext()) {
        unit = i.next();
        fileSize /= 1024.0;
    }
    return QString::number(fileSize, 'f', 2) + " " + unit;
}


bool RenderResponse::replaceVoltoRealPath(QString &path, bool reverse)
{
    bool ret = false;
    QStringList shareInfo = getAPIFileOut(SHARE_INFO_FILE);
    for(QString e : shareInfo) {
        QStringList list = e.split(":", QString::SkipEmptyParts);
        if (list.isEmpty() || list.length() != 2) continue;
        if (reverse)
        {
            if(path.startsWith(list.value(1))) {
                path.replace(list.value(1), list.value(0));
                ret = true;
                break;
            }
        }
        else
        {
            if(path.startsWith(list.value(0))) {
                path.replace(list.value(0), list.value(1));
                ret = true;
                break;
            }
        }
    }
    return ret;
}

TSession RenderResponse::findSession(const QByteArray &id)
{
    QFileInfo fi(sessionDirPath() + id);

    if (fi.exists()) {
        QFile file(fi.filePath());

        if (file.open(QIODevice::ReadOnly)) {
            QDataStream ds(&file);
            TSession result(id);
            ds >> *static_cast<QVariantMap *>(&result);
            if (ds.status() == QDataStream::Ok)
                return result;
        }
    }
    return TSession();
}

QString RenderResponse::sessionDirPath()
{
    return Tf::app()->tmpPath() + QLatin1String("session") + QDir::separator();
}



