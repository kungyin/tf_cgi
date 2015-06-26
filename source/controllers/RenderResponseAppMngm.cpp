#include "RenderResponseAppMngm.h"
#include "http_ftp_download.h"

#include <QDateTime>


RenderResponseAppMngm::RenderResponseAppMngm(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseAppMngm::~RenderResponseAppMngm() {
}

void RenderResponseAppMngm::preRender() {

    if(!m_pReq)
        return;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_SET_AFP:
        generateSetAfp();
        break;
    case CMD_NFS_ENABLE:
        generateNfsEnable(doc);
        break;
    case CMD_CHK_DB:
        generateCheckDb();
        break;
    case CMD_UPNP_AV_SERVER_PATH_LIST:
        generateUpnpAvServerPathList(doc);
        break;
    case CMD_UPNP_AV_SERVER_GET_CONFIG:
        generateUpnpAvServerGetConfig(doc);
        break;
    case CMD_UPNP_AV_SERVER:
        generateUpnpAvServer(doc);
        break;
    case CMD_UPNP_AV_SERVER_GET_SQLDB_STATE:
        generateUpnpAvServerGetSqldbState(doc);
        break;
    case CMD_GUI_CODEPAGE_GET_LIST:
        generateGuiCodepageGetList(doc);
        break;
    case CMD_ITUNES_SERVER_GET_XML:
        generateItunesServerGetXml(doc);
        break;
    case CMD_ITUNES_SERVER_READY:
        generateItunesServerReady(doc);
        break;
    case CMD_AV_SERVER_CHECK_PATH:
        generateUpnpAvServerCheckPath(doc);
        break;
    case CMD_AV_SERVER_PATH_SETTING:
        generateUpnpAvServerPathSetting(doc);
        break;
    case CMD_SQLDB_STOP_FINISH:
        generateSqldbStopFinish(doc);
        break;
    case CMD_UPNP_AV_SERVER_PRESCAN:
        generateUpnpAvServerPrescan(doc);
        break;
    case CMD_UPNP_AV_SERVER_PATH_DEL:
        generateUpnpAvServerPathDel(doc);
        break;
    case CMD_UPNP_AV_SERVER_SETTING:
        generateUpnpAvServerSetting();
        break;
    case CMD_GUI_CODEPAGE_ADD:
        generateGuiCodepageAdd(doc);
        break;
    case CMD_ITUNES_SERVER_SETTING:
        generateItunesServerSetting(doc);
        break;
    case CMD_ITUNES_SERVER_CHECK_PS:
        generateItunesServerCheckPs(doc);
        break;
    case CMD_ITUNES_SERVER_REFRESH:
        generateItunesServerRefresh(doc);
        break;
    case CMD_ITUNES_SERVER_REFRESH_STATE:
        generateItunesServerRefreshState(doc);
        break;
    case CMD_SYSLOG_SEARCH:
        generateSyslogSearch(doc);
        break;
    case CMD_GET_VOLUME_INFO:
        generateGetVolumeInfo(doc);
        break;
    case CMD_SYSLOG_GET_LOG_FILE_OPTION:
        generateSyslogGetLogFileOption(doc);
        break;
    case CMD_SYSLOG_GET_CONFIG:
        generateSyslogGetConfig(doc);
        break;
    case CMD_SYSLOG_GET_SELECT_OPTION:
        generateSyslogGetSelectOption(doc);
        break;
    case CMD_SYSLOG_SET_CONFIG:
        generateSyslogSetConfig(str);
        break;
    case CMD_SYSLOG_EXPORT:
        generateSyslogExport();
        break;
    case CMD_SYSLOG_GET_EXPORT_STATUS:
        generateSyslogGetExportStatus(doc);
        break;
    case CMD_SYSLOG_CLEAR:
        generateSyslogClear();
        break;

    case CMD_LOCAL_BACKUP_NOW:
        generateLocalBackupNow(doc);
        break;
    case CMD_LOCAL_BACKUP_LIST:
        generateLocalBackupList(doc);
        break;
    case CMD_LOCAL_BACKUP_SAMBA_FORMAT:
        generateLocalBackupSambaFormat(doc);
        break;
    case CMD_LOCAL_BACKUP_ADD:
        generateLocalBackupAdd(str);
        break;
    case CMD_LOCAL_BACKUP_INFO:
        generateLocalBackupInfo(doc);
        break;
    case CMD_LOCAL_BACKUP_RENEW:
        generateLocalBackupRenew(str);
        break;
    case CMD_LOCAL_BACKUP_DEL:
        generateLocalBackupDel(doc);
        break;
    case CMD_LOCAL_BACKUP_TEST:
        generateLocalBackupTest(doc);
        break;

    case CMD_GET_RSYNC_INFO:
        generateGetRsyncInfo(doc);
        break;
    case CMD_SET_RSYNC_SERVER:
        generateSetRsyncServer(str);
        break;

    case CMD_GET_BACKUP_LIST:
        generateGetBackupList(doc);
        break;
    case CMD_GET_ALL_TASK_NAME:
        generateGetAllTaskName(doc);
        break;
    case CMD_SERVER_TEST:
        generateServerTest(doc);
        break;
    case CMD_CHECK_RSYNC_RW:
        generateCheckRsyncRw(doc);
        break;
    case CMD_SET_SCHEDULE:
        generateSetSchedule(str);
        break;
    case CMD_GET_MODIFY_INFO:
        generateGetModifyInfo(doc);
        break;
    case CMD_DEL_SCHEDULE:
        generateDelSchedule(str);
        break;
    case CMD_ENABLE_DISABLE_SCHEDULE:
        generateEnableDisableSchedule(str);
        break;
    case CMD_BACKUP_NOW:
        generateBackupNow(str);
        break;

    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

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

/* todo */
void RenderResponseAppMngm::generateLocalBackupNow(QDomDocument &doc) {

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDateTime curDatetime = QDateTime::currentDateTime();
    QDomElement dateElement = doc.createElement("date");
    root.appendChild(dateElement);
    dateElement.appendChild(doc.createTextNode(curDatetime.toString("MM/dd/yyyy")));

    QDomElement hourElement = doc.createElement("hour");
    root.appendChild(hourElement);
    hourElement.appendChild(doc.createTextNode(curDatetime.toString("hh")));

    QDomElement minsElement = doc.createElement("mins");
    root.appendChild(minsElement);
    minsElement.appendChild(doc.createTextNode(curDatetime.toString("mm")));

}

QString RenderResponseAppMngm::getIcon(QString status) {

    //0=status_queue, 2=status_queue or status_download, 3=status_ok, 4=status_fail, 6=icon_stop

    QString img = "/web/images/%1.png";
    QString ret;
    if(status == "0")
        ret = img.arg("status_queue");
    else if(status == "2")
        ret = img.arg("status_download");
    else if(status == "3")
        ret = img.arg("status_ok");
    else if(status == "4")
        ret = img.arg("status_fail");
    else if(status == "5")
        ret = img.arg("icon_stop");

    return ret;
}


void RenderResponseAppMngm::generateLocalBackupList(QDomDocument &doc) {

    QString strProgressBar = "&lt;span class=&apos;progressBar&apos; id=&apos;progressbar_row%1&apos;&gt;%2&lt;/span&gt;";
    QString strImage = "&lt;IMG src=&apos;%1&apos;&gt;";
    QString strBackupStart = "&lt;a href=javascript:%1_%2(&apos;%3&apos;)&gt;&lt;IMG border\
            =&apos;0&apos; src=&apos;/web/images/%2.png&apos;&gt;&lt;/a&gt;";

    DOWNLOAD_LIST *taskList;
    int total = 0, pageCount = 0;
    int page = m_pReq->parameter("page").toInt();
    int rp = m_pReq->parameter("rp").toInt();
    memset(&taskList, 0, sizeof(DOWNLOAD_LIST*));
    GetListXmlValue(0, page, rp, &total, &pageCount, &taskList);

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    for (int i = 0; i < pageCount; i++)
    {
        UpdateTaskPercent(taskList[i].task_id);
        //printf("DOWNLOAD_LIST[%s %s %s %s %s %s %s]\n",
        //        task_list[i].task_id, task_list[i].src, task_list[i].dest, task_list[i].percent, task_list[i].status, task_list[i].speed, task_list[i].execat, task_list[i].comment);

        QDomElement rowElement1 = doc.createElement("row");
        root.appendChild(rowElement1);
        rowElement1.setAttribute("id", QString::number(i+1));
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement1.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(QString(taskList[i].src)));

        /* todo: Volume_1 is /mnt/HD/HD_a2 ?? */
        QString dest = QString(taskList[i].dest);
        dest.replace("/mnt/HD/HD_a2", "Volume_1");
        dest.replace("/mnt/HD/HD_b2", "Volume_2");

        QDomElement cellElement2 = doc.createElement("cell");
        rowElement1.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode(dest));

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement1.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode(strProgressBar.arg(QString::number(i+1))
                                                    .arg(QString(taskList[i].percent))));

        QDomElement cellElement4 = doc.createElement("cell");
        rowElement1.appendChild(cellElement4);
        cellElement4.appendChild(doc.createTextNode(strImage.arg(getIcon(QString(taskList[i].status)))));

        QDomElement cellElement5 = doc.createElement("cell");
        rowElement1.appendChild(cellElement5);
        cellElement5.appendChild(doc.createTextNode(QString(taskList[i].speed)));

        QDateTime execat = QDateTime::fromString(QString(taskList[i].execat), "yyyyMMddhhmm");
        QDomElement cellElement6 = doc.createElement("cell");
        rowElement1.appendChild(cellElement6);
        cellElement6.appendChild(doc.createTextNode(execat.toString("MM/dd/yy hh:mm")));


        QString arg1;
        if(m_pReq->parameter("cmd").contains("Downloads_Schedule_"))
            arg1 = "downloads";
        else if(m_pReq->parameter("cmd").contains("Local_Backup_"))
            arg1 = "localbackup";

        /* todo: "--" */
        QString arg2 = "start";
        if(QString(taskList[i].percent) == "100")
            arg2 = "stop";
        QDomElement cellElement7 = doc.createElement("cell");
        rowElement1.appendChild(cellElement7);
        cellElement7.appendChild(doc.createTextNode(strBackupStart
                                .arg(arg1).arg(arg2).arg(QString(taskList[i].task_id))));

        QString comment = "-";
        if(!QString(taskList[i].comment).isEmpty()) {
            QString commentStr = "%1 %2";
            QString arg1;
            if(QString(taskList[i].comment).at(0) == '1')
                arg1 = "Fail";
            else if(QString(taskList[i].comment).at(0) == '0')
                arg1 = "Success";
            QString subComment = QString(taskList[i].comment).mid(1);
            QDateTime datetime = QDateTime::fromString(subComment, "yyyyMMddhhmm");
            comment = commentStr.arg(arg1).arg(datetime.toString("MM/dd/yy mm:ss"));
        }
        QDomElement cellElement8 = doc.createElement("cell");
        rowElement1.appendChild(cellElement8);
        cellElement8.appendChild(doc.createTextNode(comment));

        QDomElement cellElement9 = doc.createElement("cell");
        rowElement1.appendChild(cellElement9);
        cellElement9.appendChild(doc.createTextNode(QString(taskList[i].task_id)));

        QDomElement cellElement10 = doc.createElement("cell");
        rowElement1.appendChild(cellElement10);
        cellElement10.appendChild(doc.createTextNode("0"));

        FreeList(&taskList[i]);

    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(m_pReq->parameter("page")));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(total)));

}

