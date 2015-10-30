#include <QDir>

#include "RenderResponseNasSharing.h"
#include "Databaseobject.h"

static QMap<QString, QString> raid_mode_map {

    { "standard",    "1"    },
    { "linear"  ,    "2"    },
    { "raid0"   ,    "3"    },
    { "raid1"   ,    "4"    },

};

static QMap<QString, QString> file_type_map {

    { "ext2",    "1"    },
    { "ext3",    "2"    },
    { "ext4",    "3"    },

};

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

    case CMD_NAS_SHARING_55:
        generateDeviceInfo();
        break;

    case CMD_NAS_SHARING_70:
        generateCheckDiskFreeSize();
        break;
    case CMD_NAS_SHARING_73:
        generateGetHdInfo();
        break;
    case CMD_NAS_SHARING_74:
        //generateCheckVolume();
        break;
    case CMD_NAS_SHARING_75:
        generateGetVolumeInfo();
        break;
    case CMD_NAS_SHARING_76:
        //generateCheckVolume();
        break;
    case CMD_NAS_SHARING_77:
        //generateCheckVolume();
        break;
    case CMD_NAS_SHARING_78:
        //generateCheckVolume();
        break;
    case CMD_NAS_SHARING_79:
        //generateCheckVolume();
        break;
    case CMD_NAS_SHARING_81:
        //generateCheckVolume();
        break;
    case CMD_NAS_SHARING_82:
        //generateCheckVolume();
        break;
    case CMD_NAS_SHARING_83:
        //generateCheckVolume();
        break;
    case CMD_NAS_SHARING_84:
        //generateCheckVolume();
        break;
    case CMD_NAS_SHARING_85:
        //generateCheckVolume();
        break;
    case CMD_NAS_SHARING_86:
        //generateCheckVolume();
        break;
    case CMD_NAS_SHARING_87:
        //generateCheckVolume();
        break;
    case CMD_NAS_SHARING_88:
        //generateCheckVolume();
        break;
    case CMD_NAS_SHARING_89:
        //generateCheckVolume();
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

