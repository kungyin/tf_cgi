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

    case CMD_SMART_XML_CREATE_DEVICE_LIST:
        generateSmartXmlCreateDeviceList(doc);
        break;
    case CMD_SMART_XML_CREATE_SMART_INFO:
        generateSmartXmlCreateSmartInfo(doc);
        break;

    case CMD_RESOURCE:
        generateResource(doc);
        break;

    case CMD_GET_SERVICE:
        generateGetService(doc);
        break;
    case CMD_MODULE_LIST:
        generateModuleList(doc);
        break;

    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

}

void RenderResponseSysStatus::generateGetStatus(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_status", true, ";");

    QDomElement root = doc.createElement("status");
    doc.appendChild(root);
    QDomElement bondingEnableElement = doc.createElement("bonding_enable");
    root.appendChild(bondingEnableElement);
    bondingEnableElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement bondingModeElement = doc.createElement("bonding_mode");
    root.appendChild(bondingModeElement);
    bondingModeElement.appendChild(doc.createTextNode(apiOut.value(1)));

    QDomElement dhcpEnableElement = doc.createElement("dhcp_enable");
    root.appendChild(dhcpEnableElement);
    dhcpEnableElement.appendChild(doc.createTextNode(apiOut.value(2)));
    QDomElement ipElement = doc.createElement("ip");
    root.appendChild(ipElement);
    ipElement.appendChild(doc.createTextNode(apiOut.value(3)));

    QDomElement netmaskElement = doc.createElement("netmask");
    root.appendChild(netmaskElement);
    netmaskElement.appendChild(doc.createTextNode(apiOut.value(4)));
    QDomElement gatewayElement = doc.createElement("gateway");
    root.appendChild(gatewayElement);
    gatewayElement.appendChild(doc.createTextNode(apiOut.value(5)));

    QDomElement dns1Element = doc.createElement("dns1");
    root.appendChild(dns1Element);
    dns1Element.appendChild(doc.createTextNode(apiOut.value(6)));
    QDomElement dns2Element = doc.createElement("dns2");
    root.appendChild(dns2Element);
    dns2Element.appendChild(doc.createTextNode(apiOut.value(7)));
    QDomElement txrxElement = doc.createElement("txrx");
    root.appendChild(txrxElement);
    txrxElement.appendChild(doc.createTextNode(apiOut.value(8)));
    QDomElement lan2DhcpEnableElement = doc.createElement("lan2_dhcp_enable");
    root.appendChild(lan2DhcpEnableElement);
    lan2DhcpEnableElement.appendChild(doc.createTextNode(apiOut.value(9)));

    QDomElement lan2IpElement = doc.createElement("lan2_ip");
    root.appendChild(lan2IpElement);
    lan2IpElement.appendChild(doc.createTextNode(apiOut.value(10)));
    QDomElement lan2NetmaskElement = doc.createElement("lan2_netmask");
    root.appendChild(lan2NetmaskElement);
    lan2NetmaskElement.appendChild(doc.createTextNode(apiOut.value(11)));
    QDomElement lan2GatewayElement = doc.createElement("lan2_gateway");
    root.appendChild(lan2GatewayElement);
    lan2GatewayElement.appendChild(doc.createTextNode(apiOut.value(12)));

    QDomElement lan2Dns1Element = doc.createElement("lan2_dns1");
    root.appendChild(lan2Dns1Element);
    lan2Dns1Element.appendChild(doc.createTextNode(apiOut.value(13)));
    QDomElement lan2Dns2Element = doc.createElement("lan2_dns2");
    root.appendChild(lan2Dns2Element);
    lan2Dns2Element.appendChild(doc.createTextNode(apiOut.value(14)));
    QDomElement lan2TxrxElement = doc.createElement("lan2_txrx");
    root.appendChild(lan2TxrxElement);
    lan2TxrxElement.appendChild(doc.createTextNode(apiOut.value(15)));

    QDomElement nameElement = doc.createElement("name");
    root.appendChild(nameElement);
    nameElement.appendChild(doc.createTextNode(apiOut.value(16)));
    QDomElement workgroupElement = doc.createElement("workgroup");
    root.appendChild(workgroupElement);
    workgroupElement.appendChild(doc.createTextNode(apiOut.value(17)));
    QDomElement descriptionElement = doc.createElement("description");
    root.appendChild(descriptionElement);
    descriptionElement.appendChild(doc.createTextNode(apiOut.value(18)));

    QDomElement macElement = doc.createElement("mac");
    root.appendChild(macElement);
    macElement.appendChild(doc.createTextNode(apiOut.value(19)));
    QDomElement lan2MacElement = doc.createElement("lan2_mac");
    root.appendChild(lan2MacElement);
    lan2MacElement.appendChild(doc.createTextNode(apiOut.value(20)));

    QDomElement manufacturerElement = doc.createElement("manufacturer");
    root.appendChild(manufacturerElement);
    manufacturerElement.appendChild(doc.createTextNode(apiOut.value(21)));
    QDomElement productElement = doc.createElement("product");
    root.appendChild(productElement);
    productElement.appendChild(doc.createTextNode(apiOut.value(22)));

    QDomElement batteryElement = doc.createElement("battery");
    root.appendChild(batteryElement);
    batteryElement.appendChild(doc.createTextNode(apiOut.value(23)));
    QDomElement upsStatusElement = doc.createElement("ups_status");
    root.appendChild(upsStatusElement);
    upsStatusElement.appendChild(doc.createTextNode(apiOut.value(24)));
    QDomElement upsTypeElement = doc.createElement("ups_type");
    root.appendChild(upsTypeElement);
    upsTypeElement.appendChild(doc.createTextNode(apiOut.value(25)));

    QDomElement flashInfoElement = doc.createElement("flash_info");
    root.appendChild(flashInfoElement);

    QVector<QString> flashInfoContentElement;
    flashInfoContentElement << "Manufacturer" << "Product" << "Partition";

    for(int i = 0; i < apiOut.value(26).split("#").size(); i++) {
        int eleNameIdx = i;
        if(eleNameIdx > flashInfoContentElement.size() - 1)
            eleNameIdx = flashInfoContentElement.size() - 1;
        QDomElement element = doc.createElement(flashInfoContentElement.at(eleNameIdx));
        flashInfoElement.appendChild(element);
        element.appendChild(doc.createTextNode(apiOut.value(26).split("#").value(i)));
    }

    QDomElement uptimeElement = doc.createElement("uptime");
    root.appendChild(uptimeElement);
    uptimeElement.appendChild(doc.createTextNode(apiOut.value(27)));
}