/* todo */
void RenderResponseAppMngm::generateLocalBackupSambaFormat(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    //for
    QDomElement itemElement = doc.createElement("item");
    root.appendChild(itemElement);

    QDomElement volElement = doc.createElement("vol");
    itemElement.appendChild(volElement);
    volElement.appendChild(doc.createTextNode("Volume_1"));

}


/* renew: false
   add  : true  */

void RenderResponseAppMngm::renewOrAdd(bool bAdd) {

    QString paraLoginMethod = m_pReq->parameter("f_login_method");
    DOWNLOAD_TASK_INFO taskInfo;

    taskInfo.is_download = 1;
    if(m_pReq->parameter("cmd").contains("Downloads_Schedule_"))
        taskInfo.is_download = 1;
    else if(m_pReq->parameter("cmd").contains("Local_Backup_"))
        taskInfo.is_download = 0;

    taskInfo.is_src_login = paraLoginMethod.toInt() ? 0 : 1;
    taskInfo.is_dst_login = 0;
    taskInfo.is_file = m_pReq->parameter("f_type").toInt() ? 0 : 1;
    taskInfo.execat = m_pReq->parameter("f_at").toLocal8Bit().data();
    taskInfo.login_id = m_pReq->parameter("f_login_user").toLocal8Bit().data();
    taskInfo.src = m_pReq->parameter("f_URL").toLocal8Bit().data();
    taskInfo.src_user = m_pReq->parameter("f_user").toLocal8Bit().data();
    taskInfo.src_pwd = m_pReq->parameter("f_pwd").toLocal8Bit().data();

    /* todo: Volume_1 is /mnt/HD/HD_a2 ?? */
    QString dest = m_pReq->parameter("f_dir");
    dest.replace("Volume_1", "/mnt/HD/HD_a2");
    dest.replace("Volume_2", "/mnt/HD/HD_b2");
    taskInfo.dest = dest.toLocal8Bit().data();

    taskInfo.dst_user = NULL;
    taskInfo.dst_pwd = NULL;

    QMap<QString, int> recurTypeMap;
    recurTypeMap.insert("none", 0);
    recurTypeMap.insert("day", 1);
    recurTypeMap.insert("week", 2);
    recurTypeMap.insert("month", 3);
    taskInfo.recur_type = recurTypeMap.value(m_pReq->parameter("f_period"));
    taskInfo.recur_date = -1;


    if(taskInfo.recur_type == 2)
        taskInfo.recur_date = m_pReq->parameter("f_period_week").toInt();
    else if(taskInfo.recur_type == 3)
        taskInfo.recur_date = m_pReq->parameter("f_period_month").toInt();

    taskInfo.is_inc = 1;
    taskInfo.rename = m_pReq->parameter("f_rename").toLocal8Bit().data();
    taskInfo.charset = m_pReq->parameter("f_lang").toLocal8Bit().data();

    char *taskId = NULL;
    if(!bAdd)
        taskId = m_pReq->parameter("f_idx").toLocal8Bit().data();
    if(SaveTaskXml(taskInfo, &taskId) != RET_SUCCESS)
        tDebug("RenderResponseAppMngm::generateLocalBackupAdd() : failed");

    if(taskId)
        free(taskId);
}


