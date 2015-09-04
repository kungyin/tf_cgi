#include "RenderResponseSetupWizard.h"

RenderResponseSetupWizard::RenderResponseSetupWizard(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseSetupWizard::~RenderResponseSetupWizard() {
}

void RenderResponseSetupWizard::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_CHK_ADMIN_PW:
        generateChkAdminPw();
        break;
    case CMD_SET_LED:
        generateSetLed();
        break;
    case CMD_GET_WIZARD:
        generateGetWizard();
        break;
    default:
        break;
    }

}

void RenderResponseSetupWizard::generateChkAdminPw() {

    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API
                                      + " system_chk_admin_pw " + m_pReq->parameter("pw"), true);

    QDomElement root = doc.createElement("chk_info");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseSetupWizard::generateSetLed() {
    QString paraLed = m_pReq->parameter("led");
    QString paraStatus = m_pReq->parameter("status");


    QString led = "power blue";

    if(paraLed.compare("0") == 0)
        led = "power blue";
    else if(paraLed.compare("1-0") == 0)
        led = "usb red";
    else if(paraLed.compare("1-1") == 0)
        led = "usb blue";
    else if(paraLed.compare("2-0") == 0)
        led = "hd0 red";
    else if(paraLed.compare("2-1") == 0)
        led = "hd0 blue";
    else if(paraLed.compare("3-0") == 0)
        led = "hd1 red";
    else if(paraLed.compare("3-1") == 0)
        led = "hd1 blue";

    QString status = "on";

    if(paraStatus.compare("0") == 0)
        status = "off";
    else if(paraStatus.compare("1") == 0)
        status = "on";
    else if(paraStatus.compare("2") == 0)
        status = "blinking";

    QStringList apiOut = getAPIStdOut(ENV_PATH + SCRIPT_LED_API + " " + led + " " + status, true);

}

void RenderResponseSetupWizard::generateGetWizard() {

    QDomDocument doc;

    QMap<QString, QString> lan0Info = getNasCfg("lan0");
    QMap<QString, QString> lan1Info = getNasCfg("lan1");
    QVector<QMap<QString, QString>> lanInfo;
    if(lan0Info.isEmpty() || lan1Info.isEmpty())
        return;
    lanInfo << lan0Info << lan1Info;

    QDomElement root = doc.createElement("wizard");
    doc.appendChild(root);

    for(auto e : lanInfo) {
        QDomElement lanElement = doc.createElement("lan");
        root.appendChild(lanElement);

        QDomElement vlanEnableElement = doc.createElement("vlan_enable");
        lanElement.appendChild(vlanEnableElement);
        QDomText vlanEnableValue = doc.createTextNode(e.value("vlan_enable"));
        vlanEnableElement.appendChild(vlanEnableValue);

        QDomElement vlanIDElement = doc.createElement("vlan_id");
        lanElement.appendChild(vlanIDElement);
        QDomText vlanIDValue = doc.createTextNode(e.value("vlan_id"));
        vlanIDElement.appendChild(vlanIDValue);

        QDomElement dhcpEnableElement = doc.createElement("dhcp_enable");
        lanElement.appendChild(dhcpEnableElement);
        QDomText dhcpEnableValue = doc.createTextNode(e.value("dhcp_enable"));
        dhcpEnableElement.appendChild(dhcpEnableValue);

        QDomElement dnsManualElement = doc.createElement("dns_manual");
        lanElement.appendChild(dnsManualElement);
        QDomText dnsManualValue = doc.createTextNode(e.value("dns_manual"));
        dnsManualElement.appendChild(dnsManualValue);

        QDomElement ipElement = doc.createElement("ip");
        lanElement.appendChild(ipElement);
        QDomText ipValue = doc.createTextNode(e.value("ip"));
        ipElement.appendChild(ipValue);

        QDomElement netmaskElement = doc.createElement("netmask");
        lanElement.appendChild(netmaskElement);
        QDomText netmaskValue = doc.createTextNode(e.value("netmask"));
        netmaskElement.appendChild(netmaskValue);

        QDomElement gatewayElement = doc.createElement("gateway");
        lanElement.appendChild(gatewayElement);
        QDomText gatewayValue = doc.createTextNode(e.value("gateway"));
        gatewayElement.appendChild(gatewayValue);

        QDomElement dns1Element = doc.createElement("dns1");
        lanElement.appendChild(dns1Element);
        QDomText dns1Value = doc.createTextNode(e.value("dns1"));
        dns1Element.appendChild(dns1Value);

        QDomElement dns2Element = doc.createElement("dns2");
        lanElement.appendChild(dns2Element);
        QDomText dns2Value = doc.createTextNode(e.value("dns2"));
        dns2Element.appendChild(dns2Value);

    }

    QDomElement systemElement = doc.createElement("system");
    root.appendChild(systemElement);

    QMap<QString, QString> sambaInfo = getNasCfg("samba");
    QMap<QString, QString> timeInfo = getNasCfg("time");

    QDomElement nameElement = doc.createElement("name");
    systemElement.appendChild(nameElement);
    nameElement.appendChild(doc.createTextNode(sambaInfo.value("netbios_name")));

    QDomElement workgroupElement = doc.createElement("workgroup");
    systemElement.appendChild(workgroupElement);
    workgroupElement.appendChild(doc.createTextNode(sambaInfo.value("workgroup")));

    QDomElement descriptionElement = doc.createElement("description");
    systemElement.appendChild(descriptionElement);
    descriptionElement.appendChild(doc.createTextNode(sambaInfo.value("server_string")));

    QDomElement timezoneElement = doc.createElement("timezone");
    systemElement.appendChild(timezoneElement);
    timezoneElement.appendChild(doc.createTextNode(timeInfo.value("timezone")));

    m_var = doc.toString();

}

