#include "RenderResponseMyDlink.h"

RenderResponseMyDlink::RenderResponseMyDlink(THttpRequest &req, CGI_COMMAND cmd)
    : m_bLoginStatus(false)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseMyDlink::~RenderResponseMyDlink() {
}

void RenderResponseMyDlink::preRender() {

    if(!m_pReq)
        return;

    if(m_pReq->header().path().contains("info.cgi")) {
        generateInfo();
    }
    else {
        m_bLoginStatus = isLogin();


        switch(m_cmd) {
        case CMD_1:
            generateLogin();
            tDebug("OOOOOOOOOOOOOO");
            break;
        case CMD_2:
            generateSetDeviceName();
            break;
        case CMD_3:
            generateGetDeviceInfo();
            break;
//        case CMD_4:
//            generateListVolume();
//            break;
        case CMD_5:
            generateListFolder();
            break;
//        case CMD_6:
//            generateDownload();
//            break;
//        case CMD_7:
//            generateUpload();
//            break;
//        case CMD_9:
//            generateListDir();
//            break;
//        case CMD_10:
//            generateCopy();
//            break;
//        case CMD_11:
//            generateRename();
//            break;

        default:
            break;
        }

    }

}

/* todo */
void RenderResponseMyDlink::generateInfo() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_lan_mac_info", true, ";");
    QString fmtOut = "Product=dlink-8B21F7\n"
            "Model=DNS-320L-B\n"
            "Version=1.01.0905.2014\n"
            "Build=\n"
            "Macaddr=%1\n"
            "Wireless=NO\n"
            "Ptz=";

    QString ret = fmtOut.arg(apiOut.value(0));
    m_var = ret;

}


bool RenderResponseMyDlink::isLogin() {

    QString paraName = QUrl::fromPercentEncoding(m_pReq->parameter("name").toLocal8Bit());
    QString loginStr = "login#username=" + QByteArray::fromBase64(paraName.toLocal8Bit()) +
            "#pwd=" + QUrl::fromPercentEncoding(m_pReq->parameter("pwd").toLocal8Bit());

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_home_api " + loginStr, true);
    return apiOut.value(0) == "1" ? true : false;

}

void RenderResponseMyDlink::generatePrefix(QDomDocument &doc) {

    QDomElement root = doc.createElement("xml");
    doc.appendChild(root);
    QDomElement authStatusElement = doc.createElement("auth_status");
    root.appendChild(authStatusElement);
    authStatusElement.appendChild(doc.createTextNode(m_bLoginStatus ? "1" : "0"));

}

void RenderResponseMyDlink::generateLogin() {

    QDomDocument doc;
    generatePrefix(doc);
    QDomElement root = doc.documentElement();
    if(m_bLoginStatus) {
        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));
    }

    m_var = doc.toString();

}

/* todo */
void RenderResponseMyDlink::generateSetDeviceName() {

    QDomDocument doc;
    generatePrefix(doc);

    QString paraDeviceName = QUrl::fromPercentEncoding(m_pReq->parameter("device_name").toLocal8Bit());
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DEVICE_API + " set ", true, ";");

    QDomElement root = doc.documentElement();
    //if(m_bLoginStatus) {
        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));
    //}

        QDomElement statusElement = doc.createElement("status");
        root.appendChild(statusElement);
        statusElement.appendChild(doc.createTextNode("0"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseMyDlink::generateGetDeviceInfo() {

    QDomDocument doc;
    generatePrefix(doc);

    QString paraType = m_pReq->parameter("type").toLocal8Bit();
    QStringList apiOutDevice = getAPIStdOut(API_PATH + SCRIPT_DEVICE_API + " get", true, ";");

    QDomElement root = doc.documentElement();

    if(m_bLoginStatus) {
        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));

        if(paraType == "1") {
            QDomElement deviceNameElement = doc.createElement("device_name");
            root.appendChild(deviceNameElement);
            deviceNameElement.appendChild(doc.createTextNode(apiOutDevice.value(0)));
            QDomElement modelNameElement = doc.createElement("model_name");
            root.appendChild(modelNameElement);
            modelNameElement.appendChild(doc.createTextNode(""));
            QDomElement macElement = doc.createElement("mac");
            root.appendChild(macElement);
            macElement.appendChild(doc.createTextNode(""));
        }
    }

    m_var = doc.toString();

}

void RenderResponseMyDlink::generateListFolder() {
    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());
    QString paraPage = m_pReq->parameter("page");
    QString paraItem = m_pReq->parameter("item");
//    QString paraRootPath = m_pReq->parameter("root_path");

    QDir dir(paraPath);
    QDir::Filters filters = QDir::NoDotAndDotDot | QDir::Dirs;
    filters |= QDir::AllEntries;
    QFileInfoList fileList = dir.entryInfoList(filters);

    QListIterator<QFileInfo> iter(fileList);
    while (iter.hasNext()) {
        QFileInfo entry = iter.next();

        if(            entry.fileName() == "lost+found"
                    || entry.fileName() == "Nas_Prog"
                    || entry.fileName() == "aMule"
                    || entry.fileName() == "ShareCenter_Sync") {
            fileList.removeOne(entry);
            continue;
        }
    }

    for(QFileInfo e : fileList) {

        for(QString shareEntry : shareInfo) {
            if(e.absoluteFilePath().compare(shareEntry.split(":").value(1)) == 0) {
                fileName = shareEntry.split(":").value(0);
                break;
            }
        }

        if(e.absoluteDir().absolutePath() == "/mnt/HD" && !fileName.startsWith("Volume_"))
            break;


        if(e.isDir()) {
            QString line1 = (paraChkFlag.compare("1") == 0) ?
                        checkboxLine.arg(e.absoluteFilePath()).arg(checkboxSrc.arg(fileName)).arg(fileName) : QString::null;
            QString line2 = hrefLine.arg(e.absoluteFilePath() + QDir::separator()).arg(fileName);
            content += cssLiClass.arg("").arg(line1).arg(line2);
        }
        else {
            QString fileVolumePath = e.absoluteFilePath();
            if(fileVolumePath.startsWith("/mnt/HD/HD_")) {
                for(QString shareEntry : shareInfo) {
                    if(fileVolumePath.startsWith(shareEntry.split(":").value(1))) {
                        fileVolumePath.replace(shareEntry.split(":").value(1), shareEntry.split(":").value(0));
                        break;
                    }
                }
            }
            QString line1 = (paraChkFlag.compare("1") == 0) ?
                        checkboxLine.arg(e.absoluteFilePath()).arg(QString::null).arg(fileVolumePath) : QString::null;
            QString line2 = hrefLine.arg(e.absoluteFilePath()).arg(fileName);
            content += cssLiClassWithID.arg(line1).arg(line2);
        }
    }

    m_var = cssUlClass.arg(content);
}
