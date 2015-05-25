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
