#include <QDir>

#include "RenderResponseNasSharing.h"
#include "Databaseobject.h"

RenderResponseNasSharing::RenderResponseNasSharing(THttpRequest &req, CGI_COMMAND cmd)
    : m_bLoginStatus(false)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseNasSharing::~RenderResponseNasSharing() {
}

void RenderResponseNasSharing::preRender() {

    if(!m_pReq)
        return;

    m_bLoginStatus = isLogin();

    switch(m_cmd) {
    case CMD_NAS_SHARING_1:
        generateLogin();
        break;
    case CMD_NAS_SHARING_2:
        generateScanFolder();
        break;
    case CMD_NAS_SHARING_4:
        generateCreateFolder();
        break;
    case CMD_NAS_SHARING_5:
        generateDelete();
        break;
    case CMD_NAS_SHARING_6:
        generateRename();
        break;
    case CMD_NAS_SHARING_7:
        generateDownload();
        break;
    case CMD_NAS_SHARING_9:
        generateDiskInfo();
        break;
    case CMD_NAS_SHARING_10:
        generateListAll();
        break;
    case CMD_NAS_SHARING_16:
        generateCheckVolume();
        break;

    default:
        break;
    }

}



bool RenderResponseNasSharing::isLogin() {

    QString paraUser = QUrl::fromPercentEncoding(m_pReq->parameter("user").toLocal8Bit());
    QString loginStr = paraUser.toLocal8Bit() +
            " " + QUrl::fromPercentEncoding(m_pReq->parameter("passwd").toLocal8Bit());

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_CHK_PWD + " " + loginStr, true);
    return apiOut.value(0) == "OK" ? true : false;

}

void RenderResponseNasSharing::generatePrefix(QDomDocument &doc) {

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement nasSharingElement = doc.createElement("nas_sharing");
    root.appendChild(nasSharingElement);
    QDomElement authStateElement = doc.createElement("auth_state");
    nasSharingElement.appendChild(authStateElement);
    authStateElement.appendChild(doc.createTextNode(m_bLoginStatus ? "1" : "0"));

}

void RenderResponseNasSharing::generateLogin() {

    QDomDocument doc;
    generatePrefix(doc);
    QDomNode nasSharingNode = doc.documentElement().firstChild();
    if(m_bLoginStatus) {
        QDomElement versionElement = doc.createElement("version");
        nasSharingNode.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(NAS_SHARING_VERSION));

        MediaDbDataProvider mediaProvider;
        int size = mediaProvider.GetTotalSize("", "tbl_multimedia_folder");
        QDomElement mediaFolderElement = doc.createElement("media_folder");
        nasSharingNode.appendChild(mediaFolderElement);
        mediaFolderElement.appendChild(doc.createTextNode(QString::number(size)));

        QStringList shareInfo = getAPIFileOut(SHARE_INFO_FILE);

        for(QString shareEntry : shareInfo) {
            QStringList shareList = shareEntry.split(":");
            QDomElement itemElement = doc.createElement("item");
            nasSharingNode.appendChild(itemElement);

            QDomElement shareNameElement = doc.createElement("share_name");
            itemElement.appendChild(shareNameElement);
            shareNameElement.appendChild(doc.createTextNode(shareList.value(0).toLocal8Bit().toBase64()));
            QDomElement folderPathElement = doc.createElement("folder_path");
            itemElement.appendChild(folderPathElement);
            folderPathElement.appendChild(doc.createTextNode(shareList.value(1).toLocal8Bit().toBase64()));
            QDomElement readWriteElement = doc.createElement("read_write");
            itemElement.appendChild(readWriteElement);
            readWriteElement.appendChild(doc.createTextNode("1"));
        }
    }

    m_var = doc.toString();

}

