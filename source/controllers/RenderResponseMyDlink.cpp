#include <QDir>
#include <sys/sysinfo.h>

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
            break;
        case CMD_2:
            generateSetDeviceName();
            break;
        case CMD_3:
            generateGetDeviceInfo();
            break;
        case CMD_4:
            generateListVolume();
            break;
        case CMD_5:
            generateListFolder();
            break;
        case CMD_6:
            generateDownload();
            break;
        case CMD_8:
            generateDelete();
            break;
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
        case CMD_17:
            generateRestart();
            break;
        case CMD_20:
            generateGetLog();
            break;
        case CMD_21:
            generateSetAppOrder();
            break;
        case CMD_22:
            generateGetAppOrder();
            break;
        default:
            break;
        }

    }

}

void RenderResponseMyDlink::generateInfo() {

    QStringList arg = QStringList() << "system_get_lan_mac_info";
    QStringList apiOutMac = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");
    QStringList arg1 = QStringList() << "get";
    QStringList apiOutDev = getAPIStdOut(API_PATH + SCRIPT_DEVICE_API, arg1, true, ";");
    QStringList apiOutModel = getAPIFileOut(MODEL_FILE);
    QMap<QString, QString> systemInfo = getNasCfg("system");

    QString fmtOut = "Product=%1\n"
            "Model=%2\n"
            "Version=%3\n"
            "Build=\n"
            "Macaddr=%4\n"
            "Wireless=NO\n"
            "Ptz=";

    QString ret = fmtOut.arg(apiOutDev.value(0), apiOutModel.value(0),
                             systemInfo.value("sw_ver"), apiOutMac.value(0));
    m_var = ret;

}


bool RenderResponseMyDlink::isLogin() {

    QString paraName = QUrl::fromPercentEncoding(m_pReq->parameter("name").toLocal8Bit());
    QString loginStr = QByteArray::fromBase64(paraName.toLocal8Bit()) +
            " " + QUrl::fromPercentEncoding(m_pReq->parameter("pwd").toLocal8Bit());

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_CHK_PWD + " " + loginStr, true);
    return apiOut.value(0) == "OK" ? true : false;

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

void RenderResponseMyDlink::generateSetDeviceName() {

    QDomDocument doc;
    generatePrefix(doc);

    QString paraDeviceName = QUrl::fromPercentEncoding(m_pReq->parameter("device_name").toLocal8Bit());

    QDomElement root = doc.documentElement();
    if(m_bLoginStatus) {
        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));

        QStringList arg = QStringList() << "get";
        QStringList apiOutGet = getAPIStdOut(API_PATH + SCRIPT_DEVICE_API, arg, true, ";");
        QStringList arg1 = QStringList() << "set" << paraDeviceName << apiOutGet.value(1) << apiOutGet.value(2);
        QStringList apiOutSet = getAPIStdOut(API_PATH + SCRIPT_DEVICE_API, arg1, true, ";");
    }

    QStringList apiOutHostname = getAPIFileOut(HOSTNAME_FILE, true);

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOutHostname.value(0) == paraDeviceName ? "1" : "0"));

    m_var = doc.toString();

}

