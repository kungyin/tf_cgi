#include "RenderResponseAppMngm.h"
#include "http_ftp_download.h"
#include "Databaseobject.h"

#include <QDateTime>
#include <QFileInfo>


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

    switch(m_cmd) {
    case CMD_SET_AFP:
        generateSetAfp();
        break;
    case CMD_NFS_ENABLE:
        generateNfsEnable();
        break;
    case CMD_CHK_DB:
        generateCheckDb();
        break;
    case CMD_UPNP_AV_SERVER_PATH_LIST:
        generateUpnpAvServerPathList();
        break;
    case CMD_UPNP_AV_SERVER_GET_CONFIG:
        generateUpnpAvServerGetConfig();
        break;
    case CMD_UPNP_AV_SERVER:
        generateUpnpAvServer();
        break;
    case CMD_UPNP_AV_SERVER_GET_SQLDB_STATE:
        generateUpnpAvServerGetSqldbState();
        break;
    case CMD_GUI_CODEPAGE_GET_LIST:
        generateGuiCodepageGetList();
        break;
    case CMD_ITUNES_SERVER_GET_XML:
        generateItunesServerGetXml();
        break;
    case CMD_ITUNES_SERVER_READY:
        generateItunesServerReady();
        break;
    case CMD_AV_SERVER_CHECK_PATH:
        generateUpnpAvServerCheckPath();
        break;
    case CMD_AV_SERVER_PATH_SETTING:
        generateUpnpAvServerPathSetting();
        break;
    case CMD_SQLDB_STOP_FINISH:
        generateSqldbStopFinish();
        break;
    case CMD_UPNP_AV_SERVER_PRESCAN:
        generateUpnpAvServerPrescan();
        break;
    case CMD_UPNP_AV_SERVER_PATH_DEL:
        generateUpnpAvServerPathDel();
        break;
    case CMD_UPNP_AV_SERVER_SETTING:
        generateUpnpAvServerSetting();
        break;
    case CMD_GUI_CODEPAGE_ADD:
        generateGuiCodepageAdd();
        break;
    case CMD_ITUNES_SERVER_SETTING:
        generateItunesServerSetting();
        break;
    case CMD_ITUNES_SERVER_CHECK_PS:
        generateItunesServerCheckPs();
        break;
    case CMD_ITUNES_SERVER_REFRESH:
        generateItunesServerRefresh();
        break;
    case CMD_ITUNES_SERVER_REFRESH_STATE:
        generateItunesServerRefreshState();
        break;
    case CMD_SYSLOG_SEARCH:
        generateSyslogSearch();
        break;
    case CMD_GET_VOLUME_INFO:
        generateGetVolumeInfo();
        break;
    case CMD_SYSLOG_GET_LOG_FILE_OPTION:
        generateSyslogGetLogFileOption();
        break;
    case CMD_SYSLOG_GET_CONFIG:
        generateSyslogGetConfig();
        break;
    case CMD_SYSLOG_GET_SELECT_OPTION:
        generateSyslogGetSelectOption();
        break;
    case CMD_SYSLOG_SET_CONFIG:
        generateSyslogSetConfig();
        break;
    case CMD_SYSLOG_EXPORT:
        generateSyslogExport();
        break;
    case CMD_SYSLOG_GET_EXPORT_STATUS:
        generateSyslogGetExportStatus();
        break;
    case CMD_SYSLOG_CLEAR:
        generateSyslogClear();
        break;

    case CMD_LOCAL_BACKUP_NOW:
        generateLocalBackupNow();
        break;
    case CMD_LOCAL_BACKUP_LIST:
        generateLocalBackupList();
        break;
    case CMD_LOCAL_BACKUP_SAMBA_FORMAT:
        generateLocalBackupSambaFormat();
        break;
    case CMD_LOCAL_BACKUP_ADD:
        generateLocalBackupAdd();
        break;
    case CMD_LOCAL_BACKUP_INFO:
        generateLocalBackupInfo();
        break;
    case CMD_LOCAL_BACKUP_RENEW:
        generateLocalBackupRenew();
        break;
    case CMD_LOCAL_BACKUP_DEL:
        generateLocalBackupDel();
        break;
    case CMD_LOCAL_BACKUP_TEST:
        generateLocalBackupTest();
        break;

    case CMD_GET_RSYNC_INFO:
        generateGetRsyncInfo();
        break;
    case CMD_SET_RSYNC_SERVER:
        generateSetRsyncServer();
        break;

    case CMD_GET_BACKUP_LIST:
        generateGetBackupList();
        break;
    case CMD_GET_ALL_TASK_NAME:
        generateGetAllTaskName();
        break;
    case CMD_SERVER_TEST:
        generateServerTest();
        break;
    case CMD_CHECK_RSYNC_RW:
        generateCheckRsyncRw();
        break;
    case CMD_SET_SCHEDULE:
        generateSetSchedule();
        break;
    case CMD_GET_MODIFY_INFO:
        generateGetModifyInfo();
        break;
    case CMD_DEL_SCHEDULE:
        generateDelSchedule();
        break;
    case CMD_ENABLE_DISABLE_SCHEDULE:
        generateEnableDisableSchedule();
        break;
    case CMD_BACKUP_NOW:
        generateBackupNow();
        break;
    case CMD_MTP_INFO_GET:
        generateMtpInfoGet();
        break;
    case CMD_USB_BACKUP_INFO_GET:
        generateUsbBackupInfoGet();
        break;
    case CMD_MTP_INFO_SET:
        generateMtpInfoSet();
        break;
    case CMD_USB_BACKUP_INFO_SET:
        generateUsbBackupInfoSet();
        break;
    case CMD_GET_USB_MAPPING_INFO:
        generateGetUsbMappingInfo();
        break;

    default:
        break;
    }

}

void RenderResponseAppMngm::generateSetAfp() {
    QString paraAfp = m_pReq->allParameters().value("afp").toString();
    if(setNasCfg("afp", "enable", paraAfp))
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_AFP_API, true);
}

