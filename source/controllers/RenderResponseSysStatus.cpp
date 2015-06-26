#include "RenderResponseSysStatus.h"
#include <cassert>
#include <THttpUtility>

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

void RenderResponseSysStatus::generateMtpInfo(QDomDocument &doc) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_mtp_info");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.isEmpty() ? "0" : "1"));

    QList<QString> mtpContentElement;
    mtpContentElement << "usb_port" << "manufacturer" << "product";

    for(int i = 0; i < apiOut.size(); i++) {
        QDomElement mtpElement = doc.createElement("mtp");
        root.appendChild(mtpElement);
        if( mtpContentElement.size() == apiOut.value(i).split(";").size() ) {
            for(int j = 0; j < apiOut.value(i).split(";").size(); j++) {

                QDomElement element = doc.createElement(mtpContentElement.value(j));
                mtpElement.appendChild(element);
                element.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(j)));
            }
        }
        else {
            //assert(0);
            tError("RenderResponseSysStatus::generateMtpInfo(): "
                   "mtpContentElement size is not equal to apiOut size.");
        }
    }
}

void RenderResponseSysStatus::generateUsbPrinterInfo(QDomDocument &doc) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_usb_printer_info");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.isEmpty() ? "0" : "1"));

    QList<QString> printerContentElement;
    printerContentElement << "usb_port" << "manufacturer" << "product" << "printer_name";

    for(int i = 0; i < apiOut.size(); i++) {
        QDomElement printerElement = doc.createElement("printer");
        root.appendChild(printerElement);
        if( printerContentElement.size() == apiOut.value(i).split(";").size() ) {

            for(int j = 0; j < apiOut.value(i).split(";").size(); j++) {

                QDomElement element = doc.createElement(printerContentElement.value(j));
                printerElement.appendChild(element);
                element.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(j)));
            }
        }
        else {
            //assert(0);
            tError("RenderResponseSysStatus::generateUsbPrinterInfo() :"
                   "printerContentElement size is not equal to apiOut size.");
        }
    }

}


void RenderResponseSysStatus::generateUpsInfo2(QDomDocument &doc) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_ups_info2");

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.isEmpty() ? "0" : "1"));

    QList<QString> upsContentElement(QList<QString>() << "usb_port" << "manufacturer" << "product");

    for(int i = 0; i < apiOut.size(); i++) {
        QDomElement upsElement = doc.createElement("ups");
        root.appendChild(upsElement);
        if( upsContentElement.size() == apiOut.value(i).split(";").size() ) {

            for(int j = 0; j < apiOut.value(i).split(";").size(); j++) {

                QDomElement element = doc.createElement(upsContentElement.value(j));
                upsElement.appendChild(element);
                element.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(j)));
            }
        }
        else {
            //assert(0);
            tError("RenderResponseSysStatus::generateUpsInfo2(): "
                   "upsContentElement size is not equal to apiOut size.");
        }
    }

}

void RenderResponseSysStatus::generateSmartXmlCreateDeviceList(QDomDocument &doc) {

    QString paraPage = m_pReq->parameter("page");
    QString paraRp = m_pReq->parameter("rp");

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_device_smart_info");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    /* todo */
    QString uiContent = /*THttpUtility::htmlEscape(*/"&lt;a href=javascript:onclick=GetSmartInfo(&apos;sda&apos;,&apos;0&apos;)"
            ";&gt;&lt;IMG border=&apos;0&apos; src=&apos;/web/images/normal.png&apos; alt=&apos;"
            "Normal&apos;&gt;&lt;/a&gt;"/*)*/;

    for(int i = 0; i < apiOut.size(); i++) {
        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        if( 6 == apiOut.value(i).split(";").size() ) {

            for(int j = 0; j < apiOut.value(i).split(";").size(); j++) {

                QDomElement cellElement = doc.createElement("cell");
                rowElement.appendChild(cellElement);
                cellElement.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(j)));
            }
        }
        else {
            //assert(0);
            tError("RenderResponseSysStatus::generateSmartXmlCreateDeviceList(): "
                   "element size is not equal to apiOut size.");
        }
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode(uiContent));

        rowElement.setAttribute("id", QString::number(i));
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

}

