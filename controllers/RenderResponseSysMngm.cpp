#include "RenderResponseSysMngm.h"
#include "AppDefine.h"

#include <QTimeZone>

RenderResponseSysMngm::RenderResponseSysMngm(QVariantMap &map, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_renderType = RENDER_TYPE_UNKNOWN;
    m_pMap = &map;
}

RenderResponseSysMngm::~RenderResponseSysMngm() {
}

RENDER_TYPE RenderResponseSysMngm::preRender() {

    if(!m_pMap)
        return RENDER_TYPE_UNKNOWN;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_GET_TIME:
        generateGetTime(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_MANUAL_TIME:
        generateManualTime();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_TIMEZONE:
        generateTimezone();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_NTP_TIME:
        generateNtpTime();
        m_renderType = RENDER_TYPE_NULL;
        break;
    case CMD_GET_TIME_STATUS:
        generateGetTimeStatus(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_DEVICE_INFO:
        generateGetDeviceInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_DEVICE:
        generateDevice();
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

/* todo */
void RenderResponseSysMngm::generateGetTime(QDomDocument &doc) {

    QDateTime currentTime = QDateTime::currentDateTime();

    QDomElement root = doc.createElement("time");
    doc.appendChild(root);
    QDomElement timezoneElement = doc.createElement("timezone");
    root.appendChild(timezoneElement);
    timezoneElement.appendChild(doc.createTextNode("34"));
    QDomElement ntpEnableElement = doc.createElement("ntp_enable");
    root.appendChild(ntpEnableElement);
    ntpEnableElement.appendChild(doc.createTextNode("0"));
    QDomElement ntpServerElement = doc.createElement("ntp_server");
    root.appendChild(ntpServerElement);
    ntpServerElement.appendChild(doc.createTextNode(""));
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

/* todo */
void RenderResponseSysMngm::generateManualTime() {
    QString paraYear = m_pMap->value("f_year").toString();
    QString paraMonth = m_pMap->value("f_month").toString();
    QString paraDay = m_pMap->value("f_day").toString();
    QString paraHour = m_pMap->value("f_hour").toString();
    QString paraMin = m_pMap->value("f_min").toString();
    QString paraSec = m_pMap->value("f_sec").toString();

#ifndef SIMULATOR_MODE
    uint timeToSet = QDateTime(QDate(paraYear.toInt(), paraMonth.toInt(), paraDay.toInt()),
                               QTime(paraHour.toInt(), paraMin.toInt(), paraSec.toInt())).toTime_t();
#endif
}

/* todo */
void RenderResponseSysMngm::generateTimezone() {
    QString paraTimezone = m_pMap->value("f_timezone").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);

}

/* todo */
void RenderResponseSysMngm::generateNtpTime() {
    QString paraNtpEnable = m_pMap->value("f_ntp_enable").toString();
    QString paraNtpServer = m_pMap->value("f_ntp_server").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);
}

/* todo */
void RenderResponseSysMngm::generateGetTimeStatus(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);

    QDomElement root = doc.createElement("time");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode("done"));
    QDomElement updateTimeElement = doc.createElement("update_time");
    root.appendChild(updateTimeElement);
    updateTimeElement.appendChild(doc.createTextNode(""));
}

/* todo */
void RenderResponseSysMngm::generateGetDeviceInfo(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);

    QDomElement root = doc.createElement("device_info");
    doc.appendChild(root);
    QDomElement nameElement = doc.createElement("name");
    root.appendChild(nameElement);
    nameElement.appendChild(doc.createTextNode("dlink-8B21F7"));
    QDomElement workgroupElement = doc.createElement("workgroup");
    root.appendChild(workgroupElement);
    workgroupElement.appendChild(doc.createTextNode("workgroup"));
    QDomElement descriptionElement = doc.createElement("description");
    root.appendChild(descriptionElement);
    descriptionElement.appendChild(doc.createTextNode("DNS-340L"));
}

/* todo */
void RenderResponseSysMngm::generateDevice() {
    QString paraHostname = m_pMap->value("hostname").toString();
    QString paraWorkgroup = m_pMap->value("workgroup").toString();
    QString paraDescription = m_pMap->value("description").toString();
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_HOME_API + " -g ssl_info", true);
}
