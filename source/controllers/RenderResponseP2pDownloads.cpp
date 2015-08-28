#include "RenderResponseP2pDownloads.h"

RenderResponseP2pDownloads::RenderResponseP2pDownloads(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseP2pDownloads::~RenderResponseP2pDownloads() {
}

void RenderResponseP2pDownloads::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_P2P_STATE:
        generateP2pState();
        break;
    case CMD_P2P_GET_LIST_BY_PRIORITY:
        generateP2pGetListByPriority();
        break;
    case CMD_P2P_ADD_TORRENT_URL:
        generateP2pAddTorrentUrl();
        break;
    case CMD_P2P_GET_URL_STATE:
        generateP2pGetUrlState();
        break;
    case CMD_P2P_CURRENT_SES_STATE:
        generateP2pCurrentSesState();
        break;
    case CMD_P2P_ADD_TORRENT_FILE_NEW:
        generateP2pAddTorrentFileNew();
        break;
    case CMD_P2P_DEL_ALL_COMPLETED:
        generateP2pDelAllCompleted();
        break;
    case CMD_P2P_GET_TORRENT_SCHEDULING:
        generateP2pGetTorrentScheduling();
        break;
    case CMD_P2P_TORRENT_SCHEDULING_SET:
        generateP2pTorrentSchedulingSet();
        break;
    case CMD_P2P_DETAIL_TORRENT:
        generateP2pDetailTorrent();
        break;
    case CMD_P2P_PRIORITY_SET:
        generateP2pPrioritySet();
        break;
    case CMD_P2P_DEL_TORRENT:
        generateP2pDelTorrent();
        break;
    case CMD_P2P_GET_SETTING_INFO:
        generateP2pGetSettingInfo();
        break;
    case CMD_P2P_GET_HD:
        generateP2pGetHd();
        break;
    case CMD_P2P_SET_CONFIG:
        generateP2pSetConfig();
        break;

    default:
        break;
    }

}

void RenderResponseP2pDownloads::generateP2pState() {

    QDomDocument doc;
    QMap<QString, QString> p2pInfo = getNasCfg("p2p");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement p2pElement = doc.createElement("p2p");
    root.appendChild(p2pElement);
    p2pElement.appendChild(doc.createTextNode(p2pInfo.value("enable")));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pGetListByPriority() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_P2P_API + " --get-list");

    QString titleContent = "<span id='id_%1' title='%2' alt='%2'>%2</span>";
    QString imgCompleteContent = "<IMG border='0' src='/web/images/icon-show-%1.gif'>";
    QString progressContent = "<span class='progressBar' id='progressbar_row%1'>%2</span>";
    QString imgStatusContent = "<img border='0' src='/web/images/status_%1.png'>";
    QString jsContent = "<a href=javascript:%1('%2')><IMG border='0' src='/web/images/%1.png'></a>";

    QVariantMap listMap;
    listMap.insert("total", apiOut.size());
    listMap.insert("page", m_pReq->parameter("page"));

    QVariantList itemMapList;
    QVariantMap itemMap;

    for(int i = 0; i < apiOut.size(); i++) {
        itemMap.insert("id", i+1);

        QStringList itemValues = apiOut.value(i).split(":");
        QString imgComCont = "-";
        switch(itemValues.value(3).toInt()) {
        case 1:
            imgComCont = imgCompleteContent.arg("active");
            break;
        case 2:
            imgComCont = imgCompleteContent.arg("complete");
            break;
        default:
            break;
        }

        QString imgStaCont = "-";
        switch(itemValues.value(6).toInt()) {
        case 0:
            imgStaCont = imgStatusContent.arg("queue");
            break;
        case 1:
            imgStaCont = imgStatusContent.arg("download");
            break;
        case 2:
            imgStaCont = imgStatusContent.arg("upload");
            break;
        default:
            break;
        }

        QString jsCont = "-";
        switch(itemValues.value(9).toInt()) {
        case 0:
            jsCont = jsContent.arg("stop", "0");
            break;
        case 1:
            jsCont = jsContent.arg("start", "1");
            break;
        default:
            break;
        }

        QVariantList torrent1;
        torrent1 <<
                    titleContent.arg(itemValues.value(0), itemValues.value(1)) <<
                    itemValues.value(2) <<
                    imgComCont <<
                    itemValues.value(4) <<
                    progressContent.arg(QString::number(i+1), itemValues.value(5)) <<
                    imgStaCont <<
                    itemValues.value(7) <<
                    jsCont <<
                    itemValues.value(2);

        itemMap.insert("cell", torrent1);
        itemMapList.append(itemMap);
    }

    listMap.insert("rows", itemMapList);

    m_var = QJsonDocument::fromVariant(listMap);
}