void RenderResponseSysStatus::generateStatusVolumeInfo(QDomDocument &doc) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_hdd_volume_info");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    for(QString entry : apiOut) {
        QDomElement itmeElement = doc.createElement("item");
        root.appendChild(itmeElement);

        QDomElement volumeElement = doc.createElement("volume");
        itmeElement.appendChild(volumeElement);
        volumeElement.appendChild(doc.createTextNode(entry.split(";").value(0)));
        QDomElement raidModeElement = doc.createElement("raid_mode");
        itmeElement.appendChild(raidModeElement);
        raidModeElement.appendChild(doc.createTextNode(entry.split(";").value(1)));

        QDomElement statusElement = doc.createElement("status");
        itmeElement.appendChild(statusElement);
        statusElement.appendChild(doc.createTextNode(entry.split(";").value(2)));
        QDomElement totalSizeElement = doc.createElement("total_size");
        itmeElement.appendChild(totalSizeElement);
        totalSizeElement.appendChild(doc.createTextNode(entry.split(";").value(3)));
        QDomElement useSizeElement = doc.createElement("use_size");
        itmeElement.appendChild(useSizeElement);
        useSizeElement.appendChild(doc.createTextNode(entry.split(";").value(4)));

        QDomElement freeSizeElement = doc.createElement("free_size");
        itmeElement.appendChild(freeSizeElement);
        freeSizeElement.appendChild(doc.createTextNode(entry.split(";").value(5)));
        QDomElement usedRateElement = doc.createElement("used_rate");
        itmeElement.appendChild(usedRateElement);
        usedRateElement.appendChild(doc.createTextNode(entry.split(";").value(6)));
    }
}

