#include "RenderResponseSysMngm.h"

#include <QProcess>
#include <QTimeZone>
#include <QFileInfo>
#include <QDir>
#include <QTimer>
#include <QSettings>
#include <TAppSettings>
#include <TWebApplication>
#include <unistd.h>

RenderResponseSysMngm::RenderResponseSysMngm(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseSysMngm::~RenderResponseSysMngm() {
}

void RenderResponseSysMngm::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_GET_TIME:
        generateGetTime();
        break;
    case CMD_MANUAL_TIME:
        generateManualTime();
        break;
    case CMD_TIMEZONE:
        generateTimezone();
        break;
    case CMD_NTP_TIME:
        generateNtpTime();
        break;
    case CMD_GET_TIME_STATUS:
        generateGetTimeStatus();
        break;
    case CMD_GET_DEVICE_INFO:
        generateGetDeviceInfo();
        break;
    case CMD_DEVICE:
        generateDevice();
        break;
    case CMD_DETECT_DANGEROUS:
        generateDetectDangerous();
        break;
    case CMD_GET_IDEL:
        generateGetIdle();
        break;
    case CMD_GET_TEMPERATURE:
        generateGetTemperature();
        break;
    case CMD_GET_RESTORE_STATUS:
        generateGetRestoreStatus();
        break;
    case CMD_RESTART:
        generateRestart();
        break;
    case CMD_RESTORE:
        generateRestore();
        break;
    case CMD_SHUTDOWN:
        generateShutdown();
        break;
    case CMD_IDLE:
        generateIdle();
        break;
    case CMD_TEMPERATURE:
        generateTemperature();
        break;
    case CMD_BACKUP_CONF:
        generateBackupConf();
        break;
    case CMD_RESTORE_CONF:
        generateRestoreConf();
        break;

    case CMD_GET_POWER_MGR:
        generateGetPowerMgr();
        break;
    case CMD_POWER_MANAGEMENT:
        generatePowerManagement();
        break;
    case CMD_POWER_RECV:
        generatePowerRecovery();
        break;
    case CMD_FAN:
        generateFan();
        break;
    case CMD_POWER_OFF_SCH:
        generatePowerOffSchedule();
        break;

    case CMD_GET_EMAIL_XML:
        generateGetEmailXml();
        break;
    case CMD_GET_EVENT_XML:
        generateGetEventXml();
        break;
    case CMD_EMAIL_EVENT:
        generateEmailEvent();
        break;
    case CMD_EMAIL:
        generateEmail();
        break;
    case CMD_EMAIL_TEST:
        generateEmailTest();
        break;
    case CMD_EMAIL_TEST_RESULT:
        generateEmailTestResult();
        break;
    case CMD_EMAIL_CLEAR:
        generateEmailClear();
        break;

    case CMD_SMS_ADD:
        generateSmsAdd();
        break;
    case CMD_SMS_MODIFY:
        generateSmsModify();
        break;
    case CMD_SMS_TEST:
        generateSmsTest();
        break;
    case CMD_SMS_TEST_RESULT:
        generateSmsTestResult();
        break;
    case CMD_SMS_DEL:
        generateSmsDel();
        break;

    case CMD_LOG_SYSTEM:
        generateLogSystem();
        break;
    case CMD_GET_LOG_INFO:
        generateGetLogInfo();
        break;
    case CMD_LOG_SERVER:
        generateLogServer();
        break;
    case CMD_SEND_LOG_TEST:
        generateSendLogTest();
        break;
    case CMD_LOG_BACKUP:
        generateLogBackup();
        break;
    case CMD_LOG_CLEAR:
        generateLogClear();
        break;

    case CMD_GUI_UPS_INFO:
        generateUpsInfo();
        break;
    case CMD_GUI_UPS_MATER_LIST:
        generateUpsMaterList();
        break;
    case CMD_GUI_UPS_STATUS_INFO:
        generateUpsStatusInfo();
        break;
    case CMD_GUI_UPS_ADD:
        generateUpsAdd();
        break;
    case CMD_GUI_UPS_SLAVE_SETTING:
        generateUpsSlaveSetting();
        break;
    case CMD_GUI_UPS_PS:
        generateUpsPs();
        break;
    case CMD_USB_STORAGE_UMOUNT:
        generateUsbStorageUmount();
        break;
    case CMD_USB_PRINTER_CLEAR:
        generateUsbPrinterClear();
        break;

    case CMD_FIRM_V_XML:
        generateFirmVXml();
        break;
    case CMD_CHECK_POWER_SCH:
        generateCheckPowerSch();
        break;
    case CMD_FIRMWARE_INIT_UPLOAD:
        generateFirmwareInitUpload();
        break;
    case CMD_FIRMWARE_UPLOAD:
        generateFirmwareUpload();
        break;
    case CMD_GET_PERCENTAGE:
        generateGetPercentage();
        break;
    case CMD_GET_FIRMWARE_VERIFY:
        generateGetFirmwareVerify();
        break;
    case CMD_GET_UP_FW:
        generateGetUpFw();
        break;
    case CMD_REBOOT:
        generateReboot();
        break;
    case CMD_GET_LIVE_FIRM:
        generateGetLiveFirm();
        break;
    case CMD_SET_LIVE_FIRM:
        generateSetLiveFirm();
        break;
    case CMD_CHECK_LIVE_FIRM:
        generateCheckLiveFirm();
        break;
    case CMD_GET_LIVE_FIRM_VER:
        generateGetLiveFirmVer();
        break;
    case CMD_FIRMWARE_DOWNLOAD:
        generateFirmwareDownload();
        break;

    default:
        break;
    }

}