void RenderResponseAppMngm::generateLocalBackupAdd(QString &str) {

    renewOrAdd(true);

    if(m_pReq->parameter("cmd") == QString("Downloads_Schedule_Add"))
        str = "<script>location.href='/web/download_mgr/downloads_setting.html?id=8401878'</script>";
    else if(m_pReq->parameter("cmd") == QString("Local_Backup_Add"))
        str = "<script>location.href='/web/backup_mgr/localbackup_setting.html?id=8401878'</script>";

}

void RenderResponseAppMngm::generateLocalBackupInfo(QDomDocument &doc) {

    QString idx = m_pReq->parameter("f_idx");

    DOWNLOAD_TASK task;
    memset(&task, 0, sizeof(DOWNLOAD_TASK));
    GetTaskXmlValue(idx.toLocal8Bit().data(), TAG_ALL, &task);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement idxElement = doc.createElement("idx");
    root.appendChild(idxElement);
    idxElement.appendChild(doc.createTextNode(idx));

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(QString(task.status)));

    QDomElement periodElement = doc.createElement("period");
    root.appendChild(periodElement);
    periodElement.appendChild(doc.createTextNode(QString(task.period)));

    QDomElement recurDateElement = doc.createElement("recur_date");
    root.appendChild(recurDateElement);
    recurDateElement.appendChild(doc.createTextNode(QString(task.recur_date)));

    QDomElement fileTypeElement = doc.createElement("file_type");
    root.appendChild(fileTypeElement);
    fileTypeElement.appendChild(doc.createTextNode(QString(task.is_file) == "1" ? "0" : "1"));

    QDomElement srcElement = doc.createElement("src");
    root.appendChild(srcElement);
    srcElement.appendChild(doc.createTextNode(QString(task.src)));

    /* todo */
    QString dest = QString(task.src);
    dest.replace("/mnt/HD/HD_a2", "Volume_1");
    dest.replace("/mnt/HD/HD_b2", "Volume_2");
    QDomElement destElement = doc.createElement("dest");
    root.appendChild(destElement);
    destElement.appendChild(doc.createTextNode(dest));

    QDomElement srcUserElement = doc.createElement("src_user");
    root.appendChild(srcUserElement);
    srcUserElement.appendChild(doc.createTextNode(QString(task.src_user)));

    QDomElement srcPasswdElement = doc.createElement("src_passwd");
    root.appendChild(srcPasswdElement);
    srcPasswdElement.appendChild(doc.createTextNode(QString(task.src_pwd)));

    QDomElement dstUserElement = doc.createElement("dst_user");
    root.appendChild(dstUserElement);
    dstUserElement.appendChild(doc.createTextNode(QString(task.dst_user)));

    QDomElement dstPasswdElement = doc.createElement("dst_passwd");
    root.appendChild(dstPasswdElement);
    dstPasswdElement.appendChild(doc.createTextNode(QString(task.dst_pwd)));

    QDomElement execatElement = doc.createElement("execat");
    root.appendChild(execatElement);
    execatElement.appendChild(doc.createTextNode(QString(task.execat)));

    QDomElement renameElement = doc.createElement("rename");
    root.appendChild(renameElement);
    renameElement.appendChild(doc.createTextNode(QString(task.rename)));

    QString elementName, elementValue;
    if(m_pReq->parameter("cmd").contains("Downloads_Schedule_")) {
        elementName = "lang";
        elementValue = QString(task.option.lang);
    }
    else if(m_pReq->parameter("cmd").contains("Local_Backup_")) {
        elementName = "inc";
        elementValue = QString(task.option.inc);
    }

    QDomElement incElement = doc.createElement(elementName);
    root.appendChild(incElement);
    incElement.appendChild(doc.createTextNode(elementValue));

    FreeTask(&task);

}