void RenderResponseSysStatus::generateUsbStorageInfo(QDomDocument &doc) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_usb_storage_info", false);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    if(apiOut.isEmpty()) {
        QDomElement resElement = doc.createElement("res");
        root.appendChild(resElement);
        resElement.appendChild(doc.createTextNode("0"));
    }
    else {
        for(QString e : apiOut) {
            QDomElement usbElement = doc.createElement("usb");
            root.appendChild(usbElement);
            QDomElement usbPortElement = doc.createElement("usb_port");
            usbElement.appendChild(usbPortElement);
            usbPortElement.appendChild(doc.createTextNode(e.split(";").value(0)));
            QDomElement manufacturerElement = doc.createElement("manufacturer");
            usbElement.appendChild(manufacturerElement);
            manufacturerElement.appendChild(doc.createTextNode(e.split(";").value(1)));

            QDomElement productElement = doc.createElement("product");
            usbElement.appendChild(productElement);
            productElement.appendChild(doc.createTextNode(e.split(";").value(2)));

            QDomElement mapDevElement = doc.createElement("map_dev");
            usbElement.appendChild(mapDevElement);
            mapDevElement.appendChild(doc.createTextNode(e.split(";").value(3)));
            QDomElement usbVersionElement = doc.createElement("usb_version");
            usbElement.appendChild(usbVersionElement);
            usbVersionElement.appendChild(doc.createTextNode(e.split(";").value(4)));
            QDomElement totalSizeElement = doc.createElement("total_size");
            usbElement.appendChild(totalSizeElement);
            totalSizeElement.appendChild(doc.createTextNode(e.split(";").value(5)));

            QDomElement partitionsElement = doc.createElement("partitions");
            root.appendChild(partitionsElement);
            for(QString partitionEntry : e.split(";").value(6).split("#")) {
                QDomElement partitionElement = doc.createElement("partition");
                root.appendChild(partitionElement);
                QDomElement shareNameElement = doc.createElement("share_name");
                partitionElement.appendChild(shareNameElement);
                shareNameElement.appendChild(doc.createTextNode(partitionEntry.split(",").value(0)));

                QDomElement psizeElement = doc.createElement("psize");
                partitionElement.appendChild(psizeElement);
                psizeElement.appendChild(doc.createTextNode(partitionEntry.split(",").value(1)));

                QDomElement pusedSizeElement = doc.createElement("pused_size");
                partitionElement.appendChild(pusedSizeElement);
                pusedSizeElement.appendChild(doc.createTextNode(partitionEntry.split(",").value(2)));

                QDomElement fsTypeElement = doc.createElement("fs_type");
                partitionElement.appendChild(fsTypeElement);
                fsTypeElement.appendChild(doc.createTextNode(partitionEntry.split(",").value(3)));
            }
        }
    }

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

/* todo: need API */
void RenderResponseSysStatus::generateSmartXmlCreateDeviceList(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    //for(int i=0; i < apiOut.size(); i++) {
//        if(apiOut.at(i).isEmpty())
//            continue;
//        if(apiOut.at(i).split(",").size() < 2)
//            continue;

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode("Disk1"));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode("Seagate"));

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode("ST3000DM001-9YN166"));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createTextNode("S1F0HYJ4"));
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createTextNode("32"));

        QDomElement cellElement6 = doc.createElement("cell");
        rowElement.appendChild(cellElement6);
        cellElement6.appendChild(doc.createTextNode("2930266584"));
        QDomElement cellElement7 = doc.createElement("cell");
        rowElement.appendChild(cellElement7);
        cellElement7.appendChild(doc.createTextNode("&lt;a href=javascript:onclick=GetSmartInfo\
            (&apos;sdb&apos;,&apos;1&apos;);&gt;&lt;IMG border=&apos;0&apos; src=&apos;/web/images\
            /normal.png&apos; alt=&apos;Normal&apos;&gt;&lt;/a&gt;"));

        rowElement.setAttribute("id", "1");
    //}

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("2"));

}

