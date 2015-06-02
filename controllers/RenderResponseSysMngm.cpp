#include "RenderResponseSysMngm.h"

#include <QTimeZone>
#include <QFileInfo>

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

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_GET_TIME:
        generateGetTime(doc);
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
        generateGetTimeStatus(doc);
        break;
    case CMD_GET_DEVICE_INFO:
        generateGetDeviceInfo(doc);
        break;
    case CMD_DEVICE:
        generateDevice();
        break;
    case CMD_DETECT_DANGEROUS:
        generateDetectDangerous(doc);
        break;
    case CMD_GET_IDEL:
        generateGetIdle(str);
        break;
    case CMD_GET_TEMPERATURE:
        generateGetTemperature(doc);
        break;
    case CMD_GET_RESTORE_STATUS:
        generateGetRestoreStatus(str);
        break;
    case CMD_RESTART:
        generateRestart(str);
        break;
    case CMD_RESTORE:
        generateRestore(str);
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
        generateBackupConf(str);
        break;
    case CMD_RESTORE_CONF:
        generateRestoreConf(str);
        break;

    case CMD_GET_POWER_MGR:
        generateGetPowerMgr(doc);
        break;
    case CMD_POWER_MANAGEMENT:
        generatePowerManagement(str);
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
        generateGetEmailXml(doc);
        break;
    case CMD_GET_EVENT_XML:
        generateGetEventXml(doc);
        break;
    case CMD_EMAIL_EVENT:
        generateEmailEvent(str);
        break;
    case CMD_EMAIL:
        generateEmail(str);
        break;
    case CMD_EMAIL_TEST:
        generateEmailTest();
        break;
    case CMD_EMAIL_TEST_RESULT:
        generateEmailTestResult(doc);
        break;
    case CMD_EMAIL_CLEAR:
        generateEmailClear(str);
        break;

    case CMD_LOG_SYSTEM:
        generateLogSystem(str);
        break;
    case CMD_GET_LOG_INFO:
        generateGetLogInfo(doc);
        break;
    case CMD_LOG_SERVER:
        generateLogServer();
        break;
    case CMD_SEND_LOG_TEST:
        generateSendLogTest();
        break;
    case CMD_LOG_BACKUP:
        generateLogBackup(str);
        break;
    case CMD_LOG_CLEAR:
        generateLogClear();
        break;

    case CMD_GUI_UPS_INFO:
        generateUpsInfo(doc);
        break;
    case CMD_GUI_UPS_SLAVE_SETTING:
        generateUpsSlaveSetting(doc);
        break;
    case CMD_GUI_UPS_PS:
        generateUpsPs(doc);
        break;
    case CMD_USB_STORAGE_UMOUNT:
        generateUsbStorageUmount(doc);
        break;
    case CMD_USB_PRINTER_CLEAR:
        generateUsbPrinterClear(doc);
        break;

    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

}

void RenderResponseSysMngm::generateGetTime(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");

    QDateTime currentTime = QDateTime::currentDateTime();

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
    yearElement.appendChild(doc.createTextNode(QString::number(currentTime.date().year())));
    QDomElement monElement = doc.createElement("mon");
    root.appendChild(monElement);
    monElement.appendChild(doc.createTextNode(QString::number(currentTime.date().month())));
    QDomElement dayElement = doc.createElement("day");
    root.appendChild(dayElement);
    dayElement.appendChild(doc.createTextNode(QString::number(currentTime.date().day())));

    QDomElement hourElement = doc.createElement("hour");
    root.appendChild(hourElement);
    hourElement.appendChild(doc.createTextNode(QString::number(currentTime.time().hour())));
    QDomElement minElement = doc.createElement("min");
    root.appendChild(minElement);
    minElement.appendChild(doc.createTextNode(QString::number(currentTime.time().minute())));
    QDomElement secElement = doc.createElement("sec");
    root.appendChild(secElement);
    secElement.appendChild(doc.createTextNode(QString::number(currentTime.time().second())));
}

void RenderResponseSysMngm::generateManualTime() {
    QString paraYear = m_pReq->allParameters().value("f_year").toString();
    QString paraMonth = m_pReq->allParameters().value("f_month").toString();
    QString paraDay = m_pReq->allParameters().value("f_day").toString();
    QString paraHour = m_pReq->allParameters().value("f_hour").toString();
    QString paraMin = m_pReq->allParameters().value("f_min").toString();
    QString paraSec = m_pReq->allParameters().value("f_sec").toString();

    QString timeToSet = QDateTime(QDate(paraYear.toInt(), paraMonth.toInt(), paraDay.toInt()),
                               QTime(paraHour.toInt(), paraMin.toInt(), paraSec.toInt())).toString("yyyy-mm-dd hh:mm:ss");

    tDebug("set date/time: %s", timeToSet.toLocal8Bit().data());
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " set " + timeToSet, true);
}

void RenderResponseSysMngm::generateTimezone() {
    QString paraTimezone = m_pReq->allParameters().value("f_timezone").toString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_TIMEZONE_API + " " + paraTimezone, true);

}

