#include "RenderResponse.h"
#include "AppDefine.h"

QStringList RenderResponseBase::getAPIStdOut(QString apiCmd) {
    QStringList ret;
    char *buff;
    size_t len = 0;
    FILE *fd = popen(apiCmd.toLocal8Bit(), "r");
    while((getline(&buff, &len, fd)) != -1)
        ret << buff;
    pclose(fd);

    return ret;
}

QString RenderResponseBase::getAPIStdOutOneLine(QString apiCmd) {
    QString firstLine;
    QStringList list = getAPIStdOut(apiCmd);
    if(!list.isEmpty())
        firstLine = list.at(0);
    return firstLine;
}

bool RenderResponseBase::setNasCfg(QString title, QString key, QString value) {
    QString sectionTitle =  QString("[%1]").arg(title);

    QByteArray data;
    QFile file(SYS_CONFIG_FILE);
    file.open(QIODevice::ReadWrite);
    data = file.readAll();
    QString fileData(data);
    fileData.remove(QChar('\r'));
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
    fileData.replace(idxToSetValue, fileData.indexOf("\n", idxToSetValue) - idxToSetValue, value);

    file.reset();
    file.write(fileData.toUtf8());
    file.close();
    return true;
}

bool RenderResponseBase::setNasCfg(QString title, QMap<QString, QString> &map) {
    QString sectionTitle =  QString("[%1]").arg(title);

    QByteArray data;
    QFile file(SYS_CONFIG_FILE);
    file.open(QIODevice::ReadWrite);
    data = file.readAll();
    QString fileData(data);
    fileData.remove(QChar('\r'));
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
        fileData.replace(idxToSetValue, fileData.indexOf("\n", idxToSetValue) - idxToSetValue, map.value(entry));
    }

    file.reset();
    file.write(fileData.toUtf8());
    file.close();
    return true;
}


QMap<QString, QString> RenderResponseBase::getNasCfg(QString title) {
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
            ret.insert(fields.at(0), fields.at(1));
    }
    file.close();
    return ret;
}