void RenderResponseAppMngm::generateLocalBackupRenew(QString &str) {
    renewOrAdd(false);

    if(m_pReq->parameter("cmd") == QString("Downloads_Schedule_Renew"))
        str = "<script>location.href='/web/download_mgr/downloads_setting.html'</script>";
    else if(m_pReq->parameter("cmd") == QString("Local_Backup_Renew"))
        str = "<script>location.href='/web/backup_mgr/localbackup_setting.html?id=8401878'</script>";
}

void RenderResponseAppMngm::generateLocalBackupDel(QDomDocument &doc) {

    RESULT_STATUS result = DeleteTaskXml(m_pReq->parameter("f_idx").toLocal8Bit().data());
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement idxElement = doc.createElement("idx");
    root.appendChild(idxElement);
    idxElement.appendChild(doc.createTextNode(m_pReq->parameter("f_idx")));

    QDomElement fnameElement = doc.createElement("fname");
    root.appendChild(fnameElement);
    fnameElement.appendChild(doc.createTextNode(m_pReq->parameter("f_idx") + ".xml"));

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode("0"));
}

void RenderResponseAppMngm::generateLocalBackupTest(QDomDocument &doc) {

    DOWNLOAD_TEST_RESULT *testResult = NULL;
    QString user = m_pReq->parameter("f_user");
    QString pwd = m_pReq->parameter("f_pwd");

    if(user == "*****") {
        user.clear();
        pwd.clear();
    }

    /* Null user is anonymount. */
    /* type ? */
    RESULT_STATUS resultSatus = TestDownloadTask(m_pReq->parameter("f_type").toInt(),
                                            user.isEmpty() ? NULL : user.toLocal8Bit().data(),
                                            pwd.isEmpty() ? NULL : pwd.toLocal8Bit().data(),
                                            m_pReq->parameter("f_lang").toLocal8Bit().data(),
                                            m_pReq->parameter("f_src").toLocal8Bit().data(),
                                            testResult);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement suserElement = doc.createElement("f_suser");
    root.appendChild(suserElement);
    suserElement.appendChild(doc.createTextNode(user));

    QDomElement spasswdElement = doc.createElement("f_spasswd");
    root.appendChild(spasswdElement);
    spasswdElement.appendChild(doc.createTextNode(pwd));

    if(!m_pReq->parameter("f_lang").isEmpty()) {
        QDomElement langElement = doc.createElement("f_lang");
        root.appendChild(langElement);
        langElement.appendChild(doc.createTextNode(m_pReq->parameter("f_lang")));
    }

    QDomElement srcElement = doc.createElement("src");
    root.appendChild(srcElement);
    srcElement.appendChild(doc.createTextNode(m_pReq->parameter("f_src")));

    int result = -1;
    int size = -1;
    if(testResult) {
        result = testResult->result;
        size = testResult->size;
    }

    QDomElement resultElement = doc.createElement("result");
    root.appendChild(resultElement);
    resultElement.appendChild(doc.createTextNode(QString::number(result)));

    QDomElement sizeElement = doc.createElement("size");
    root.appendChild(sizeElement);
    sizeElement.appendChild(doc.createTextNode(QString::number(size)));
}

