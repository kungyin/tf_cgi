#include "RenderResponseAppMngm.h"
#include "AppDefine.h"

RenderResponseAppMngm::RenderResponseAppMngm(QVariantMap &map, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_renderType = RENDER_TYPE_UNKNOWN;
    m_pMap = &map;
}

RenderResponseAppMngm::~RenderResponseAppMngm() {
}

RENDER_TYPE RenderResponseAppMngm::preRender() {

    if(!m_pMap)
        return RENDER_TYPE_UNKNOWN;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_SET_AFP:
        generateSetAfp();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_NFS_ENABLE:
        generateNfsEnable(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_CHK_DB:
        generateCheckDb();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_UPNP_AV_SERVER_PATH_LIST:
        generateUpnpAvServerPathList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_UPNP_AV_SERVER_GET_CONFIG:
        generateUpnpAvServerGetConfig(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_UPNP_AV_SERVER:
        generateUpnpAvServer(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_UPNP_AV_SERVER_GET_SQLDB_STATE:
        generateUpnpAvServerGetSqldbState(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GUI_CODEPAGE_GET_LIST:
        generateGuiCodepageGetList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_ITUNES_SERVER_GET_XML:
        generateItunesServerGetXml(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_ITUNES_SERVER_READY:
        generateItunesServerReady(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_AV_SERVER_CHECK_PATH:
        generateUpnpAvServerCheckPath(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_AV_SERVER_PATH_SETTING:
        generateUpnpAvServerPathSetting(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SQLDB_STOP_FINISH:
        generateSqldbStopFinish(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_UPNP_AV_SERVER_PRESCAN:
        generateUpnpAvServerPrescan(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_UPNP_AV_SERVER_PATH_DEL:
        generateUpnpAvServerPathDel(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_UPNP_AV_SERVER_SETTING:
        generateUpnpAvServerSetting();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_GUI_CODEPAGE_ADD:
        generateGuiCodepageAdd(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_ITUNES_SERVER_SETTING:
        generateItunesServerSetting(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_ITUNES_SERVER_CHECK_PS:
        generateItunesServerCheckPs(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_ITUNES_SERVER_REFRESH:
        generateItunesServerRefresh(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_ITUNES_SERVER_REFRESH_STATE:
        generateItunesServerRefreshState(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

    return m_renderType;
}

void RenderResponseAppMngm::generateSetAfp() {
    QString paraAfp = m_pMap->value("afp").toString();
    if(setNasCfg("afp", "enable", paraAfp))
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_AFP_API, true);
}

void RenderResponseAppMngm::generateNfsEnable(QDomDocument &doc) {
    QString paraNfsStatus = m_pMap->value("nfs_status").toString();
    QStringList apiOut;
    if(setNasCfg("nfs", "enable", paraNfsStatus))
        apiOut = getAPIStdOut(API_PATH + SCRIPT_NFS_API, true);

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.isEmpty() ? "0" : apiOut.value(0)));
}

/* todo */
void RenderResponseAppMngm::generateCheckDb() {
//    if(setNasCfg("nfs", "enable", paraNfsStatus))
//        apiOut = getAPIStdOut(API_PATH + SCRIPT_NFS_API, true);
}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerPathList(QDomDocument &doc) {
    QString paraPage = m_pMap->value("page").toString();
    QString paraRp = m_pMap->value("rp").toString();
    QString paraQuery = m_pMap->value("query").toString();
    QString paraQType = m_pMap->value("qtype").toString();
    QString paraField = m_pMap->value("f_field").toString();
    QString paraUser = m_pMap->value("user").toString();

//    QStringList apiOut;
//    if(setNasCfg("nfs", "enable", paraNfsStatus))
//        apiOut = getAPIStdOut(API_PATH + SCRIPT_NFS_API, true);

    QString cellcontent3 = "&lt;a href=javascript:upnp_path_refresh_one(&apos;%1');>&lt;IMG border=&apos;0&apos; \
                            src=&apos;/web/images/refresh_over.png&apos;&gt;&lt;/a&gt;";
    QString cellcontent4 = "&lt;IMG border=&apos;0&apos; src=&apos;/web/images/on.png&apos;&gt;";
    //for(int i=0; i < apiOut.size(); i++) {
//        if(apiOut.at(i).isEmpty())
//            continue;
//        if(apiOut.at(i).split(",").size() < 2)
//            continue;

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);
    QDomElement rowElement = doc.createElement("row");
    root.appendChild(rowElement);

    QDomElement cellElement1 = doc.createElement("cell");
    rowElement.appendChild(cellElement1);
    cellElement1.appendChild(doc.createTextNode("1"));

    QDomElement cellElement2 = doc.createElement("cell");
    rowElement.appendChild(cellElement2);
    cellElement2.appendChild(doc.createTextNode("Volume_1"));

    QDomElement cellElement3 = doc.createElement("cell");
    rowElement.appendChild(cellElement3);
    cellElement3.appendChild(doc.createTextNode(cellcontent3.arg("1")));

    QDomElement cellElement4 = doc.createElement("cell");
    rowElement.appendChild(cellElement4);
    cellElement4.appendChild(doc.createTextNode(cellcontent4));

    QDomElement cellElement5 = doc.createElement("cell");
    rowElement.appendChild(cellElement5);
    cellElement5.appendChild(doc.createTextNode("/mnt/HD/HD_a2/dddd"));

    rowElement.setAttribute("id", "1");

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("3"));

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerGetConfig(QDomDocument &doc) {

//    QStringList apiOut;
//    if(setNasCfg("nfs", "enable", paraNfsStatus))
//        apiOut = getAPIStdOut(API_PATH + SCRIPT_NFS_API, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode("0"));

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServer(QDomDocument &doc) {

//    QStringList apiOut;
//    if(setNasCfg("nfs", "enable", paraNfsStatus))
//        apiOut = getAPIStdOut(API_PATH + SCRIPT_NFS_API, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("0"));
}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerGetSqldbState(QDomDocument &doc) {

//    QStringList apiOut;
//    if(setNasCfg("nfs", "enable", paraNfsStatus))
//        apiOut = getAPIStdOut(API_PATH + SCRIPT_NFS_API, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement dbStateElement = doc.createElement("db_state");
    root.appendChild(dbStateElement);
    dbStateElement.appendChild(doc.createTextNode("26"));
    QDomElement dbFileElement = doc.createElement("db_file");
    root.appendChild(dbFileElement);
    dbFileElement.appendChild(doc.createTextNode("/mnt/HD/HD_a2/web/jquery/css/redmond/images/SM_ui-icons_454545_256x240.png.jpg"));
}

void RenderResponseAppMngm::generateGuiCodepageGetList(QDomDocument &doc) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

    for (auto e : apiOut) {
        QDomElement itemElement = doc.createElement("item");
        root.appendChild(itemElement);

        QDomElement langElement = doc.createElement("lang");
        itemElement.appendChild(langElement);
        langElement.appendChild(doc.createTextNode(e.split(",").value(0)));

        QDomElement descElement = doc.createElement("desc");
        itemElement.appendChild(descElement);
        descElement.appendChild(doc.createTextNode(e.split(",").value(1)));
    }

}

/* todo */
void RenderResponseAppMngm::generateItunesServerGetXml(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode("0"));
    QDomElement ipElement = doc.createElement("ip");
    root.appendChild(ipElement);
    ipElement.appendChild(doc.createTextNode("192.168.100.85"));
    QDomElement rootElement = doc.createElement("root");
    root.appendChild(rootElement);
    rootElement.appendChild(doc.createTextNode("1"));
    QDomElement folderElement = doc.createElement("folder");
    root.appendChild(folderElement);
    folderElement.appendChild(doc.createTextNode("DNS-340L_SHARE"));
    QDomElement passwdElement = doc.createElement("passwd");
    root.appendChild(passwdElement);
    passwdElement.appendChild(doc.createTextNode(""));
    QDomElement langElement = doc.createElement("lang");
    root.appendChild(langElement);
    langElement.appendChild(doc.createTextNode("ISO-8859-1"));
    QDomElement rescanIntervalElement = doc.createElement("rescan_interval");
    root.appendChild(rescanIntervalElement);
    rescanIntervalElement.appendChild(doc.createTextNode("0"));
}

/* todo */
void RenderResponseAppMngm::generateItunesServerReady(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode("1"));
    QDomElement mp3FinishElement = doc.createElement("mp3_finish");
    root.appendChild(mp3FinishElement);
    mp3FinishElement.appendChild(doc.createTextNode("1"));
    QDomElement itunesReadyElement = doc.createElement("itunes_ready");
    root.appendChild(itunesReadyElement);
    itunesReadyElement.appendChild(doc.createTextNode("1"));
    QDomElement stateElement = doc.createElement("state");
    root.appendChild(stateElement);
    stateElement.appendChild(doc.createTextNode("1"));

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerCheckPath(QDomDocument &doc) {

    QString paraDir = m_pMap->value("f_dir").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement itemElement = doc.createElement("item");
    root.appendChild(itemElement);

    QDomElement resElement = doc.createElement("res");
    itemElement.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
    QDomElement pathElement = doc.createElement("path");
    itemElement.appendChild(pathElement);
    pathElement.appendChild(doc.createTextNode("Volume_1/dddd"));

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerPathSetting(QDomDocument &doc) {

    QString paraDir = m_pMap->value("f_dir").toString();
    QString paraRefresh = m_pMap->value("f_refresh").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

}

/* todo */
void RenderResponseAppMngm::generateSqldbStopFinish(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("0"));

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerPrescan(QDomDocument &doc) {

    QString paraDir = m_pMap->value("f_dir").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerPathDel(QDomDocument &doc) {

    QString paraDir = m_pMap->value("f_dir").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement itemElement = doc.createElement("item");
    root.appendChild(itemElement);

    QDomElement resElement = doc.createElement("res");
    itemElement.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
    QDomElement pathElement = doc.createElement("path");
    itemElement.appendChild(pathElement);
    pathElement.appendChild(doc.createTextNode("Volume_1/dddd"));

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerSetting() {

    QString paraUpnpAvServer = m_pMap->value("f_UPNPAVServer").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

}

/* todo */
void RenderResponseAppMngm::generateGuiCodepageAdd(QDomDocument &doc) {

    QString paraLang = m_pMap->value("f_lang").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

}

/* todo */
void RenderResponseAppMngm::generateItunesServerSetting(QDomDocument &doc) {

    QString paraItunesServer = m_pMap->value("f_iTunesServer").toString();
    QString paraRoot = m_pMap->value("f_root").toString();
    QString paraDir = m_pMap->value("f_dir").toString();
    QString paraPasswd = m_pMap->value("f_passwd").toString();
    QString paraLang = m_pMap->value("f_lang").toString();
    QString paraRescanInterval = m_pMap->value("f_rescan_interval").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("3"));
    QDomElement stateElement = doc.createElement("state");
    root.appendChild(stateElement);
    stateElement.appendChild(doc.createTextNode("1"));

}

/* todo */
void RenderResponseAppMngm::generateItunesServerCheckPs(QDomDocument &doc) {

    QString paraType = m_pMap->value("f_type").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
    QDomElement typeElement = doc.createElement("type");
    root.appendChild(typeElement);
    typeElement.appendChild(doc.createTextNode("3"));

}

/* todo */
void RenderResponseAppMngm::generateItunesServerRefresh(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

}

/* todo */
void RenderResponseAppMngm::generateItunesServerRefreshState(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement stateElement = doc.createElement("state");
    root.appendChild(stateElement);
    stateElement.appendChild(doc.createTextNode("1"));
    QDomElement barElement = doc.createElement("bar");
    root.appendChild(barElement);
    barElement.appendChild(doc.createTextNode("100"));
    QDomElement mp3CounterElement = doc.createElement("mp3_counter");
    root.appendChild(mp3CounterElement);
    mp3CounterElement.appendChild(doc.createTextNode("0"));
    QDomElement totalMp3Element = doc.createElement("total_mp3");
    root.appendChild(totalMp3Element);
    totalMp3Element.appendChild(doc.createTextNode("0"));
    QDomElement mp3FinishElement = doc.createElement("mp3_finish");
    root.appendChild(mp3FinishElement);
    mp3FinishElement.appendChild(doc.createTextNode("1"));

}