void RenderResponseNasSharing::generateScanFolder() {

    QString paraPath = QByteArray::fromBase64(m_pReq->parameter("path").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);
    QDomNode nasSharingNode = doc.documentElement().firstChild();
    if(m_bLoginStatus) {

        QDir dir(paraPath);
        QDir::Filters filters = QDir::NoDotAndDotDot | QDir::Dirs;
        filters |= QDir::AllEntries;
        QFileInfoList fileList = dir.entryInfoList(filters);

        QListIterator<QFileInfo> iter(fileList);
        while (iter.hasNext()) {
            QFileInfo entry = iter.next();

            if( No_Display_File_Set.contains(entry.fileName()) ) {
                fileList.removeOne(entry);
                continue;
            }
        }

        QDomElement itemsElement = doc.createElement("items");
        nasSharingNode.appendChild(itemsElement);
        QStringList itemTagNames(QStringList()
            << "file_path" << "file_name" << "file_date" << "file_size" << "file_type" << "sm" << "tn");

        QSet<QString> supportPhotoSet;
        supportPhotoSet << "jpg" << "jpeg" << "gif" << "bmp" << "png";

        for(QFileInfo e : fileList) {

            QStringList itemContent;
            QDomElement itemElement = doc.createElement("item");
            itemsElement.appendChild(itemElement);

            itemContent << e.absoluteFilePath().toLocal8Bit().toBase64()
                        << e.fileName().toLocal8Bit().toBase64()
                        << e.lastModified().toString("yyyy/MM/dd hh:mm:ss");
            if(e.isDir())
                itemContent << "-1" << "1" << "" << "";
            else {
                itemContent << QString::number(e.size()) << "2" << "" << "";

                QDir thumbnailDir(e.absolutePath() + QDir::separator() + ".thumbnail");
                if(thumbnailDir.exists()) {
                    QSetIterator<QString> iter(supportPhotoSet);
                    while (iter.hasNext()) {
                        QString suffix = iter.next();
                        if(suffix.compare(e.suffix(), Qt::CaseInsensitive) == 0) {
                            QString thumbnailPerfix = thumbnailDir.absolutePath() + QDir::separator() + e.fileName();
                            QFileInfo thumbnailPath(thumbnailPerfix + "." + e.suffix());
                            QFileInfo thumbnailBigPath(thumbnailPerfix + ".big." + e.suffix());

                            if(thumbnailPath.exists())
                                itemContent.replace(5, thumbnailPath.absoluteFilePath().toLocal8Bit().toBase64());
                            if(thumbnailBigPath.exists())
                                itemContent.replace(6, thumbnailBigPath.absoluteFilePath().toLocal8Bit().toBase64());

                            break;
                        }
                    }
                }
            }

            for(int i=0; i < itemTagNames.size(); i++) {
                QDomElement element = doc.createElement(itemTagNames.value(i));
                itemElement.appendChild(element);
                element.appendChild(doc.createTextNode(itemContent.value(i)));
            }
        }

    }

    m_var = doc.toString();

}

