#include <QProcess>

#include "RenderResponseNetwork.h"

RenderResponseNetwork::RenderResponseNetwork(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseNetwork::~RenderResponseNetwork() {
}

void RenderResponseNetwork::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_GET_LLTD:
        generateGetLLTD();
        break;
    case CMD_LAN_XML:
        generateLanXml();
        break;
    case CMD_IPV6:
        generateIPV6();
        break;
    case CMD_LAN_STATUS:
        generateLanStatus();
        break;
    case CMD_LAN_XML2:
        generateLanXml2();
        break;
    case CMD_SETIP_LOCK:
        generateSetIPLock();
        break;
    case CMD_IP:
        generateIP();
        break;
    case CMD_DEFAULT_GW:
        generateDefaultGw();
        break;
    case CMD_SET_IPV6:
        generateSetIPv6();
        break;
    case CMD_CHK_IPV6_ADDR:
        generateChkIPv6Addr();
        break;
    case CMD_CHK_GW_ADDR:
        generateChkGwAddr();
        break;
    case CMD_SPEED:
        generateSpeed();
        break;
    case CMD_LLTD:
        generateLLTD();
        break;
    case CMD_GET_DDNS:
        generateGetDdns();
        break;
    case CMD_GET_DDNS_STATUS:
        generateGetDdnsStatus();
        break;
    case CMD_DDNS:
        generateDdns();
        break;
    case CMD_PORTFORWARDING_GET:
        generatePortForwardingGet();
        break;
    case CMD_UPNP_TEST:
        generateUpnpTest();
        break;
    case CMD_UPNP_TEST_RESULT:
        generateUpnpTestResult();
        break;
    case CMD_PORTFORWARDING_TOTAL:
        generatePortForwardingTotal();
        break;
    case CMD_GET_PORT_TABLE:
        generateGetPortTable();
        break;
    case CMD_PORTFORWARDING_ADD_SCAN:
        generatePortFrowardingAddScan();
        break;
    case CMD_PORTFORWARDING_ADD:
        generatePortFrowardingAdd();
        break;
    case CMD_PORTFORWARDING_MODIFY:
        generatePortFrowardingModify();
        break;
    case CMD_PORTFORWARDING_DEL:
        generatePortFrowardingDel();
        break;
    case CMD_PORTFORWARDING_GET_PORT:
        generatePortFrowardingGetPort();
        break;
    case CMD_GET_SSH_PORT:
        generateGetSshPort();
        break;
    case CMD_SET_SSH_PORT:
        generateSetSshPort();
        break;

    default:
        break;
    }

}

void RenderResponseNetwork::generateGetLLTD() {

    QDomDocument doc;
    QMap<QString, QString> lltdIndo = getNasCfg("lltd");

    QDomElement root = doc.createElement("lltd");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    QDomText text = doc.createTextNode(lltdIndo.value("enable"));
    enableElement.appendChild(text);

    m_var = doc.toString();

}

