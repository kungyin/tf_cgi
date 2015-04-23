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
    QDomElement root = doc.createElement("lltd");
    doc.appendChild(root);
    QDomElement enable = doc.createElement("enable");
    root.appendChild(enable);
    QDomText text = doc.createTextNode("0");
    enable.appendChild(text);
}

void RenderResponseNetwork::generateLanXml(QDomDocument &doc) {
    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement bondingEnableElement = doc.createElement("bonding_enable");
    root.appendChild(bondingEnableElement);
    QDomText bondingEnableValue = doc.createTextNode("1");
    bondingEnableElement.appendChild(bondingEnableValue);
    QDomElement bondingModeElement = doc.createElement("bonding_mode");
    root.appendChild(bondingModeElement);
    QDomText bondingModeValue = doc.createTextNode("0");
    bondingModeElement.appendChild(bondingModeValue);
    QDomElement defaultGatewayElement = doc.createElement("default_gw");
    root.appendChild(defaultGatewayElement);
    QDomText defaultGatewayValue = doc.createTextNode("lan0");
    defaultGatewayElement.appendChild(defaultGatewayValue);

    QDomElement lanElement = doc.createElement("lan");
    root.appendChild(lanElement);
    for(int i=0; i<2; i++) {
        QDomElement speedElement = doc.createElement("speed");
        lanElement.appendChild(speedElement);
        QDomText speedValue = doc.createTextNode("0");
        speedElement.appendChild(speedValue);

        QDomElement dhcpEnableElement = doc.createElement("dhcp_enable");
        lanElement.appendChild(dhcpEnableElement);
        QDomText dhcpEnableValue = doc.createTextNode("1");
        dhcpEnableElement.appendChild(dhcpEnableValue);

        QDomElement dnsManualElement = doc.createElement("dns_manual");
        lanElement.appendChild(dnsManualElement);
        QDomText dnsManualValue = doc.createTextNode("0");
        dnsManualElement.appendChild(dnsManualValue);

        QDomElement ipElement = doc.createElement("ip");
        lanElement.appendChild(ipElement);
        QDomText ipValue = doc.createTextNode("192.168.100.203");
        ipElement.appendChild(ipValue);

        QDomElement netmaskElement = doc.createElement("netmask");
        lanElement.appendChild(netmaskElement);
        QDomText netmaskValue = doc.createTextNode("255.255.255.0");
        netmaskElement.appendChild(netmaskValue);

        QDomElement gatewayElement = doc.createElement("gateway");
        lanElement.appendChild(gatewayElement);
        QDomText gatewayValue = doc.createTextNode("192.168.100.5");
        gatewayElement.appendChild(gatewayValue);

        QDomElement jumboEnableElement = doc.createElement("jumbo_enable");
        lanElement.appendChild(jumboEnableElement);
        QDomText jumboEnableValue = doc.createTextNode("0");
        jumboEnableElement.appendChild(jumboEnableValue);

        QDomElement jumboMtuElement = doc.createElement("jumbo_mtu");
        lanElement.appendChild(jumboMtuElement);
        QDomText jumboMtuValue = doc.createTextNode("1500");
        jumboMtuElement.appendChild(jumboMtuValue);

        QDomElement lanSpeedElement = doc.createElement("lan_speed");
        lanElement.appendChild(lanSpeedElement);
        QDomText lanSpeedValue = doc.createTextNode("100");
        lanSpeedElement.appendChild(lanSpeedValue);

        QDomElement partenerSpeedElement = doc.createElement("partener_speed");
        lanElement.appendChild(partenerSpeedElement);
        QDomText partenerSpeedValue = doc.createTextNode("100");
        partenerSpeedElement.appendChild(partenerSpeedValue);

        QDomElement dns1Element = doc.createElement("dns1");
        lanElement.appendChild(dns1Element);
        QDomText dns1Value = doc.createTextNode("192.168.100.5");
        dns1Element.appendChild(dns1Value);

        QDomElement dns2Element = doc.createElement("dns2");
        lanElement.appendChild(dns2Element);
        QDomText dns2Value = doc.createTextNode("8.8.8.8");
        dns2Element.appendChild(dns2Value);

        QDomElement vlanEnableElement = doc.createElement("vlan_enable");
        lanElement.appendChild(vlanEnableElement);
        QDomText vlanEnableValue = doc.createTextNode("0");
        vlanEnableElement.appendChild(vlanEnableValue);

        QDomElement vlanIDElement = doc.createElement("vlan_id");
        lanElement.appendChild(vlanIDElement);
        QDomText vlanIDValue = doc.createTextNode("1");
        vlanIDElement.appendChild(vlanIDValue);
    }
}