void RenderResponseP2pDownloads::generateP2pAddTorrentUrl() {

    QDomDocument doc;

    QString url = QUrl::fromPercentEncoding(m_pReq->parameter("f_torrent_url").toLocal8Bit());
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_P2P_API + " --add " + url , true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement keyNumberElement = doc.createElement("key_number");
    root.appendChild(keyNumberElement);
    keyNumberElement.appendChild(doc.createTextNode(apiOut.value(1)));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pGetUrlState() {

    QDomDocument doc;

    QStringList apiOut = getAPIFileOut(P2P_STATE_FILE, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pCurrentSesState() {

    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_p2p_current_state", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement p2pElement = doc.createElement("p2p");
    root.appendChild(p2pElement);
    p2pElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pAddTorrentFileNew() {

    QString ret("0");
    if(!m_pReq->multipartFormData().isEmpty()) {
        if(m_pReq->multipartFormData().renameUploadedFile("f_torrent_file", TORRENT_UPLOAD_FILE, true)) {
            ret = "1";
        }
    }
    QDomDocument doc;

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(ret));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pDelAllCompleted() {

    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_P2P_API + " --completed", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

/* todo: need API */
void RenderResponseP2pDownloads::generateP2pGetTorrentScheduling() {

    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QStringList configTagNames(QStringList()
        << "name" << "f_type" << "st_year" << "st_mon" << "st_day"
        << "st_hours" << "st_min" << "stop_time" << "result");

//    if( configContentElement.size() != apiOut.size() ) {
//        for(int i = 0; i < apiOut.size(); i++) {
//            QDomElement element = doc.createElement(configContentElement.value(i));
//            root.appendChild(element);
//            element.appendChild(doc.createTextNode(apiOut.value(i)));
//        }
//    }
//    else {
//        //assert(0);
//        tError("RenderResponseSysStatus::generateModuleShowInstallStatus(): "
//               "configContentElement size is not equal to apiOut size.");
//    }

    m_var = doc.toString();

}

/* todo: need API */
void RenderResponseP2pDownloads::generateP2pTorrentSchedulingSet() {

    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pDetailTorrent() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " serice_get_p2p_Detail_info " +
                                      allParametersToString(), true, ";");

    QVariantMap listMap;
    listMap.insert("name", apiOut.value(0));
    listMap.insert("detail", apiOut.value(1));
    listMap.insert("result", apiOut.value(2));

    m_var = QJsonDocument::fromVariant(listMap);
}

void RenderResponseP2pDownloads::generateP2pPrioritySet() {

    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_P2P_API + " --priority " +
                                      m_pReq->parameter("f_priority"), true, ";");


    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pDelTorrent() {

    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_P2P_API + " --remove " +
                                      m_pReq->parameter("f_torrent_url"), true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pGetSettingInfo() {
    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_p2p_setting_info", true, ":");

    QDomElement root = doc.createElement("device_info");
    doc.appendChild(root);

    QStringList configTagNames(QStringList()
            << "result" << "p2p" << "port" << "port_number"
            << "bandwidth" << "bandwidth_upload_rate" << "bandwidth_downlaod_rate"
            << "seeding" << "seeding_percent" << "seeding_mins" << "encryption"
            << "autodownload" << "current_ses_state" << "flow_control_download_rate"
            << "flow_control_upload_rate" << "flow_control");

    if(apiOut.value(0) == "0") {
        QDomElement element = doc.createElement(configTagNames.value(0));
        root.appendChild(element);
        element.appendChild(doc.createTextNode(apiOut.value(0)));
    }
    else {
        if( configTagNames.size() == apiOut.size() ) {
            for(int i = 0; i < apiOut.size(); i++) {
                QDomElement element = doc.createElement(configTagNames.value(i));
                root.appendChild(element);
                element.appendChild(doc.createTextNode(apiOut.value(i)));
            }
        }
        else {
            //assert(0);
            tError("RenderResponseP2pDownloads::generateP2pGetSettingInfo() :"
                   "configTagNames size is not equal to apiOut size.");
        }
    }

    m_var = doc.toString();
}

void RenderResponseP2pDownloads::generateP2pGetHd() {

    QStringList shareInfo = getAPIFileOut(SHARE_INFO_FILE);

    QString selectClass = "<select size=\"1\" name=\"f_hdd_list\" disabled>\n"
                          "%1"
                          "</select>";
    QString optionClass =  "    <option value=\"%1\"%2>%3</option>\n";
    QString opt;

    for(int i = 0; i<shareInfo.size(); i++) {
        QString folderName = shareInfo.value(i).right(shareInfo.value(i).length()
                                                      - (shareInfo.value(i).lastIndexOf("/") + 1));
        QString select;
        if(i == 0)
            select = " selected";
        opt += optionClass.arg(folderName, select, shareInfo.value(i).split(":").value(0));
    }

    m_var = selectClass.arg(opt);

}

void RenderResponseP2pDownloads::generateP2pSetConfig() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_p2p_setting " +
                                      allParametersToString());
    m_var = "<script>location.href='/web/download_mgr/p2p_set.html?id=8401878'</script>";

}