void RenderResponseNetwork::generateLanXml() {

    QDomDocument doc;

    QStringList arg = QStringList() << "network_check_lan_speed";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

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

    QMap<QString, QString> lan0Info = getNasCfg("lan0");
    QMap<QString, QString> lan1Info = getNasCfg("lan1");
    QVector<QMap<QString, QString>> lanInfo;
    if(lan0Info.isEmpty() || lan1Info.isEmpty())
        return;
    lanInfo << lan0Info << lan1Info;

    for(auto e : lanInfo) {
        QDomElement lanElement = doc.createElement("lan");
        root.appendChild(lanElement);

        QDomElement speedElement = doc.createElement("speed");
        lanElement.appendChild(speedElement);
        QDomText speedValue = doc.createTextNode(e.value("speed"));
        speedElement.appendChild(speedValue);

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

        QDomElement jumboEnableElement = doc.createElement("jumbo_enable");
        lanElement.appendChild(jumboEnableElement);
        QDomText jumboEnableValue = doc.createTextNode(e.value("jumbo_enable"));
        jumboEnableElement.appendChild(jumboEnableValue);

        QDomElement jumboMtuElement = doc.createElement("jumbo_mtu");
        lanElement.appendChild(jumboMtuElement);
        QDomText jumboMtuValue = doc.createTextNode(e.value("jumbo_mtu"));
        jumboMtuElement.appendChild(jumboMtuValue);

        QDomElement lanSpeedElement = doc.createElement("lan_speed");
        lanElement.appendChild(lanSpeedElement);
        QDomText lanSpeedValue = doc.createTextNode(e.value("lan_speed"));
        lanSpeedElement.appendChild(lanSpeedValue);

        QDomElement partenerSpeedElement = doc.createElement("partener_speed");
        lanElement.appendChild(partenerSpeedElement);
        QDomText partenerSpeedValue = doc.createTextNode(e.value("partener_speed"));
        partenerSpeedElement.appendChild(partenerSpeedValue);

        QDomElement dns1Element = doc.createElement("dns1");
        lanElement.appendChild(dns1Element);
        QDomText dns1Value = doc.createTextNode(e.value("dns1"));
        dns1Element.appendChild(dns1Value);

        QDomElement dns2Element = doc.createElement("dns2");
        lanElement.appendChild(dns2Element);
        QDomText dns2Value = doc.createTextNode(e.value("dns2"));
        dns2Element.appendChild(dns2Value);

        QDomElement vlanEnableElement = doc.createElement("vlan_enable");
        lanElement.appendChild(vlanEnableElement);
        QDomText vlanEnableValue = doc.createTextNode(e.value("vlan_enable"));
        vlanEnableElement.appendChild(vlanEnableValue);

        QDomElement vlanIDElement = doc.createElement("vlan_id");
        lanElement.appendChild(vlanIDElement);
        QDomText vlanIDValue = doc.createTextNode(e.value("vlan_id"));
        vlanIDElement.appendChild(vlanIDValue);
    }

    m_var = doc.toString();

}

void RenderResponseNetwork::generateIPV6() {

    QDomDocument doc;

    QDomElement root = doc.createElement("ipv6");
    doc.appendChild(root);

    QMap<QString, QString> bondingInfo = getNasCfg("bonding");
    QMap<QString, QString> ipv6Lan0Info = getNasCfg("lan0_ipv6");
    QMap<QString, QString> ipv6Lan1Info = getNasCfg("lan1_ipv6");

    QStringList ipv6ContentElement(QStringList()
        << "bonding_enable" << "bonding_mode" << "local_addr");

    QDomElement bondingEnableElement = doc.createElement(ipv6ContentElement.value(0));
    root.appendChild(bondingEnableElement);
    bondingEnableElement.appendChild(doc.createTextNode(bondingInfo.value("enable")));
    QDomElement bondingModeElement = doc.createElement(ipv6ContentElement.value(1));
    root.appendChild(bondingModeElement);
    bondingModeElement.appendChild(doc.createTextNode(bondingInfo.value("mode")));
    QDomElement localAddrElement = doc.createElement(ipv6ContentElement.value(2));
    root.appendChild(localAddrElement);
    localAddrElement.appendChild(doc.createTextNode(ipv6Lan0Info.value("local_ipv6address")));

    QVector<QMap<QString, QString>> ipv6LanInfo;
    if(ipv6Lan0Info.isEmpty() || ipv6Lan1Info.isEmpty())
        return;
    ipv6LanInfo << ipv6Lan0Info << ipv6Lan1Info;

    for(auto e : ipv6LanInfo) {
        QDomElement interfaceElement = doc.createElement("interface");
        root.appendChild(interfaceElement);

        QDomElement modeElement = doc.createElement("mode");
        interfaceElement.appendChild(modeElement);
        modeElement.appendChild(doc.createTextNode(e.value("mode")));

        QDomElement itemElement = doc.createElement("item");
        interfaceElement.appendChild(itemElement);
        QDomElement addrElement = doc.createElement("addr");
        itemElement.appendChild(addrElement);
        addrElement.appendChild(doc.createTextNode(e.value("ipv6address")));
        QDomElement prefixElement = doc.createElement("prefix");
        itemElement.appendChild(prefixElement);
        prefixElement.appendChild(doc.createTextNode(e.value("prefix_length")));

        QDomElement gwElement = doc.createElement("gw");
        interfaceElement.appendChild(gwElement);
        gwElement.appendChild(doc.createTextNode(e.value("gateway")));
        QDomElement dns1Element = doc.createElement("dns1");
        interfaceElement.appendChild(dns1Element);
        dns1Element.appendChild(doc.createTextNode(e.value("dns1")));
        QDomElement dns2Element = doc.createElement("dns2");
        interfaceElement.appendChild(dns2Element);
        dns2Element.appendChild(doc.createTextNode(e.value("dns2")));
    }

    m_var = doc.toString();

}