void RenderResponseAppMngm::generateNfsEnable() {
    QDomDocument doc;
    QString paraNfsStatus = m_pReq->allParameters().value("nfs_status").toString();
    QStringList apiOut;
    if(setNasCfg("nfs", "enable", paraNfsStatus))
        apiOut = getAPIStdOut(API_PATH + SCRIPT_NFS_API + " restart", true);

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.isEmpty() ? "0" : apiOut.value(0)));
    m_var = doc.toString();
}

/* todo */
void RenderResponseAppMngm::generateCheckDb() {
//    if(setNasCfg("nfs", "enable", paraNfsStatus))
//        apiOut = getAPIStdOut(API_PATH + SCRIPT_NFS_API, true);
}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerPathList() {
    QDomDocument doc;
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();

//    QStringList apiOut;
//    if(setNasCfg("nfs", "enable", paraNfsStatus))
//        apiOut = getAPIStdOut(API_PATH + SCRIPT_NFS_API, true);

    QString cellcontent3 = "<a href=javascript:upnp_path_refresh_one('%1');><IMG border='0' "
                            "src='/web/images/refresh_over.png'></a>";
    QString cellcontent4 = "<IMG border='0' src='/web/images/on.png'>";
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
    cellElement3.appendChild(doc.createCDATASection(cellcontent3.arg("1")));

    QDomElement cellElement4 = doc.createElement("cell");
    rowElement.appendChild(cellElement4);
    cellElement4.appendChild(doc.createCDATASection(cellcontent4));

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

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerGetConfig() {
    QDomDocument doc;

//    QStringList apiOut;
//    if(setNasCfg("nfs", "enable", paraNfsStatus))
//        apiOut = getAPIStdOut(API_PATH + SCRIPT_NFS_API, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode("0"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServer() {
    QDomDocument doc;

//    QStringList apiOut;
//    if(setNasCfg("nfs", "enable", paraNfsStatus))
//        apiOut = getAPIStdOut(API_PATH + SCRIPT_NFS_API, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("0"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerGetSqldbState() {
    QDomDocument doc;

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
    m_var = doc.toString();

}

void RenderResponseAppMngm::generateGuiCodepageGetList() {

    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");
    char *name = NULL, *desc = NULL;
    int codepage_cnt = GetCodepageList(1, &name, &desc);
    free(name);
    free(desc);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(QString::number(codepage_cnt)));

    for (int i = 0; i < codepage_cnt; i++) {
        GetCodepageList(i + 1, &name, &desc);
        QDomElement itemElement = doc.createElement("item");
        root.appendChild(itemElement);

        QDomElement langElement = doc.createElement("lang");
        itemElement.appendChild(langElement);
        langElement.appendChild(doc.createTextNode(QString(name)));

        QDomElement descElement = doc.createElement("desc");
        itemElement.appendChild(descElement);
        descElement.appendChild(doc.createTextNode(QString(desc)));
        free(name);
        free(desc);
    }

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateItunesServerGetXml() {
    QDomDocument doc;

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

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateItunesServerReady() {
    QDomDocument doc;

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

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerCheckPath() {
    QDomDocument doc;

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

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerPathSetting() {
    QDomDocument doc;

    QString paraDir = m_pReq->allParameters().value("f_dir").toString();
    QString paraRefresh = m_pReq->allParameters().value("f_refresh").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateSqldbStopFinish() {
    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("0"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerPrescan() {
    QDomDocument doc;

    QString paraDir = m_pReq->allParameters().value("f_dir").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerPathDel() {
    QDomDocument doc;

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

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateUpnpAvServerSetting() {

    QString paraUpnpAvServer = m_pReq->allParameters().value("f_UPNPAVServer").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

}

/* todo */
void RenderResponseAppMngm::generateGuiCodepageAdd() {
    QDomDocument doc;

    QString paraLang = m_pReq->allParameters().value("f_lang").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateItunesServerSetting() {
    QDomDocument doc;

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

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateItunesServerCheckPs() {
    QDomDocument doc;

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

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateItunesServerRefresh() {
    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateItunesServerRefreshState() {
    QDomDocument doc;

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

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateSyslogSearch() {
    QDomDocument doc;

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
    QString paraKeyword = m_pReq->allParameters().value("f_keyword").toString();

    SyslogDbDataProvider sys;
    QSqlError err = sys.SelectDataFromPara(paraPage, paraRp, paraSortname, paraSortorder, paraQuery, paraQType, paraField,
                           paraUser, paraLogFile, paraDateFrom, paraDateTo, paraViewSeverity, paraLogHost,
                           paraLogFacility, paraLogApplication, paraKeyword);
    if (err.isValid())
    {
        QDomElement db_error = doc.createElement("error");
        doc.appendChild(db_error);
        db_error.appendChild(doc.createTextNode(err.text()));
        return;
    }
    int size = sys.GetSize();

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    /*QString cellContent1 = "&amp;nbsp;[origin&amp;nbsp;software=&quot;rsyslogd&quot;&amp;nbsp;swVersion=\
            &quot;5.8.6&quot;&amp;nbsp;x-pid=&quot;%1&quot;&amp;nbsp;x-info=&quot;\
            http://www.rsyslog.com&quot;]&amp;nbsp;start";
    QString cellContent2 = "&amp;nbsp;[origin&amp;nbsp;software=&quot;rsyslogd&quot;&amp;nbsp;swVersion=\
            &quot;5.8.6&quot;&amp;nbsp;x-pid=&quot;%1&quot;&amp;nbsp;x-info=&quot;\
            http://www.rsyslog.com&quot;]&amp;nbsp;exiting&amp;nbsp;on&amp;nbsp;signal&amp;nbsp;15.";*/

    QDomElement rowElement;
    QDomElement cellElement1;
    QDomElement cellElement2;
    QDomElement cellElement3;
    QDomElement cellElement4;
    QDomElement cellElement5;
    QDomElement cellElement6;
    QDomElement cellElement7;
    QString deviceReportedTime;
    QStringList timeList;
    for (int i = 0; i < size; i++)
    {
        if (sys.GetSelectedData()->next())
        {
            deviceReportedTime = sys.GetSelectedData()->value("DeviceReportedTime").toString();
            if (deviceReportedTime.isEmpty()) continue;
            timeList = deviceReportedTime.split("T");
            if (timeList.count() != 2) continue;
            rowElement = doc.createElement("row");
            root.appendChild(rowElement);
            cellElement1 = doc.createElement("cell");
            rowElement.appendChild(cellElement1);
            cellElement1.appendChild(doc.createTextNode(timeList.at(0)));
            cellElement2 = doc.createElement("cell");
            rowElement.appendChild(cellElement2);
            cellElement2.appendChild(doc.createTextNode(timeList.at(1)));

            cellElement3 = doc.createElement("cell");
            rowElement.appendChild(cellElement3);
            cellElement3.appendChild(doc.createTextNode(sys.GetSelectedData()->value("Facility").toString()));
            cellElement4 = doc.createElement("cell");
            rowElement.appendChild(cellElement4);
            cellElement4.appendChild(doc.createTextNode(sys.GetSelectedData()->value("FromHost").toString()));
            cellElement5 = doc.createElement("cell");
            rowElement.appendChild(cellElement5);
            cellElement5.appendChild(doc.createTextNode(sys.GetSelectedData()->value("Priority").toString()));

            cellElement6 = doc.createElement("cell");
            rowElement.appendChild(cellElement6);
            cellElement6.appendChild(doc.createTextNode(sys.GetSelectedData()->value("SysLogTag").toString()));
            cellElement7 = doc.createElement("cell");
            /*QUrl url(sys.GetSelectedData()->value("Message").toString());
            rowElement.appendChild(cellElement7);
            cellElement7.appendChild(doc.createTextNode(url.toEncoded().data()));*/
            rowElement.appendChild(cellElement7);
            cellElement7.appendChild(doc.createTextNode(sys.GetSelectedData()->value("Message").toString()));

            rowElement.setAttribute("id", QString::number(i + 1));
        }
        else break;
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(size)));

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateGetVolumeInfo() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_volume_info");
    QStringList apiArgs;
    if (!apiOut.isEmpty()) apiArgs = apiOut.at(0).split(";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    //for(int i=0; i < apiOut.size(); i++) {
//        if(apiOut.at(i).isEmpty())
//            continue;
//        if(apiOut.at(i).split(",").size() < 2)
//            continue;
    QDomElement itemElement, optValueElement, guiValueElement;
    for(int i = 0; i < apiArgs.size(); i++)
    {
        itemElement = doc.createElement("item");
        root.appendChild(itemElement);
        optValueElement = doc.createElement("opt_value");
        itemElement.appendChild(optValueElement);
        optValueElement.appendChild(doc.createTextNode(apiArgs.at(i)));
        guiValueElement = doc.createElement("gui_value");
        itemElement.appendChild(guiValueElement);
        guiValueElement.appendChild(doc.createTextNode(apiArgs.at(i)));
    }

    //}

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateSyslogGetLogFileOption() {
    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    SyslogDbDataProvider sys;
    QSqlError err = sys.GetAllDatabase();
    if (err.isValid())
    {
        QDomElement db_error = doc.createElement("error");
        doc.appendChild(db_error);
        db_error.appendChild(doc.createTextNode(err.text()));
        return;
    }
    int size = sys.GetSize();

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QString dbName;
    QDomElement cellElement;
    for (int i = 0; i < size; i++)
    {
        if (sys.GetSelectedData()->next())
        {
            dbName = sys.GetSelectedData()->value(0).toString();
            if (dbName.indexOf("Syslog_") >= 0)
            {
                cellElement = doc.createElement("cell");
                root.appendChild(cellElement);
                cellElement.appendChild(doc.createTextNode(dbName));
            }
        }
    }

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateSyslogGetConfig() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_log_cfg");
    QStringList apiArgs;
    if (!apiOut.isEmpty()) apiArgs = apiOut.at(0).split(";");
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    if (apiArgs.size() != 15) return;

    QDomElement syslogEnableElement = doc.createElement("syslog_enable");
    root.appendChild(syslogEnableElement);
    syslogEnableElement.appendChild(doc.createTextNode(apiArgs.at(0)));
    QDomElement syslogFolderElement = doc.createElement("syslog_folder");
    root.appendChild(syslogFolderElement);
    syslogFolderElement.appendChild(doc.createTextNode(apiArgs.at(1)));
    QDomElement syslogUdpElement = doc.createElement("syslog_udp");
    root.appendChild(syslogUdpElement);
    syslogUdpElement.appendChild(doc.createTextNode(apiArgs.at(2)));

    QDomElement archiveSizeEnElement = doc.createElement("archive_size_en");
    root.appendChild(archiveSizeEnElement);
    archiveSizeEnElement.appendChild(doc.createTextNode(apiArgs.at(3)));
    QDomElement archiveSizeElement = doc.createElement("archive_size");
    root.appendChild(archiveSizeElement);
    archiveSizeElement.appendChild(doc.createTextNode(apiArgs.at(4)));

    QDomElement archiveNumEnElement = doc.createElement("archive_num_en");
    root.appendChild(archiveNumEnElement);
    archiveNumEnElement.appendChild(doc.createTextNode(apiArgs.at(5)));
    QDomElement archiveNumElement = doc.createElement("archive_num");
    root.appendChild(archiveNumElement);
    archiveNumElement.appendChild(doc.createTextNode(apiArgs.at(6)));

    QDomElement archiveCycleEnElement = doc.createElement("archive_cycle_en");
    root.appendChild(archiveCycleEnElement);
    archiveCycleEnElement.appendChild(doc.createTextNode(apiArgs.at(7)));
    QDomElement archiveCycleElement = doc.createElement("archive_cycle");
    root.appendChild(archiveCycleElement);
    archiveCycleElement.appendChild(doc.createTextNode(apiArgs.at(8)));

    QDomElement folderQuotaSizeElement = doc.createElement("folder_quota_size");
    root.appendChild(folderQuotaSizeElement);
    folderQuotaSizeElement.appendChild(doc.createTextNode(apiArgs.at(9)));

    QDomElement emailEnableElement = doc.createElement("email_enable");
    root.appendChild(emailEnableElement);
    emailEnableElement.appendChild(doc.createTextNode(apiArgs.at(10)));
    QDomElement emailSeverityElement = doc.createElement("email_severity");
    root.appendChild(emailSeverityElement);
    emailSeverityElement.appendChild(doc.createTextNode(apiArgs.at(11)));
    QDomElement sendMailElement = doc.createElement("send_mail");
    root.appendChild(sendMailElement);
    sendMailElement.appendChild(doc.createTextNode(apiArgs.at(12)));

    QDomElement syslogStatusElement = doc.createElement("syslog_status");
    root.appendChild(syslogStatusElement);
    syslogStatusElement.appendChild(doc.createTextNode(apiArgs.at(13)));
    QDomElement archiveStatusElement = doc.createElement("archive_status");
    root.appendChild(archiveStatusElement);
    archiveStatusElement.appendChild(doc.createTextNode(apiArgs.at(14)));

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateSyslogGetSelectOption() {
    QDomDocument doc;

    QString paraDatabase = m_pReq->allParameters().value("f_database").toString();

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    SyslogDbDataProvider sys;
    QSqlError err = sys.SelectAllServerity(paraDatabase);
    if (err.isValid())
    {
        QDomElement db_error = doc.createElement("error");
        doc.appendChild(db_error);
        db_error.appendChild(doc.createTextNode(err.text()));
        return;
    }
    int size = sys.GetSize(), i = 0;

    QDomElement severityElement;
    QDomElement severityCellElement;
    if (size > 0)
    {
        severityElement = doc.createElement("severity");
        root.appendChild(severityElement);
        for (i = 0; i < size; i++)
        {
            if (sys.GetSelectedData()->next())
            {
                severityCellElement = doc.createElement("cell");
                severityElement.appendChild(severityCellElement);
                severityCellElement.appendChild(doc.createTextNode(sys.GetSelectedData()->value(0).toString()));
            }
        }
    }

    err = sys.SelectAllHost(paraDatabase);
    if (err.isValid())
    {
        QDomElement db_error = doc.createElement("error");
        doc.appendChild(db_error);
        db_error.appendChild(doc.createTextNode(err.text()));
        return;
    }
    size = sys.GetSize();
    QDomElement hostElement;
    QDomElement hostCellElement;
    if (size > 0)
    {
        hostElement = doc.createElement("host");
        root.appendChild(hostElement);
        for (i = 0; i < size; i++)
        {
            if (sys.GetSelectedData()->next())
            {
                hostCellElement = doc.createElement("cell");
                hostElement.appendChild(hostCellElement);
                hostCellElement.appendChild(doc.createTextNode(sys.GetSelectedData()->value(0).toString()));
            }
        }
    }

    err = sys.SelectAllFacility(paraDatabase);
    if (err.isValid())
    {
        QDomElement db_error = doc.createElement("error");
        doc.appendChild(db_error);
        db_error.appendChild(doc.createTextNode(err.text()));
        return;
    }
    size = sys.GetSize();
    QDomElement facilityElement;
    QDomElement facilityCellElement;
    if (size > 0)
    {
        facilityElement = doc.createElement("facility");
        root.appendChild(facilityElement);
        for (i = 0; i < size; i++)
        {
            if (sys.GetSelectedData()->next())
            {
                facilityCellElement = doc.createElement("cell");
                facilityElement.appendChild(facilityCellElement);
                facilityCellElement.appendChild(doc.createTextNode(sys.GetSelectedData()->value(0).toString()));
            }
        }
    }

    err = sys.SelectAllApplication(paraDatabase);
    if (err.isValid())
    {
        QDomElement db_error = doc.createElement("error");
        doc.appendChild(db_error);
        db_error.appendChild(doc.createTextNode(err.text()));
        return;
    }
    size = sys.GetSize();
    QDomElement applicationElement;
    QDomElement applicationCellElement;
    if (size > 0)
    {
        applicationElement = doc.createElement("application");
        root.appendChild(applicationElement);
        for (i = 0; i < size; i++)
        {
            if (sys.GetSelectedData()->next())
            {
                applicationCellElement = doc.createElement("cell");
                applicationElement.appendChild(applicationCellElement);
                applicationCellElement.appendChild(doc.createTextNode(sys.GetSelectedData()->value(0).toString()));
            }
        }
    }
    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateSyslogSetConfig() {

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

    QString args = QString(" f_syslog_enable=%1#f_syslog_folder=%2#f_syslog_udp=%3#"
                           "f_archive_size_en=%4#f_archive_size=%5#f_archive_num_en=%6#"
                           "f_archive_cycle_en=%7#f_archive_cycle=%8#f_folder_quota_size=%9#"
                           "f_email_severity=%10#f_email_enable=%11#is_sendmail=%12#f_new_log_folder=%13")
            .arg(paraSyslogEnable)
            .arg(paraSyslogFolder)
            .arg(paraSyslogUdp)
            .arg(paraArchiveSizeEn)
            .arg(paraArchiveSize)
            .arg(paraArchiveNumEn)
            .arg(paraArchiveCycleEn)
            .arg(paraArchiveCycle)
            .arg(paraFolderQuotaSize)
            .arg(paraEmailSeverity)
            .arg(paraEmailEnable)
            .arg(paraIsSendmail)
            .arg(paraNewLogFolder);
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_log_cfg" + args);

    m_var = "<script>location.href='/web/app_mgr/log_server.html?id=8401878'</script>";

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
    QString paraKeyword = m_pReq->allParameters().value("f_keyword").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();

    SyslogDbDataProvider sys;
    m_var = sys.DumpDataFromPara(paraLogFile, paraDateFrom, paraDateTo, paraViewSeverity, paraLogHost, paraLogFacility, paraLogApplication, paraKeyword, paraRp);

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

}

/* todo */
void RenderResponseAppMngm::generateSyslogGetExportStatus() {
    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    QFileInfo f("/tmp/syslogsendok");
    if (f.exists())
        statusElement.appendChild(doc.createTextNode("1"));
    else
        statusElement.appendChild(doc.createTextNode("-1"));
    QFile::remove("/tmp/syslogsendok");

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateSyslogClear() {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

}

/* todo */
void RenderResponseAppMngm::generateLocalBackupNow() {
    QDomDocument doc;

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

    m_var = doc.toString();

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


void RenderResponseAppMngm::generateLocalBackupList() {
    QDomDocument doc;

    QString strProgressBar = "<span class='progressBar' id='progressbar_row%1'>%2</span>";
    QString strImage = "<IMG src='%1'>";
    QString strBackupStart =
            "<a href=javascript:%1_%2('%3')><IMG border='0' src='/web/images/%2.png'></a>";

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
        cellElement3.appendChild(doc.createCDATASection(strProgressBar.arg(QString::number(i+1))
                                                    .arg(QString(taskList[i].percent))));

        QDomElement cellElement4 = doc.createElement("cell");
        rowElement1.appendChild(cellElement4);
        cellElement4.appendChild(doc.createCDATASection(strImage.arg(getIcon(QString(taskList[i].status)))));

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
        cellElement7.appendChild(doc.createCDATASection(strBackupStart
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

    m_var = doc.toString();

}

/* todo */
void RenderResponseAppMngm::generateLocalBackupSambaFormat() {
    QDomDocument doc;

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FTP_API + " -g codepage");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    //for
    QDomElement itemElement = doc.createElement("item");
    root.appendChild(itemElement);

    QDomElement volElement = doc.createElement("vol");
    itemElement.appendChild(volElement);
    volElement.appendChild(doc.createTextNode("Volume_1"));

    m_var = doc.toString();

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


void RenderResponseAppMngm::generateLocalBackupAdd() {

    renewOrAdd(true);

    if(m_pReq->parameter("cmd") == QString("Downloads_Schedule_Add"))
        m_var = "<script>location.href='/web/download_mgr/downloads_setting.html?id=8401878'</script>";
    else if(m_pReq->parameter("cmd") == QString("Local_Backup_Add"))
        m_var = "<script>location.href='/web/backup_mgr/localbackup_setting.html?id=8401878'</script>";

}

void RenderResponseAppMngm::generateLocalBackupInfo() {
    QDomDocument doc;

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
    m_var = doc.toString();

}

void RenderResponseAppMngm::generateLocalBackupRenew() {
    renewOrAdd(false);

    if(m_pReq->parameter("cmd") == QString("Downloads_Schedule_Renew"))
        m_var = "<script>location.href='/web/download_mgr/downloads_setting.html'</script>";
    else if(m_pReq->parameter("cmd") == QString("Local_Backup_Renew"))
        m_var = "<script>location.href='/web/backup_mgr/localbackup_setting.html?id=8401878'</script>";
}

void RenderResponseAppMngm::generateLocalBackupDel() {
    QDomDocument doc;

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
    m_var = doc.toString();

}

void RenderResponseAppMngm::generateLocalBackupTest() {

    QDomDocument doc;

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

    m_var = doc.toString();

}

void RenderResponseAppMngm::generateGetRsyncInfo() {
    QDomDocument doc;

    RSYNC_INFO rsyncInfo;
    memset(&rsyncInfo, 0, sizeof(RSYNC_INFO));
    RESULT_STATUS status = GetRsyncInfo(&rsyncInfo);

    QDomElement root = doc.createElement("rsync_info");
    doc.appendChild(root);

    if(status == RET_SUCCESS) {
        QDomElement serverEnableElement = doc.createElement("server_enable");
        root.appendChild(serverEnableElement);
        serverEnableElement.appendChild(doc.createTextNode(QString::number(rsyncInfo.is_enable)));

        QDomElement serverPwElement = doc.createElement("server_pw");
        root.appendChild(serverPwElement);
        serverPwElement.appendChild(doc.createTextNode(QString(rsyncInfo.pwd)));

        QDomElement localIpElement = doc.createElement("local_ip");
        root.appendChild(localIpElement);
        localIpElement.appendChild(doc.createTextNode(QString(rsyncInfo.local_ip)));
    }
    else
        tDebug("RenderResponseAppMngm::generateGetRsyncInfo() status: %d", status);
    FreeRsyncInfo(&rsyncInfo);

    m_var = doc.toString();

}

void RenderResponseAppMngm::generateSetRsyncServer() {

    RESULT_STATUS status = SetRsyncInfo(m_pReq->parameter("f_onoff").toInt(),
                                        m_pReq->parameter("f_password").toLocal8Bit().data());
    tDebug("RenderResponseAppMngm::generateSetRsyncServer() status: %d", status);
    m_var = "<script>location.href='/web/backup_mgr/remote_server.html'</script>";

}

void RenderResponseAppMngm::generateGetBackupList() {
    QDomDocument doc;

    QString paraPage = m_pReq->parameter("page");
    QString paraRp = m_pReq->parameter("rp");

    REMOTE_LIST *taskList;
    int total = 0, pageCount = 0;
    memset(&taskList, 0, sizeof(REMOTE_LIST*));
    GetRemoteListXmlValue(paraPage.toInt(), paraRp.toInt(), &total, &pageCount, &taskList);

    QString cellcontent3 = "<img border='0' src='/web/images/%1.png' width='27'"
            " height='17' onclick='onoff_job(\"task\",0)'>";
    QString cellcontent4 = "<img border='0' src='/web/images/backup.png' width='16'"
            " height='16' onclick='backup_now(\"task\")'>";

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    for (int i = 0; i < pageCount; i++)
    {
        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);

        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(QString(taskList->task_name)));

        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode(QString(taskList->schedule_mode)));

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode(QString(taskList->state)));

        /* what value is taskList->enable? */
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createCDATASection(cellcontent3.arg(QString(taskList->enable))));

        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createCDATASection(cellcontent4));

        QDomElement cellElement6 = doc.createElement("cell");
        rowElement.appendChild(cellElement6);
        cellElement6.appendChild(doc.createTextNode("-"));

        rowElement.setAttribute("id", QString::number(i));

        FreeRemoteList(&taskList[i]);
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(total)));

    m_var = doc.toString();

}

void RenderResponseAppMngm::generateGetAllTaskName() {

    QDomDocument doc;

    char **nameList;
    int taskNum = GetAllRemoteTaskName(&nameList);

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);

    for (int i = 0; i < taskNum; i++) {

        QDomElement taskElement = doc.createElement("task");
        root.appendChild(taskElement);

        QDomElement nameElement = doc.createElement("name");
        taskElement.appendChild(nameElement);
        nameElement.appendChild(doc.createTextNode(QString(nameList[i])));

    }

    FreeRemoteTaskName(taskNum, &nameList);
    m_var = doc.toString();

}

/* s_type= 1 | 2 (int)
 * // 1=nas to nas backup, 2=nas to linux backup */
void RenderResponseAppMngm::generateServerTest() {
    QDomDocument doc;

    QString paraIp = m_pReq->parameter("ip");
    QString paraType = m_pReq->parameter("s_type");
    QString paraDirection = m_pReq->parameter("direction");
    QString paraTask = m_pReq->parameter("task");
    QString paraKeepExistFile = m_pReq->parameter("keep_exist_file");
    QString paraLocalPath = m_pReq->parameter("local_path");
    QString paraIncremental = m_pReq->parameter("incremental");
    QString paraEncryption = m_pReq->parameter("encryption");
    QString paraRsyncUser = m_pReq->parameter("rsync_user");
    QString paraRsyncPw = m_pReq->parameter("rsync_pw");
    QString paraSshUser = m_pReq->parameter("ssh_user");
    QString paraSshPw = m_pReq->parameter("ssh_pw");
    QString paraIncNum = m_pReq->parameter("inc_num");

    REMOTE_TEST_RESULT result;
    memset(&result, 0, sizeof(REMOTE_TEST_RESULT));
    TestRemoteBackupTask(paraIp.toLocal8Bit().data(), paraType.toInt(), paraDirection.toInt(),
                         paraTask.toLocal8Bit().data(), paraLocalPath.toLocal8Bit().data(),
                         paraEncryption.toInt(), paraKeepExistFile.toInt(), paraRsyncUser.toLocal8Bit().data(),
                         paraRsyncPw.toLocal8Bit().data(), paraSshUser.toLocal8Bit().data(),
                         paraSshPw.toLocal8Bit().data(), &result);

    QDomElement root = doc.createElement("test_info");
    doc.appendChild(root);

    QDomElement sshTestStatusElement = doc.createElement("ssh_test_status");
    root.appendChild(sshTestStatusElement);
    sshTestStatusElement.appendChild(doc.createTextNode(QString::number(result.ssh_test_result)));

    QDomElement rsyncTestStatusElement = doc.createElement("rsync_test_status");
    root.appendChild(rsyncTestStatusElement);
    rsyncTestStatusElement.appendChild(doc.createTextNode(QString::number(result.rsync_test_result)));

    if(result.rsync_test_result == 101 ) {

        if(paraType == "1") {
            /* todo: need API */
            QDomElement remoteHdA2FreeSizeElement = doc.createElement("remote_hd_a2_free_size");
            root.appendChild(remoteHdA2FreeSizeElement);
            remoteHdA2FreeSizeElement.appendChild(doc.createTextNode("2.7T"));
        }

        int count = 0;
        char **node = NULL;
        GetRemoteRsyncSharePath(paraIp.toLocal8Bit().data(), &count, &node);
        QStringList remoteNodes;
        for (int i = 0; i < count; i++)
            remoteNodes << node[i];
        FreeRemoteTaskName(count, &node);

        if(paraType == "2") {
            for(QString e : remoteNodes) {
                QDomElement shareNodeElement = doc.createElement("share_node");
                root.appendChild(shareNodeElement);

                QDomElement nameElement = doc.createElement("name");
                shareNodeElement.appendChild(nameElement);
                nameElement.appendChild(doc.createTextNode(e));
            }
        }

        char **name = NULL, **path = NULL;
        int volCount = 0;
        GetRsyncSharePath(&volCount, &name, &path);

        QMap<QString, QString> shareNodeMap;
        for(int i=0; i< volCount; i++) {
            shareNodeMap.insert(QString(name[i]), QString(path[i]));
        }
        FreeRsyncSharePath(volCount, &name, &path);

        char *size = NULL;
        GetLocalDeviceSizeString(shareNodeMap.value("Volume_1").toLocal8Bit().data(), NULL, &size);
        QDomElement localDirectoryUsedSizeElement = doc.createElement("local_directory_used_size");
        root.appendChild(localDirectoryUsedSizeElement);
        localDirectoryUsedSizeElement.appendChild(doc.createTextNode(QString(size)));
        if(size)
            free(size);

        if(paraType == "1") {
            for(QString e : shareNodeMap.keys()) {
                QDomElement shareNodeElement = doc.createElement("share_node");
                root.appendChild(shareNodeElement);

                QDomElement nameElement = doc.createElement("name");
                shareNodeElement.appendChild(nameElement);
                nameElement.appendChild(doc.createTextNode(e));
                QDomElement pathElement = doc.createElement("path");
                shareNodeElement.appendChild(pathElement);
                pathElement.appendChild(doc.createTextNode(shareNodeMap.value(e)));
            }
        }
    }
    m_var = doc.toString();

}

void RenderResponseAppMngm::generateCheckRsyncRw() {
    QDomDocument doc;

    QString paraIp = m_pReq->parameter("ip");
    QString paraType = m_pReq->parameter("s_type");
    QString paraDirection = m_pReq->parameter("direction");
    QString paraTask = m_pReq->parameter("task");
    QString paraKeepExistFile = m_pReq->parameter("keep_exist_file");
    QString paraLocalPath = m_pReq->parameter("local_path");
    QString paraIncremental = m_pReq->parameter("incremental");
    QString paraEncryption = m_pReq->parameter("encryption");
    QString paraRsyncUser = m_pReq->parameter("rsync_user");
    QString paraRsyncPw = m_pReq->parameter("rsync_pw");
    QString paraSshUser = m_pReq->parameter("ssh_user");
    QString paraSshPw = m_pReq->parameter("ssh_pw");
    QString paraIncNum = m_pReq->parameter("inc_num");
    QString paraRemotePath = m_pReq->parameter("remote_path");

    int rsyncRet = TestRsyncConnect(paraIp.toLocal8Bit().data(), paraType.toInt(), paraDirection.toInt(),
                                    paraTask.toLocal8Bit().data(), paraLocalPath.toLocal8Bit().data(),
                                    paraEncryption.toInt(), paraKeepExistFile.toInt(),
                                    paraRsyncUser.toLocal8Bit().data(), paraRsyncPw.toLocal8Bit().data(),
                                    paraSshUser.toLocal8Bit().data(), paraSshPw.toLocal8Bit().data());

    QDomElement root = doc.createElement("rsync_info");
    doc.appendChild(root);

    QDomElement rsyncRetElement = doc.createElement("rsync_ret");
    root.appendChild(rsyncRetElement);
    rsyncRetElement.appendChild(doc.createTextNode(QString::number(rsyncRet)));
    m_var = doc.toString();

}

void RenderResponseAppMngm::generateSetSchedule() {

    REMOTE_BACKUP_INFO r_info;
    memset(&r_info, 0, sizeof(REMOTE_BACKUP_INFO));
    r_info.task_name = m_pReq->parameter("task").toLocal8Bit().data();
    r_info.is_enable = 1;
    r_info.state = 1;
    r_info.server_type = m_pReq->parameter("s_type").toInt();
    r_info.backup_type = m_pReq->parameter("direction").toInt();
    r_info.schedule_mode = m_pReq->parameter("schedule_type").toInt();
    r_info.is_use_ssh = m_pReq->parameter("ssh_user").isEmpty() ? 0 : 1;
    r_info.is_keep_exist_file = m_pReq->parameter("keep_exist_file").toInt();
    r_info.is_inc_enable = m_pReq->parameter("incremental").toInt();
    r_info.inc_number = m_pReq->parameter("inc_num").toInt();
    r_info.rsync_user = m_pReq->parameter("rsync_user").toLocal8Bit().data();
    r_info.rsync_pwd = m_pReq->parameter("rsync_pw").toLocal8Bit().data();
    r_info.ssh_user = m_pReq->parameter("ssh_user").toLocal8Bit().data();
    r_info.ssh_pwd = m_pReq->parameter("ssh_pw").toLocal8Bit().data();
    r_info.remote_ip = m_pReq->parameter("ip").toLocal8Bit().data();
    r_info.remote_path = m_pReq->parameter("remote_path").toLocal8Bit().data();

    QString localPath = m_pReq->parameter("local_path");
    localPath.replace("Volume_1", "/mnt/HD/HD_a2");
    localPath.replace("Volume_2", "/mnt/HD/HD_b2");
    r_info.local_path = localPath.toLocal8Bit().data();

    //QDateTime execat = QDateTime::fromString(QString(taskList[i].execat), "yyyyMMddhhmm");
    //    crond_type= 1 | 2 | 3 (int) //1->Monthly, 2-> Weekly 3-> (defualt)
    //    recur_type= 0~4(int) //0=none, 1=day, 2=week, 3=month if schedule_mode=3
    //    recur_date= 0~6 | 1~31 (int) //recur_type=2 -> 0~6=Sun, Mon, Tue, Wed, Thu, Fri, Sat . recur_type=3 -> 1~31

    /* todo */
    r_info.execat = "1230";
    if(m_pReq->parameter("crond_type") == "1")
        r_info.recur_type = 3;
    else
        r_info.recur_type = 2;
    r_info.recur_date = m_pReq->parameter("day").toInt();
    SaveRemoteXml(r_info, 1);

    m_var = "N/A";

}

void RenderResponseAppMngm::generateGetModifyInfo() {
    QDomDocument doc;

    REMOTE_BACKUP_INFO r_info_ret;
    memset(&r_info_ret, 0, sizeof(REMOTE_BACKUP_INFO));
    GetRemoteTaskXmlValue(m_pReq->parameter("name").toLocal8Bit().data(), TAG_R_ALL, &r_info_ret);

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);

    QDomElement jobNameElement = doc.createElement("job_name");
    root.appendChild(jobNameElement);
    jobNameElement.appendChild(doc.createTextNode(m_pReq->parameter("name")));

    QDomElement serverTypeElement = doc.createElement("server_type");
    root.appendChild(serverTypeElement);
    serverTypeElement.appendChild(doc.createTextNode(QString::number(r_info_ret.server_type)));

    QDomElement backupTypeElement = doc.createElement("backup_type");
    root.appendChild(backupTypeElement);
    backupTypeElement.appendChild(doc.createTextNode(QString::number(r_info_ret.backup_type)));

    QDomElement scheduleModeElement = doc.createElement("schedule_mode");
    root.appendChild(scheduleModeElement);
    scheduleModeElement.appendChild(doc.createTextNode(QString::number(r_info_ret.schedule_mode)));

    QDomElement useSshElement = doc.createElement("use_ssh");
    root.appendChild(useSshElement);
    useSshElement.appendChild(doc.createTextNode(QString::number(r_info_ret.is_use_ssh)));

    QDomElement keepExistFileElement = doc.createElement("keep_exist_file");
    root.appendChild(keepExistFileElement);
    keepExistFileElement.appendChild(doc.createTextNode(QString::number(r_info_ret.is_keep_exist_file)));

    QDomElement incBackupElement = doc.createElement("inc_backup");
    root.appendChild(incBackupElement);
    incBackupElement.appendChild(doc.createTextNode(QString::number(r_info_ret.is_inc_enable)));

    QDomElement incNumberElement = doc.createElement("inc_number");
    root.appendChild(incNumberElement);
    incNumberElement.appendChild(doc.createTextNode(QString::number(r_info_ret.inc_number)));

    QDomElement scheduleElement = doc.createElement("schedule");
    root.appendChild(scheduleElement);
    scheduleElement.appendChild(doc.createTextNode(""));

    QDomElement remoteIpElement = doc.createElement("remote_ip");
    root.appendChild(remoteIpElement);
    remoteIpElement.appendChild(doc.createTextNode(QString(r_info_ret.remote_ip)));

    QDomElement localPathElement = doc.createElement("local_path");
    root.appendChild(localPathElement);
    localPathElement.appendChild(doc.createTextNode(QString(r_info_ret.local_path)));

    QDomElement rsyncUserElement = doc.createElement("rsync_user");
    root.appendChild(rsyncUserElement);
    rsyncUserElement.appendChild(doc.createTextNode(QString(r_info_ret.rsync_user)));

    QDomElement rsyncPwElement = doc.createElement("rsync_pw");
    root.appendChild(rsyncPwElement);
    rsyncPwElement.appendChild(doc.createTextNode(QString(r_info_ret.rsync_pwd)));

    QDomElement sshUserElement = doc.createElement("ssh_user");
    root.appendChild(sshUserElement);
    sshUserElement.appendChild(doc.createTextNode(QString(r_info_ret.ssh_user)));

    QDomElement sshPwElement = doc.createElement("ssh_pw");
    root.appendChild(sshPwElement);
    sshPwElement.appendChild(doc.createTextNode(QString(r_info_ret.ssh_pwd)));

    QDomElement remotePathElement = doc.createElement("remote_path");
    root.appendChild(remotePathElement);
    remotePathElement.appendChild(doc.createTextNode(QString(r_info_ret.remote_path)));

    FreeRemoteTask(&r_info_ret);
    m_var = doc.toString();

}

void RenderResponseAppMngm::generateDelSchedule() {

    DeleteRemoteTaskXml(m_pReq->parameter("name").toLocal8Bit().data());
    m_var = "N/A";

}

void RenderResponseAppMngm::generateEnableDisableSchedule() {

    StartStopRemoteTask(m_pReq->parameter("name").toLocal8Bit().data(),
                        m_pReq->parameter("enable").toLocal8Bit().data());
    m_var = "N/A";

}

void RenderResponseAppMngm::generateBackupNow() {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_START_REMOTE_BACKUP + " " + m_pReq->parameter("name"));
    m_var = "N/A";

}

void RenderResponseAppMngm::generateMtpInfoGet() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_mtp_info",
                                      true,
                                      ";");
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QStringList configTagNames(QStringList()
        << "backup_date" << "state" << "dest_dir" << "mtp_status");

    if( configTagNames.size() == apiOut.size() ) {
        for(int i=0; i < configTagNames.size(); i++) {
            QDomElement configContentElement = doc.createElement(configTagNames.value(i));
            root.appendChild(configContentElement);
            configContentElement.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseSysStatus::generateMtpInfoGet(): "
               "configTagNames size is not equal to apiOut size.");
    }
    m_var = doc.toString();

}

void RenderResponseAppMngm::generateUsbBackupInfoGet() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_usb_backup_info",
                                      true,
                                      ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.isEmpty() ? "0" : "1"));

    QStringList configTagNames(QStringList()
        << "front_usb" << "state" << "direction" << "source_dir"
        << "dest_dir" << "type" << "backup_status");

    if(!apiOut.isEmpty()) {
        if( configTagNames.size() == apiOut.size() ) {
            for(int i=0; i < configTagNames.size(); i++) {
                QDomElement configContentElement = doc.createElement(configTagNames.value(i));
                root.appendChild(configContentElement);
                configContentElement.appendChild(doc.createTextNode(apiOut.value(i)));
            }
        }
        else {
            //assert(0);
            tError("RenderResponseSysStatus::generateUsbBackupInfoGet(): "
                   "configTagNames size is not equal to apiOut size.");
        }
    }
    m_var = doc.toString();

}

void RenderResponseAppMngm::generateMtpInfoSet() {
    QDomDocument doc;

    QString paraEnable = m_pReq->parameter("f_enable");
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                          " service_set_mtp_backups_cfg " + allParametersToString(),
                                      true,
                                      ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(paraEnable));

    /* todo: Volume_1 is /mnt/HD/HD_a2 ?? */
//    QString dest = "/mnt/HD/HD_a2";
//    if(paraDestDir == "Volume_2")
//        dest = "/mnt/HD/HD_b2";

    QDomElement destElement = doc.createElement("dest");
    root.appendChild(destElement);
    destElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAppMngm::generateUsbBackupInfoSet() {
    QDomDocument doc;

//    QString paraEnable = m_pReq->parameter("f_enable");
//    QString paraDirection = m_pReq->parameter("f_direction");
//    QString paraSourceDir = m_pReq->parameter("f_source_dir");
//    QString paraDestDir = m_pReq->parameter("f_dest_dir");
//    QString paraType = m_pReq->parameter("f_type");

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API +
                                      " service_set_usb_backup_cfg " + allParametersToString(), true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseAppMngm::generateGetUsbMappingInfo() {
    QDomDocument doc;

    QStringList apiOut = getAPIFileOut(USB_SHARE_INFO_FILE, true);

    QDomElement root = doc.createElement("mapping_info");
    doc.appendChild(root);
    QDomElement itemElement = doc.createElement("item");
    root.appendChild(itemElement);
    QDomElement dataElement = doc.createElement("data");
    itemElement.appendChild(dataElement);
    dataElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

