#include "RenderResponse.h"
#include "AppDefine.h"

RenderResponse::RenderResponse(QVariantMap &map, CGI_COMMAND cmd)
    : m_session("")
    , m_loginStatus(0)
{
    m_cmd = cmd;
    m_renderType = RENDER_TYPE_UNKNOWN;
    m_pMap = &map;
}

RenderResponse::~RenderResponse() {
}

RENDER_TYPE RenderResponse::preRender() {

    if(!m_pMap)
        return RENDER_TYPE_UNKNOWN;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_VOLUME_STATUS:
        generateVolumeStatus(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_FMT_GET_SYNC_SATTE:
        generateFMTGetSyncState(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_FMT_GET_AUTO_REBUILD_INFO:
        generateFMTGetAutoRebuildInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_AJAXPLORER_STOP:
        generateAJAXPlorerStop(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_FMT_CREATE_DISKMGR:
        generateFMTCreateDiskMGR(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SMART_HD_LIST:
        generateSmartHDList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SMART_XML_CREATE_TEST_LIST:
        generateCreateTestList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SMART_SCHEDULE_LIST:
        generateSmartScheduleList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SMART_GET_TEST_STATUS:
        generateGetTestStatus(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SMART_SET_SCHEDULE:
    {
        if(m_pMap->contains("f_flag")) {
            QString paraFlag = m_pMap->value("f_flag").toString();
            if(paraFlag.compare("1") == 0)
                generateSmartSetSchedule(doc);
            else if(paraFlag.compare("0") == 0)
                generateSmartDelSchedule(doc);
        }
        m_renderType = RENDER_TYPE_XML;
        break;
    }
    case CMD_SCANDISK_INFO:
        generateScanDiskInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SMART_TEST_START:
        generateSmartTestStart(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_CHECK_DISK_REMOUNT_STATUS:
        generateCheckDiskRemountState(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SCANDISK_RUN_E2FSCK:
        generateScanDiskRunE2fsck(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SCANDISK_FINISH:
        generateScanDiskFinish(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_CGI_IS_BUILD_IN_LANGUAGE:
        generateIsBuildInLanguage(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_CGI_GET_USER_LANGUAGE:
        generateGetUserLanguage(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_CGI_GET_SSL_INFO:
        generateGetSslInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_UI_CHECK_WTO:
        generateUICheckWto(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_FW_STATUS:
        generateFWStatus(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_LOGIN:
        generateLogin(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_LOGOUT:
        generateLogout(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

    return m_renderType;
}

QStringList RenderResponse::getAPIStdOut(QString apiCmd) {
    QStringList ret;
    char *buff;
    size_t len = 0;
    FILE *fd = popen(apiCmd.toLocal8Bit(), "r");
    while((getline(&buff, &len, fd)) != -1)
        ret << buff;
    pclose(fd);

    return ret;
}

QString RenderResponse::getAPIStdOutOneLine(QString apiCmd) {
    QString firstLine;
    QStringList list = getAPIStdOut(apiCmd);
    if(!list.isEmpty())
        firstLine = list.at(0);
    return firstLine;
}

void RenderResponse::generateVolumeStatus(QDomDocument &doc) {
//    QString paraFlag;
//    if(m_pMap->contains("f_flag"))
//        paraFlag = m_pMap->value("f_flag").toString();

    QString apiOut = getAPIStdOutOneLine(API_PATH + "sysapi_dsk -g volume_status");

    QStringList fields = apiOut.split(",");
    if(fields.size() < 2)
        return;

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("flag");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode(fields.at(0));
    tag1.appendChild(t1);
    QDomElement tag2 = doc.createElement("state");
    root.appendChild(tag2);
    QDomText t2 = doc.createTextNode(fields.at(1));
    tag2.appendChild(t2);
}

void RenderResponse::generateFMTGetSyncState(QDomDocument &doc) {

    QString apiOut = getAPIStdOutOneLine(API_PATH + "sysapi_dsk -g sync_state");

    QStringList fields = apiOut.split(",");
    if(fields.size() < 2)
        return;

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("res");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode(fields.at(0));
    tag1.appendChild(t1);
    QDomElement tag2 = doc.createElement("wait_sync");
    root.appendChild(tag2);
    QDomText t2 = doc.createTextNode(fields.at(1));
    tag2.appendChild(t2);
}

void RenderResponse::generateFMTGetAutoRebuildInfo(QDomDocument &doc) {

    QString apiOut = getAPIStdOutOneLine(API_PATH + "sysapi_dsk -g auto_sync");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("auto_sync");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode(apiOut);
    tag1.appendChild(t1);
}

/* todo */
void RenderResponse::generateAJAXPlorerStop(QDomDocument &doc) {

//#ifndef SIMULATOR_MODE
//    QString apiOut = getAPIStdOut(API_PATH + "sysapi_dsk -s ajaxplorer stop");
//#else
//    QString apiOut = "1";
//#endif

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("res");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode("1");
    tag1.appendChild(t1);
}

/* todo */
void RenderResponse::generateFMTCreateDiskMGR(QDomDocument &doc) {
    if(!m_pMap)
        return;

    QString paraCreateType;
    QString paraCreateVolumeInfo;
    QString paraAutoSync;

    if(m_pMap->contains("f_create_type"))
        paraCreateType = m_pMap->value("f_create_type").toString();
    if(m_pMap->contains("f_create_volume_info"))
        paraCreateVolumeInfo = m_pMap->value("f_create_volume_info").toString();
    if(m_pMap->contains("f_auto_sync"))
        paraAutoSync = m_pMap->value("f_auto_sync").toString();

    QStringList paraList = paraCreateVolumeInfo.split("%2C");
    if(paraList.size() != 30) {
        return;
    }
    else {
        QStringList paraSubList1 = paraList.mid(0, 15);
        QStringList paraSubList2 = paraList.mid(15, 15);
    }

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("res");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode("1");
    tag1.appendChild(t1);
}

/* todo */
void RenderResponse::generateSmartHDList(QDomDocument &doc) {

    if(!m_pMap)
        return;

    QString paraPage;
    QString paraRp;
    QString paraQuery;
    QString paraQtype;
    QString paraField;
    QString paraUser;

    if(m_pMap->contains("page"))
        paraPage = m_pMap->value("page").toString();
    if(m_pMap->contains("rp"))
        paraRp = m_pMap->value("rp").toString();
    if(m_pMap->contains("query"))
        paraQuery = m_pMap->value("query").toString();
    if(m_pMap->contains("qtype"))
        paraQtype = m_pMap->value("qtype").toString();
    if(m_pMap->contains("f_field"))
        paraField = m_pMap->value("f_field").toString();
    if(m_pMap->contains("user"))
        paraUser = m_pMap->value("user").toString();

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QDomElement rowElement1 = doc.createElement("row");
    root.appendChild(rowElement1);
    rowElement1.setAttribute("id", "1");

    QDomElement cellElement1 = doc.createElement("cell");
    rowElement1.appendChild(cellElement1);
    QDomElement inputElement1 = doc.createElement("input");
    cellElement1.appendChild(inputElement1);
    inputElement1.setAttribute("type", "checkbox");
    inputElement1.setAttribute("value", "0,sda,S1F0HDP7");
    inputElement1.setAttribute("id", "smart_hdd_num_0");
    inputElement1.setAttribute("name", "smart_hdd_num");
    QDomElement cellElement2 = doc.createElement("cell");
    rowElement1.appendChild(cellElement2);
    cellElement2.appendChild(doc.createTextNode("Disk1"));
    QDomElement cellElement3 = doc.createElement("cell");
    rowElement1.appendChild(cellElement3);
    cellElement3.appendChild(doc.createTextNode("Seagate"));
    QDomElement cellElement4 = doc.createElement("cell");
    rowElement1.appendChild(cellElement4);
    cellElement4.appendChild(doc.createTextNode("ST3000DM001-9YN166"));
    QDomElement cellElement5 = doc.createElement("cell");
    rowElement1.appendChild(cellElement5);
    cellElement5.appendChild(doc.createTextNode("-"));
    QDomElement cellElement6 = doc.createElement("cell");
    rowElement1.appendChild(cellElement6);
    cellElement6.appendChild(doc.createTextNode("-"));

    QDomElement rowElement2 = doc.createElement("row");
    root.appendChild(rowElement2);
    rowElement2.setAttribute("id", "2");

    QDomElement cellElement7 = doc.createElement("cell");
    rowElement2.appendChild(cellElement7);
    QDomElement inputElement2 = doc.createElement("input");
    cellElement7.appendChild(inputElement2);
    inputElement2.setAttribute("type", "checkbox");
    inputElement2.setAttribute("value", "1,sdb,S1F0HDP9");
    inputElement2.setAttribute("id", "smart_hdd_num_0");
    inputElement2.setAttribute("name", "smart_hdd_num");
    QDomElement cellElement8 = doc.createElement("cell");
    rowElement2.appendChild(cellElement8);
    cellElement8.appendChild(doc.createTextNode("Disk2"));
    QDomElement cellElement9 = doc.createElement("cell");
    rowElement2.appendChild(cellElement9);
    cellElement9.appendChild(doc.createTextNode("Seagate"));
    QDomElement cellElement10 = doc.createElement("cell");
    rowElement2.appendChild(cellElement10);
    cellElement10.appendChild(doc.createTextNode("ST3000DM001-9YN166"));
    QDomElement cellElement11 = doc.createElement("cell");
    rowElement2.appendChild(cellElement11);
    cellElement11.appendChild(doc.createTextNode("-"));
    QDomElement cellElement12 = doc.createElement("cell");
    rowElement2.appendChild(cellElement12);
    cellElement12.appendChild(doc.createTextNode("-"));

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("2"));

}

/* todo */
void RenderResponse::generateCreateTestList(QDomDocument &doc) {
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement sendElement = doc.createElement("send_mail");
    root.appendChild(sendElement);
    sendElement.appendChild(doc.createTextNode("0"));
    QDomElement smartElement = doc.createElement("smart_mail");
    root.appendChild(smartElement);
    smartElement.appendChild(doc.createTextNode("0"));
}

/* todo */
void RenderResponse::generateSmartScheduleList(QDomDocument &doc) {

    if(!m_pMap)
        return;

    QString paraPage;
    QString paraRp;
    QString paraQuery;
    QString paraQtype;
    QString paraField;
    QString paraUser;

    if(m_pMap->contains("page"))
        paraPage = m_pMap->value("page").toString();
    if(m_pMap->contains("rp"))
        paraRp = m_pMap->value("rp").toString();
    if(m_pMap->contains("query"))
        paraQuery = m_pMap->value("query").toString();
    if(m_pMap->contains("qtype"))
        paraQtype = m_pMap->value("qtype").toString();
    if(m_pMap->contains("f_field"))
        paraField = m_pMap->value("f_field").toString();
    if(m_pMap->contains("user"))
        paraUser = m_pMap->value("user").toString();

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QDomElement rowElement1 = doc.createElement("row");
    root.appendChild(rowElement1);
    rowElement1.setAttribute("id", "1");

    QDomElement cellElement1 = doc.createElement("cell");
    rowElement1.appendChild(cellElement1);
    cellElement1.appendChild(doc.createTextNode("S.M.A.R.T - Quick"));
    QDomElement cellElement2 = doc.createElement("cell");
    rowElement1.appendChild(cellElement2);
    cellElement2.appendChild(doc.createTextNode("Disk1,Disk2"));
    QDomElement cellElement3 = doc.createElement("cell");
    rowElement1.appendChild(cellElement3);
    cellElement3.appendChild(doc.createTextNode("MON 17:00 / Weekly"));
    QDomElement cellElement4 = doc.createElement("cell");
    rowElement1.appendChild(cellElement4);
    QDomElement aElement = doc.createElement("a");
    rowElement1.appendChild(aElement);
    aElement.setAttribute("href", "javascript:onclick=create_schedule_wait(0)><IMG border='0' src='/web/images/delete_over.png'");

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("1"));
}

/* todo */
void RenderResponse::generateGetTestStatus(QDomDocument &doc) {
    QDomElement root = doc.createElement("Button");
    doc.appendChild(root);
    QDomElement stateElement = doc.createElement("State");
    root.appendChild(stateElement);
    stateElement.appendChild(doc.createTextNode("0:"));
}

/* todo */
void RenderResponse::generateSmartSetSchedule(QDomDocument &doc) {

    if(!m_pMap)
        return;

    QString paraDevice;
    QString paraType;
    QString paraHour;
    QString paraMin;
    QString paraWeekly;
    QString paraDay;
    QString paraTestType;
    QString paraSlot;
    QString paraMailFlag;

    if(m_pMap->contains("f_device"))
        paraDevice = m_pMap->value("f_device").toString();
    if(m_pMap->contains("f_type"))
        paraType = m_pMap->value("f_type").toString();
    if(m_pMap->contains("f_hour"))
        paraHour = m_pMap->value("f_hour").toString();
    if(m_pMap->contains("f_min"))
        paraMin = m_pMap->value("f_min").toString();
    if(m_pMap->contains("f_weekly"))
        paraWeekly = m_pMap->value("f_weekly").toString();
    if(m_pMap->contains("f_day"))
        paraDay = m_pMap->value("f_day").toString();
    if(m_pMap->contains("f_test_type"))
        paraTestType = m_pMap->value("f_test_type").toString();
    if(m_pMap->contains("f_slot"))
        paraSlot = m_pMap->value("f_slot").toString();
    if(m_pMap->contains("f_mail_flag"))
        paraMailFlag = m_pMap->value("f_mail_flag").toString();

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement cmdElement = doc.createElement("cmd");
    root.appendChild(cmdElement);
    cmdElement.appendChild(doc.createTextNode("1:short:0 :00:00:1:06"));
}

/* todo */
void RenderResponse::generateSmartDelSchedule(QDomDocument &doc) {
    if(!m_pMap)
        return;

    QString paraMailFlag;
    if(m_pMap->contains("f_mail_flag"))
        paraMailFlag = m_pMap->value("f_mail_flag").toString();

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement cmdElement = doc.createElement("cmd");
    root.appendChild(cmdElement);
    cmdElement.appendChild(doc.createTextNode("null"));
}

/* todo */
void RenderResponse::generateSmartTestStart(QDomDocument &doc) {

    if(!m_pMap)
        return;

    QString paraDevice;
    QString paraType;
    QString paraMailFlag;

    if(m_pMap->contains("f_device"))
        paraDevice = m_pMap->value("f_device").toString();
    if(m_pMap->contains("f_type"))
        paraType = m_pMap->value("f_type").toString();
    if(m_pMap->contains("f_mail_flag"))
        paraMailFlag = m_pMap->value("f_mail_flag").toString();

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
}

void RenderResponse::generateScanDiskInfo(QDomDocument &doc) {
    QStringList apiOutList = getAPIStdOut(API_PATH + "sysapi_dsk -g scandsk_info");

    QStringList line1 = apiOutList.at(0).split(",");
    QStringList line2 = apiOutList.at(1).split(",");
    QStringList line3 = apiOutList.at(2).split(",");
    if(line1.size() < 2 || line2.size() < 2 || line3.size() < 2)
        return;

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

    for (int i=0; i<apiOutList.size(); i++) {
        QStringList line = apiOutList.at(i).split(",");
        if(line.size() < 2)
            continue;
        QDomElement itemElement1 = doc.createElement("item");
        root.appendChild(itemElement1);
        QDomElement optElement1 = doc.createElement("opt_value");
        itemElement1.appendChild(optElement1);
        optElement1.appendChild(doc.createTextNode(line.at(0)));
        QDomElement guiElement1 = doc.createElement("gui_value");
        itemElement1.appendChild(guiElement1);
        guiElement1.appendChild(doc.createTextNode(line.at(1)));
    }
}

void RenderResponse::generateCheckDiskRemountState(QDomDocument &doc) {
    QString apiOut = getAPIStdOutOneLine(API_PATH + "sysapi_dsk -g dsk_remount_state");
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut));
}

void RenderResponse::generateScanDiskRunE2fsck(QDomDocument &doc) {
    QDomElement root = doc.createElement("script");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode("location.href='/web/dsk_mgr/hd_scandisk_state.html'"));
}

void RenderResponse::generateScanDiskFinish(QDomDocument &doc) {
    QString apiOut = getAPIStdOutOneLine(API_PATH + "sysapi_dsk -g scandsk_finish");
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut));
}

/***** Login/Logout *****/

void RenderResponse::generateIsBuildInLanguage(QDomDocument &doc) {

    QDomElement root = doc.createElement("flag");
    doc.appendChild(root);

    QString val = getAPIStdOutOneLine(API_PATH + "sysapi_home -g build_in_language");

    root.appendChild(doc.createTextNode(val));
}

void RenderResponse::generateGetUserLanguage(QDomDocument &doc) {
    QDomElement root = doc.createElement("language");
    doc.appendChild(root);

    QString val = getAPIStdOutOneLine(API_PATH + "sysapi_home -g cgi_get_user_language");

    root.appendChild(doc.createTextNode(val));
}

void RenderResponse::generateGetSslInfo(QDomDocument &doc) {
    QString apiOut = getAPIStdOutOneLine(API_PATH + "sysapi_home -g ssl_info");

    QStringList fields = apiOut.split(",");
    if(fields.size() < 2)
        return;

    QDomElement root = doc.createElement("ssl_info");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode(fields.at(0)));
    QDomElement portElement = doc.createElement("port");
    root.appendChild(portElement);
    portElement.appendChild(doc.createTextNode(fields.at(1)));
}

void RenderResponse::generateUICheckWto(QString &str) {
    QString apiOut = getAPIStdOutOneLine(API_PATH + "sysapi_home -g ui_check_wto");
    str = apiOut;
}

void RenderResponse::generateFWStatus(QString &str) {
    QString apiOut = getAPIStdOutOneLine(API_PATH + "sysapi_home -g fw_status");
    str = apiOut;
}

void RenderResponse::generateLogin(QString &str) {
    if(!m_pMap)
        return;

    QString paraUsername;
    QString paraPwd;
    QString paraPort;
    QString paraType;
    QString paraFUsername;
    QString paraPrePwd;
    QString paraSsl;
    QString paraC1;
    QString paraSslPort;

    if(m_pMap->contains("username"))
        paraUsername = m_pMap->value("username").toString();
    if(m_pMap->contains("pwd"))
        paraPwd = m_pMap->value("pwd").toString();
    if(m_pMap->contains("port"))
        paraPort = m_pMap->value("port").toString();
    if(m_pMap->contains("f_type"))
        paraType = m_pMap->value("f_type").toString();
    if(m_pMap->contains("f_username"))
        paraFUsername = m_pMap->value("f_username").toString();
    if(m_pMap->contains("pre_pwd"))
        paraPrePwd = m_pMap->value("pre_pwd").toString();
    if(m_pMap->contains("ssl"))
        paraSsl = m_pMap->value("ssl").toString();
    if(m_pMap->contains("C1"))
        paraC1 = m_pMap->value("C1").toString();
    if(m_pMap->contains("ssl_port"))
        paraSslPort = m_pMap->value("ssl_port").toString();

    QString apiOut = getAPIStdOutOneLine(API_PATH + "sysapi_home -g login " + paraUsername + " " + paraPwd);

    if(paraSsl.compare("1") == 0) {
#ifndef SIMULATOR_MODE
        QString sslEnableOut = getAPIStdOutOneLine("nas_cfg -s web ssl_enable 1");
        QString sslPortOut = getAPIStdOutOneLine("nas_cfg -s web ssl_port 443");

        //todo: restart.
#endif
    }

    if(paraC1.compare("ON") == 0) {
        m_session = paraUsername;
    }

    if(apiOut.compare("1") == 0) {
        m_loginStatus = 1;
    }
}

void RenderResponse::generateLogout(QString &str) {
    if(!m_pMap)
        return;

    QString paraUsername;
    QString paraOS;

    if(m_pMap->contains("name"))
        paraUsername = m_pMap->value("name").toString();
    if(m_pMap->contains("os"))
        paraOS = m_pMap->value("os").toString();

    QString apiOut = getAPIStdOutOneLine(API_PATH + "sysapi_home -s logout " + paraUsername);
    m_loginStatus = -1;

}
