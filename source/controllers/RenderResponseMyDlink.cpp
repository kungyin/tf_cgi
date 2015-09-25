#include <QDir>

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
        case CMD_6:
            generateDownload();
            break;
//        case CMD_7:
//            generateUpload();
//            break;
        case CMD_9:
            generateMove();
            break;
        case CMD_10:
            generateCopy();
            break;
        case CMD_11:
            generateRename();
            break;
        case CMD_12:
            generateDu();
            break;
        case CMD_13:
            generateCompress();
            break;
        case CMD_14:
            generateMkdir();
            break;

//        case CMD_12:
//            generateDu();
//            break;
//        case CMD_12:
//            generateDu();
//            break;
//        case CMD_12:
//            generateDu();
//            break;
        case CMD_20:
            generateGetLog();
            break;
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

    QDomDocument doc;
    generatePrefix(doc);
    QDomElement root = doc.documentElement();

    if(m_bLoginStatus) {
        if(!QDir(paraPath).exists()) {
            QDomElement statusElement = doc.createElement("status");
            root.appendChild(statusElement);
            statusElement.appendChild(doc.createTextNode("0"));
        }
        else {

            QDomElement versionElement = doc.createElement("version");
            root.appendChild(versionElement);
            versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));

            QDomElement pathElement = doc.createElement("path");
            root.appendChild(pathElement);
            pathElement.appendChild(doc.createTextNode(paraPath));

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

            QDomElement totalItemElement = doc.createElement("total_item");
            root.appendChild(totalItemElement);
            totalItemElement.appendChild(doc.createTextNode(QString::number(fileList.size())));

            int totalPages = getTotalPages(paraItem.toInt(), fileList.size());
            QDomElement pageIndexElement = doc.createElement("page_index");
            root.appendChild(pageIndexElement);
            pageIndexElement.appendChild(doc.createTextNode(QString::number(totalPages)));

            QFileInfoList fileListInPage(fileList);
            int rp = paraItem.toInt();
            if(fileList.size() > rp)
                fileListInPage = fileList.mid((paraPage.toInt()-1) * rp, rp);

            QDomElement itemInPageElement = doc.createElement("item_in_page");
            root.appendChild(itemInPageElement);
            itemInPageElement.appendChild(doc.createTextNode(QString::number(fileListInPage.size())));

            QDomElement itemsElement = doc.createElement("items");
            root.appendChild(itemsElement);
            QStringList itemTagNames(QStringList()
                << "name" << "type" << "size" << "access_time" << "permission");

            for(QFileInfo e : fileListInPage) {

                QStringList itemContent;
                QDomElement itemElement = doc.createElement("item");
                itemsElement.appendChild(itemElement);

                itemContent << e.fileName();
                if(e.isDir()) {
                    itemContent << "1";
                }
                else {
                    itemContent << "2";
                }

                itemContent << QString::number(e.size())
                            << e.lastModified().toString("yyyy-MM-dd hh:mm:ss")
                            << "2";

                for(int i=0; i < itemTagNames.size(); i++) {
                    QDomElement element = doc.createElement(itemTagNames.value(i));
                    itemElement.appendChild(element);
                    element.appendChild(doc.createTextNode(itemContent.value(i)));
                }
            }
        }
    }

    m_var = doc.toString();
}

void RenderResponseMyDlink::generateDownload() {
    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());
    QString paraRedir = m_pReq->parameter("redir");

    QDomDocument doc;
    generatePrefix(doc);

    QFileInfo file(paraPath);

    if(!m_bLoginStatus) {
        m_var = doc.toString();
        emit typeChanged(RENDER_TYPE_XML);
    }
    else {
        if(file.exists() && file.isFile()) {
            if(paraRedir == "0") {
                m_var = getSecretPath(paraPath);
                emit typeChanged(RENDER_TYPE_STRING);
            }
            else {
                tDebug("RenderResponseMyDlink::generateDownload() - file: %s", paraPath.toLocal8Bit().data());
                m_var = paraPath;
            }
        }
        else {
            QDomElement root = doc.documentElement();
            QDomElement statusElement = doc.createElement("status");
            root.appendChild(statusElement);
            statusElement.appendChild(doc.createTextNode("0"));
            m_var = doc.toString();
            emit typeChanged(RENDER_TYPE_XML);
        }
    }
}