/* todo */
void RenderResponseNetwork::generateIPV6(QDomDocument &doc) {

}

void RenderResponseNetwork::generateLanStatus(QDomDocument &doc) {
    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement speed1 = doc.createElement("lan1_speed");
    root.appendChild(speed1);
    QDomText value1 = doc.createTextNode("100");
    speed1.appendChild(value1);
    QDomElement speed2 = doc.createElement("lan2_speed");
    root.appendChild(speed2);
    QDomText value2 = doc.createTextNode("0");
    speed2.appendChild(value2);
}

void RenderResponseNetwork::generateLanXml2(QDomDocument &doc) {
    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement ip1 = doc.createElement("ip1");
    root.appendChild(ip1);
    QDomText value1 = doc.createTextNode("169.254.153.61");
    ip1.appendChild(value1);
    QDomElement ip2 = doc.createElement("ip2");
    root.appendChild(ip2);
    QDomText value2 = doc.createTextNode("192.168.100.220");
    ip2.appendChild(value2);
}

/* todo */
void RenderResponseNetwork::generateSetIPLock(QDomDocument &doc) {

    QString paraLan;

    if(m_pMap->contains("lan"))
        paraLan = m_pMap->value("lan").toString();
}

/* todo */
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
}


/* todo */
void RenderResponseNetwork::generateLLTD(QDomDocument &doc) {

    QString paraEnable;

    if(m_pMap->contains("f_enable"))
        paraEnable = m_pMap->value("f_enable").toString();
}

void RenderResponseNetwork::generateGetDdns(QDomDocument &doc) {
    QDomElement root = doc.createElement("ddns");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    QDomText enableValue = doc.createTextNode("0");
    enableElement.appendChild(enableValue);
    QDomElement usernameElement = doc.createElement("username");
    root.appendChild(usernameElement);
    QDomElement pwdElement = doc.createElement("pwd");
    root.appendChild(pwdElement);
    QDomElement domainElement = doc.createElement("domain");
    root.appendChild(domainElement);
    QDomElement serverElement = doc.createElement("server");
    root.appendChild(serverElement);
    QDomElement timeoutElement = doc.createElement("timeout");
    root.appendChild(timeoutElement);
    QDomText timeoutValue = doc.createTextNode("576");
    timeoutElement.appendChild(timeoutValue);
}

void RenderResponseNetwork::generateGetDdnsStatus(QDomDocument &doc) {
    QDomElement root = doc.createElement("ddns");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    QDomText statusValue = doc.createTextNode("continue");
    statusElement.appendChild(statusValue);
    QDomElement updatetimeElement = doc.createElement("updatetime");
    root.appendChild(updatetimeElement);
    QDomElement nexttimeElement = doc.createElement("nexttime");
    root.appendChild(nexttimeElement);
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


    QDomElement root = doc.createElement("ddns");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    QDomText enableValue = doc.createTextNode("0");
    enableElement.appendChild(enableValue);
    QDomElement usernameElement = doc.createElement("username");
    root.appendChild(usernameElement);
    QDomElement pwdElement = doc.createElement("pwd");
    root.appendChild(pwdElement);
    QDomElement domainElement = doc.createElement("domain");
    root.appendChild(domainElement);
    QDomElement serverElement = doc.createElement("server");
    root.appendChild(serverElement);
    QDomElement timeoutElement = doc.createElement("timeout");
    root.appendChild(timeoutElement);
    QDomText timeoutValue = doc.createTextNode("576");
    timeoutElement.appendChild(timeoutValue);
}

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

void RenderResponseNetwork::generateUpnpTest(QString &str) {
    str = "Not Found";
}

void RenderResponseNetwork::generateUpnpTestResult(QString &str) {
    str = "Found";
}

void RenderResponseNetwork::generatePortForwardingTotal(QString &str) {
    str = "23";
}

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