void RenderResponseSysMngm::generateGetTime() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");
    //QDateTime currentTime = QDateTime::currentDateTime();

    QDomElement root = doc.createElement("time");
    doc.appendChild(root);
    QDomElement timezoneElement = doc.createElement("timezone");
    root.appendChild(timezoneElement);
    timezoneElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement ntpEnableElement = doc.createElement("ntp_enable");
    root.appendChild(ntpEnableElement);
    ntpEnableElement.appendChild(doc.createTextNode(apiOut.value(1)));
    QDomElement ntpServerElement = doc.createElement("ntp_server");
    root.appendChild(ntpServerElement);
    ntpServerElement.appendChild(doc.createTextNode(apiOut.value(2)));
    QDomElement yearElement = doc.createElement("year");
    root.appendChild(yearElement);
    yearElement.appendChild(doc.createTextNode(apiOut.value(3)));
    QDomElement monElement = doc.createElement("mon");
    root.appendChild(monElement);
    monElement.appendChild(doc.createTextNode(apiOut.value(4)));
    QDomElement dayElement = doc.createElement("day");
    root.appendChild(dayElement);
    dayElement.appendChild(doc.createTextNode(apiOut.value(5)));

    QDomElement hourElement = doc.createElement("hour");
    root.appendChild(hourElement);
    hourElement.appendChild(doc.createTextNode(apiOut.value(6)));
    QDomElement minElement = doc.createElement("min");
    root.appendChild(minElement);
    minElement.appendChild(doc.createTextNode(apiOut.value(7)));
    QDomElement secElement = doc.createElement("sec");
    root.appendChild(secElement);
    secElement.appendChild(doc.createTextNode(apiOut.value(8)));

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateManualTime() {
    QString paraYear = m_pReq->allParameters().value("f_year").toString();
    QString paraMonth = m_pReq->allParameters().value("f_month").toString();
    QString paraDay = m_pReq->allParameters().value("f_day").toString();
    QString paraHour = m_pReq->allParameters().value("f_hour").toString();
    QString paraMin = m_pReq->allParameters().value("f_min").toString();
    QString paraSec = m_pReq->allParameters().value("f_sec").toString();

    QDateTime manualTime = QDateTime(QDate(paraYear.toInt(), paraMonth.toInt(), paraDay.toInt()),
            QTime(paraHour.toInt(), paraMin.toInt(), paraSec.toInt()));
    QDateTime currentTime = QDateTime::currentDateTime();
    //setSessionDiff(manualTime.toTime_t() - currentTime.toTime_t());

    tDebug("set date/time: %s", manualTime.toString("yyyy-MM-dd hh:mm:ss").toLocal8Bit().data());
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " set " + manualTime.toString("yyyy-MM-dd hh:mm:ss"), true);
    if(m_pSession)
        m_pSession->insert("time", QDateTime::currentDateTime());


}

void RenderResponseSysMngm::generateTimezone() {

    QString paraTimezone = m_pReq->allParameters().value("f_timezone").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_TIMEZONE_API + " " + paraTimezone, true);
    //setSessionDiff(currentTimeBefore.toTime_t() - currentTimeAfter.toTime_t());

    if(m_pSession)
        m_pSession->insert("time", QDateTime::currentDateTime());
}

void RenderResponseSysMngm::generateNtpTime() {
    QString paraNtpEnable = m_pReq->allParameters().value("f_ntp_enable").toString();
    QString paraNtpServer = m_pReq->allParameters().value("f_ntp_server").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_NTP_API +
                                      " set " + paraNtpEnable + " " + paraNtpServer, true);

    if(m_pSession)
        m_pSession->insert("time", QDateTime::currentDateTime());
}