void RenderResponseMyDlink::generateMove() {
    QString paraSrcPath = QUrl::fromPercentEncoding(m_pReq->parameter("src_path").toLocal8Bit());
    QString paraDesPath = QUrl::fromPercentEncoding(m_pReq->parameter("des_path").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    QDomElement root = doc.documentElement();
    bool bMove = move(paraSrcPath, paraDesPath);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(bMove ? "1" : "0"));

    if(m_bLoginStatus) {
        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));
    }
    m_var = doc.toString();

}

void RenderResponseMyDlink::generateCopy() {
    QString paraSrcPath = QUrl::fromPercentEncoding(m_pReq->parameter("src_path").toLocal8Bit());
    QString paraDesPath = QUrl::fromPercentEncoding(m_pReq->parameter("des_path").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    QDomElement root = doc.documentElement();
    bool bCopy = copy(paraSrcPath, paraDesPath);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(bCopy ? "1" : "0"));

    if(m_bLoginStatus) {
        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));
    }
    m_var = doc.toString();

}

void RenderResponseMyDlink::generateRename() {
    QString paraSrcPath = QUrl::fromPercentEncoding(m_pReq->parameter("src_path").toLocal8Bit());
    QString paraDesPath = QUrl::fromPercentEncoding(m_pReq->parameter("des_path").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    QDomElement root = doc.documentElement();
    bool bRename = QFile::rename(paraSrcPath, paraDesPath);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(bRename ? "1" : "0"));

    if(m_bLoginStatus) {
        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));
    }
    m_var = doc.toString();

}

void RenderResponseMyDlink::generateDu() {
    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    if(m_bLoginStatus) {
        QDomElement root = doc.documentElement();
        double size = getSize(paraPath)/1024;

        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));
        QDomElement sizeElement = doc.createElement("size");
        root.appendChild(sizeElement);
        sizeElement.appendChild(doc.createTextNode(QString::number(size)));
    }
    m_var = doc.toString();

}

void RenderResponseMyDlink::generateCompress() {
    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());
    QString paraFiles = QUrl::fromPercentEncoding(m_pReq->parameter("files").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    if(m_bLoginStatus) {
        QDomElement root = doc.documentElement();
        QString tgzFile = compressTgz(paraPath, paraFiles);

        QDomElement statusElement = doc.createElement("status");
        root.appendChild(statusElement);
        statusElement.appendChild(doc.createTextNode(!tgzFile.isEmpty() ? "1" : "0"));

        if(!tgzFile.isEmpty()) {
            QDomElement versionElement = doc.createElement("version");
            root.appendChild(versionElement);
            versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));
            QDomElement fileNameElement = doc.createElement("file_name");
            root.appendChild(fileNameElement);
            fileNameElement.appendChild(doc.createTextNode(tgzFile));
        }
    }
    m_var = doc.toString();

}

void RenderResponseMyDlink::generateMkdir() {
    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    if(m_bLoginStatus) {
        QFileInfo dirInfo(paraPath);

        QDomElement root = doc.documentElement();
        bool bMkdir = mkdir(dirInfo.absolutePath(), dirInfo.fileName());
        QDomElement statusElement = doc.createElement("status");
        root.appendChild(statusElement);
        statusElement.appendChild(doc.createTextNode(bMkdir ? "1" : "0"));

        if(bMkdir) {
            QDomElement versionElement = doc.createElement("version");
            root.appendChild(versionElement);
            versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));
        }
    }
    m_var = doc.toString();

}

/* todo */
void RenderResponseMyDlink::generateGetLog() {
    QString paraType = QUrl::fromPercentEncoding(m_pReq->parameter("type").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    QDomElement root = doc.documentElement();

    QString status = QDir(MYDLINK_TMP_PATH).exists() ? "1" : "0";
    if(status == "1") {
        QString paraForLog = "-c";
        if(paraType == "0")
            paraForLog = "-o " + MYDLINK_LOG_FILE;

        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_CLOG + " " + paraForLog);

    }

    if(m_bLoginStatus) {

        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));
        /* todo */
        QDomElement pathElement = doc.createElement("path");
        root.appendChild(pathElement);
        pathElement.appendChild(doc.createTextNode(MYDLINK_TMP_PATH));

    }

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(status));

    m_var = doc.toString();

}
