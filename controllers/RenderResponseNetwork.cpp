#include <QProcess>

#include "RenderResponseNetwork.h"
#include "AppDefine.h"

RenderResponseNetwork::RenderResponseNetwork(QVariantMap &map, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_renderType = RENDER_TYPE_UNKNOWN;
    m_pMap = &map;
}

RenderResponseNetwork::~RenderResponseNetwork() {
}

RENDER_TYPE RenderResponseNetwork::preRender() {

    if(!m_pMap)
        return RENDER_TYPE_UNKNOWN;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_GET_LLTD:
        generateGetLLTD(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_LAN_XML:
        generateLanXml(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_IPV6:
        generateIPV6(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_LAN_STATUS:
        generateLanStatus(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_LAN_XML2:
        generateLanXml2(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SETIP_LOCK:
        generateSetIPLock(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_IP:
        generateIP(doc);
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_SPEED:
        generateSpeed(doc);
        m_renderType = RENDER_TYPE_UNKNOWN;
        break;
    case CMD_LLTD:
        generateLLTD(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_DDNS:
        generateGetDdns(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_GET_DDNS_STATUS:
        generateGetDdnsStatus(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_DDNS:
        generateDdns(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_PORTFORWARDING_GET:
        generatePortForwardingGet(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_UPNP_TEST:
        generateUpnpTest(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_UPNP_TEST_RESULT:
        generateUpnpTestResult(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_PORTFORWARDING_TOTAL:
        generatePortForwardingTotal(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_GET_PORT_TABLE:
        generateGetPortTable(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_PORTFORWARDING_ADD_SCAN:
        generatePortFrowardingAddScan(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_PORTFORWARDING_ADD:
        generatePortFrowardingAdd(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_PORTFORWARDING_MODIFY:
        generatePortFrowardingModify(str);
        m_renderType = RENDER_TYPE_STRING;
        break;
    case CMD_PORTFORWARDING_DEL:
        generatePortFrowardingDel(str);
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

void RenderResponseNetwork::generateGetLLTD(QDomDocument &doc) {
    QMap<QString, QString> lltdIndo = getNasCfg("lltd");

    QDomElement root = doc.createElement("lltd");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    QDomText text = doc.createTextNode(lltdIndo.value("enable"));
    enableElement.appendChild(text);
}

void RenderResponseNetwork::generateLanXml(QDomDocument &doc) {
    QDomElement root = doc.createElement("info");
    doc.appendChild(root);

    QMap<QString, QString> bondingInfo = getNasCfg("bonding");
    QMap<QString, QString> networkInfo = getNasCfg("network");

    QDomElement bondingEnableElement = doc.createElement("bonding_enable");
    root.appendChild(bondingEnableElement);
    QDomText bondingEnableValue = doc.createTextNode(bondingInfo.value("enable"));
    bondingEnableElement.appendChild(bondingEnableValue);
    QDomElement bondingModeElement = doc.createElement("bonding_mode");
    root.appendChild(bondingModeElement);
    QDomText bondingModeValue = doc.createTextNode(bondingInfo.value("mode"));
    bondingModeElement.appendChild(bondingModeValue);
    QDomElement defaultGatewayElement = doc.createElement("default_gw");
    root.appendChild(defaultGatewayElement);
    QDomText defaultGatewayValue = doc.createTextNode(networkInfo.value("default_gw"));
    defaultGatewayElement.appendChild(defaultGatewayValue);

    QMap<QString, QString> lanInfo = getNasCfg("lan0");
    if(lanInfo.isEmpty())
        return;

    QDomElement lanElement = doc.createElement("lan");
    root.appendChild(lanElement);

    QDomElement speedElement = doc.createElement("speed");
    lanElement.appendChild(speedElement);
    QDomText speedValue = doc.createTextNode(lanInfo.value("speed"));
    speedElement.appendChild(speedValue);

    QDomElement dhcpEnableElement = doc.createElement("dhcp_enable");
    lanElement.appendChild(dhcpEnableElement);
    QDomText dhcpEnableValue = doc.createTextNode(lanInfo.value("dhcp_enable"));
    dhcpEnableElement.appendChild(dhcpEnableValue);

    QDomElement dnsManualElement = doc.createElement("dns_manual");
    lanElement.appendChild(dnsManualElement);
    QDomText dnsManualValue = doc.createTextNode(lanInfo.value("dns_manual"));
    dnsManualElement.appendChild(dnsManualValue);

    QDomElement ipElement = doc.createElement("ip");
    lanElement.appendChild(ipElement);
    QDomText ipValue = doc.createTextNode(lanInfo.value("ip"));
    ipElement.appendChild(ipValue);

    QDomElement netmaskElement = doc.createElement("netmask");
    lanElement.appendChild(netmaskElement);
    QDomText netmaskValue = doc.createTextNode(lanInfo.value("netmask"));
    netmaskElement.appendChild(netmaskValue);

    QDomElement gatewayElement = doc.createElement("gateway");
    lanElement.appendChild(gatewayElement);
    QDomText gatewayValue = doc.createTextNode(lanInfo.value("gateway"));
    gatewayElement.appendChild(gatewayValue);

    QDomElement jumboEnableElement = doc.createElement("jumbo_enable");
    lanElement.appendChild(jumboEnableElement);
    QDomText jumboEnableValue = doc.createTextNode(lanInfo.value("jumbo_enable"));
    jumboEnableElement.appendChild(jumboEnableValue);

    QDomElement jumboMtuElement = doc.createElement("jumbo_mtu");
    lanElement.appendChild(jumboMtuElement);
    QDomText jumboMtuValue = doc.createTextNode(lanInfo.value("jumbo_mtu"));
    jumboMtuElement.appendChild(jumboMtuValue);

    QDomElement lanSpeedElement = doc.createElement("lan_speed");
    lanElement.appendChild(lanSpeedElement);
    QDomText lanSpeedValue = doc.createTextNode(lanInfo.value("lan_speed"));
    lanSpeedElement.appendChild(lanSpeedValue);

    QDomElement partenerSpeedElement = doc.createElement("partener_speed");
    lanElement.appendChild(partenerSpeedElement);
    QDomText partenerSpeedValue = doc.createTextNode(lanInfo.value("partener_speed"));
    partenerSpeedElement.appendChild(partenerSpeedValue);

    QDomElement dns1Element = doc.createElement("dns1");
    lanElement.appendChild(dns1Element);
    QDomText dns1Value = doc.createTextNode(lanInfo.value("dns1"));
    dns1Element.appendChild(dns1Value);

    QDomElement dns2Element = doc.createElement("dns2");
    lanElement.appendChild(dns2Element);
    QDomText dns2Value = doc.createTextNode(lanInfo.value("dns2"));
    dns2Element.appendChild(dns2Value);

    QDomElement vlanEnableElement = doc.createElement("vlan_enable");
    lanElement.appendChild(vlanEnableElement);
    QDomText vlanEnableValue = doc.createTextNode(lanInfo.value("vlan_enable"));
    vlanEnableElement.appendChild(vlanEnableValue);

    QDomElement vlanIDElement = doc.createElement("vlan_id");
    lanElement.appendChild(vlanIDElement);
    QDomText vlanIDValue = doc.createTextNode(lanInfo.value("vlan_id"));
    vlanIDElement.appendChild(vlanIDValue);

}

/* todo */
void RenderResponseNetwork::generateIPV6(QDomDocument &doc) {

}

void RenderResponseNetwork::generateLanStatus(QDomDocument &doc) {
    QMap<QString, QString> lanInfo = getNasCfg("lan0");
    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement speed1 = doc.createElement("lan1_speed");
    root.appendChild(speed1);
    QDomText value1 = doc.createTextNode(lanInfo.value("speed"));
    speed1.appendChild(value1);
//    QDomElement speed2 = doc.createElement("lan2_speed");
//    root.appendChild(speed2);
//    QDomText value2 = doc.createTextNode("0");
//    speed2.appendChild(value2);
}

void RenderResponseNetwork::generateLanXml2(QDomDocument &doc) {
    QMap<QString, QString> lanInfo = getNasCfg("lan0");
    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement ip1 = doc.createElement("ip1");
    root.appendChild(ip1);
    QDomText value1 = doc.createTextNode(lanInfo.value("ip"));
    ip1.appendChild(value1);
//    QDomElement ip2 = doc.createElement("ip2");
//    root.appendChild(ip2);
//    QDomText value2 = doc.createTextNode("192.168.100.220");
//    ip2.appendChild(value2);
}

/* todo */
void RenderResponseNetwork::generateSetIPLock(QDomDocument &doc) {

    QString paraLan;

    if(m_pMap->contains("lan"))
        paraLan = m_pMap->value("lan").toString();
}

void RenderResponseNetwork::generateIP(QDomDocument &doc) {

    QString paraDhcpEnable, paraIP, paraGateway,
            paraNetmask, paraDns1, paraDns2,
            paraVlanEnable, paraVlanID, paraDnsManual,
            paraLan;

    if(m_pMap->contains("f_dhcp_enable"))
        paraDhcpEnable = m_pMap->value("f_dhcp_enable").toString();
    if(m_pMap->contains("f_ip"))
        paraIP = m_pMap->value("f_ip").toString();
    if(m_pMap->contains("f_gateway"))
        paraGateway = m_pMap->value("f_gateway").toString();
    if(m_pMap->contains("f_netmask"))
        paraNetmask = m_pMap->value("f_netmask").toString();
    if(m_pMap->contains("f_dns1"))
        paraDns1 = m_pMap->value("f_dns1").toString();
    if(m_pMap->contains("f_dns2"))
        paraDns2 = m_pMap->value("f_dns2").toString();
    if(m_pMap->contains("vlan_enable"))
        paraVlanEnable = m_pMap->value("vlan_enable").toString();
    if(m_pMap->contains("vlan_id"))
        paraVlanID = m_pMap->value("vlan_id").toString();
    if(m_pMap->contains("f_dns_manual"))
        paraDnsManual = m_pMap->value("f_dns_manual").toString();
    if(m_pMap->contains("lan"))
        paraLan = m_pMap->value("lan").toString();

    if(paraLan.compare("0") == 0) {
        QMap<QString, QString> map;
        map.insert("dhcp_enable", paraDhcpEnable);
        map.insert("ip", paraIP);
        map.insert("gateway", paraGateway);
        map.insert("netmask", paraNetmask);

        if(paraDnsManual.compare("1") == 0) {
            map.insert("dns1", paraDns1);
            map.insert("dns2", paraDns1);
        }
        map.insert("dns_manual", paraDnsManual);
        map.insert("vlan_enable", paraVlanEnable);
        map.insert("vlan_id", paraVlanID);

        if(setNasCfg("lan0", map)) {
#ifndef SIMULATOR_MODE
            QProcess process;
            QStringList arg;
            arg << "restart";
            process.start(NETWORK_SCRIPT, arg);
#endif
        }
    }
}

void RenderResponseNetwork::generateSpeed(QDomDocument &doc) {
    QString paraSpeed;

    if(m_pMap->contains("lan0"))
        paraSpeed = m_pMap->value("lan0").toString();

    setNasCfg("lan0", "speed", paraSpeed);
}

void RenderResponseNetwork::generateLLTD(QDomDocument &doc) {

    QString paraEnable;

    if(m_pMap->contains("f_enable"))
        paraEnable = m_pMap->value("f_enable").toString();

    if(setNasCfg("lltd", "enable", paraEnable)) {
        getAPIStdOut(API_PATH + SCRIPT_LLTD_CTL + " start");
    }
}

void RenderResponseNetwork::generateGetDdns(QDomDocument &doc) {
    QMap<QString, QString> ddnsInfo = getNasCfg("ddns");

    QDomElement root = doc.createElement("ddns");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    QDomText enableValue = doc.createTextNode(ddnsInfo.value("enable"));
    enableElement.appendChild(enableValue);

    QDomElement usernameElement = doc.createElement("username");
    root.appendChild(usernameElement);
    QDomText usernameValue = doc.createTextNode(ddnsInfo.value("username"));
    usernameElement.appendChild(usernameValue);

    QDomElement pwdElement = doc.createElement("pwd");
    root.appendChild(pwdElement);
    QDomText pwdValue = doc.createTextNode(ddnsInfo.value("pwd"));
    pwdElement.appendChild(pwdValue);

    QDomElement domainElement = doc.createElement("domain");
    root.appendChild(domainElement);
    QDomText domainValue = doc.createTextNode(ddnsInfo.value("domain"));
    domainElement.appendChild(domainValue);

    QDomElement serverElement = doc.createElement("server");
    root.appendChild(serverElement);
    QDomText serverValue = doc.createTextNode(ddnsInfo.value("server"));
    serverElement.appendChild(serverValue);

    QDomElement timeoutElement = doc.createElement("timeout");
    root.appendChild(timeoutElement);

    bool ok = false;
    int iTimeout = ddnsInfo.value("timeout").toInt(&ok);
    QDomText timeoutValue;
    if(ok)
        timeoutValue = doc.createTextNode(QString::number(iTimeout/60/60));
    timeoutElement.appendChild(timeoutValue);
}

void RenderResponseNetwork::generateGetDdnsStatus(QDomDocument &doc) {

    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_DDNS_CTL + " -S");
    if(apiOutList.size() < 5)
        return;

    QDomElement root = doc.createElement("ddns");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    QDomText statusValue = doc.createTextNode(apiOutList.at(1));
    statusElement.appendChild(statusValue);

    QDomElement updatetimeElement = doc.createElement("updatetime");
    root.appendChild(updatetimeElement);

    bool ok = false;
    QDomText updateTimeValue;
    uint iUpdateTime = apiOutList.at(2).toInt(&ok);
    if(ok) {
        QDateTime update = QDateTime::fromTime_t(iUpdateTime);
        updateTimeValue = doc.createTextNode(update.toString("yyyy/M/d h:m:s"));
    }
    updatetimeElement.appendChild(updateTimeValue);

    QDomElement nexttimeElement = doc.createElement("nexttime");
    root.appendChild(nexttimeElement);

    ok = false;
    QDomText nextTimeValue;
    uint iNextTime = apiOutList.at(3).toInt(&ok);
    if(ok) {
        QDateTime next = QDateTime::fromTime_t(iNextTime);
        nextTimeValue = doc.createTextNode(next.toString("yyyy/M/d h:m:s"));
    }
    nexttimeElement.appendChild(nextTimeValue);
}

void RenderResponseNetwork::generateDdns(QDomDocument &doc) {

    QString paraEnable, paraDdnsServer, paraDdnsDomain,
            paraDdnsUsername, paraPassword, paraRePassword;

    if(m_pMap->contains("f_enable"))
        paraEnable = m_pMap->value("f_enable").toString();
    if(m_pMap->contains("f_ddns_server"))
        paraDdnsServer = m_pMap->value("f_ddns_server").toString();
    if(m_pMap->contains("f_ddns_domain"))
        paraDdnsDomain = m_pMap->value("f_ddns_domain").toString();
    if(m_pMap->contains("f_ddns_username"))
        paraDdnsUsername = m_pMap->value("f_ddns_username").toString();
    if(m_pMap->contains("f_ddns_password"))
        paraPassword = m_pMap->value("f_ddns_password").toString();
    if(m_pMap->contains("f_ddns_re_password"))
        paraRePassword = m_pMap->value("f_ddns_re_password").toString();

    if(paraPassword.compare(paraRePassword) != 0)
        return;

    QMap<QString, QString> map;
    map.insert("enable", paraEnable);
    map.insert("server", paraDdnsServer);
    map.insert("domain", paraDdnsDomain);
    map.insert("username", paraDdnsUsername);
    map.insert("pwd", paraPassword);

    if(setNasCfg("ddns", map)) {
        getAPIStdOut(API_PATH + SCRIPT_DDNS_CTL + " -T");
    }

    generateGetDdns(doc);
}

/* todo */
void RenderResponseNetwork::generatePortForwardingGet(QDomDocument &doc) {
    QString paraPage, paraRp, paraSortname,
            paraSortOrder, paraQuery, paraQType,
            paraField, paraUser;

    QString strCheckboxEnable = "&lt;input type='checkbox' checked disabled class='scan'&gt";
    QString strCheckboxDisable = "&lt;input type='checkbox' disabled class='scan'&gt";

    if(m_pMap->contains("page"))
        paraPage = m_pMap->value("page").toString();
    if(m_pMap->contains("rp"))
        paraRp = m_pMap->value("rp").toString();
    if(m_pMap->contains("sortname"))
        paraSortname = m_pMap->value("sortname").toString();
    if(m_pMap->contains("sortorder"))
        paraSortOrder = m_pMap->value("sortorder").toString();
    if(m_pMap->contains("query"))
        paraQuery = m_pMap->value("query").toString();
    if(m_pMap->contains("qtype"))
        paraQType = m_pMap->value("qtype").toString();
    if(m_pMap->contains("f_field"))
        paraField = m_pMap->value("f_field").toString();
    if(m_pMap->contains("user"))
        paraUser = m_pMap->value("user").toString();

    for(int i=0; i<3; i++) {
        QDomElement root = doc.createElement("rows");
        doc.appendChild(root);
        QDomElement rowElement1 = doc.createElement("row");
        root.appendChild(rowElement1);
        rowElement1.setAttribute("id", "0");
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement1.appendChild(cellElement1);
        QDomText cellValue1 = doc.createTextNode(strCheckboxEnable);
        cellElement1.appendChild(cellValue1);

        QDomElement cellElement2 = doc.createElement("cell");
        rowElement1.appendChild(cellElement2);
        QDomText cellValue2 = doc.createTextNode("OK");
        cellElement2.appendChild(cellValue2);

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement1.appendChild(cellElement3);
        QDomText cellValue3 = doc.createTextNode("BitTorrent");
        cellElement3.appendChild(cellValue3);

        QDomElement cellElement4 = doc.createElement("cell");
        rowElement1.appendChild(cellElement4);
        QDomText cellValue4 = doc.createTextNode("TCP");
        cellElement4.appendChild(cellValue4);

        QDomElement cellElement5 = doc.createElement("cell");
        rowElement1.appendChild(cellElement5);
        QDomText cellValue5 = doc.createTextNode("6882");
        cellElement5.appendChild(cellValue5);

        QDomElement cellElement6 = doc.createElement("cell");
        rowElement1.appendChild(cellElement6);
        QDomText cellValue6 = doc.createTextNode("6882");
        cellElement6.appendChild(cellValue6);
    }
}

/* todo */
void RenderResponseNetwork::generateUpnpTest(QString &str) {
    str = "Not Found";
}

/* todo */
void RenderResponseNetwork::generateUpnpTestResult(QString &str) {
    str = "Found";
}

/* todo */
void RenderResponseNetwork::generatePortForwardingTotal(QString &str) {
    str = "23";
}

/* todo */
void RenderResponseNetwork::generateGetPortTable(QDomDocument &doc) {

    QDomElement root = doc.createElement("root");
    doc.appendChild(root);
    for(int i=0; i<5; i++) {
        QDomElement portElement = doc.createElement("port");
        root.appendChild(portElement);
        QDomElement serviceElement = doc.createElement("service");
        portElement.appendChild(serviceElement);
        QDomText serviceValue = doc.createTextNode("BitTorrent");
        serviceElement.appendChild(serviceValue);
        QDomElement protocolElement = doc.createElement("protocol");
        portElement.appendChild(protocolElement);
        QDomText protocolValue = doc.createTextNode("TCP");
        protocolElement.appendChild(protocolValue);
        QDomElement localPortElement = doc.createElement("local_port");
        portElement.appendChild(localPortElement);
        QDomText portValue = doc.createTextNode("6883");
        localPortElement.appendChild(portValue);
    }
}

/* todo */
void RenderResponseNetwork::generatePortFrowardingAddScan(QString &str) {
    QString paraService, paraEnable, paraProtocol,
            paraPPort, paraEPort;

    if(m_pMap->contains("service"))
        paraService = m_pMap->value("service").toString();
    if(m_pMap->contains("enable"))
        paraEnable = m_pMap->value("enable").toString();
    if(m_pMap->contains("protocol"))
        paraProtocol = m_pMap->value("protocol").toString();
    if(m_pMap->contains("p_port"))
        paraPPort = m_pMap->value("p_port").toString();
    if(m_pMap->contains("e_port"))
        paraEPort = m_pMap->value("e_port").toString();

    str = "error";
}

/* todo */
void RenderResponseNetwork::generatePortFrowardingAdd(QString &str) {
    QString paraService, paraEnable, paraProtocol,
            paraPPort, paraEPort;

    if(m_pMap->contains("enable"))
        paraEnable = m_pMap->value("enable").toString();
    if(m_pMap->contains("protocol"))
        paraProtocol = m_pMap->value("protocol").toString();
    if(m_pMap->contains("p_port"))
        paraPPort = m_pMap->value("p_port").toString();
    if(m_pMap->contains("e_port"))
        paraEPort = m_pMap->value("e_port").toString();
    if(m_pMap->contains("service"))
        paraService = m_pMap->value("service").toString();

    str = "OK1";
}

/* todo */
void RenderResponseNetwork::generatePortFrowardingModify(QString &str) {
    QString paraService, paraEnable, paraProtocol,
            paraPPort, paraEPort, paraScan,
            paraOldEPort;

    if(m_pMap->contains("enable"))
        paraEnable = m_pMap->value("enable").toString();
    if(m_pMap->contains("protocol"))
        paraProtocol = m_pMap->value("protocol").toString();
    if(m_pMap->contains("p_port"))
        paraPPort = m_pMap->value("p_port").toString();
    if(m_pMap->contains("e_port"))
        paraEPort = m_pMap->value("e_port").toString();
    if(m_pMap->contains("service"))
        paraService = m_pMap->value("service").toString();
    if(m_pMap->contains("scan"))
        paraScan = m_pMap->value("scan").toString();
    if(m_pMap->contains("old_e_port"))
        paraOldEPort = m_pMap->value("old_e_port").toString();

    str = "OK1";
}

/* todo */
void RenderResponseNetwork::generatePortFrowardingDel(QString &str) {
    QString paraService, paraProtocol,
            paraPPort, paraEPort, paraScan;

    if(m_pMap->contains("protocol"))
        paraProtocol = m_pMap->value("protocol").toString();
    if(m_pMap->contains("p_port"))
        paraPPort = m_pMap->value("p_port").toString();
    if(m_pMap->contains("e_port"))
        paraEPort = m_pMap->value("e_port").toString();
    if(m_pMap->contains("service"))
        paraService = m_pMap->value("service").toString();
    if(m_pMap->contains("scan"))
        paraScan = m_pMap->value("scan").toString();

    str = "ok";
}
