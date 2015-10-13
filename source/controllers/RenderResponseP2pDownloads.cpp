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
    case CMD_P2P_HOME_STATE:
        generateP2PHomeState();
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
    case CMD_P2P_GET_TORRENT_INFO:
        generateP2pGetTorrentInfo();
        break;
    case CMD_P2P_START_TORRENT:
        generateP2pStartTorrent();
        break;
    case CMD_P2P_PAUSE_TORRENT:
        generateP2pPauseTorrent();
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

void RenderResponseP2pDownloads::generateP2PHomeState() {

    QDomDocument doc;

    QStringList arg = QStringList() << "service_p2p_home_stat";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(apiOut.value(0)));

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
            jsCont = jsContent.arg("stop", QString::number(i+1));
            break;
        case 1:
            jsCont = jsContent.arg("start", QString::number(i+1));
            break;
        default:
            break;
        }

        QVariantList torrent1;
        torrent1 <<
                    titleContent.arg(itemValues.value(0), itemValues.value(1)) <<
                    itemValues.value(2);

        if(m_pReq->parameter("f_field") == "1")
            torrent1 << imgComCont;

        torrent1 <<
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

    //QString url = QUrl::fromPercentEncoding(m_pReq->parameter("f_torrent_url").toLocal8Bit());
    QStringList arg = QStringList() << "service_set_p2p_url_torrent" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

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

    QStringList arg = QStringList() << "service_p2p_current_state";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

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
            getAPIStdOut(API_PATH + SCRIPT_P2P_API + " --add " + TORRENT_UPLOAD_FILE);
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

void RenderResponseP2pDownloads::generateP2pGetTorrentScheduling() {

    QDomDocument doc;

    QString paraTorrentIndex = m_pReq->parameter("f_torrent_index");
    QStringList arg = QStringList() << "service_get_p2p_torrent_schedue" << paraTorrentIndex;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API, arg, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QStringList configTagNames(QStringList()
        << "name" << "f_type" << "st_year" << "st_mon" << "st_day"
        << "st_hours" << "st_min" << "stop_time" << "result");

    if( configTagNames.size() == apiOut.size() ) {
        if(apiOut.value(1) == "none") {
            QStringList configTagNamesNone(QStringList()
                << "name" << "f_type" << "start_time" << "stop_time" << "result");
            QStringList configContents(QStringList()
                << apiOut.value(0) << apiOut.value(1) << apiOut.value(2) << apiOut.value(3) << apiOut.value(8));

            for(int i = 0; i < configContents.size(); i++) {
                QDomElement element = doc.createElement(configTagNamesNone.value(i));
                root.appendChild(element);
                element.appendChild(doc.createTextNode(configContents.value(i)));
            }
        }
        else {
            for(int i = 0; i < apiOut.size(); i++) {
                QDomElement element = doc.createElement(configTagNames.value(i));
                root.appendChild(element);
                element.appendChild(doc.createTextNode(apiOut.value(i)));
            }
        }
    }
    else {
        //assert(0);
        tError("RenderResponseSysStatus::generateP2pGetTorrentScheduling(): "
               "configTagNames size is not equal to apiOut size.");
    }

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pTorrentSchedulingSet() {

    QDomDocument doc;

    QString paraTorrentIndex = m_pReq->parameter("f_torrent_index");
    QString paraStartTime = m_pReq->parameter("f_start_time");
    QString paraStopTime = m_pReq->parameter("f_stop_time");
    QString paraType = m_pReq->parameter("f_type");

//    QString date = QDate::currentDate().toString("yyyyMMdd");
//    QString isDialy = paraType == "daily" ? "1" : "0";
//    QString scheduleFormat("%1%2%3");
//    QString schedule = scheduleFormat.arg(isDialy, date, paraStartTime);
//    if(!paraStopTime.isEmpty())
//        schedule += date + paraStopTime;

//    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_P2P_API +
//                 " --set-schedule 1 " + paraTorrentIndex + " " + schedule, true);

    QStringList arg = QStringList() << "service_set_p2p_torrent_schedule" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pDetailTorrent() {
    QStringList arg = QStringList() << "service_get_p2p_Detail_info" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QVariantMap listMap;
    listMap.insert("name", apiOut.value(0));
    listMap.insert("detail", apiOut.value(1));
    listMap.insert("result", apiOut.value(2));

    m_var = QJsonDocument::fromVariant(listMap);
}

void RenderResponseP2pDownloads::generateP2pPrioritySet() {

    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_p2p_torrent_priority " +
                                      allParametersToString(), true, ";");


    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pDelTorrent() {

    QDomDocument doc;

//    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_P2P_API + " --remove " +
//                                      m_pReq->parameter("f_torrent_url"), true);

    QStringList arg = QStringList() << "service_set_p2p_torrent_remove" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pGetTorrentInfo() {

    QDomDocument doc;

    QStringList arg = QStringList() << "service_get_p2p_torrent_info";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement numElement = doc.createElement("downloading_num");
    root.appendChild(numElement);
    numElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(apiOut.value(1)));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pStartTorrent() {

    QDomDocument doc;

    QStringList arg = QStringList() << "service_set_p2p_torrent_start" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pPauseTorrent() {

    QDomDocument doc;

    QStringList arg = QStringList() << "service_set_p2p_torrent_pause" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseP2pDownloads::generateP2pGetSettingInfo() {
    QDomDocument doc;
    QStringList arg = QStringList() << "service_get_p2p_setting_info";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QDomElement root = doc.createElement("config");
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

/*
 * [p2p enable][HD_a2];[HD_b2];[selected_hdd]
//device not found
1;;;

//device found
// two hdd and select Volume_1
0;Volume_1;Volume_2;Volume_1

// one hdd and select Volume_1
0;Volume_1;;Volume_1
*/
void RenderResponseP2pDownloads::generateP2pGetHd() {

    QStringList arg = QStringList() << "service_get_p2p_save_device";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");
    QStringList shareInfo = getAPIFileOut(SHARE_INFO_FILE);

    QStringList apiOutShared = apiOut.mid(1, 2);

    QString selectClass = "<select size=\"1\" name=\"f_hdd_list\"%1>\n"
                          "%2"
                          "</select>";
    QString optionClass =  "    <option value=\"%1\"%2>%3</option>\n";
    QString opt;

    for(int i = 0; i<apiOutShared.size(); i++) {
        if(apiOutShared.value(i).isEmpty())
            continue;

        QString folderName;
        for(QString e : shareInfo) {
            if(e.contains(apiOutShared.value(i))) {
                folderName = e.right(e.length() - (e.lastIndexOf("/") + 1));
                break;
            }
        }
        if(folderName.isEmpty())
            continue;

        QString select;
        if(apiOut.value(3) == apiOutShared.value(i))
            select = " selected";
        opt += optionClass.arg(folderName, select, apiOutShared.value(i));
    }

    QString disableValue = apiOut.value(0).compare("1") == 0 ? " disabled" : "";
    m_var = selectClass.arg(disableValue, opt);

}

void RenderResponseP2pDownloads::generateP2pSetConfig() {

    QStringList arg = QStringList() << "service_set_p2p_setting" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);
    m_var = "<script>location.href='/web/download_mgr/p2p_set.html?id=8401878'</script>";

}