void RenderResponseNasSharing::generateCreateFolder() {

    QString paraPath = QByteArray::fromBase64(m_pReq->parameter("path").toLocal8Bit());
    QString paraFolder = QByteArray::fromBase64(m_pReq->parameter("foldername").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    if(m_bLoginStatus) {
        mkdir(paraPath, paraFolder);
    }

    m_var = doc.toString();

}

void RenderResponseNasSharing::generateDelete() {

    QString paraPath = QByteArray::fromBase64(m_pReq->parameter("path").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    if(m_bLoginStatus) {
        remove(paraPath);
    }

    m_var = doc.toString();

}

void RenderResponseNasSharing::generateRename() {

    QString paraPath = QByteArray::fromBase64(m_pReq->parameter("path").toLocal8Bit());
    QString paraOldName = QByteArray::fromBase64(m_pReq->parameter("oldname").toLocal8Bit());
    QString paraNewName = QByteArray::fromBase64(m_pReq->parameter("newname").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    if(m_bLoginStatus) {
        if(!paraPath.endsWith(QDir::separator()))
            paraPath += QDir::separator();
        QDir().rename(paraPath + paraOldName, paraPath + paraNewName);
    }

    m_var = doc.toString();

}

void RenderResponseNasSharing::generateDownload() {

    QString paraPath = QByteArray::fromBase64(m_pReq->parameter("path").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    if(m_bLoginStatus) {
        QFileInfo file(paraPath);
        if(file.exists() && file.isFile()) {
            tDebug("RenderResponseNasSharing::generateDownload() - file: %s", paraPath.toLocal8Bit().data());
            m_var = paraPath;
        }
        else
            tDebug("RenderResponseNasSharing::generateDownload() - file: %s doesn't exist"
                   , paraPath.toLocal8Bit().data());
    }

    m_var = doc.toString();

}

void RenderResponseNasSharing::generateDiskInfo() {

    QString paraPath = QByteArray::fromBase64(m_pReq->parameter("path").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);
    QDomNode nasSharingNode = doc.documentElement().firstChild();

    if(m_bLoginStatus) {
        QStringList apiOut = getAPIStdOut("df -h " + paraPath, false, "", 1).value(1)
                .split(" ", QString::SkipEmptyParts);

        QStringList tagNames(QStringList()
            << "total_size" << "used_size" << "free_size" << "used_percent");
        QStringList diskInfo(QStringList()
            << apiOut.value(1).trimmed() << apiOut.value(2).trimmed()
            << apiOut.value(3).trimmed() << apiOut.value(4).trimmed().remove('%'));
        for(int i=0; i < tagNames.size(); i++) {
            QDomElement element = doc.createElement(tagNames.value(i));
            nasSharingNode.appendChild(element);
            element.appendChild(doc.createTextNode(diskInfo.value(i)));
        }
    }

    m_var = doc.toString();

}

void RenderResponseNasSharing::generateListAll() {

    QString paraPath = QByteArray::fromBase64(m_pReq->parameter("path").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);
    QDomNode nasSharingNode = doc.documentElement().firstChild();

    if(m_bLoginStatus) {
        QFileInfoList list;
        recursiveSearch(paraPath, list);

        QStringList itemTagNames(QStringList()
            << "file_path" << "file_name" << "file_date" << "file_size" << "file_type");
        for(QFileInfo e : list) {
            QStringList itemContent;
            QDomElement itemElement = doc.createElement("item");
            nasSharingNode.appendChild(itemElement);

            itemContent << e.absoluteFilePath().toLocal8Bit().toBase64()
                        << e.fileName().toLocal8Bit().toBase64()
                        << e.lastModified().toString("ddd MMM dd hh:mm:ss yyyy");
            if(e.isDir())
                itemContent << "-1" << "1";
            else {
                itemContent << QString::number(e.size()) << "2";
            }

            for(int i=0; i < itemTagNames.size(); i++) {
                QDomElement element = doc.createElement(itemTagNames.value(i));
                itemElement.appendChild(element);
                element.appendChild(doc.createTextNode(itemContent.value(i)));
            }
        }
    }

    m_var = doc.toString();

}

/* todo */
void RenderResponseNasSharing::generateCheckVolume() {
    QString paraPath = QByteArray::fromBase64(m_pReq->parameter("path").toLocal8Bit());
    QString paraFolderName = QByteArray::fromBase64(m_pReq->parameter("foldername").toLocal8Bit());
    QString paraFileName = QByteArray::fromBase64(m_pReq->parameter("filename").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);
    QDomNode nasSharingNode = doc.documentElement().firstChild();

    if(m_bLoginStatus) {

        QStringList itemTagNames(QStringList()
            << "file_size" << "space_allow");
        QStringList sharingContent(QStringList() << "-1" << "1");

        for(int i=0; i < itemTagNames.size(); i++) {
            QDomElement element = doc.createElement(itemTagNames.value(i));
            nasSharingNode.appendChild(element);
            element.appendChild(doc.createTextNode(sharingContent.value(i)));
        }
    }

    m_var = doc.toString();

}