/* todo */
void RenderResponseAppMngm::generateGetRsyncInfo(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("rsync_info");
    doc.appendChild(root);

    QDomElement serverEnableElement = doc.createElement("server_enable");
    root.appendChild(serverEnableElement);
    serverEnableElement.appendChild(doc.createTextNode("1"));

    QDomElement serverPwElement = doc.createElement("server_pw");
    root.appendChild(serverPwElement);
    serverPwElement.appendChild(doc.createTextNode("000000"));

    QDomElement localIpElement = doc.createElement("local_ip");
    root.appendChild(localIpElement);
    localIpElement.appendChild(doc.createTextNode("192.168.100.85"));

}

/* todo */
void RenderResponseAppMngm::generateSetRsyncServer(QString &str) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");
    str = "<script>location.href='/web/backup_mgr/remote_server.html'</script>";

}


/* todo */
void RenderResponseAppMngm::generateGetBackupList(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

        QString cellcontent3 = "&lt;img border=&apos;0&apos; src=&apos;/web/images/stop.png&apos; width=&apos;27&apos\
                               ; height=&apos;17&apos; onclick=&apos;onoff_job(&quot;task&quot;,0)&apos;&gt;";
        QString cellcontent4 = "&lt;img border=&apos;0&apos; src=&apos;/web/images/backup.png&apos; width=&apos;16&apos\
                                ; height=&apos;16&apos; onclick=&apos;backup_now(&quot;task&quot;)&apos;&gt;";
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
        cellElement1.appendChild(doc.createTextNode("task"));

        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode("Manual"));

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode(""));

        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createTextNode(cellcontent3));

        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createTextNode(cellcontent4));

        QDomElement cellElement6 = doc.createElement("cell");
        rowElement.appendChild(cellElement6);
        cellElement6.appendChild(doc.createTextNode("-"));

        rowElement.setAttribute("id", "1");

        QDomElement pageElement = doc.createElement("page");
        root.appendChild(pageElement);
        pageElement.appendChild(doc.createTextNode("1"));

        QDomElement totalElement = doc.createElement("total");
        root.appendChild(totalElement);
        totalElement.appendChild(doc.createTextNode("1"));

}