void RenderResponseNetwork::generateLanStatus() {

    QDomDocument doc;
    QMap<QString, QString> lan0Info = getNasCfg("lan0");
    QMap<QString, QString> lan1Info = getNasCfg("lan1");

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement speed1 = doc.createElement("lan1_speed");
    root.appendChild(speed1);
    QDomText value1 = doc.createTextNode(lan0Info.value("speed"));
    speed1.appendChild(value1);
    QDomElement speed2 = doc.createElement("lan2_speed");
    root.appendChild(speed2);
    QDomText value2 = doc.createTextNode(lan1Info.value("speed"));
    speed2.appendChild(value2);

    m_var = doc.toString();

}

void RenderResponseNetwork::generateLanXml2() {

    QDomDocument doc;
    //QMap<QString, QString> lan0Info = getNasCfg("lan0");
    QMap<QString, QString> lan1Info = getNasCfg("lan1");

    /* Get IP before changing */
    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_GET_IP + " 0", true);

    QDomElement root = doc.createElement("info");
    doc.appendChild(root);
    QDomElement ip1 = doc.createElement("ip1");
    root.appendChild(ip1);
    QDomText value1 = doc.createTextNode(apiOutList.value(0));
    ip1.appendChild(value1);
    QDomElement ip2 = doc.createElement("ip2");
    root.appendChild(ip2);
    QDomText value2 = doc.createTextNode(lan1Info.value("ip"));
    ip2.appendChild(value2);

#ifndef SIMULATOR_MODE
    tDebug("exec: %s", NETWORK_SCRIPT.toLocal8Bit().data());
    if(!startDetached(NETWORK_SCRIPT, QStringList() << "restart"))
        tError("process cannot be started: %s", NETWORK_SCRIPT.toLocal8Bit().data());
#endif

    m_var = doc.toString();

}

/* todo */
void RenderResponseNetwork::generateSetIPLock() {

    QString paraLan;

    if(m_pReq->allParameters().contains("lan"))
        paraLan = m_pReq->allParameters().value("lan").toString();
}

void RenderResponseNetwork::generateIP() {

    QString paraDhcpEnable, paraIP, paraGateway,
            paraNetmask, paraDns1, paraDns2,
            paraVlanEnable, paraVlanID, paraDnsManual,
            paraLan;

    if(m_pReq->allParameters().contains("f_dhcp_enable"))
        paraDhcpEnable = m_pReq->allParameters().value("f_dhcp_enable").toString();
    if(m_pReq->allParameters().contains("f_ip"))
        paraIP = m_pReq->allParameters().value("f_ip").toString();
    if(m_pReq->allParameters().contains("f_gateway"))
        paraGateway = m_pReq->allParameters().value("f_gateway").toString();
    if(m_pReq->allParameters().contains("f_netmask"))
        paraNetmask = m_pReq->allParameters().value("f_netmask").toString();
    if(m_pReq->allParameters().contains("f_dns1"))
        paraDns1 = m_pReq->allParameters().value("f_dns1").toString();
    if(m_pReq->allParameters().contains("f_dns2"))
        paraDns2 = m_pReq->allParameters().value("f_dns2").toString();
    if(m_pReq->allParameters().contains("vlan_enable"))
        paraVlanEnable = m_pReq->allParameters().value("vlan_enable").toString();
    if(m_pReq->allParameters().contains("vlan_id"))
        paraVlanID = m_pReq->allParameters().value("vlan_id").toString();
    if(m_pReq->allParameters().contains("f_dns_manual"))
        paraDnsManual = m_pReq->allParameters().value("f_dns_manual").toString();
    if(m_pReq->allParameters().contains("lan"))
        paraLan = m_pReq->allParameters().value("lan").toString();

    /* only set Lan0 now */
    if(paraLan.compare("0") == 0) {
        QMap<QString, QString> map;
        map.insert("dhcp_enable", paraDhcpEnable);
        map.insert("ip", paraIP);
        map.insert("gateway", paraGateway);
        map.insert("netmask", paraNetmask);

        if(paraDnsManual.compare("1") == 0) {
            map.insert("dns1", paraDns1);
            map.insert("dns2", paraDns2);
        }
        map.insert("dns_manual", paraDnsManual);
        map.insert("vlan_enable", paraVlanEnable);
        map.insert("vlan_id", paraVlanID);

        if(!setNasCfg("lan0", map))
            tDebug("setNasCfg lan0 failed");
    }
}