void RenderResponseSysMngm::generateGetTimeStatus() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_NTP_API + " status", true, ";");

    QDomElement root = doc.createElement("time");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement updateTimeElement = doc.createElement("update_time");
    root.appendChild(updateTimeElement);
    updateTimeElement.appendChild(doc.createTextNode(apiOut.value(1)));

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateGetDeviceInfo() {

    QDomDocument doc;
    QStringList arg = QStringList() << "get";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DEVICE_API, arg, true, ";");

    QDomElement root = doc.createElement("device_info");
    doc.appendChild(root);
    QDomElement nameElement = doc.createElement("name");
    root.appendChild(nameElement);
    nameElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement workgroupElement = doc.createElement("workgroup");
    root.appendChild(workgroupElement);
    workgroupElement.appendChild(doc.createTextNode(apiOut.value(1)));
    QDomElement descriptionElement = doc.createElement("description");
    root.appendChild(descriptionElement);
    descriptionElement.appendChild(doc.createTextNode(apiOut.value(2)));

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateDevice() {
    QString paraHostname = m_pReq->allParameters().value("hostname").toString();
    QString paraWorkgroup = m_pReq->allParameters().value("workgroup").toString();
    QString paraDescription = m_pReq->allParameters().value("description").toString();
    QStringList arg = QStringList() << "set" << paraHostname << paraWorkgroup << paraDescription;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DEVICE_API, arg, true);
}

void RenderResponseSysMngm::generateDetectDangerous() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_POWER_API + " status", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseSysMngm::generateGetIdle() {
    QSettings settings(Tf::app()->appSettingsFilePath(), QSettings::NativeFormat);
    int idleTimeInMin = settings.value("Session.LifeTime").toInt() / 60;
    m_var = QString::number(idleTimeInMin);
}

void RenderResponseSysMngm::generateGetTemperature() {

    QDomDocument doc;

    if(m_pReq->header().path().contains("status_mgr.cgi")) {
        QStringList arg = QStringList() << "system_get_system_temperature";
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

        QDomElement root = doc.createElement("status");
        doc.appendChild(root);
        QDomElement temperatureElement = doc.createElement("temperature");
        root.appendChild(temperatureElement);
        temperatureElement.appendChild(doc.createTextNode(apiOut.value(0)));
    }
    else {
        QMap<QString, QString> mailEventInfo = getNasCfg("mail_event");

        QDomElement root = doc.createElement("mail_info");
        doc.appendChild(root);
        QDomElement kotElement = doc.createElement("kot");
        root.appendChild(kotElement);
        kotElement.appendChild(doc.createTextNode(mailEventInfo.value("hdd_temperature_kot")));
        QDomElement temperatureElement = doc.createElement("temperature");
        root.appendChild(temperatureElement);
        temperatureElement.appendChild(doc.createTextNode(mailEventInfo.value("hdd_temperature_temperature")));
    }

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateGetRestoreStatus() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_RESTORE_API + " status", true);
    m_var = apiOut.value(0);
}

void RenderResponseSysMngm::generateRestart() {
    startDetached(API_PATH + SCRIPT_POWER_API, QStringList() << "restart");
    m_var = "/web/dsk_mgr/wait.html";
}

void RenderResponseSysMngm::generateRestore() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_RESTORE_API + " resetdef", true);
    m_var = "/web/dsk_mgr/wait.html";
}

void RenderResponseSysMngm::generateShutdown() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_POWER_API + " web_off");
}

void RenderResponseSysMngm::generateIdle() {
    QString paraIdle = m_pReq->allParameters().value("f_idle").toString();
    int idleTimeInSec = paraIdle.toInt() * 60;
    setNasCfg("General", "Session.LifeTime", QString::number(idleTimeInSec), Tf::app()->appSettingsFilePath(), "");
    QStringList apiOut = getAPIStdOut(API_PATH + TREEFROG_MANAGER + " -k restart");
}

void RenderResponseSysMngm::generateTemperature() {
    QString paraTemperature = m_pReq->allParameters().value("f_temperature").toString();
    QString paraKoc = m_pReq->allParameters().value("f_kot").toString();

    QMap<QString, QString> map;
    map.insert("hdd_temperature_temperature", paraTemperature);
    map.insert("hdd_temperature_kot", paraKoc);
    if(!setNasCfg("mail_event", map))
        tDebug("setNasCfg mail_event failed");
}

void RenderResponseSysMngm::generateBackupConf() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_CONFIG_API + " save", true);
    QString filePath = apiOut.value(0);
    tDebug("file: %s", filePath.toLocal8Bit().data());
    QFileInfo file(filePath);
    if(file.exists() && file.isFile())
        m_var = filePath;
}

void RenderResponseSysMngm::generateRestoreConf() {

    if(!m_pReq->multipartFormData().isEmpty()) {
        if(m_pReq->multipartFormData().renameUploadedFile("file", USER_IMPORT_FILE, true)) {
            QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_CONFIG_API + " load", true);
            if(apiOut.value(0).compare("0") == 0) {
                m_var = "<script>parent.location.href='/web/dsk_mgr/wait.html'</script>";
                startDetached(API_PATH + SCRIPT_POWER_API, QStringList() << "restart");
            }
            else {
                m_var = "/web/system_mgr/system.html";
                emit typeChanged(RENDER_TYPE_REDIRECT);
            }
        }
    }

}

