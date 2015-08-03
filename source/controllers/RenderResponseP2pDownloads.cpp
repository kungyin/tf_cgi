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
    case CMD_P2P_GET_LIST_BY_PRIORITY:
        generateP2pGetListByPriority();
        break;

    case CMD_NONE:
    default:
        break;
    }

}

/* todo */
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

