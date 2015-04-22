#include "RenderResponse.h"

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