void RenderResponseSysMngm::generateGetPowerMgr() {

    QDomDocument doc;
    QStringList arg = QStringList() << "system_powermgr_info";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("power");
    doc.appendChild(root);

    for(int i = 0; i < apiOut.size(); i++) {
        QStringList schItems = apiOut.value(i).split(";").mid(0, 7);
        QString schStr = "sch_on";
        if(i == 1)
            schStr = "sch_off";

        int j = 0;
        for(QString e : schItems) {

            QDomElement schElement = doc.createElement(schStr);
            root.appendChild(schElement);

            QDomElement enableElement = doc.createElement("enable");
            schElement.appendChild(enableElement);
            enableElement.appendChild(doc.createTextNode(e.split(",").value(0)));

            if(i == 0) {
                QDomElement wdayElement = doc.createElement("wday");
                schElement.appendChild(wdayElement);
                wdayElement.appendChild(doc.createTextNode(QString::number(j)));
            }

            QDomElement hourElement = doc.createElement("hour");
            schElement.appendChild(hourElement);
            hourElement.appendChild(doc.createTextNode(e.split(",").value(1)));

            QDomElement minuteElement = doc.createElement("minute");
            schElement.appendChild(minuteElement);
            minuteElement.appendChild(doc.createTextNode(e.split(",").value(2)));
            j++;
        }
        if(i == 0) {
            QDomElement hibernationEnableElement = doc.createElement("hdd_hibernation_enable");
            root.appendChild(hibernationEnableElement);
            hibernationEnableElement.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(7)));

            QDomElement turnOffTimeElement = doc.createElement("turn_off_time");
            root.appendChild(turnOffTimeElement);
            turnOffTimeElement.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(8)));

            QDomElement recvEnableElement = doc.createElement("recovery_enable");
            root.appendChild(recvEnableElement);
            recvEnableElement.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(9)));
        }
        else if(i == 1) {
            QDomElement powerOffEnableElement = doc.createElement("power_off_enable");
            root.appendChild(powerOffEnableElement);
            powerOffEnableElement.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(7)));

            QDomElement fanElement = doc.createElement("fan");
            root.appendChild(fanElement);
            fanElement.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(8)));

            QDomElement ledEnableElement = doc.createElement("led_enable");
            root.appendChild(ledEnableElement);
            ledEnableElement.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(9)));

            QDomElement ledTimeElement = doc.createElement("led_time");
            root.appendChild(ledTimeElement);
            ledTimeElement.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(10)));
        }
    }
    m_var = doc.toString();

}

void RenderResponseSysMngm::generatePowerManagement() {
    QString paraHibEnable = m_pReq->parameter("f_hdd_hibernation_enable");
    QString paraTurnOffTime = m_pReq->parameter("f_turn_off_time");

    QMap<QString, QString> map;

    map.insert("hdd_hibernation_enable", paraHibEnable);
    map.insert("turn_off_time", paraTurnOffTime);
    if(!setNasCfg("power_management", map))
        tDebug("RenderResponseSysMngm::generatePowerManagement(): setNasCfg power_management failed");
    else
    {
        QStringList arg = QStringList() << "system_hdd_hibernation_setting";
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
    }

    m_var = "Location: /web/system_mgr/power_mgr.html";
}

void RenderResponseSysMngm::generatePowerRecovery() {
    QString paraRecvEnable = m_pReq->parameter("f_recovery_enable");

    if(!setNasCfg("power_management", "recovery_enable", paraRecvEnable))
        tDebug("RenderResponseSysMngm::generatePowerRecovery(): setNasCfg power_management failed");
    else
    {
        QStringList arg = QStringList() << "system_power_recovery_setting";
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
    }

}

void RenderResponseSysMngm::generateFan() {
    QString paraFanType = m_pReq->parameter("f_fan_type");

    if(!setNasCfg("power_management", "fan", paraFanType))
        tDebug("RenderResponseSysMngm::generateFan(): setNasCfg power_management failed");
    else
    {
        QStringList arg = QStringList() << "system_fan_control_setting";
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
    }
}