void RenderResponseMyDlink::generateGetDeviceInfo() {

    QDomDocument doc;
    generatePrefix(doc);

    QString paraType = m_pReq->parameter("type").toLocal8Bit();

    QDomElement root = doc.documentElement();

    if(m_bLoginStatus) {
        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));

        if(paraType == "0") {
            getDevInfoType1(doc);
            getDevInfoType2(doc);
            getDevInfoType3(doc);
            getDevInfoType4(doc);
        }
        else if(paraType == "1") {
            getDevInfoType1(doc);
        }
        else if(paraType == "2") {
            getDevInfoType2(doc);
        }
        else if(paraType == "3") {
            getDevInfoType3(doc);
        }
        else if(paraType == "4") {
            getDevInfoType4(doc);
        }
        else if(paraType == "5") {
            //QStringList arg = QStringList() << "system_get_device_smart_info";
            //QStringList apiOutSmartList = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

            QDomElement disksElement = doc.createElement("new_disks");
            root.appendChild(disksElement);

//            QStringList disksTagNames(QStringList()
//                << "device" << "manufacture" << "model" << "size");
//            for(QString e : apiOutSmartList) {

//                QStringList disksContents(QStringList()
//                    << e.split(";").value(6) << e.split(";").value(1) << e.split(";").value(2)
//                                          << e.split(";").value(5));

//                QDomElement diskElement = doc.createElement("disk");
//                disksElement.appendChild(diskElement);
//                for(int i = 0; i < disksTagNames.size(); i++) {
//                    QDomElement element = doc.createElement(disksTagNames.value(i));
//                    diskElement.appendChild(element);
//                    element.appendChild(doc.createTextNode(disksContents.value(i)));
//                }
//            }

//            QStringList typeTagNames(QStringList()
//                << "standard" << "jbod" << "raid0" << "raid1" << "raid5" << "raid5_spare"
//                << "raid10"  << "raid0_jbod" << "raid1_jbod" << "raid5_jbod"
//                << "raid5_spare_jbod" << "raid10_jbod");
//            QStringList typeContents(QStringList()
//                << "1" << "1" << "1" << "1" << "0" << "0"
//                << "0"  << "1" << "1" << "0"
//                << "0" << "0");
//            for(int i = 0; i < typeTagNames.size(); i++) {
//                QDomElement element = doc.createElement(typeTagNames.value(i));
//                root.appendChild(element);
//                element.appendChild(doc.createTextNode(typeContents.value(i)));
//            }

        }
        else if(paraType == "6") {
            QStringList shareInfo = getAPIFileOut(SHARE_INFO_FILE);
            QStringList arg = QStringList() << "Module_Get_Info";
            QStringList apiOutModule = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

            QDomElement servicesElement = doc.createElement("services");
            root.appendChild(servicesElement);

            QStringList serviceNames(QStringList()
                << "My Photos" << "My Music" << "My Files" << "P2P Download" << "My Surveillance");

            // todo : My Surveillance
            QString hasHdd = shareInfo.isEmpty() ? "0" : "1";
            QStringList serviceStatus(QStringList()
                << hasHdd << hasHdd << hasHdd
                << apiOutModule.value(0).split(";").value(0) << "0");

            QStringList servicePort(QStringList()
                << "80" << "80" << "80" << "" << "8080");

            QStringList servicePage(QStringList()
                << "photo_center/index.html" << "MyMusic/index.html"
                << "web/web_file/web_file_server.html" << "web/download_mgr/p2p_main.html"
                << "MySurveillance/index.html");

            QMap<QString, QVariant> idxMap;
            idxMap.insert("My Photos", 0);
            idxMap.insert("My Music", 1);
            idxMap.insert("My Files", 2);
            idxMap.insert("P2P Download", 3);
            idxMap.insert("My Surveillance", 4);
            QStringList appOrder = getNasCfg("mydlink").value("mydlk_app_order").split(",");

            for(int i = 0; i < appOrder.size(); i++) {
                int index = -1;
                QString key = appOrder.value(i).trimmed();
                if(idxMap.contains(key)) {
                    index = idxMap.value(key).toInt();

                    QDomElement serviceElement = doc.createElement("service");
                    servicesElement.appendChild(serviceElement);
                    QDomElement nameElement = doc.createElement("name");
                    serviceElement.appendChild(nameElement);
                    nameElement.appendChild(doc.createTextNode(serviceNames.value(index)));
                    QDomElement statusElement = doc.createElement("status");
                    serviceElement.appendChild(statusElement);
                    statusElement.appendChild(doc.createTextNode(serviceStatus.value(index)));
                    QDomElement portElement = doc.createElement("port");
                    serviceElement.appendChild(portElement);
                    portElement.appendChild(doc.createTextNode(servicePort.value(index)));
                    QDomElement pageElement = doc.createElement("page");
                    serviceElement.appendChild(pageElement);
                    pageElement.appendChild(doc.createTextNode(servicePage.value(index)));
                }
            }

        }
    }

    m_var = doc.toString();

}