/* todo */
void RenderResponseAppMngm::generateGetAllTaskName(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
}

/* todo */
void RenderResponseAppMngm::generateServerTest(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");
        //for(int i=0; i < apiOut.size(); i++) {
    //        if(apiOut.at(i).isEmpty())
    //            continue;
    //        if(apiOut.at(i).split(",").size() < 2)
    //            continue;

        QDomElement root = doc.createElement("test_info");
        doc.appendChild(root);

        QDomElement sshTestStatusElement = doc.createElement("ssh_test_status");
        root.appendChild(sshTestStatusElement);
        sshTestStatusElement.appendChild(doc.createTextNode("1"));

        QDomElement rsyncTestStatusElement = doc.createElement("rsync_test_status");
        root.appendChild(rsyncTestStatusElement);
        rsyncTestStatusElement.appendChild(doc.createTextNode("101"));

        QDomElement remoteHdA2FreeSizeElement = doc.createElement("remote_hd_a2_free_size");
        root.appendChild(remoteHdA2FreeSizeElement);
        remoteHdA2FreeSizeElement.appendChild(doc.createTextNode("2.7T"));

        QDomElement localDirectoryUsedSizeElement = doc.createElement("local_directory_used_size");
        root.appendChild(localDirectoryUsedSizeElement);
        localDirectoryUsedSizeElement.appendChild(doc.createTextNode("8.0K"));

        QDomElement shareNodeElement = doc.createElement("share_node");
        root.appendChild(shareNodeElement);

        QDomElement nameElement = doc.createElement("name");
        shareNodeElement.appendChild(nameElement);
        nameElement.appendChild(doc.createTextNode("Volume_1"));

        QDomElement pathElement = doc.createElement("path");
        shareNodeElement.appendChild(pathElement);
        pathElement.appendChild(doc.createTextNode("/mnt/HD/HD_a2"));
}