/* todo */
void RenderResponseNetwork::generateDefaultGw() {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    QString paraDefaultGw = m_pReq->parameter("default_gw");
}

void RenderResponseNetwork::generateSetIPv6() {

    QString paraLan = m_pReq->parameter("f_lan");
    QString paraIPv6Mode = m_pReq->parameter("f_ipv6_mode");
    QString paraIPv6Addr = m_pReq->parameter("f_ipv6_addr");
    QString paraIPv6Gw = m_pReq->parameter("f_ipv6_gw");
    QString paraIPv6Prefix = m_pReq->parameter("f_ipv6_prefix");
    QString paraIPv6Dns1 = m_pReq->parameter("f_ipv6_dns1");
    QString paraIPv6Dns2 = m_pReq->parameter("f_ipv6_dns2");

    /* only set Lan0 now */
    if(paraLan.compare("0") == 0) {
        QMap<QString, QString> map;
        map.insert("mode", paraIPv6Mode);
        map.insert("ipv6address", paraIPv6Addr);
        map.insert("gateway", paraIPv6Gw);
        map.insert("prefix_length", paraIPv6Prefix);
        map.insert("dns1", paraIPv6Dns1);
        map.insert("dns2", paraIPv6Dns2);

        if(!setNasCfg("lan0_ipv6", map))
            tDebug("setNasCfg lan0_ipv6 failed");
    }

    /* wrong API */
    QStringList arg = QStringList() << "network_set_ipv6";
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg);

}

void RenderResponseNetwork::generateChkIPv6Addr() {
    QDomDocument doc;

    QStringList arg = QStringList() << "network_chk_ipv6_addr" << m_pReq->parameter("addr");
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    QDomElement root = doc.createElement("ipv6");
    doc.appendChild(root);
    QDomElement formatElement = doc.createElement("addr_format");
    root.appendChild(formatElement);
    formatElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement addrElement = doc.createElement("addr");
    root.appendChild(addrElement);
    addrElement.appendChild(doc.createTextNode(apiOut.value(0).toInt() == -1
                                               ? QString::null : m_pReq->parameter("addr")));

    m_var = doc.toString();
}

void RenderResponseNetwork::generateChkGwAddr() {
    QDomDocument doc;

    QStringList arg = QStringList() << "network_chk_ipv6_gateway_addr" << allParametersToString();
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API, arg, true);

    QDomElement root = doc.createElement("ipv6");
    doc.appendChild(root);
    QDomElement formatElement = doc.createElement("addr_format");
    root.appendChild(formatElement);
    formatElement.appendChild(doc.createTextNode(apiOut.value(0)));

    m_var = doc.toString();

}

void RenderResponseNetwork::generateSpeed() {
    QString paraSpeed = m_pReq->parameter("lan0");

    if(!paraSpeed.isEmpty())
        setNasCfg("lan0", "speed", paraSpeed);

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_NETWORK_SPEED + " -t");
}

void RenderResponseNetwork::generateLLTD() {

    QString paraEnable =  m_pReq->parameter("f_enable");

    bool bSet = false;
    if(setNasCfg("lltd", "enable", paraEnable)) {
        getAPIStdOut(API_PATH + SCRIPT_LLTD_CTL + " start");
        bSet = true;
    }

    m_var = "../web/network_mgr/ip.html";

}

void RenderResponseNetwork::generateGetDdns() {

    QDomDocument doc;
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

    m_var = doc.toString();

}