void RenderResponseNasSharing::generateDeviceInfo() {
    QDomDocument doc;
    QStringList arg = QStringList() << "system_get_system_status";
    QStringList apiOutSysStatus = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement lanElement = doc.createElement("lan");
    root.appendChild(lanElement);

    QStringList itemTagNames(QStringList()
        << "ip" << "netmask" << "gateway" << "dns1" << "dns2" << "mac");

    QList<QStringList> itemList;
    itemList << (QStringList()
        << apiOutSysStatus.value(3) << apiOutSysStatus.value(4) << apiOutSysStatus.value(5)
        << apiOutSysStatus.value(6) << apiOutSysStatus.value(7) << apiOutSysStatus.value(19));
    if(!apiOutSysStatus.value(10).isEmpty())
        itemList << (QStringList()
            << apiOutSysStatus.value(10) << apiOutSysStatus.value(11) << apiOutSysStatus.value(12)
            << apiOutSysStatus.value(13) << apiOutSysStatus.value(14)  << apiOutSysStatus.value(20));

    for(QStringList item : itemList) {
        QDomElement itemElement = doc.createElement("item");
        lanElement.appendChild(itemElement);
        for(int i=0; i < itemTagNames.size(); i++) {
            QDomElement element = doc.createElement(itemTagNames.value(i));
            itemElement.appendChild(element);
            element.appendChild(doc.createTextNode(item.value(i)));
        }
    }

    arg.clear(); arg = QStringList() << "system_get_system_temperature";
    QStringList apiOutTemp = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
    QString uptime = QDateTime::fromTime_t(apiOutSysStatus.value(27).toInt()).toUTC().toString("d,h,s");
    QStringList deviceTagNames(QStringList()
        << "workgroup" << "name" << "description" << "temperature" << "uptime");
    QStringList deviceContent(QStringList()
        << apiOutSysStatus.value(17) << apiOutSysStatus.value(16) << apiOutSysStatus.value(18)
        << apiOutTemp.value(0) << uptime);

    QDomElement deviceElement = doc.createElement("device");
    root.appendChild(deviceElement);
    for(int i=0; i < deviceTagNames.size(); i++) {
        QDomElement element = doc.createElement(deviceTagNames.value(i));
        deviceElement.appendChild(element);
        element.appendChild(doc.createTextNode(deviceContent.value(i)));
    }

    QList<QMap<QString, QByteArray>> diskItemList;
    QDomDocument readFileDoc;
    readXml(USED_VOLUME_INFO_FILE, readFileDoc);
    QDomNode n = readFileDoc.documentElement().firstChild().firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement();
        if(!e.isNull() && e.tagName() == "item") {
            QDomNodeList list = e.childNodes();
            QMap<QString, QByteArray> map;

            for(int i = 0; i < list.size(); i++) {
                QDomElement childElement = list.at(i).toElement();
                map.insert(childElement.tagName(), childElement.text().toLocal8Bit());
            }
            diskItemList << map;
        }
        n = n.nextSibling();
    }
    QStringList shareInfo = getAPIFileOut(SHARE_INFO_FILE);

    QStringList diskItemTagNames(QStringList()
        << "volume_num" << "raid_mode" << "raidStatus" << "my_mdx" << "sync_perct" << "sync_time"
        << "total_size" << "use_size" << "free_size" << "used_rate");

    QDomElement volumeElement = doc.createElement("volume");
    root.appendChild(volumeElement);
    for(QMap<QString, QByteArray> e : diskItemList) {
        bool bFound = false;
        QString volName = "Volume_" + e.value("volume");
        QString realPath = volName;
        for(auto shareInfoEntry : shareInfo) {
            if(shareInfoEntry.contains(volName)) {
                bFound = true;
                replaceVoltoRealPath(realPath);
                break;
            }
        }
        if(!bFound)
            continue;

        QStringList apiOutDf = getAPIStdOut("df " + realPath, false, "", 1).value(1)
                .split(" ", QString::SkipEmptyParts);

        QString mdx = e.value("mount").right(e.value("mount").length()
                                             - (e.value("mount").lastIndexOf(QDir::separator()) + 1));
        /* todo: disk encryption rule */
        QStringList itemContent(QStringList() << e.value("volume")
            << e.value("raid_mode") << e.value("raid_status") << mdx << "0" << "0"
            << apiOutDf.value(1) << apiOutDf.value(2) << apiOutDf.value(3) << apiOutDf.value(4).remove("%")
            );

        QDomElement itemElement = doc.createElement("item");
        volumeElement.appendChild(itemElement);
        for(int i=0; i < diskItemTagNames.size(); i++) {
            QDomElement element = doc.createElement(diskItemTagNames.value(i));
            itemElement.appendChild(element);
            element.appendChild(doc.createTextNode(itemContent.value(i)));
        }
    }

    QStringList apiOutFwVer = getAPIStdOut(API_PATH + SCRIPT_MDB + " get fw_version", true);
    QString fwDate = getAPIFileOut(FIRMWARE_VERSION_FILE).value(0).section('.', 2, 3);

    QDomElement firmwareElement = doc.createElement("firmware");
    root.appendChild(firmwareElement);
    QDomElement versionElement = doc.createElement("version");
    firmwareElement.appendChild(versionElement);
    versionElement.appendChild(doc.createTextNode(apiOutFwVer.value(0)));

    QDomElement dateElement = doc.createElement("date");
    firmwareElement.appendChild(dateElement);
    dateElement.appendChild(doc.createTextNode(QDateTime::fromString(fwDate, "MMdd.yyyy").toString("MM/dd/yyyy")));

    m_var = doc.toString();
}

void RenderResponseNasSharing::generateCheckDiskFreeSize() {
    QString paraPath = QByteArray::fromBase64(m_pReq->parameter("path").toLocal8Bit());

    m_var = "0";
    if(m_bLoginStatus) {
        QStringList apiOut = getAPIStdOut("df " + paraPath, false, "", 1).value(1)
                .split(" ", QString::SkipEmptyParts);
        m_var = apiOut.value(3);
    }

}