void RenderResponseSysMngm::generatePowerOffSchedule() {
    QString paraPowerOffEnable = m_pReq->parameter("f_power_off_enable");
    QString paraSchedule = m_pReq->parameter("schedule").replace(",", "^").replace(" ", ",");
    QString paraOffSchedule = m_pReq->parameter("off_schedule").replace(",", "^").replace(" ", ",");

    QMap<QString, QMap<QString, QString>> titleMap;
    QMap<QString, QString> map[3];
    map[0].insert("power_off_scheduling_enable", paraPowerOffEnable);
    map[1].insert("schedule", paraSchedule);
    map[2].insert("off_schedule", paraOffSchedule);
    titleMap.insert("power_management", map[0]);
    titleMap.insert("power_on_sch", map[1]);
    titleMap.insert("power_off_sch", map[2]);

    if(!setNasCfg(titleMap)) {
        tDebug("RenderResponseSysMngm::generatePowerOffSchedule(): setNasCfg failed");
        return;
    }

    QStringList arg = QStringList() << "system_power_onoff_schedule";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
}

void RenderResponseSysMngm::generateGetEmailXml() {

    QDomDocument doc;
    QStringList arg = QStringList() << "service_get_email_info";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QDomElement root = doc.createElement("mail");
    doc.appendChild(root);
    QDomElement authElement = doc.createElement("auth");
    root.appendChild(authElement);
    authElement.appendChild(doc.createTextNode(apiOut.value(0)));

    QDomElement usernameElement = doc.createElement("username");
    root.appendChild(usernameElement);
    usernameElement.appendChild(doc.createTextNode(apiOut.value(1)));

    QDomElement pwdElement = doc.createElement("pwd");
    root.appendChild(pwdElement);
    pwdElement.appendChild(doc.createTextNode(apiOut.value(2)));

    QDomElement smtpElement = doc.createElement("smtp");
    root.appendChild(smtpElement);
    smtpElement.appendChild(doc.createTextNode(apiOut.value(3)));

    QDomElement senderElement = doc.createElement("sender");
    root.appendChild(senderElement);
    senderElement.appendChild(doc.createTextNode(apiOut.value(4)));

    QDomElement receiverElement = doc.createElement("receiver");
    root.appendChild(receiverElement);
    receiverElement.appendChild(doc.createTextNode(apiOut.value(5)));

    QDomElement portElement = doc.createElement("port");
    root.appendChild(portElement);
    portElement.appendChild(doc.createTextNode(apiOut.value(6)));

    QDomElement smtpAuthElement = doc.createElement("smtp_auth");
    root.appendChild(smtpAuthElement);
    smtpAuthElement.appendChild(doc.createTextNode(apiOut.value(7)));

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateGetEventXml() {

    QDomDocument doc;
    QStringList arg = QStringList() << "service_get_event_info";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QDomElement root = doc.createElement("event");
    doc.appendChild(root);

    QDomElement pwdElement = doc.createElement("pwd");
    root.appendChild(pwdElement);
    pwdElement.appendChild(doc.createTextNode(apiOut.value(0)));

    QDomElement hddSpaceStatusElement = doc.createElement("hdd_space_status");
    root.appendChild(hddSpaceStatusElement);
    hddSpaceStatusElement.appendChild(doc.createTextNode(apiOut.value(1)));

    QDomElement hddFullElement = doc.createElement("hdd_full");
    root.appendChild(hddFullElement);
    hddFullElement.appendChild(doc.createTextNode(apiOut.value(2)));

    QDomElement hddCrashElement = doc.createElement("hdd_crash");
    root.appendChild(hddCrashElement);
    hddCrashElement.appendChild(doc.createTextNode(apiOut.value(3)));

    QDomElement hddDegradedElement = doc.createElement("hdd_degraded");
    root.appendChild(hddDegradedElement);
    hddDegradedElement.appendChild(doc.createTextNode(apiOut.value(4)));

    QDomElement hddRebuildIsDoneElement = doc.createElement("hdd_rebuild_is_done");
    root.appendChild(hddRebuildIsDoneElement);
    hddRebuildIsDoneElement.appendChild(doc.createTextNode(apiOut.value(5)));

    QDomElement hddRebuildStartElement = doc.createElement("hdd_rebuild_start");
    root.appendChild(hddRebuildStartElement);
    hddRebuildStartElement.appendChild(doc.createTextNode(apiOut.value(6)));

    QDomElement hddRemoveElement = doc.createElement("hdd_remove");
    root.appendChild(hddRemoveElement);
    hddRemoveElement.appendChild(doc.createTextNode(apiOut.value(7)));

    QDomElement hddInsertElement = doc.createElement("hdd_insert");
    root.appendChild(hddInsertElement);
    hddInsertElement.appendChild(doc.createTextNode(apiOut.value(8)));

    QDomElement hddTemperatureElement = doc.createElement("hdd_temperature");
    root.appendChild(hddTemperatureElement);
    hddTemperatureElement.appendChild(doc.createTextNode(apiOut.value(9)));

    QDomElement firmwareUpdateElement = doc.createElement("firmware_update");
    root.appendChild(firmwareUpdateElement);
    firmwareUpdateElement.appendChild(doc.createTextNode(apiOut.value(10)));

    QDomElement systemLogScheduleElement = doc.createElement("system_log_schedule");
    root.appendChild(systemLogScheduleElement);
    systemLogScheduleElement.appendChild(doc.createTextNode(apiOut.value(11)));

    QDomElement systemLogFullElement = doc.createElement("system_log_full");
    root.appendChild(systemLogFullElement);
    systemLogFullElement.appendChild(doc.createTextNode(apiOut.value(12)));

    if(!apiOut.value(13).isEmpty()) {
        QDomElement hddSpaceSchElement = doc.createElement("hddspace_sch");
        root.appendChild(hddSpaceSchElement);
        hddSpaceSchElement.appendChild(doc.createTextNode(apiOut.value(13)));
    }

    if(!apiOut.value(14).isEmpty()) {
        QDomElement logSchElement = doc.createElement("log_sch");
        root.appendChild(logSchElement);
        logSchElement.appendChild(doc.createTextNode(apiOut.value(14)));
    }

    QDomElement btDownloadElement = doc.createElement("bt_download");
    root.appendChild(btDownloadElement);
    btDownloadElement.appendChild(doc.createTextNode(apiOut.value(15)));

    QDomElement configUpdateElement = doc.createElement("config_update");
    root.appendChild(configUpdateElement);
    configUpdateElement.appendChild(doc.createTextNode(apiOut.value(16)));

    QDomElement smartTestElement = doc.createElement("smart_test");
    root.appendChild(smartTestElement);
    smartTestElement.appendChild(doc.createTextNode(apiOut.value(17)));

    QDomElement recoverPwerFailElement = doc.createElement("recover_power_fail");
    root.appendChild(recoverPwerFailElement);
    recoverPwerFailElement.appendChild(doc.createTextNode(apiOut.value(18)));

    QDomElement upsElement = doc.createElement("ups");
    root.appendChild(upsElement);
    upsElement.appendChild(doc.createTextNode(apiOut.value(19)));

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateEmailEvent() {
    QStringList arg = QStringList() << "service_set_event_setting" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);
    m_var = "Content-type: text/html";
}

void RenderResponseSysMngm::generateEmail() {

    QMap<QString, QString> map;
    map.insert("auth", m_pReq->parameter("login_method"));
    map.insert("username", QUrl::fromPercentEncoding(m_pReq->parameter("f_username").toLocal8Bit()));
    map.insert("pwd", m_pReq->parameter("f_password"));
    map.insert("smtp", m_pReq->parameter("f_smtp"));
    map.insert("sender", QUrl::fromPercentEncoding(m_pReq->parameter("f_sender").toLocal8Bit()));
    map.insert("receiver", QUrl::fromPercentEncoding(m_pReq->parameter("f_receiver").toLocal8Bit()));
    map.insert("port", m_pReq->parameter("f_port"));
    map.insert("smtp_auth", m_pReq->parameter("f_smtp_auth"));

    if(!setNasCfg("mail", map))
        tDebug("RenderResponseSysMngm::generateEmail(): setNasCfg <mail> failed");

    m_var = "Content-type: text/html";
}

void RenderResponseSysMngm::generateEmailTest() {
    QStringList arg = QStringList() << "service_set_send_email_test" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);
}