void RenderResponseMyDlink::getDevInfoType1(QDomDocument &doc) {
    QDomElement root = doc.documentElement();

    QStringList arg = QStringList() << "get";
    QStringList apiOutDevice = getAPIStdOut(API_PATH + SCRIPT_DEVICE_API, arg, true, ";");
    QStringList apiOutModel = getAPIFileOut(MODEL_FILE);
    QStringList arg1 = QStringList() << "system_get_lan_mac_info";
    QStringList apiOutMac = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg1, true, ";");

    QDomElement deviceNameElement = doc.createElement("device_name");
    root.appendChild(deviceNameElement);
    deviceNameElement.appendChild(doc.createTextNode(apiOutDevice.value(0)));
    QDomElement modelNameElement = doc.createElement("model_name");
    root.appendChild(modelNameElement);
    modelNameElement.appendChild(doc.createTextNode(apiOutModel.value(0)));
    QDomElement macElement = doc.createElement("mac");
    root.appendChild(macElement);
    macElement.appendChild(doc.createTextNode(apiOutMac.value(0)));
}

void RenderResponseMyDlink::getDevInfoType2(QDomDocument &doc) {
    QDomElement root = doc.documentElement();

    QStringList arg = QStringList() << "system_get_device_detail_info";
    QStringList apiOutDev = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");
    arg.clear(); arg = QStringList() << "system_get_system_temperature";
    QStringList apiOutTemp = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
    arg.clear(); arg = QStringList() << "service_home_api" << "cgi_get_fw_status";
    QStringList apiOutFwStatus = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
    arg.clear(); arg = QStringList() << "system_get_device_smart_info";
    QStringList apiOutSmartList = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);
    QStringList apiOutFwVer = getAPIStdOut(API_PATH + SCRIPT_MDB + " get fw_version", true);

    struct sysinfo info;
    sysinfo(&info);

    QDomElement memorySizeElement = doc.createElement("memory_size");
    root.appendChild(memorySizeElement);
    memorySizeElement.appendChild(doc.createTextNode(apiOutDev.value(11)));
    QDomElement sysTempElement = doc.createElement("system_temp");
    root.appendChild(sysTempElement);
    sysTempElement.appendChild(doc.createTextNode(apiOutTemp.value(0)));
    QDomElement uptimeElement = doc.createElement("system_uptime");
    root.appendChild(uptimeElement);
    uptimeElement.appendChild(doc.createTextNode(QString::number(info.uptime)));
    QDomElement fwElement = doc.createElement("fw_ver");
    root.appendChild(fwElement);
    fwElement.appendChild(doc.createTextNode(apiOutFwVer.value(0)));
    QDomElement abnormalShutdownElement = doc.createElement("abnormal_shutdown");
    root.appendChild(abnormalShutdownElement);
    abnormalShutdownElement.appendChild(doc.createTextNode(apiOutFwStatus.value(0) == "1" ? "1" : "0"));

    QDomElement disksElement = doc.createElement("disks");
    root.appendChild(disksElement);

    QStringList disksTagNames(QStringList()
        << "device" << "manufacture" << "model" << "size" << "serial");
    for(QString e : apiOutSmartList) {

        QStringList disksContents(QStringList()
            << e.split(";").value(6) << e.split(";").value(1) << e.split(";").value(2)
                                  << e.split(";").value(5) << e.split(";").value(3));

        QDomElement diskElement = doc.createElement("disk");
        disksElement.appendChild(diskElement);
        for(int i = 0; i < disksTagNames.size(); i++) {
            QDomElement element = doc.createElement(disksTagNames.value(i));
            diskElement.appendChild(element);
            element.appendChild(doc.createTextNode(disksContents.value(i)));
        }
    }
}

void RenderResponseMyDlink::getDevInfoType3(QDomDocument &doc) {
    QDomElement root = doc.documentElement();

    QStringList arg = QStringList() << "system_get_resource_info";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg).value(0).split(";");

    QDomElement rxElement = doc.createElement("rx");
    root.appendChild(rxElement);
    rxElement.appendChild(doc.createTextNode(apiOut.value(1)));
    QDomElement txElement = doc.createElement("tx");
    root.appendChild(txElement);
    txElement.appendChild(doc.createTextNode(apiOut.value(2)));
    QDomElement cpuLoadElement = doc.createElement("cpu_load");
    root.appendChild(cpuLoadElement);
    cpuLoadElement.appendChild(doc.createTextNode(apiOut.value(10).remove('%')));

    int iMemUsed = apiOut.value(5).toInt() - apiOut.value(6).toInt();
    QDomElement memUsedElement = doc.createElement("memory_used");
    root.appendChild(memUsedElement);
    memUsedElement.appendChild(doc.createTextNode(QString::number(iMemUsed)));
}