void RenderResponseSysStatus::generateSmartXmlCreateSmartInfo(QDomDocument &doc) {

    QString paraPage = m_pReq->parameter("page");
    QString paraRp = m_pReq->parameter("rp");
    QString paraField = m_pReq->parameter("f_field");

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_device_smart_list " + paraField);

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    /* todo: page maybe wrong */
    for(int i = 0; i < apiOut.size(); i++) {

        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);
        if( 6 == apiOut.value(i).split(";").size() ) {

            for(int j = 0; j < apiOut.value(i).split(";").size(); j++) {

                QDomElement cellElement = doc.createElement("cell");
                rowElement.appendChild(cellElement);
                cellElement.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(j)));
            }
        }
        else {
            //assert(0);
            tError("RenderResponseSysStatus::generateSmartXmlCreateSmartInfo(): "
                   "element size is not equal to apiOut size.");
        }

        rowElement.setAttribute("id", QString::number(i+1));
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

}


void RenderResponseSysStatus::generateResource(QDomDocument &doc) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_resource_info");

    QDomElement root = doc.createElement("xml");
    doc.appendChild(root);

    QList<QString> resourceContentElement(QList<QString>()
        << "bonding_enable" << "lan_r_speed" << "lan_t_speed" << "lan2_r_speed" << "lan2_t_speed"
        << "mem_total" << "mem_free" << "buffers" << "cached" << "now_time" << "cpu");

    if( resourceContentElement.size() == apiOut.value(0).split(";").size() ) {

        for(int i=0; i < apiOut.value(0).split(";").size(); i++) {
            QDomElement element = doc.createElement(resourceContentElement.value(i));
            root.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(0).split(";").value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseSysStatus::generateResource() :"
            "resourceContentElement size is not equal to apiOut size.");

        tDebug(" %d", apiOut.value(0).split(";").size());
        tDebug(" %d", resourceContentElement.size());

    }

    for(int i=1; i < apiOut.size(); i++) {

        QDomElement processMainElement = doc.createElement("process_main");
        root.appendChild(processMainElement);

        QList<QString> processContentElement(QList<QString>()
            << "command" << "user" << "pid" << "cpu" << "mem");
        if( processContentElement.size() == apiOut.value(i).split(";").size() ) {
            for(int j = 0; j < apiOut.value(i).split(";").size(); j++) {
                QDomElement element = doc.createElement(processContentElement.value(j));
                processMainElement.appendChild(element);
                element.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(j).remove("%")));
            }
        }
        else {
            //assert(0);
            tError("RenderResponseSysStatus::generateResource(): "
                   "processContentElement size is not equal to apiOut size.");
        }
    }
}

void RenderResponseSysStatus::generateGetService(QDomDocument &doc) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_system_services", true, ";");

    QDomElement root = doc.createElement("service");
    doc.appendChild(root);

    QList<QString> serviceContentElement(QList<QString>()
        << "afp_enable" << "nfs_enable" << "ddns_enable" << "ddns_status" << "upnp_enable"
        << "tm_enable" << "ftp_enable" << "p2p_enable" << "syslog_enable" << "syslog_status"
        << "syslog_folder");

    if( serviceContentElement.size() == apiOut.size() ) {
        for(int i = 0; i < apiOut.size(); i++) {
            QDomElement element = doc.createElement(serviceContentElement.value(i));
            root.appendChild(element);
            element.appendChild(doc.createTextNode(apiOut.value(i)));
        }
    }
    else {
        //assert(0);
        tError("RenderResponseSysStatus::generateGetService(): "
               "serviceContentElement size is not equal to apiOut size.");
    }

}

void RenderResponseSysStatus::generateModuleList(QDomDocument &doc) {

    QString paraPage = m_pReq->parameter("page");
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_package_list");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    for(int i = 0; i < apiOut.size(); i++) {
        QDomElement rowElement = doc.createElement("row");
        root.appendChild(rowElement);

        if( 3 == apiOut.value(i).split(";").size() ) {
            for(int j = 0; j < apiOut.value(i).split(";").size(); j++) {
                QDomElement cellElement = doc.createElement("cell");
                rowElement.appendChild(cellElement);
                cellElement.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(j)));
            }
        }
        else {
            //assert(0);
            tError("RenderResponseSysStatus::generateModuleList(): "
                   "element size is not equal to apiOut size.");
        }

        /* todo */
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

        rowElement.setAttribute("id", QString::number(i+1));

    }
    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode(paraPage));

    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));

}