void RenderResponseNetwork::generateGetDdnsStatus() {

    QDomDocument doc;

    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_DDNS_CTL + " -S");

    QDomElement root = doc.createElement("ddns");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    QDomText statusValue = doc.createTextNode(apiOutList.value(0));
    statusElement.appendChild(statusValue);

    QDomElement updatetimeElement = doc.createElement("updatetime");
    root.appendChild(updatetimeElement);

    QDomElement nexttimeElement = doc.createElement("nexttime");
    root.appendChild(nexttimeElement);

    if(apiOutList.size() == 3) {
        bool ok = false;
        QDomText updateTimeValue;
        uint iUpdateTime = apiOutList.value(1).toInt(&ok);
        if(ok) {
            QDateTime update = QDateTime::fromTime_t(iUpdateTime);
            updateTimeValue = doc.createTextNode(update.toString("yyyy/M/d h:m:s"));
        }
        updatetimeElement.appendChild(updateTimeValue);

        ok = false;
        QDomText nextTimeValue;
        uint iNextTime = apiOutList.value(2).toInt(&ok);
        if(ok) {
            QDateTime next = QDateTime::fromTime_t(iNextTime);
            nextTimeValue = doc.createTextNode(next.toString("yyyy/M/d h:m:s"));
        }
        nexttimeElement.appendChild(nextTimeValue);
    }

    m_var = doc.toString();

}

void RenderResponseNetwork::generateDdns() {

    QString paraEnable, paraDdnsServer, paraDdnsDomain,
            paraDdnsUsername, paraPassword, paraRePassword;

    if(m_pReq->allParameters().contains("f_enable"))
        paraEnable = m_pReq->allParameters().value("f_enable").toString();
    if(m_pReq->allParameters().contains("f_ddns_server"))
        paraDdnsServer = m_pReq->allParameters().value("f_ddns_server").toString();
    if(m_pReq->allParameters().contains("f_ddns_domain"))
        paraDdnsDomain = m_pReq->allParameters().value("f_ddns_domain").toString();
    if(m_pReq->allParameters().contains("f_ddns_username"))
        paraDdnsUsername = m_pReq->allParameters().value("f_ddns_username").toString();
    if(m_pReq->allParameters().contains("f_ddns_password"))
        paraPassword = m_pReq->allParameters().value("f_ddns_password").toString();
    if(m_pReq->allParameters().contains("f_ddns_re_password"))
        paraRePassword = m_pReq->allParameters().value("f_ddns_re_password").toString();

//    if(paraPassword.compare(paraRePassword) != 0)
//        return;

    QMap<QString, QString> map;
    map.insert("enable", paraEnable);
    map.insert("server", paraDdnsServer);
    map.insert("domain", paraDdnsDomain);
    map.insert("username", paraDdnsUsername);
    map.insert("pwd", paraPassword);

    if(setNasCfg("ddns", map)) {
        getAPIStdOut(API_PATH + SCRIPT_DDNS_CTL + " -T");
    }

    generateGetDdns();

}

void RenderResponseNetwork::generatePortForwardingGet() {

    QDomDocument doc;
    QString paraPage, paraRp, paraSortname,
            paraSortOrder, paraQuery, paraQType,
            paraField, paraUser;

    if(m_pReq->allParameters().contains("page"))
        paraPage = m_pReq->allParameters().value("page").toString();
    if(m_pReq->allParameters().contains("rp"))
        paraRp = m_pReq->allParameters().value("rp").toString();
    if(m_pReq->allParameters().contains("sortname"))
        paraSortname = m_pReq->allParameters().value("sortname").toString();
    if(m_pReq->allParameters().contains("sortorder"))
        paraSortOrder = m_pReq->allParameters().value("sortorder").toString();
    if(m_pReq->allParameters().contains("query"))
        paraQuery = m_pReq->allParameters().value("query").toString();
    if(m_pReq->allParameters().contains("qtype"))
        paraQType = m_pReq->allParameters().value("qtype").toString();
    if(m_pReq->allParameters().contains("f_field"))
        paraField = m_pReq->allParameters().value("f_field").toString();
    if(m_pReq->allParameters().contains("user"))
        paraUser = m_pReq->allParameters().value("user").toString();

    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_UPNP_CTL + " -L");

    //apiOutList
    /* ****** output ********
     *
        FTP,TCP,6990,6990,1,OK
        FTP,UDP,6991,6991,0,ERROR

     ********************** */

    QStringList pfList(apiOutList);
    int rp = paraRp.toInt();
    if(pfList.size() > rp)
        pfList = apiOutList.mid((paraPage.toInt()-1) * rp, rp);

    QString strCheckboxEnable = "<input type='checkbox' checked disabled class='scan'>";
    QString strCheckboxDisable = "<input type='checkbox' disabled class='scan'>";
    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    for(int i = 0; i < pfList.size(); i++) {
        if(pfList.at(i).isEmpty())
            continue;
        QStringList line = pfList.at(i).split(",");
        if(line.size() < 6)
            continue;

        QDomElement rowElement1 = doc.createElement("row");
        root.appendChild(rowElement1);
        rowElement1.setAttribute("id", QString::number(i));
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement1.appendChild(cellElement1);
        QDomText cellValue1 = doc.createCDATASection((line.at(4).compare("1") == 0) ?
                                                 strCheckboxEnable : strCheckboxDisable);
        cellElement1.appendChild(cellValue1);

        QDomElement cellElement2 = doc.createElement("cell");
        rowElement1.appendChild(cellElement2);
        QDomText cellValue2 = doc.createTextNode(line.at(5));
        cellElement2.appendChild(cellValue2);

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement1.appendChild(cellElement3);
        QDomText cellValue3 = doc.createTextNode(line.at(0));
        cellElement3.appendChild(cellValue3);

        QDomElement cellElement4 = doc.createElement("cell");
        rowElement1.appendChild(cellElement4);
        QDomText cellValue4 = doc.createTextNode(line.at(1));
        cellElement4.appendChild(cellValue4);

        QDomElement cellElement5 = doc.createElement("cell");
        rowElement1.appendChild(cellElement5);
        QDomText cellValue5 = doc.createTextNode(line.at(2));
        cellElement5.appendChild(cellValue5);

        QDomElement cellElement6 = doc.createElement("cell");
        rowElement1.appendChild(cellElement6);
        QDomText cellValue6 = doc.createTextNode(line.at(3));
        cellElement6.appendChild(cellValue6);
    }
    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOutList.size())));

    m_var = doc.toString();

}

