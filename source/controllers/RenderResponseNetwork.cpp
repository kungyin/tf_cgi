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

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_GET_LLTD:
        generateGetLLTD(doc);
        break;
    case CMD_LAN_XML:
        generateLanXml(doc);
        break;
    case CMD_IPV6:
        generateIPV6(doc);
        break;
    case CMD_LAN_STATUS:
        generateLanStatus(doc);
        break;
    case CMD_LAN_XML2:
        generateLanXml2(doc);
        break;
    case CMD_SETIP_LOCK:
        generateSetIPLock();
        break;
    case CMD_IP:
        generateIP();
        break;
    case CMD_SPEED:
        generateSpeed();
        break;
    case CMD_LLTD:
        generateLLTD(doc);
        break;
    case CMD_GET_DDNS:
        generateGetDdns(doc);
        break;
    case CMD_GET_DDNS_STATUS:
        generateGetDdnsStatus(doc);
        break;
    case CMD_DDNS:
        generateDdns(doc);
        break;
    case CMD_PORTFORWARDING_GET:
        generatePortForwardingGet(doc);
        break;
    case CMD_UPNP_TEST:
        generateUpnpTest();
        break;
    case CMD_UPNP_TEST_RESULT:
        generateUpnpTestResult(str);
        break;
    case CMD_PORTFORWARDING_TOTAL:
        generatePortForwardingTotal(str);
        break;
    case CMD_GET_PORT_TABLE:
        generateGetPortTable(doc);
        break;
    case CMD_PORTFORWARDING_ADD_SCAN:
        generatePortFrowardingAddScan(str);
        break;
    case CMD_PORTFORWARDING_ADD:
        generatePortFrowardingAdd(str);
        break;
    case CMD_PORTFORWARDING_MODIFY:
        generatePortFrowardingModify(str);
        break;
    case CMD_PORTFORWARDING_DEL:
        generatePortFrowardingDel(str);
        break;
    case CMD_PORTFORWARDING_GET_PORT:
        generatePortFrowardingGetPort(doc);
        break;
    case CMD_GET_SSH_PORT:
        generateGetSshPort(doc);
        break;
    case CMD_SET_SSH_PORT:
        generateSetSshPort(doc);
        break;
    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

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
}

/* todo */
void RenderResponseNetwork::generateIPV6(QDomDocument &doc) {

}

void RenderResponseNetwork::generateLanStatus(QDomDocument &doc) {
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
}

void RenderResponseNetwork::generateLanXml2(QDomDocument &doc) {
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
    if(!QProcess::startDetached(NETWORK_SCRIPT, QStringList() << "restart"))
        tError("process cannot be started: %s", NETWORK_SCRIPT.toLocal8Bit().data());
#endif
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

void RenderResponseNetwork::generateSpeed() {
    QString paraSpeed;

    if(m_pReq->allParameters().contains("lan0"))
        paraSpeed = m_pReq->allParameters().value("lan0").toString();

    setNasCfg("lan0", "speed", paraSpeed);
}

void RenderResponseNetwork::generateLLTD(QDomDocument &doc) {

    QString paraEnable;

    if(m_pReq->allParameters().contains("f_enable"))
        paraEnable = m_pReq->allParameters().value("f_enable").toString();

    bool bSet = false;
    if(setNasCfg("lltd", "enable", paraEnable)) {
        getAPIStdOut(API_PATH + SCRIPT_LLTD_CTL + " start");
        bSet = true;
    }

    QDomElement root = doc.createElement("lltd");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode(bSet ? paraEnable : "0"));
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
    if(apiOutList.size() < 4)
        return;

    QDomElement root = doc.createElement("ddns");
    doc.appendChild(root);
    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    QDomText statusValue = doc.createTextNode(apiOutList.at(0));
    statusElement.appendChild(statusValue);

    QDomElement updatetimeElement = doc.createElement("updatetime");
    root.appendChild(updatetimeElement);

    bool ok = false;
    QDomText updateTimeValue;
    uint iUpdateTime = apiOutList.at(1).toInt(&ok);
    if(ok) {
        QDateTime update = QDateTime::fromTime_t(iUpdateTime);
        updateTimeValue = doc.createTextNode(update.toString("yyyy/M/d h:m:s"));
    }
    updatetimeElement.appendChild(updateTimeValue);

    QDomElement nexttimeElement = doc.createElement("nexttime");
    root.appendChild(nexttimeElement);

    ok = false;
    QDomText nextTimeValue;
    uint iNextTime = apiOutList.at(2).toInt(&ok);
    if(ok) {
        QDateTime next = QDateTime::fromTime_t(iNextTime);
        nextTimeValue = doc.createTextNode(next.toString("yyyy/M/d h:m:s"));
    }
    nexttimeElement.appendChild(nextTimeValue);
}