/* todo: need API */
void RenderResponseSysStatus::generateSmartXmlCreateSmartInfo(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    //for(int i=0; i < apiOut.size(); i++) {
//        if(apiOut.at(i).isEmpty())
//            continue;
//        if(apiOut.at(i).split(",").size() < 2)
//            continue;

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        QDomElement cellElement1 = doc.createElement("cell");
        rowElement.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode("1"));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode("Raw_Read_Error_Rate"));

        QDomElement cellElement3 = doc.createElement("cell");
        rowElement.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode("117"));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement.appendChild(cellElement4);
        cellElement4.appendChild(doc.createTextNode("100"));
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement.appendChild(cellElement5);
        cellElement5.appendChild(doc.createTextNode("6"));

        QDomElement cellElement6 = doc.createElement("cell");
        rowElement.appendChild(cellElement6);
        cellElement6.appendChild(doc.createTextNode("132806608"));

        rowElement.setAttribute("id", "1");
    //}

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("3"));

}


/* todo: need API */
void RenderResponseSysStatus::generateResource(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");

    QDomElement root = doc.createElement("xml");
    doc.appendChild(root);

    QDomElement bondingEnableElement = doc.createElement("bonding_enable");
    root.appendChild(bondingEnableElement);
    bondingEnableElement.appendChild(doc.createTextNode("0"));
    QDomElement lanRSpeedElement = doc.createElement("lan_r_speed");
    root.appendChild(lanRSpeedElement);
    lanRSpeedElement.appendChild(doc.createTextNode("4954335"));

    QDomElement lanTSpeedElement = doc.createElement("lan_t_speed");
    root.appendChild(lanTSpeedElement);
    lanTSpeedElement.appendChild(doc.createTextNode("24244223"));
    QDomElement lan2RSpeedElement = doc.createElement("lan2_r_speed");
    root.appendChild(lan2RSpeedElement);
    lan2RSpeedElement.appendChild(doc.createTextNode("0"));
    QDomElement lan2TSpeedElement = doc.createElement("lan2_t_speed");
    root.appendChild(lan2TSpeedElement);
    lan2TSpeedElement.appendChild(doc.createTextNode("0"));

    QDomElement memTotalElement = doc.createElement("mem_total");
    root.appendChild(memTotalElement);
    memTotalElement.appendChild(doc.createTextNode("509748"));
    QDomElement memFreeElement = doc.createElement("mem_free");
    root.appendChild(memFreeElement);
    memFreeElement.appendChild(doc.createTextNode("346748"));
    QDomElement buffersElement = doc.createElement("buffers");
    root.appendChild(buffersElement);
    buffersElement.appendChild(doc.createTextNode("10404"));

    QDomElement cachedElement = doc.createElement("cached");
    root.appendChild(cachedElement);
    cachedElement.appendChild(doc.createTextNode("84924"));
    QDomElement nowTimeElement = doc.createElement("now_time");
    root.appendChild(nowTimeElement);
    nowTimeElement.appendChild(doc.createTextNode("1430112389"));
    QDomElement cpuElement = doc.createElement("cpu");
    root.appendChild(cpuElement);
    cpuElement.appendChild(doc.createTextNode("0%"));

    //for(int i=0; i < apiOut.size(); i++) {

        QDomElement processMainElement = doc.createElement("process_main");
        root.appendChild(processMainElement);
        QDomElement commandElement = doc.createElement("command");
        processMainElement.appendChild(commandElement);
        commandElement.appendChild(doc.createTextNode("/usr/libexec/mysqld"));
        QDomElement userElement = doc.createElement("user");
        processMainElement.appendChild(userElement);
        userElement.appendChild(doc.createTextNode("root"));

        QDomElement pidElement = doc.createElement("pid");
        processMainElement.appendChild(pidElement);
        pidElement.appendChild(doc.createTextNode("2332"));

        QDomElement processCpuElement = doc.createElement("cpu");
        processMainElement.appendChild(processCpuElement);
        processCpuElement.appendChild(doc.createTextNode("0.0"));

        QDomElement memElement = doc.createElement("mem");
        processMainElement.appendChild(memElement);
        memElement.appendChild(doc.createTextNode("5.2"));

    //}

}