void RenderResponseSysMngm::generateEmailTestResult() {

    QDomDocument doc;
    QStringList arg = QStringList() << "service_get_send_email_test_result";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("test");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseSysMngm::generateEmailClear() {
    QStringList arg = QStringList() << "service_set_clear_email_save_config";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);
    m_var = "Content-type: text/html";
}

void RenderResponseSysMngm::generateSmsAdd() {
    QStringList arg = QStringList() << "service_add_sms_config" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);
}

void RenderResponseSysMngm::generateSmsModify() {
    QStringList arg = QStringList() << "service_save_sms_config" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);
}

void RenderResponseSysMngm::generateSmsTest() {
    QStringList arg = QStringList() << "service_sms_send" << "test";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
}

void RenderResponseSysMngm::generateSmsTestResult() {
    QStringList arg = QStringList() << "service_sms_test_result";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);
    m_var = apiOut.value(0);
}

void RenderResponseSysMngm::generateSmsDel() {
    QStringList arg = QStringList() << "service_del_sms_config" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);
}

void RenderResponseSysMngm::generateLogSystem() {
    QString paraPage = m_pReq->parameter("page");
    QString paraRp = m_pReq ->parameter("rp") ;
//    QString paraSortname = m_pReq ->parameter("sortname") ;
//    QString paraSortorder = m_pReq ->parameter("sortorder") ;
//    QString paraQuery = m_pReq ->parameter("query") ;
//    QString paraQType = m_pReq ->parameter("qtype") ;
//    QString paraField = m_pReq ->parameter("f_field") ;
//    QString paraUser = m_pReq ->parameter("user") ;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_CLOG + " -g 0 | tac", false, ",", 1);

    QVariantMap listMap;
    listMap.insert("total", QString::number(apiOut.size()));
    listMap.insert("page", paraPage);

    QVariantList itemMapList;
    int logStart = (paraPage.toInt()-1) * paraRp.toInt();
    int logEnd = logStart + paraRp.toInt();
    if(logEnd > apiOut.size())
        logEnd = apiOut.size();
    for(int i = logStart; i < logEnd; i++) {
        int diff = 0;
        if(apiOut.value(i).indexOf("  ") == 3)
            diff = 1;
        QString logDate = apiOut.value(i).section(" ", 0, 1 + diff);
        QString logTime = apiOut.value(i).section(" ", 2 + diff, 2 + diff);
        QString strLog = apiOut.value(i).section(" ", 4 + diff);
        QString logContent = strLog.right(strLog.length() - (strLog.indexOf(": ") + 2));

        QVariantMap itemMap;
        itemMap.insert("id", QString::number(i+1));
        QVariantList log;
        log << logDate << logTime << logContent;
        itemMap.insert("cell", log);
        itemMapList.append(itemMap);
    }

    listMap.insert("rows", itemMapList);

    m_var = QJsonDocument::fromVariant(listMap);

}

