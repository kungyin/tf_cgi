#include "RenderResponseSysStatus.h"

RenderResponseSysStatus::RenderResponseSysStatus(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseSysStatus::~RenderResponseSysStatus() {
}

void RenderResponseSysStatus::preRender() {

    if(!m_pReq)
        return;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_GET_STATUS:
        generateGetStatus(doc);
        break;
    case CMD_STATUS_VOLUME_INFO:
        generateStatusVolumeInfo(doc);
        break;
    case CMD_USB_STORAGE_INFO:
        generateUsbStorageInfo(doc);
        break;
    case CMD_MTP_INFO:
        generateMtpInfo(doc);
        break;
    case CMD_USB_PRINTER_INFO:
        generateUsbPrinterInfo(doc);
        break;
    case CMD_UPS_INFO2:
        generateUpsInfo2(doc);
        break;
    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

}

/* todo: need API */
void RenderResponseSysStatus::generateGetStatus(QDomDocument &doc) {
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");

    QDomElement root = doc.createElement("status");
    doc.appendChild(root);
    QDomElement bondingEnableElement = doc.createElement("bonding_enable");
    root.appendChild(bondingEnableElement);
    bondingEnableElement.appendChild(doc.createTextNode("0"));
    QDomElement bondingModeElement = doc.createElement("bonding_mode");
    root.appendChild(bondingModeElement);
    bondingModeElement.appendChild(doc.createTextNode("1"));

    QDomElement dhcpEnableElement = doc.createElement("dhcp_enable");
    root.appendChild(dhcpEnableElement);
    dhcpEnableElement.appendChild(doc.createTextNode("1"));
    QDomElement ipElement = doc.createElement("ip");
    root.appendChild(ipElement);
    ipElement.appendChild(doc.createTextNode("192.168.100.85"));

    QDomElement netmaskElement = doc.createElement("netmask");
    root.appendChild(netmaskElement);
    netmaskElement.appendChild(doc.createTextNode("255.255.255.0"));
    QDomElement gatewayElement = doc.createElement("gateway");
    root.appendChild(gatewayElement);
    gatewayElement.appendChild(doc.createTextNode("192.168.100.5"));

    QDomElement dns1Element = doc.createElement("dns1");
    root.appendChild(dns1Element);
    dns1Element.appendChild(doc.createTextNode(""));
    QDomElement dns2Element = doc.createElement("dns2");
    root.appendChild(dns2Element);
    dns2Element.appendChild(doc.createTextNode(""));
    QDomElement txrxElement = doc.createElement("txrx");
    root.appendChild(txrxElement);
    txrxElement.appendChild(doc.createTextNode(""));
    QDomElement lan2DhcpEnableElement = doc.createElement("lan2_dhcp_enable");
    root.appendChild(lan2DhcpEnableElement);
    lan2DhcpEnableElement.appendChild(doc.createTextNode(""));

    QDomElement lan2IpElement = doc.createElement("lan2_ip");
    root.appendChild(lan2IpElement);
    lan2IpElement.appendChild(doc.createTextNode(""));
    QDomElement lan2NetmaskElement = doc.createElement("lan2_netmask");
    root.appendChild(lan2NetmaskElement);
    lan2NetmaskElement.appendChild(doc.createTextNode(""));
    QDomElement lan2GatewayElement = doc.createElement("lan2_gateway");
    root.appendChild(lan2GatewayElement);
    lan2GatewayElement.appendChild(doc.createTextNode(""));

    QDomElement lan2Dns1Element = doc.createElement("lan2_dns1");
    root.appendChild(lan2Dns1Element);
    lan2Dns1Element.appendChild(doc.createTextNode(""));
    QDomElement lan2Dns2Element = doc.createElement("lan2_dns2");
    root.appendChild(lan2Dns2Element);
    lan2Dns2Element.appendChild(doc.createTextNode(""));
    QDomElement lan2TxrxElement = doc.createElement("lan2_txrx");
    root.appendChild(lan2TxrxElement);
    lan2TxrxElement.appendChild(doc.createTextNode(""));

    QDomElement nameElement = doc.createElement("name");
    root.appendChild(nameElement);
    nameElement.appendChild(doc.createTextNode(""));
    QDomElement workgroupElement = doc.createElement("workgroup");
    root.appendChild(workgroupElement);
    workgroupElement.appendChild(doc.createTextNode(""));
    QDomElement descriptionElement = doc.createElement("description");
    root.appendChild(descriptionElement);
    descriptionElement.appendChild(doc.createTextNode(""));

    QDomElement macElement = doc.createElement("mac");
    root.appendChild(macElement);
    macElement.appendChild(doc.createTextNode(""));
    QDomElement lan2MacElement = doc.createElement("lan2_mac");
    root.appendChild(lan2MacElement);
    lan2MacElement.appendChild(doc.createTextNode(""));

    QDomElement manufacturerElement = doc.createElement("manufacturer");
    root.appendChild(manufacturerElement);
    manufacturerElement.appendChild(doc.createTextNode(""));
    QDomElement productElement = doc.createElement("product");
    root.appendChild(productElement);
    productElement.appendChild(doc.createTextNode(""));

    QDomElement batteryElement = doc.createElement("battery");
    root.appendChild(batteryElement);
    batteryElement.appendChild(doc.createTextNode(""));
    QDomElement upsStatusElement = doc.createElement("ups_status");
    root.appendChild(upsStatusElement);
    upsStatusElement.appendChild(doc.createTextNode(""));
    QDomElement upsTypeElement = doc.createElement("ups_type");
    root.appendChild(upsTypeElement);
    upsTypeElement.appendChild(doc.createTextNode(""));

    QDomElement flashInfoElement = doc.createElement("flash_info");
    root.appendChild(flashInfoElement);
    flashInfoElement.appendChild(doc.createTextNode(""));
    QDomElement uptimeElement = doc.createElement("uptime");
    root.appendChild(uptimeElement);
    uptimeElement.appendChild(doc.createTextNode(""));
}

/* todo: need API */
void RenderResponseSysStatus::generateStatusVolumeInfo(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    //for
    QDomElement itmeElement = doc.createElement("item");
    root.appendChild(itmeElement);

    QDomElement volumeElement = doc.createElement("volume");
    root.appendChild(volumeElement);
    volumeElement.appendChild(doc.createTextNode("2"));
    QDomElement raidModeElement = doc.createElement("raid_mode");
    root.appendChild(raidModeElement);
    raidModeElement.appendChild(doc.createTextNode("standard"));

    QDomElement statusElement = doc.createElement("status");
    root.appendChild(statusElement);
    statusElement.appendChild(doc.createTextNode("0"));
    QDomElement totalSizeElement = doc.createElement("total_size");
    root.appendChild(totalSizeElement);
    totalSizeElement.appendChild(doc.createTextNode("1920264152"));
    QDomElement useSizeElement = doc.createElement("use_size");
    root.appendChild(useSizeElement);
    useSizeElement.appendChild(doc.createTextNode("200140"));

    QDomElement freeSizeElement = doc.createElement("free_size");
    root.appendChild(freeSizeElement);
    freeSizeElement.appendChild(doc.createTextNode(""));
    QDomElement usedRateElement = doc.createElement("used_rate");
    root.appendChild(usedRateElement);
    usedRateElement.appendChild(doc.createTextNode("0"));

}

/* todo: need API */
void RenderResponseSysStatus::generateUsbStorageInfo(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("0"));

}

/* todo: need API */
void RenderResponseSysStatus::generateMtpInfo(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("0"));

}

/* todo: need API */
void RenderResponseSysStatus::generateUsbPrinterInfo(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("0"));

}


/* todo: need API */
void RenderResponseSysStatus::generateUpsInfo2(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("0"));

}