/* todo */
void RenderResponseAppMngm::generateCheckRsyncRw(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");
    QDomElement root = doc.createElement("rsync_info");
    doc.appendChild(root);

    QDomElement rsyncRetElement = doc.createElement("rsync_ret");
    root.appendChild(rsyncRetElement);
    rsyncRetElement.appendChild(doc.createTextNode("101"));
}


/* todo */
void RenderResponseAppMngm::generateSetSchedule(QString &str) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");
    str = "N/A";

}

/* todo */
void RenderResponseAppMngm::generateGetModifyInfo(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");
    QDomElement root = doc.createElement("info");
    doc.appendChild(root);

    QDomElement jobNameElement = doc.createElement("job_name");
    root.appendChild(jobNameElement);
    jobNameElement.appendChild(doc.createTextNode("task"));

    QDomElement serverTypeElement = doc.createElement("server_type");
    root.appendChild(serverTypeElement);
    serverTypeElement.appendChild(doc.createTextNode("2"));

    QDomElement backupTypeElement = doc.createElement("backup_type");
    root.appendChild(backupTypeElement);
    backupTypeElement.appendChild(doc.createTextNode("2"));

    QDomElement scheduleModeElement = doc.createElement("schedule_mode");
    root.appendChild(scheduleModeElement);
    scheduleModeElement.appendChild(doc.createTextNode("1"));

    QDomElement useSshElement = doc.createElement("use_ssh");
    root.appendChild(useSshElement);
    useSshElement.appendChild(doc.createTextNode("0"));

    QDomElement keepExistFileElement = doc.createElement("keep_exist_file");
    root.appendChild(keepExistFileElement);
    keepExistFileElement.appendChild(doc.createTextNode("0"));

    QDomElement incBackupElement = doc.createElement("inc_backup");
    root.appendChild(incBackupElement);
    incBackupElement.appendChild(doc.createTextNode("0"));

    QDomElement incNumberElement = doc.createElement("inc_number");
    root.appendChild(incNumberElement);
    incNumberElement.appendChild(doc.createTextNode("3"));

    QDomElement scheduleElement = doc.createElement("schedule");
    root.appendChild(scheduleElement);
    scheduleElement.appendChild(doc.createTextNode(""));

    QDomElement remoteIpElement = doc.createElement("remote_ip");
    root.appendChild(remoteIpElement);
    remoteIpElement.appendChild(doc.createTextNode("192.168.100.203"));

    QDomElement localPathElement = doc.createElement("local_path");
    root.appendChild(localPathElement);
    localPathElement.appendChild(doc.createTextNode("Volume_1"));

    QDomElement rsyncUserElement = doc.createElement("rsync_user");
    root.appendChild(rsyncUserElement);
    rsyncUserElement.appendChild(doc.createTextNode("admin"));

    QDomElement rsyncPwElement = doc.createElement("rsync_pw");
    root.appendChild(rsyncPwElement);
    rsyncPwElement.appendChild(doc.createTextNode("admin"));

    QDomElement sshUserElement = doc.createElement("ssh_user");
    root.appendChild(sshUserElement);
    sshUserElement.appendChild(doc.createTextNode(""));

    QDomElement sshPwElement = doc.createElement("ssh_pw");
    root.appendChild(sshPwElement);
    sshPwElement.appendChild(doc.createTextNode(""));

    QDomElement remotePathElement = doc.createElement("remote_path");
    root.appendChild(remotePathElement);
    remotePathElement.appendChild(doc.createTextNode("NetBackup"));
}

/* todo */
void RenderResponseAppMngm::generateDelSchedule(QString &str) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");
    str = "N/A";

}

/* todo */
void RenderResponseAppMngm::generateEnableDisableSchedule(QString &str) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");
    str = "N/A";

}

/* todo */
void RenderResponseAppMngm::generateBackupNow(QString &str) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");
    str = "N/A";

}