void RenderResponseSysMngm::generateNtpTime() {
    QString paraNtpEnable = m_pReq->allParameters().value("f_ntp_enable").toString();
    QString paraNtpServer = m_pReq->allParameters().value("f_ntp_server").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_NTP_API +
                                      " set " + paraNtpEnable + " " + paraNtpServer, true);
}

void RenderResponseSysMngm::generateGetTimeStatus(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_NTP_API + " status", true, ";");

    QDomElement root = doc.createElement("time");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement updateTimeElement = doc.createElement("update_time");
    root.appendChild(updateTimeElement);
    updateTimeElement.appendChild(doc.createTextNode(apiOut.value(1)));
}

void RenderResponseSysMngm::generateGetDeviceInfo(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DEVICE_API + " get", true, ";");

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
}

void RenderResponseSysMngm::generateDevice() {
    QString paraHostname = m_pReq->allParameters().value("hostname").toString();
    QString paraWorkgroup = m_pReq->allParameters().value("workgroup").toString();
    QString paraDescription = m_pReq->allParameters().value("description").toString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DEVICE_API + " set " +
                                      paraHostname + " " + paraWorkgroup + " " + paraDescription, true);
}

void RenderResponseSysMngm::generateDetectDangerous(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_POWER_API + " status", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));

}

void RenderResponseSysMngm::generateGetIdle(QString &str) {
    QMap<QString, QString> idleInfo = getNasCfg("idle");
    str = idleInfo.value("time");
}

void RenderResponseSysMngm::generateGetTemperature(QDomDocument &doc) {
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

void RenderResponseSysMngm::generateGetRestoreStatus(QString &str) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_RESTORE_API + " status", true);
    str = apiOut.value(0);
}

void RenderResponseSysMngm::generateRestart(QString &str) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_POWER_API + " restart");
    str = "/web/dsk_mgr/wait.html";
}

void RenderResponseSysMngm::generateRestore(QString &str) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_RESTORE_API + " resetdef", true);
    str = "/web/dsk_mgr/wait.html";
}

void RenderResponseSysMngm::generateShutdown() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_POWER_API + " shutdown");
}

void RenderResponseSysMngm::generateIdle() {
    QString paraIdle = m_pReq->allParameters().value("f_idle").toString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_IDLE_API + " set " + paraIdle);
}

void RenderResponseSysMngm::generateTemperature() {
    QString paraTemperature = m_pReq->allParameters().value("f_temperature").toString();
    QString paraKoc = m_pReq->allParameters().value("f_koc").toString();

    QMap<QString, QString> map;
    map.insert("hdd_temperature_temperature", paraTemperature);
    map.insert("hdd_temperature_kot", paraKoc);
    if(!setNasCfg("mail_event", map))
        tDebug("setNasCfg mail_event failed");
}

void RenderResponseSysMngm::generateBackupConf(QString &str) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_CONFIG_API + " save", true);
    QString filePath = apiOut.value(0);
    tDebug("file: %s", filePath.toLocal8Bit().data());
    QFileInfo file(filePath);
    if(file.exists() && file.isFile())
        str = filePath;
}

void RenderResponseSysMngm::generateRestoreConf(QString &str) {

    if(!m_pReq->multipartFormData().isEmpty()) {
        if(m_pReq->multipartFormData().renameUploadedFile("name", USER_IMPORT_FILE)) {
            QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_CONFIG_API + " load", true);
            if(apiOut.value(0).compare("0") == 0) {
                str = "<script>parent.location.href='/web/dsk_mgr/wait.html'</script>";
                getAPIStdOut(API_PATH + SCRIPT_POWER_API + " restart");
            }
        }
    }

}

void RenderResponseSysMngm::generateGetPowerMgr(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_powermgr_info");

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

}

void RenderResponseSysMngm::generatePowerManagement(QString &str) {
    QString paraHibEnable = m_pReq->parameter("f_hdd_hibernation_enable");
    QString paraTurnOffTime = m_pReq->parameter("f_turn_off_time");

    QMap<QString, QString> map;

    map.insert("hdd_hibernation_enable", paraHibEnable);
    map.insert("turn_off_time", paraTurnOffTime);
    if(!setNasCfg("power_management", map))
        tDebug("RenderResponseSysMngm::generatePowerManagement(): setNasCfg power_management failed");
    else
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_hdd_hibernation_setting", true);

    str = "Location: /web/system_mgr/power_mgr.html";
}

void RenderResponseSysMngm::generatePowerRecovery() {
    QString paraRecvEnable = m_pReq->parameter("f_recovery_enable");

    if(!setNasCfg("power_management", "recovery_enable", paraRecvEnable))
        tDebug("RenderResponseSysMngm::generatePowerRecovery(): setNasCfg power_management failed");
    else
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_power_recovery_setting", true);

}

void RenderResponseSysMngm::generateFan() {
    QString paraFanType = m_pReq->parameter("f_fan_type");

    if(!setNasCfg("power_management", "fan", paraFanType))
        tDebug("RenderResponseSysMngm::generateFan(): setNasCfg power_management failed");
    else
        QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_fan_control_setting", true);
}

