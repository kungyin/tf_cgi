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
    case CMD_NONE:
    default:
        break;
    }

}

/* todo: need API */
void RenderResponseP2pDownloads::generateP2pState() {

    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement p2pElement = doc.createElement("p2p");
    root.appendChild(p2pElement);
    p2pElement.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

/* todo: need API */
void RenderResponseP2pDownloads::generateP2pGetListByPriority() {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_status", true, ";");

    QVariantMap listMap;
    listMap.insert("total", 2);
    listMap.insert("page", 1);

    QVariantList itemMapList;
    QVariantMap itemMap;
    itemMap.insert("id", 1);
    QVariantList torrent1;
    torrent1 <<
        "<span id='id_0' title='ubuntu-12.04.5-alternate-amd64.iso' alt='ubuntu-12.04.5-alternate-amd64.iso'>ubuntu-12.04.5-alternate-amd64.iso</span>" <<
        "1" <<
        "<IMG border='0' src='/web/images/icon-show-complete.gif'>" <<
        "761.0MB" <<
        "<span class='progressBar' id='progressbar_row1'>100.0</span>" <<
        "<img border='0' src='/web/images/status_upload.png'>" <<
        "0.0 Kbps / 0.0 Kbps" <<
        "<a href=javascript:stop('0')><IMG border='0' src='/web/images/stop.png'></a>" <<
        "0";

    itemMap.insert("cell", torrent1);
    itemMapList.append(itemMap);
    listMap.insert("rows", itemMapList);

    m_var = QJsonDocument::fromVariant(listMap);
}

/* todo: need API */
void RenderResponseP2pDownloads::generateP2pAddTorrentUrl() {

    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
    QDomElement keyNumberElement = doc.createElement("key_number");
    root.appendChild(keyNumberElement);
    keyNumberElement.appendChild(doc.createTextNode("1436477502"));

    m_var = doc.toString();

}

/* todo: need API */
void RenderResponseP2pDownloads::generateP2pGetUrlState() {

    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("0"));

    m_var = doc.toString();

}

/* todo: need API */
void RenderResponseP2pDownloads::generateP2pCurrentSesState() {

    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement p2pElement = doc.createElement("p2p");
    root.appendChild(p2pElement);
    p2pElement.appendChild(doc.createTextNode("0"));

    m_var = doc.toString();

}

/* todo: need API */
void RenderResponseP2pDownloads::generateP2pAddTorrentFileNew() {

    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("0"));

    m_var = doc.toString();

}

/* todo: need API */
void RenderResponseP2pDownloads::generateP2pDelAllCompleted() {

    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

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

/* todo: need API */
void RenderResponseP2pDownloads::generateP2pDetailTorrent() {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_status", true, ";");

    QVariantMap listMap;
    listMap.insert("name", "ubuntu-12.04.5-desktop-i386.iso");
    listMap.insert("detail", "ubuntu-12.04.5-desktop-i386.iso");
    listMap.insert("result", "1");

    m_var = QJsonDocument::fromVariant(listMap);
}

/* todo: need API */
void RenderResponseP2pDownloads::generateP2pPrioritySet() {

    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

/* todo: need API */
void RenderResponseP2pDownloads::generateP2pDelTorrent() {

    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_USER_API + " -s user_add", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}