void RenderResponseNasSharing::generateGetHdInfo() {
    QDomDocument doc;
    generatePrefix(doc);
    QDomNode nasSharingNode = doc.documentElement().firstChild();

    if(m_bLoginStatus) {

        QList<QMap<QString, QByteArray>> itemList;
        QDomDocument readFileDoc;
        readXml(CURRENT_HD_INFO_FILE, readFileDoc);
        QDomNode n = readFileDoc.documentElement().firstChild().firstChild().firstChild();
        n = n.nextSibling();
        while(!n.isNull()) {
            QDomElement e = n.toElement();
            if(!e.isNull() && e.tagName() == "item") {
                QDomNodeList list = e.childNodes();
                QMap<QString, QByteArray> map;

                for(int i = 0; i < list.size(); i++) {
                    QDomElement childElement = list.at(i).toElement();
                    map.insert(childElement.tagName(), childElement.text().toLocal8Bit());
                }
                itemList << map;
            }
            n = n.nextSibling();
        }

        QStringList apiOutParti = getAPIFileOut("/proc/partitions");
        QStringList arg = QStringList() << "system_get_disk_volume_status";
        QStringList apiOutVolStatus = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

        QDomElement countElement = doc.createElement("count");
        nasSharingNode.appendChild(countElement);
        countElement.appendChild(doc.createTextNode(QString::number(itemList.size())));

        QStringList itemTagNames(QStringList()
            << "name" << "vendor" << "model" << "serial" << "scsi" << "size" << "block_all"
                                 << "block_p1" << "block_p2" << "block_p3" << "block_p4");

        for(QMap<QString, QByteArray> e : itemList) {

            QStringList blockList;
            for(QString line : apiOutParti) {
                QStringList factor = line.split(" ", QString::SkipEmptyParts);
                if(factor.value(3).startsWith(e.value("device_name")))
                    blockList << factor.value(2);
            }
            QStringList itemContent(QStringList() << e.value("device_name").toBase64()
                << e.value("vendor").toBase64() << e.value("model").toBase64() << e.value("hd_serial").toBase64()
                << e.value("scsi") << e.value("hd_GiB_size"));
            itemContent += blockList;

            QDomElement itemElement = doc.createElement("item");
            nasSharingNode.appendChild(itemElement);
            for(int i=0; i < itemTagNames.size(); i++) {
                QDomElement element = doc.createElement(itemTagNames.value(i));
                itemElement.appendChild(element);
                element.appendChild(doc.createTextNode(itemContent.value(i)));
            }

        }

        QDomElement formattingElement = doc.createElement("formatting");
        nasSharingNode.appendChild(formattingElement);
        formattingElement.appendChild(doc.createTextNode(apiOutVolStatus.value(0)));
    }

    m_var = doc.toString();
}

void RenderResponseNasSharing::generateGetVolumeInfo() {
    QDomDocument doc;
    generatePrefix(doc);
    QDomNode nasSharingNode = doc.documentElement().firstChild();

    if(m_bLoginStatus) {

        QList<QMap<QString, QByteArray>> itemList;
        QDomDocument readFileDoc;
        readXml(USED_VOLUME_INFO_FILE, readFileDoc);
        QDomNode n = readFileDoc.documentElement().firstChild().firstChild();
        while(!n.isNull()) {
            QDomElement e = n.toElement();
            if(!e.isNull() && e.tagName() == "item") {
                QDomNodeList list = e.childNodes();
                QMap<QString, QByteArray> map;

                for(int i = 0; i < list.size(); i++) {
                    QDomElement childElement = list.at(i).toElement();
                    map.insert(childElement.tagName(), childElement.text().toLocal8Bit());
                }
                itemList << map;
            }
            n = n.nextSibling();
        }
        QStringList shareInfo = getAPIFileOut(SHARE_INFO_FILE);

        QDomElement countElement = doc.createElement("count");
        nasSharingNode.appendChild(countElement);

        QStringList itemTagNames(QStringList()
            << "volume" << "raid_mode" << "raid_status" << "file_type" << "total_size" << "free_size"
            << "dev_used" << "dev_spare" << "dev_count" << "todo" << "encrypt" << "mount_status"
            << "roaming_flag");

        int count = 0;
        for(QMap<QString, QByteArray> e : itemList) {
            bool bFound = false;
            QString volName = "Volume_" + e.value("volume");
            QString realPath = volName;
            for(auto shareInfoEntry : shareInfo) {
                if(shareInfoEntry.contains(volName)) {
                    bFound = true;
                    count++;
                    replaceVoltoRealPath(realPath);
                    break;
                }
            }
            if(!bFound)
                continue;

            QStringList apiOut = getAPIStdOut("df " + realPath, false, "", 1).value(1)
                    .split(" ", QString::SkipEmptyParts);

            /* todo: disk encryption rule */
            QStringList itemContent(QStringList() << e.value("volume")
                << raid_mode_map.value(e.value("raid_mode")) << e.value("raid_status")
                << file_type_map.value(e.value("file_type")) << apiOut.value(1) << apiOut.value(3)
                << e.value("device").toBase64() << "" << e.value("dev_num") << ""
                << e.value("volume_encrypt") << e.value("mount_status") << "0");

            QDomElement itemElement = doc.createElement("item");
            nasSharingNode.appendChild(itemElement);
            for(int i=0; i < itemTagNames.size(); i++) {
                QDomElement element = doc.createElement(itemTagNames.value(i));
                itemElement.appendChild(element);
                element.appendChild(doc.createTextNode(itemContent.value(i)));
            }
        }
        countElement.appendChild(doc.createTextNode(QString::number(count)));

    }

    m_var = doc.toString();
}