void RenderResponseSysMngm::generatePowerOffSchedule() {
    QString paraPowerOffEnable = m_pReq->parameter("f_power_off_enable");
    QString paraSchedule = m_pReq->parameter("schedule").replace(",", ";").replace(" ", ",");
    QString paraOffSchedule = m_pReq->parameter("off_schedule").replace(",", ";").replace(" ", ",");

    if(!setNasCfg("power_management", "power_off_scheduling_enable", paraPowerOffEnable)) {
        tDebug("RenderResponseSysMngm::generatePowerOffSchedule(): setNasCfg power_management failed");
        return;
    }

    if(!setNasCfg("power_on_sch", "schedule", paraSchedule)) {
        tDebug("RenderResponseSysMngm::generatePowerOffSchedule(): setNasCfg power_on_sch failed");
        return;
    }

    if(!setNasCfg("power_off_sch", "off_schedule", paraOffSchedule)) {
        tDebug("RenderResponseSysMngm::generatePowerOffSchedule(): setNasCfg power_off_sch failed");
        return;
    }

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_power_onoff_schedule", true);
}

void RenderResponseSysMngm::generateGetEmailXml(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_email_info", true, ";");

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

}

void RenderResponseSysMngm::generateGetEventXml(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_mail_info", true, ";");

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

}

void RenderResponseSysMngm::generateEmailEvent(QString &str) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_event_setting "
                                      + allParametersToString());
    str = "Content-type: text/html";
}

void RenderResponseSysMngm::generateEmail(QString &str) {

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

    str = "Content-type: text/html";
}

void RenderResponseSysMngm::generateEmailTest() {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_send_email_test "
                                      + allParametersToString());
}

void RenderResponseSysMngm::generateEmailTestResult(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_send_email_test_result");

    QDomElement root = doc.createElement("test");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.value(0)));

}

void RenderResponseSysMngm::generateEmailClear(QString &str) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_clear_email_save_config");
    str = "Content-type: text/html";
}


/* todo */
void RenderResponseSysMngm::generateLogSystem(QString &str) {
    QString paraPage = m_pReq->allParameters().value("page").toString();
    QString paraRp = m_pReq->allParameters().value("rp").toString();
    QString paraSortname = m_pReq->allParameters().value("sortname").toString();
    QString paraSortorder = m_pReq->allParameters().value("sortorder").toString();
    QString paraQuery = m_pReq->allParameters().value("query").toString();
    QString paraQType = m_pReq->allParameters().value("qtype").toString();
    QString paraField = m_pReq->allParameters().value("f_field").toString();
    QString paraUser = m_pReq->allParameters().value("user").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);
    str = "{\"rows\":[],\"total\":\"0\",\"page\":\"1\"}";
}

/* todo */
void RenderResponseSysMngm::generateGetLogInfo(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);

    QDomElement root = doc.createElement("log");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode("0"));
    QDomElement ipElement = doc.createElement("ip");
    root.appendChild(ipElement);
    ipElement.appendChild(doc.createTextNode(""));
    QDomElement portElement = doc.createElement("port");
    root.appendChild(portElement);
    portElement.appendChild(doc.createTextNode("514"));
}

/* todo */
void RenderResponseSysMngm::generateLogServer() {
    QString paraEnable = m_pReq->allParameters().value("f_enable").toString();
    QString paraIp = m_pReq->allParameters().value("f_ip").toString();
    QString paraPort = m_pReq->allParameters().value("f_port").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);
}

/* todo */
void RenderResponseSysMngm::generateSendLogTest() {
    QString paraIp = m_pReq->allParameters().value("f_ip").toString();
    QString paraPort = m_pReq->allParameters().value("f_port").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);
}

/* todo */
void RenderResponseSysMngm::generateLogBackup(QString &str) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);
    //sendFile();
}

/* todo */
void RenderResponseSysMngm::generateLogClear() {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);
}

/* todo */
void RenderResponseSysMngm::generateUpsInfo(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement upsPlugmodeElement = doc.createElement("ups_plugmode");
    root.appendChild(upsPlugmodeElement);
    upsPlugmodeElement.appendChild(doc.createTextNode("0"));
    QDomElement upsModeElement = doc.createElement("ups_mode");
    root.appendChild(upsModeElement);
    upsModeElement.appendChild(doc.createTextNode("0"));
    QDomElement masterIpElement = doc.createElement("master_ip");
    root.appendChild(masterIpElement);
    masterIpElement.appendChild(doc.createTextNode("none"));
    QDomElement upsNetworkElement = doc.createElement("ups_network");
    root.appendChild(upsNetworkElement);
    upsNetworkElement.appendChild(doc.createTextNode("0"));
}

/* todo */
void RenderResponseSysMngm::generateUpsSlaveSetting(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

}

/* todo */
void RenderResponseSysMngm::generateUpsPs(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

}

/* todo */
void RenderResponseSysMngm::generateUsbStorageUmount(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("0"));

}

/* todo */
void RenderResponseSysMngm::generateUsbPrinterClear(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

}