/* todo: need API */
void RenderResponseSysStatus::generateGetService(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");

    QDomElement root = doc.createElement("service");
    doc.appendChild(root);


    QDomElement afpEnableElement = doc.createElement("afp_enable");
    root.appendChild(afpEnableElement);
    afpEnableElement.appendChild(doc.createTextNode("0"));

    QDomElement nfsEnableElement = doc.createElement("nfs_enable");
    root.appendChild(nfsEnableElement);
    nfsEnableElement.appendChild(doc.createTextNode("0"));

    QDomElement ddnsEnableElement = doc.createElement("ddns_enable");
    root.appendChild(ddnsEnableElement);
    ddnsEnableElement.appendChild(doc.createTextNode("1"));

    QDomElement ddnsStatusElement = doc.createElement("ddns_status");
    root.appendChild(ddnsStatusElement);
    ddnsStatusElement.appendChild(doc.createTextNode("off"));

    QDomElement upnpEnableElement = doc.createElement("upnp_enable");
    root.appendChild(upnpEnableElement);
    upnpEnableElement.appendChild(doc.createTextNode("0"));

    QDomElement tmEnableElement = doc.createElement("tm_enable");
    root.appendChild(tmEnableElement);
    tmEnableElement.appendChild(doc.createTextNode("0"));

    QDomElement ftpEnableElement = doc.createElement("ftp_enable");
    root.appendChild(ftpEnableElement);
    ftpEnableElement.appendChild(doc.createTextNode("0"));

    QDomElement p2pEnableElement = doc.createElement("p2p_enable");
    root.appendChild(p2pEnableElement);
    p2pEnableElement.appendChild(doc.createTextNode("0"));

    QDomElement syslogEnableElement = doc.createElement("syslog_enable");
    root.appendChild(syslogEnableElement);
    syslogEnableElement.appendChild(doc.createTextNode(""));

    QDomElement syslogStatusElement = doc.createElement("syslog_status");
    root.appendChild(syslogStatusElement);
    syslogStatusElement.appendChild(doc.createTextNode(""));

    QDomElement syslogFolderElement = doc.createElement("syslog_folder");
    root.appendChild(syslogFolderElement);
    syslogFolderElement.appendChild(doc.createTextNode("Volume_1"));

}

/* todo: need API */
void RenderResponseSysStatus::generateModuleList(QDomDocument &doc) {

    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DATE_API + " get", true, ";");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    //for(int i=0; i < apiOut.size(); i++) {

    QDomElement rowElement = doc.createElement("row");
    root.appendChild(rowElement);
    QDomElement cellElement1 = doc.createElement("cell");
    rowElement.appendChild(cellElement1);
    cellElement1.appendChild(doc.createTextNode("1"));

    QDomElement cellElement2 = doc.createElement("cell");
    rowElement.appendChild(cellElement2);
    cellElement2.appendChild(doc.createTextNode("Transmission"));

    QDomElement cellElement3 = doc.createElement("cell");
    rowElement.appendChild(cellElement3);
    cellElement3.appendChild(doc.createTextNode("1.00"));

    QDomElement cellElement4 = doc.createElement("cell");
    rowElement.appendChild(cellElement4);
    cellElement4.appendChild(doc.createTextNode(
          "&lt;img border=&apos;0&apos; src=&apos;/web/images/sign_ok.png&apos;&gt;"));

    QDomElement cellElement5 = doc.createElement("cell");
    rowElement.appendChild(cellElement5);
    cellElement5.appendChild(doc.createTextNode(
          "&lt;img border=&apos;0&apos; src=&apos;/web/images/off.png&apos;&gt;"));

    QDomElement cellElement6 = doc.createElement("cell");
    rowElement.appendChild(cellElement6);
    cellElement6.appendChild(doc.createTextNode(
          "&lt;a href=javascript:enable(&apos;Transmission&apos;,&apos;1&apos;,&apos;app&apos;)\
          &gt;&lt;img border=&apos;0&apos; src=&apos;/web/images/start.png&apos;&gt;&lt;/a&gt;"));

    QDomElement cellElement7 = doc.createElement("cell");
    rowElement.appendChild(cellElement7);
    cellElement7.appendChild(doc.createTextNode(
          "&lt;a href=javascript:del_module(&apos;Transmission&apos;,&apos;app&apos;)&gt;&lt;img \
          border=&apos;0&apos; src=&apos;/web/images/delete_over.png&apos;&gt;&lt;/a&gt;"));

    rowElement.setAttribute("id", "0");

    //}
    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("1"));

}

