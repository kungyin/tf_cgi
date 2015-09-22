#include <QProcess>
#include <QFileInfo>

#include "RenderResponse.h"

//RenderResponse::RenderResponse()
//    : m_diffTime(0)
//{
//}

QStringList RenderResponse::getAPIStdOut(QString apiCmd, bool bOneLine, QString splitChar, bool bUseSystem) {
    QStringList ret;
    QString cmd;
    QStringList input;

#ifndef SIMULATOR_MODE
    if(bUseSystem) {
        input = QStringList() << "-c" << apiCmd;
        cmd = "sh";
//        system(apiCmd.toLocal8Bit().data());
//        return ret;
    }
#else
    bUseSystem = false;
#endif


    if(!bUseSystem) {
        input = apiCmd.split(" ");
        cmd = input.value(0);
        input.removeFirst();
    }

    QString strList;
    for(QString e : input) {
        if(strList.isEmpty())
            strList += e;
        else
            strList += " " + e;
    }

    tDebug("RenderResponse::getAPIStdOut() -- apiCmd: %s %s", cmd.toLocal8Bit().data(), strList.toLocal8Bit().data());
    if(input.isEmpty())
        return ret;

    QProcess process;
    process.start(cmd, input);

    process.waitForFinished(-1);
    QString allOut = QString(process.readAllStandardOutput());
    ret = allOut.split("\n");
    tDebug("RenderResponse::getAPIStdOut() -- apiOut: %s", allOut.toLocal8Bit().data());

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

bool RenderResponse::setNasCfg(QString title, QString key, QString value) {

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

    int idxKey = fileData.indexOf(key, idxTitle + 1);
    if(idxKey == -1 || (idxBrackets != -1 && idxKey > idxBrackets)) {
        file.close();
        return false;
    }

    int idxToSetValue = fileData.indexOf("=", idxKey + 1) + 1;
    fileData.replace(idxToSetValue, fileData.indexOf("\n", idxToSetValue) - idxToSetValue, " " + value);

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

//    if(!ret.isEmpty()) {
//        ret.prepend("\"");
//        ret.append("\"");
//    }

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


void RenderResponse::replaceVoltoRealPath(QString &path)
{
    QStringList shareInfo = getAPIFileOut(SHARE_INFO_FILE);
    for(QString e : shareInfo) {
        if(path.startsWith(e.split(":").value(0))) {
            path.replace(e.split(":").value(0), e.split(":").value(1));
            break;
        }
    }
}