void RenderResponseNetwork::generateDdns(QDomDocument &doc) {

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

void RenderResponseNetwork::generatePortForwardingGet(QDomDocument &doc) {
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

    QString strCheckboxEnable = "&lt;input type='checkbox' checked disabled class='scan'&gt;";
    QString strCheckboxDisable = "&lt;input type='checkbox' disabled class='scan'&gt;";
    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    for(int i=0; i<apiOutList.size(); i++) {
        if(apiOutList.at(i).isEmpty())
            continue;
        QStringList line = apiOutList.at(i).split(",");
        if(line.size() < 6)
            continue;

        QDomElement rowElement1 = doc.createElement("row");
        root.appendChild(rowElement1);
        rowElement1.setAttribute("id", QString::number(i));
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement1.appendChild(cellElement1);
        QDomText cellValue1 = doc.createTextNode((line.at(4).compare("1") == 0) ?
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
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOutList.size())));
}

void RenderResponseNetwork::generateUpnpTest() {
    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_UPNP_CTL + " -t", true);
}


void RenderResponseNetwork::generateUpnpTestResult(QString &str) {
    QMap<QString, QString> upnpInfo = getNasCfg("upnp");
    str = upnpInfo.value("upnp_test_result");
}

void RenderResponseNetwork::generatePortForwardingTotal(QString &str) {
    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_UPNP_CTL + " -C", true);
    str = apiOutList.isEmpty() ? "" : apiOutList.at(0);
}

void RenderResponseNetwork::generateGetPortTable(QDomDocument &doc) {

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
}

void RenderResponseNetwork::generatePortFrowardingAddScan(QString &str) {
    QString paraService = m_pReq->allParameters().value("service").toString();
    QString paraEnable = m_pReq->allParameters().value("enable").toString();
    QString paraProtocol = m_pReq->allParameters().value("protocol").toString();
    QString paraPPort = m_pReq->allParameters().value("p_port").toString();
    QString paraEPort = m_pReq->allParameters().value("e_port").toString();
    if(paraService.isEmpty() || paraEnable.isEmpty()
            || paraProtocol.isEmpty() || paraPPort.isEmpty()
            || paraEPort.isEmpty()) {
        tDebug("service: %s", paraService.toLocal8Bit().data());
        str = "error";
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

    str = apiOutList.value(0);
}

void RenderResponseNetwork::generatePortFrowardingAdd(QString &str) {
    generatePortFrowardingAddScan(str);
}

void RenderResponseNetwork::generatePortFrowardingModify(QString &str) {

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
    str = apiOutList.value(0);
}

void RenderResponseNetwork::generatePortFrowardingDel(QString &str) {

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
    str = apiOutList.value(0);
}

void RenderResponseNetwork::generatePortFrowardingGetPort(QDomDocument &doc) {

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
}

void RenderResponseNetwork::generateGetSshPort(QDomDocument &doc) {
    QMap<QString, QString> sshdInfo = getNasCfg("sshd");

    QDomElement root = doc.createElement("ssh_info");
    doc.appendChild(root);
    QDomElement enableElement = doc.createElement("enable");
    root.appendChild(enableElement);
    enableElement.appendChild(doc.createTextNode(sshdInfo.value("enable")));
    QDomElement portElement = doc.createElement("port");
    root.appendChild(portElement);
    portElement.appendChild(doc.createTextNode(sshdInfo.value("port")));
}

void RenderResponseNetwork::generateSetSshPort(QDomDocument &doc) {
    QString paraEnable = m_pReq->parameter("ssh_enable");
    QString paraPort = m_pReq->parameter("ssh_port");
    QString ret = "1";

    QMap<QString, QString> map;
    map.insert("enable", paraEnable);
    map.insert("port", paraPort);

    if(setNasCfg("sshd", map))
        getAPIStdOut(API_PATH + SCRIPT_SSH_CTL + " restart");
    else
        ret = "0";

    QDomElement root = doc.createElement("ret");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode(ret));
}