void RenderResponseSysMngm::generateGetLogInfo() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_SYSLOG_API + " get_cfg", true, ";");

    QDomElement root = doc.createElement("log");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement ipElement = doc.createElement("ip");
    root.appendChild(ipElement);
    ipElement.appendChild(doc.createTextNode(apiOut.value(1)));
    QDomElement portElement = doc.createElement("port");
    root.appendChild(portElement);
    portElement.appendChild(doc.createTextNode(apiOut.value(2)));

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateLogServer() {
    QString paraEnable = m_pReq->allParameters().value("f_enable").toString();
    QString paraIp = m_pReq->allParameters().value("f_ip").toString();
    QString paraPort = m_pReq->allParameters().value("f_port").toString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_SYSLOG_API +
                                      " set_cfg " + paraEnable +
                                      " " + paraIp +
                                      " " + paraPort);
}


void RenderResponseSysMngm::generateSendLogTest() {
    QStringList arg = QStringList() << "service_syslog_send_test" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);
}

void RenderResponseSysMngm::generateLogBackup() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_SYSLOG_API + " backup");

    QFileInfo file(SENDOUT_LOGFILE);
    if(file.exists() && file.isFile())
        m_var = SENDOUT_LOGFILE;
}

void RenderResponseSysMngm::generateLogClear() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_SYSLOG_API + " clear");
}

void RenderResponseSysMngm::generateUpsInfo() {

    QDomDocument doc;
    QStringList arg = QStringList() << "service_get_ups_info";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ",");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QList<QString> upsContentElement;
    upsContentElement << "ups_plugmode" << "ups_mode" << "master_ip" << "ups_network";
    if(apiOut.size() == 6) {
        upsContentElement.insert(3, "master_battery");
        upsContentElement.insert(4, "master_status");
    }

    if( upsContentElement.size() == apiOut.size() ) {
        for(int i = 0; i < apiOut.size(); i++) {
            QDomElement element = doc.createElement(upsContentElement.value(i));
            root.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseSysStatus::generateUsbPrinterInfo() :"
               "upsContentElement size is not equal to apiOut size.");
    }

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateUpsMaterList() {

    QDomDocument doc;
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();

    QStringList arg = QStringList() << "service_get_ups_master_list";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    for(int i = 0; i < apiOut.size(); i++) {
        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode(QString::number(i+1)));
        QDomElement cellElement = doc.createElement("cell");
        rowElement.appendChild(cellElement);
        cellElement.appendChild(doc.createTextNode(apiOut.value(i)));

        rowElement.setAttribute("id", i+1);
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateUpsStatusInfo() {

    QDomDocument doc;
    QStringList arg = QStringList() << "service_get_ups_status_info";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ",");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.isEmpty() ? "0" : "1"));

    QList<QString> upsContentElement;
    upsContentElement << "manufacturer" << "product" << "battery" << "ups_status";

    if(apiOut.isEmpty())
        apiOut << "--" << "--" << "--" << "--";

    if( upsContentElement.size() == apiOut.size() ) {
        for(int i = 0; i < apiOut.size(); i++) {
            QDomElement element = doc.createElement(upsContentElement.value(i));
            root.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseSysStatus::generateUsbPrinterInfo() :"
               "upsContentElement size is not equal to apiOut size.");
    }

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateUpsAdd() {

    QDomDocument doc;
    if(!startDetached(API_PATH + SCRIPT_MANAGER_API, QStringList() <<
                                "service_set_ups_add" << allParametersToString()))
        ;
//    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_ups_add "
//                                      + allParametersToString(), true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
    m_var = doc.toString();

}