void RenderResponseMyDlink::getDevInfoType4(QDomDocument &doc) {
    QDomElement root = doc.documentElement();

    QStringList arg = QStringList() << "system_get_system_services";
    QStringList apiOutServices = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");
    arg.clear(); arg = QStringList() << "media_get_itunes_config";
    QStringList apiOutItunes = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");
    arg.clear(); arg = QStringList() << "quotainfo";
    QStringList apiOutQuota = getAPIStdOut(API_PATH + SCRIPT_QUOTA_MGR, arg, true, ";");


    QDomElement servicesElement = doc.createElement("services");
    root.appendChild(servicesElement);

    QStringList serviceNames(QStringList()
        << "FTP Server" << "NFS Server" << "AFP Server" << "Syslog Server" << "UPnP AV Server"
        << "DDNS Server" << "Time Machine" << "iTune Server" << "Quota Server" << "SNMP Server"
        << "P2P Server");

    QStringList serviceStatus(QStringList()
        << apiOutServices.value(6) << apiOutServices.value(1) << apiOutServices.value(0)
        << apiOutServices.value(8) << apiOutServices.value(4) << apiOutServices.value(3)
        << apiOutServices.value(5) << apiOutItunes.value(0) << apiOutQuota.value(4)
        << "0" << apiOutServices.value(7));

    for(int i = 0; i < serviceNames.size(); i++) {
        QDomElement serviceElement = doc.createElement("service");
        servicesElement.appendChild(serviceElement);
        QDomElement nameElement = doc.createElement("name");
        serviceElement.appendChild(nameElement);
        nameElement.appendChild(doc.createTextNode(serviceNames.value(i)));
        QDomElement statusElement = doc.createElement("status");
        serviceElement.appendChild(statusElement);
        statusElement.appendChild(doc.createTextNode(serviceStatus.value(i)));
    }
}


void RenderResponseMyDlink::generateListVolume() {

    QDomDocument doc;
    generatePrefix(doc);

    QDomElement root = doc.documentElement();
    if(m_bLoginStatus) {
        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));

        QStringList arg = QStringList() << "system_get_hdd_volume_info";
        QStringList apiOutVolInfo = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

        QMap<QString, QString> map;
        QDomDocument readFileDoc;
        readXml(SCANDISK_PROGRESS_FILE, readFileDoc);
        QDomNodeList list = readFileDoc.documentElement().childNodes();
        for(int i = 0; i < list.size(); i++)
            map.insert(list.at(i).toElement().tagName(), list.at(i).toElement().text());

        QDomElement volumesElement = doc.createElement("volumes");
        root.appendChild(volumesElement);
        for(QString e : apiOutVolInfo) {
            QStringList volItem = e.split(";");
            QStringList volTagNames(QStringList()
                << "label" << "path" << "type" << "total_size" << "used_size" << "free_size"
                << "permission" << "scandisk");

            QString volumeName = QString("Volume_%1").arg(volItem.value(0));
            QString realPath = volumeName;
            replaceVoltoRealPath(realPath);
            QString fmtType = volItem.value(1).replace("standard", "Single Disk");
            QString scandiskStatus = "0";
            if(map.value("scanned_volume") == volumeName)
                scandiskStatus = map.value("result");
            QStringList volContents(QStringList()
                << volumeName << realPath << fmtType << volItem.value(3) << volItem.value(4)
                << volItem.value(5) << "2" << scandiskStatus);

            QDomElement volumeElement = doc.createElement("volume");
            volumesElement.appendChild(volumeElement);
            for(int i = 0; i < volTagNames.size(); i++) {
                QDomElement element = doc.createElement(volTagNames.value(i));
                volumeElement.appendChild(element);
                element.appendChild(doc.createTextNode(volContents.value(i)));
            }
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

                if(No_Display_File_Set.contains(entry.fileName())) {
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

void RenderResponseMyDlink::generateDelete() {
    QString paraPath = QUrl::fromPercentEncoding(m_pReq->parameter("path").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    QDomElement root = doc.documentElement();
    bool bRemove = remove(paraPath);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(QString::number(bRemove)));

    if(m_bLoginStatus && bRemove) {
        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));
    }
    m_var = doc.toString();

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

void RenderResponseMyDlink::generateRestart() {
    QDomDocument doc;
    generatePrefix(doc);

    QDomElement root = doc.documentElement();
    startDetached(API_PATH + SCRIPT_POWER_API, QStringList() << "restart");
    if(m_bLoginStatus) {
        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));
    }

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