void RenderResponseNetwork::generateUpnpTest() {
    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_UPNP_CTL + " -t", true);
}


void RenderResponseNetwork::generateUpnpTestResult() {
    QMap<QString, QString> upnpInfo = getNasCfg("upnp");
    m_var = upnpInfo.value("upnp_test_result");
}

void RenderResponseNetwork::generatePortForwardingTotal() {
    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_UPNP_CTL + " -C", true);
    m_var = apiOutList.isEmpty() ? "" : apiOutList.at(0);
}

void RenderResponseNetwork::generateGetPortTable() {

    QDomDocument doc;
    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_UPNP_CTL + " -D");

    QDomElement root = doc.createElement("root");
    doc.appendChild(root);
    for(int i=0; i<apiOutList.size(); i++) {
        if(apiOutList.at(i).isEmpty())
            continue;
        QStringList line = apiOutList.at(i).split(",");
        if(line.size() < 3)
            continue;

        QDomElement portElement = doc.createElement("port");
        root.appendChild(portElement);
        QDomElement serviceElement = doc.createElement("service");
        portElement.appendChild(serviceElement);
        QDomText serviceValue = doc.createTextNode(line.at(0));
        serviceElement.appendChild(serviceValue);
        QDomElement protocolElement = doc.createElement("protocol");
        portElement.appendChild(protocolElement);
        QDomText protocolValue = doc.createTextNode(line.at(1));
        protocolElement.appendChild(protocolValue);
        QDomElement localPortElement = doc.createElement("local_port");
        portElement.appendChild(localPortElement);
        QDomText portValue = doc.createTextNode(line.at(2));
        localPortElement.appendChild(portValue);
    }

    m_var = doc.toString();

}

void RenderResponseNetwork::generatePortFrowardingAddScan() {
    QString paraService = m_pReq->allParameters().value("service").toString();
    QString paraEnable = m_pReq->allParameters().value("enable").toString();
    QString paraProtocol = m_pReq->allParameters().value("protocol").toString();
    QString paraPPort = m_pReq->allParameters().value("p_port").toString();
    QString paraEPort = m_pReq->allParameters().value("e_port").toString();
    if(paraService.isEmpty() || paraEnable.isEmpty()
            || paraProtocol.isEmpty() || paraPPort.isEmpty()
            || paraEPort.isEmpty()) {
        tDebug("service: %s", paraService.toLocal8Bit().data());
        m_var = "error";
        return;
    }

    QString paraCmd = m_pReq->parameter("cmd");
    QString apiParaAdd = "add_scan";
    if(paraCmd.compare("cgi_portforwarding_add") == 0)
        apiParaAdd = "add";
    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_UPNP_CTL + " -a " + apiParaAdd +
                                                                        " -p " + paraProtocol +
                                                                        " -e " + paraEPort +
                                                                        " -i " + paraPPort +
                                                                        " -s " + paraService +
                                                                        " -b " + paraEnable
                                                                        , true);

    m_var = apiOutList.value(0);
}

