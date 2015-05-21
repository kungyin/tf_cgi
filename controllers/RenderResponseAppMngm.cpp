#include "RenderResponseAppMngm.h"

RenderResponseAppMngm::RenderResponseAppMngm(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_renderType = RENDER_TYPE_UNKNOWN;
    m_pReq = &req;
}

RenderResponseAppMngm::~RenderResponseAppMngm() {
}

RENDER_TYPE RenderResponseAppMngm::preRender() {

    if(!m_pReq)
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
    case CMD_SYSLOG_SEARCH:
        generateSyslogSearch(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_VOLUME_INFO:
        generateGetVolumeInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SYSLOG_GET_LOG_FILE_OPTION:
        generateSyslogGetLogFileOption(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SYSLOG_GET_CONFIG:
        generateSyslogGetConfig(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SYSLOG_GET_SELECT_OPTION:
        generateSyslogGetSelectOption(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SYSLOG_SET_CONFIG:
        generateSyslogSetConfig(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_SYSLOG_EXPORT:
        generateSyslogExport();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_SYSLOG_GET_EXPORT_STATUS:
        generateSyslogGetExportStatus(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SYSLOG_CLEAR:
        generateSyslogClear();
        m_renderType = RENDER_TYPE_NULL;
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
    QString paraAfp = m_pReq->allParameters().value("afp").toString();
    if(setNasCfg("afp", "enable", paraAfp))
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_AFP_API, true);
}

void RenderResponseAppMngm::generateNfsEnable(QDomDocument &doc) {
    QString paraNfsStatus = m_pReq->allParameters().value("nfs_status").toString();
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
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

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

    QString paraDir = m_pReq->allParameters().value("f_dir").toString();
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

    QString paraDir = m_pReq->allParameters().value("f_dir").toString();
    QString paraRefresh = m_pReq->allParameters().value("f_refresh").toString();
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

    QString paraDir = m_pReq->allParameters().value("f_dir").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerPathDel(QDomDocument &doc) {

    QString paraDir = m_pReq->allParameters().value("f_dir").toString();
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

    QString paraUpnpAvServer = m_pReq->allParameters().value("f_UPNPAVServer").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

}

/* todo */
void RenderResponseAppMngm::generateGuiCodepageAdd(QDomDocument &doc) {

    QString paraLang = m_pReq->allParameters().value("f_lang").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

}

/* todo */
void RenderResponseAppMngm::generateItunesServerSetting(QDomDocument &doc) {

    QString paraItunesServer = m_pReq->allParameters().value("f_iTunesServer").toString();
    QString paraRoot = m_pReq->allParameters().value("f_root").toString();
    QString paraDir = m_pReq->allParameters().value("f_dir").toString();
    QString paraPasswd = m_pReq->allParameters().value("f_passwd").toString();
    QString paraLang = m_pReq->allParameters().value("f_lang").toString();
    QString paraRescanInterval = m_pReq->allParameters().value("f_rescan_interval").toString();

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

    QString paraType = m_pReq->allParameters().value("f_type").toString();

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

/* todo */
void RenderResponseAppMngm::generateSyslogSearch(QDomDocument &doc) {

    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraSortname = m_pReq->allParameters().value("sortname").toString();
    QString paraSortorder = m_pReq->allParameters().value("sortorder").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();
    QString paraLogFile = m_pReq->allParameters().value("log_file").toString();
    QString paraDateFrom = m_pReq->allParameters().value("f_date_from").toString();
    QString paraDateTo = m_pReq->allParameters().value("f_date_to").toString();
    QString paraViewSeverity = m_pReq->allParameters().value("f_view_severity").toString();
    QString paraLogHost = m_pReq->allParameters().value("log_host").toString();
    QString paraLogFacility = m_pReq->allParameters().value("log_facility").toString();
    QString paraLogApplication = m_pReq->allParameters().value("log_application").toString();
    QString paraKeyword = m_pReq->allParameters().value("keyword").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QString cellContent1 = "&amp;nbsp;[origin&amp;nbsp;software=&quot;rsyslogd&quot;&amp;nbsp;swVersion=\
            &quot;5.8.6&quot;&amp;nbsp;x-pid=&quot;%1&quot;&amp;nbsp;x-info=&quot;\
            http://www.rsyslog.com&quot;]&amp;nbsp;start";
    QString cellContent2 = "&amp;nbsp;[origin&amp;nbsp;software=&quot;rsyslogd&quot;&amp;nbsp;swVersion=\
            &quot;5.8.6&quot;&amp;nbsp;x-pid=&quot;%1&quot;&amp;nbsp;x-info=&quot;\
            http://www.rsyslog.com&quot;]&amp;nbsp;exiting&amp;nbsp;on&amp;nbsp;signal&amp;nbsp;15.";

    //for(int i=0; i < apiOut.size(); i++) {
//        if(apiOut.at(i).isEmpty())
//            continue;
//        if(apiOut.at(i).split(",").size() < 2)
//            continue;

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode("2015-05-11"));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode("23:18:29"));

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode("6"));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createTextNode("dlink-8B21F7dd"));
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createTextNode("5"));

        QDomElement cellElement6 = doc.createElement("cell");
        rowElement.appendChild(cellElement6);
        cellElement6.appendChild(doc.createTextNode("rsyslogd"));
        QDomElement cellElement7 = doc.createElement("cell");
        rowElement.appendChild(cellElement7);
        cellElement7.appendChild(doc.createTextNode(cellContent1.arg("18799")));

        rowElement.setAttribute("id", "1");
    //}

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("15"));
}

/* todo */
void RenderResponseAppMngm::generateGetVolumeInfo(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    //for(int i=0; i < apiOut.size(); i++) {
//        if(apiOut.at(i).isEmpty())
//            continue;
//        if(apiOut.at(i).split(",").size() < 2)
//            continue;

        QDomElement itemElement = doc.createElement("item");
        root.appendChild(itemElement);
        QDomElement optValueElement = doc.createElement("opt_value");
        itemElement.appendChild(optValueElement);
        optValueElement.appendChild(doc.createTextNode("Volume_1"));
        QDomElement guiValueElement = doc.createElement("gui_value");
        itemElement.appendChild(guiValueElement);
        guiValueElement.appendChild(doc.createTextNode("Volume_1"));

    //}

}

/* todo */
void RenderResponseAppMngm::generateSyslogGetLogFileOption(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("row");
    doc.appendChild(root);

}

/* todo */
void RenderResponseAppMngm::generateSyslogGetConfig(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement syslogEnableElement = doc.createElement("syslog_enable");
    root.appendChild(syslogEnableElement);
    syslogEnableElement.appendChild(doc.createTextNode(""));
    QDomElement syslogFolderElement = doc.createElement("syslog_folder");
    root.appendChild(syslogFolderElement);
    syslogFolderElement.appendChild(doc.createTextNode("Volume_1"));
    QDomElement syslogUdpElement = doc.createElement("syslog_udp");
    root.appendChild(syslogUdpElement);
    syslogUdpElement.appendChild(doc.createTextNode("514"));

    QDomElement archiveSizeEnElement = doc.createElement("archive_size_en");
    root.appendChild(archiveSizeEnElement);
    archiveSizeEnElement.appendChild(doc.createTextNode(""));
    QDomElement archiveSizeElement = doc.createElement("archive_size");
    root.appendChild(archiveSizeElement);
    archiveSizeElement.appendChild(doc.createTextNode(""));

    QDomElement archiveNumEnElement = doc.createElement("archive_num_en");
    root.appendChild(archiveNumEnElement);
    archiveNumEnElement.appendChild(doc.createTextNode(""));
    QDomElement archiveNumElement = doc.createElement("archive_num");
    root.appendChild(archiveNumElement);
    archiveNumElement.appendChild(doc.createTextNode(""));

    QDomElement archiveCycleEnElement = doc.createElement("archive_cycle_en");
    root.appendChild(archiveCycleEnElement);
    archiveCycleEnElement.appendChild(doc.createTextNode(""));
    QDomElement archiveCycleElement = doc.createElement("archive_cycle");
    root.appendChild(archiveCycleElement);
    archiveCycleElement.appendChild(doc.createTextNode(""));

    QDomElement folderQuotaSizeElement = doc.createElement("folder_quota_size");
    root.appendChild(folderQuotaSizeElement);
    folderQuotaSizeElement.appendChild(doc.createTextNode("50"));

    QDomElement emailEnableElement = doc.createElement("email_enable");
    root.appendChild(emailEnableElement);
    emailEnableElement.appendChild(doc.createTextNode(""));
    QDomElement emailSeverityElement = doc.createElement("email_severity");
    root.appendChild(emailSeverityElement);
    emailSeverityElement.appendChild(doc.createTextNode(""));
    QDomElement sendMailElement = doc.createElement("send_mail");
    root.appendChild(sendMailElement);
    sendMailElement.appendChild(doc.createTextNode("0"));

    QDomElement syslogStatusElement = doc.createElement("syslog_status");
    root.appendChild(syslogStatusElement);
    syslogStatusElement.appendChild(doc.createTextNode(""));
    QDomElement archiveStatusElement = doc.createElement("archive_status");
    root.appendChild(archiveStatusElement);
    archiveStatusElement.appendChild(doc.createTextNode(""));
}

/* todo */
void RenderResponseAppMngm::generateSyslogGetSelectOption(QDomDocument &doc) {

    QString paraDatabase = m_pReq->allParameters().value("f_database").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement severityElement = doc.createElement("severity");
    root.appendChild(severityElement);
    QDomElement severityCellElement = doc.createElement("cell");
    severityElement.appendChild(severityCellElement);
    severityCellElement.appendChild(doc.createTextNode("6"));

    QDomElement hostElement = doc.createElement("host");
    root.appendChild(hostElement);
    QDomElement hostCellElement = doc.createElement("cell");
    hostElement.appendChild(hostCellElement);
    hostCellElement.appendChild(doc.createTextNode("dlink-8B21F7dd"));

    QDomElement facilityElement = doc.createElement("facility");
    root.appendChild(facilityElement);
    QDomElement facilityCellElement = doc.createElement("cell");
    facilityElement.appendChild(facilityCellElement);
    facilityCellElement.appendChild(doc.createTextNode("5"));

    QDomElement applicationElement = doc.createElement("application");
    root.appendChild(applicationElement);
    QDomElement applicationCellElement = doc.createElement("cell");
    applicationElement.appendChild(applicationCellElement);
    applicationCellElement.appendChild(doc.createTextNode("rsyslogd"));
}

/* todo */
void RenderResponseAppMngm::generateSyslogSetConfig(QString &str) {

    QString paraSyslogEnable = m_pReq->allParameters().value("f_syslog_enable").toString();
    QString paraSyslogFolder = m_pReq->allParameters().value("f_syslog_folder").toString();
    QString paraSyslogUdp = m_pReq->allParameters().value("f_syslog_udp").toString();
    QString paraArchiveSizeEn = m_pReq->allParameters().value("f_archive_size_en").toString();
    QString paraArchiveSize = m_pReq->allParameters().value("f_archive_size").toString();
    QString paraArchiveNumEn = m_pReq->allParameters().value("f_archive_num_en").toString();
    QString paraArchiveCycleEn = m_pReq->allParameters().value("f_archive_cycle_en").toString();
    QString paraArchiveCycle = m_pReq->allParameters().value("f_archive_cycle").toString();
    QString paraFolderQuotaSize = m_pReq->allParameters().value("f_folder_quota_size").toString();
    QString paraEmailSeverity = m_pReq->allParameters().value("f_email_severity").toString();
    QString paraEmailEnable = m_pReq->allParameters().value("f_email_enable").toString();
    QString paraIsSendmail = m_pReq->allParameters().value("is_sendmail").toString();
    QString paraNewLogFolder = m_pReq->allParameters().value("f_new_log_folder").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    str = "<script>location.href='/web/app_mgr/log_server.html?id=8401878'</script>";

}

/* todo */
void RenderResponseAppMngm::generateSyslogExport() {

    QString paraLogFile = m_pReq->allParameters().value("log_file").toString();
    QString paraDateFrom = m_pReq->allParameters().value("f_date_from").toString();
    QString paraDateTo = m_pReq->allParameters().value("f_date_to").toString();
    QString paraViewSeverity = m_pReq->allParameters().value("f_view_severity").toString();
    QString paraLogHost = m_pReq->allParameters().value("log_host").toString();
    QString paraLogFacility = m_pReq->allParameters().value("log_facility").toString();
    QString paraLogApplication = m_pReq->allParameters().value("log_application").toString();
    QString paraKeyword = m_pReq->allParameters().value("keyword").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

}

/* todo */
void RenderResponseAppMngm::generateSyslogGetExportStatus(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode("1"));

}

/* todo */
void RenderResponseAppMngm::generateSyslogClear() {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

}