void RenderResponseMyDlink::generateGetLog() {
    QString paraType = QUrl::fromPercentEncoding(m_pReq->parameter("type").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    QDomElement root = doc.documentElement();

    QString status = QDir(MYDLINK_TMP_PATH).exists() ? "1" : "0";

    QString paraForLog = "-c";
    if(paraType == "0") {
        paraForLog = "-o " + MYDLINK_LOG_FILE;
        if(status == "0")
            status = QDir().mkpath(MYDLINK_TMP_PATH) ? "1" : "0";
    }
    else if(paraType == "1")
        status = remove(MYDLINK_TMP_PATH) ? "1" : "0";

    if(m_bLoginStatus && status == "1") {

        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));

        getAPIStdOut(API_PATH + SCRIPT_CLOG + " " + paraForLog);

        if(paraType == "0") {
            QString pathFormat = "http:://%1/%2";
            QString localIP = getNasCfg(getNasCfg("network").value("default_gw")).value("ip");
            QString filePath = MYDLINK_LOG_FILE;
            filePath.remove("/var/www/");

            QDomElement pathElement = doc.createElement("path");
            root.appendChild(pathElement);
            pathElement.appendChild(doc.createTextNode(pathFormat.arg(localIP, filePath)));
        }

    }

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(status));

    m_var = doc.toString();

}

void RenderResponseMyDlink::generateSetAppOrder() {

    QString paraAppOrder = QUrl::fromPercentEncoding(m_pReq->parameter("apporder").toLocal8Bit());

    QDomDocument doc;
    generatePrefix(doc);

    QDomElement root = doc.documentElement();

    if(m_bLoginStatus) {
        int status = 0;
        if(status = setNasCfg("mydlink", "mydlk_app_order", paraAppOrder)) {
            QDomElement versionElement = doc.createElement("version");
            root.appendChild(versionElement);
            versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));
        }
        QDomElement statusElement = doc.createElement("status");
        root.appendChild(statusElement);
        statusElement.appendChild(doc.createTextNode(QString::number(status)));

    }

    m_var = doc.toString();

}

void RenderResponseMyDlink::generateGetAppOrder() {

    QDomDocument doc;
    generatePrefix(doc);

    QDomElement root = doc.documentElement();

    if(m_bLoginStatus) {
        QDomElement versionElement = doc.createElement("version");
        root.appendChild(versionElement);
        versionElement.appendChild(doc.createTextNode(MYDLINK_VERSION));

        QDomElement authStateElement = doc.createElement("auth_state");
        root.appendChild(authStateElement);
        authStateElement.appendChild(doc.createTextNode("1"));

        QStringList appOrder = getNasCfg("mydlink").value("mydlk_app_order").split(",");
        for(int i = 0; i < appOrder.size(); i++) {
            QDomElement itemElement = doc.createElement("item");
            root.appendChild(itemElement);

            QDomElement appNameElement = doc.createElement("appname");
            itemElement.appendChild(appNameElement);
            appNameElement.appendChild(doc.createTextNode(appOrder.value(i).trimmed()));
            QDomElement orderElement = doc.createElement("order");
            itemElement.appendChild(orderElement);
            orderElement.appendChild(doc.createTextNode(QString::number(i+1)));
        }

    }

    m_var = doc.toString();

}