void RenderResponseSysMngm::generateUpsSlaveSetting() {

    QDomDocument doc;
    QStringList arg = QStringList() << "service_set_ups_slave" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseSysMngm::generateUpsPs() {

    QDomDocument doc;
    QStringList arg = QStringList() << "service_get_check_ups_ps";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseSysMngm::generateUsbStorageUmount() {

    QDomDocument doc;
    QStringList arg = QStringList() << "service_set_usb_storage_umount" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseSysMngm::generateUsbPrinterClear() {

    QDomDocument doc;
    QStringList arg = QStringList() << "service_set_clear_print_queue";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateFirmVXml() {

    QDomDocument doc;
    QMap<QString, QString> systemInfo = getNasCfg("system");

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_RTC_API + " -m", true, "=");

    QDomElement root = doc.createElement("version");
    doc.appendChild(root);
    QDomElement fwElement = doc.createElement("fw");
    root.appendChild(fwElement);
    fwElement.appendChild(doc.createTextNode(systemInfo.value("sw_ver")));
    QDomElement oledElement = doc.createElement("oled");
    root.appendChild(oledElement);
    oledElement.appendChild(doc.createTextNode("1.0" + apiOut.value(1).trimmed().remove("v")));
    m_var = doc.toString();

}

void RenderResponseSysMngm::generateCheckPowerSch() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FW_UPGRADE_MGR + " check_power_sch", true);
    m_var = apiOut.value(0);
}

void RenderResponseSysMngm::generateFirmwareInitUpload() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_FW_UPGRADE_MGR + " fw_init_upload_status", true);
    m_var = apiOut.value(0);
}

void RenderResponseSysMngm::generateFirmwareUpload() {
    if(!m_pReq->multipartFormData().isEmpty()) {
        if(m_pReq->multipartFormData().renameUploadedFile("file", FIRMWARE_FILE, true)) {
            m_var = "<script>location.href='/web/system_mgr/firmware_result.html'</script>";
        }
    }
}

void RenderResponseSysMngm::generateGetPercentage() {
    getAPIStdOut(API_PATH + SCRIPT_FW_UPGRADE_MGR + " firmware_verify", true);
    QStringList apiOut = this->getAPIFileOut(FIRMWARE_PERCENTAGE_FILE, true);
    m_var = apiOut.value(0);
}

void RenderResponseSysMngm::generateGetFirmwareVerify() {
    QStringList apiOut = getAPIFileOut(FIRMWARE_VERIFY_STATUS_FILE, true);
    m_var = apiOut.value(0);
}

void RenderResponseSysMngm::generateGetUpFw() {
    QStringList apiOut = getAPIFileOut(FIRMWARE_RESULT_FILE, true);
    m_var = apiOut.value(0);
}

void RenderResponseSysMngm::generateReboot() {
    daemonize();
    if(!startDetached(API_PATH + SCRIPT_FW_UPGRADE_MGR, QStringList() << "system_reboot"))
        ;
    m_var = "../web/dsk_mgr/wait.html";
}

void RenderResponseSysMngm::daemonize()
{

    if (fork())
        exit(0); // fork.  parent exits.
    setsid(); // become process group leader
    if (fork())
        _exit(0); // second parent exits.
    chdir("/"); // just so we don't mysteriously prevent fs unmounts later
    close(0); // close stdin, stdout, stderr.
    close(1);
    close(2);

}

void RenderResponseSysMngm::generateGetLiveFirm() {

    QDomDocument doc;

    QStringList arg = QStringList() << "get_live_firm";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true, ";");

    QDomElement root = doc.createElement("live_fw");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement lastTimeElement = doc.createElement("last_time");
    root.appendChild(lastTimeElement);
    lastTimeElement.appendChild(doc.createTextNode(apiOut.value(1)));
    QDomElement progressElement = doc.createElement("progress");
    root.appendChild(progressElement);
    progressElement.appendChild(doc.createTextNode(apiOut.value(2)));

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateSetLiveFirm() {

    if(startDetached(API_PATH + SCRIPT_MANAGER_API, QStringList()
                                << "check_live_firm"))
        ;

}

void RenderResponseSysMngm::generateCheckLiveFirm() {

    QDomDocument doc;

    QStringList arg = QStringList() << "check_live_firm";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("live_fw");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateGetLiveFirmVer() {

    QDomDocument doc;

    QStringList arg = QStringList() << "get_live_firm_ver";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

    QDomElement root = doc.createElement("live_fw");
    doc.appendChild(root);
    QDomElement verElement = doc.createElement("ver");
    root.appendChild(verElement);
    verElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseSysMngm::generateFirmwareDownload() {

    QStringList arg = QStringList() << "cgi_firmware_download";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);
    m_var = "<script>location.href='/web/system_mgr/firmware_result.html'</script>";

}