void RenderResponseNetwork::generatePortFrowardingAdd() {
    generatePortFrowardingAddScan();
}

void RenderResponseNetwork::generatePortFrowardingModify() {

    QString paraEnable = m_pReq->allParameters().value("enable").toString();
    QString paraProtocol = m_pReq->allParameters().value("protocol").toString();
    QString paraPPort = m_pReq->allParameters().value("p_port").toString();
    QString paraEPort = m_pReq->allParameters().value("e_port").toString();
    QString paraService = m_pReq->allParameters().value("service").toString();
    QString paraScan = m_pReq->allParameters().value("scan").toString();
    QString paraOldEPort = m_pReq->allParameters().value("old_e_port").toString();

    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_UPNP_CTL + " -m -p " + paraProtocol +
                                                                        " -e " + paraEPort +
                                                                        " -i " + paraPPort +
                                                                        " -s " + paraService +
                                                                        " -b " + paraEnable +
                                                                        " -o " + paraOldEPort
                                                                        , true);
    m_var = apiOutList.value(0);
}

void RenderResponseNetwork::generatePortFrowardingDel() {

    QString paraProtocol = m_pReq->allParameters().value("protocol").toString();
    QString paraPPort = m_pReq->allParameters().value("p_port").toString();
    QString paraEPort = m_pReq->allParameters().value("e_port").toString();
    QString paraService = m_pReq->allParameters().value("service").toString();
    QString paraScan = m_pReq->allParameters().value("scan").toString();

    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_UPNP_CTL + " -d -p " + paraProtocol +
                                                                        " -e " + paraEPort +
                                                                        " -i " + paraPPort +
                                                                        " -s " + paraService
                                                                        , true);
    m_var = apiOutList.value(0);
}

void RenderResponseNetwork::generatePortFrowardingGetPort() {

    QDomDocument doc;
    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_UPNP_CTL + " -P");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);
    for(QString e : apiOutList) {

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        QDomElement ePortElement = doc.createElement("e_port");
        rowElement.appendChild(ePortElement);
        ePortElement.appendChild(doc.createTextNode(e.split(",").value(0)));
        QDomElement protocolElement = doc.createElement("protocol");
        rowElement.appendChild(protocolElement);
        protocolElement.appendChild(doc.createTextNode(e.split(",").value(1)));
        QDomElement serviceElement = doc.createElement("service");
        rowElement.appendChild(serviceElement);
        serviceElement.appendChild(doc.createTextNode(e.split(",").value(2)));
        QDomElement localPortElement = doc.createElement("local_port");
        rowElement.appendChild(localPortElement);
        localPortElement.appendChild(doc.createTextNode(e.split(",").value(3)));
    }
    m_var = doc.toString();

}

void RenderResponseNetwork::generateGetSshPort() {

    QDomDocument doc;
    QMap<QString, QString> sshdInfo = getNasCfg("sshd");

    QDomElement root = doc.createElement("ssh_info");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode(sshdInfo.value("enable")));
    QDomElement portElement = doc.createElement("port");
    root.appendChild(portElement);
    portElement.appendChild(doc.createTextNode(sshdInfo.value("port")));
    m_var = doc.toString();

}

void RenderResponseNetwork::generateSetSshPort() {

    QDomDocument doc;
    QString paraEnable = m_pReq->parameter("ssh_enable");
    QString paraPort = m_pReq->parameter("ssh_port");
    QString ret = "1";

    QMap<QString, QString> map;
    if(!paraEnable.isEmpty())
        map.insert("enable", paraEnable);
    if(!paraPort.isEmpty())
        map.insert("port", paraPort);

    QString sshCmd = "stop";
    if(setNasCfg("sshd", map)) {
        getAPIStdOut(API_PATH + SCRIPT_SSH_CTL + " " + sshCmd);
        if(paraEnable == "1")
            getAPIStdOut(API_PATH + SCRIPT_SSH_CTL + " start");
    }
    else
        ret = "0";

    QDomElement root = doc.createElement("ret");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(ret));
    m_var = doc.toString();

}
