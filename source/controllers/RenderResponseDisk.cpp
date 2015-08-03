#include <QProcess>
#include <cassert>

#include "RenderResponseDisk.h"

RenderResponseDisk::RenderResponseDisk(THttpRequest &req, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_pReq = &req;
}

RenderResponseDisk::~RenderResponseDisk() {
}

void RenderResponseDisk::preRender() {

    if(!m_pReq)
        return;

    switch(m_cmd) {
    case CMD_VOLUME_STATUS:
        generateVolumeStatus();
        break;
    case CMD_FMT_GET_SYNC_SATTE:
        generateFMTGetSyncState();
        break;
    case CMD_FMT_GET_AUTO_REBUILD_INFO:
        generateFMTGetAutoRebuildInfo();
        break;
    case CMD_AJAXPLORER_STOP:
        generateAJAXPlorerStop();
        break;
    case CMD_FMT_CREATE_DISKMGR:
        generateFMTCreateDiskMGR();
        break;
    case CMD_SMART_HD_LIST:
        generateSmartHDList();
        break;
    case CMD_SMART_XML_CREATE_TEST_LIST:
        generateCreateTestList();
        break;
    case CMD_SMART_SCHEDULE_LIST:
        generateSmartScheduleList();
        break;
    case CMD_SMART_GET_TEST_STATUS:
        generateGetTestStatus();
        break;
    case CMD_SMART_SET_SCHEDULE:
        generateSmartSetSchedule();
        break;
    case CMD_SCANDISK_INFO:
        generateScanDiskInfo();
        break;
    case CMD_SMART_TEST_START:
        generateSmartTestStart();
        break;
    case CMD_CHECK_DISK_REMOUNT_STATUS:
        generateCheckDiskRemountState();
        break;
    case CMD_SCANDISK_RUN_E2FSCK:
        generateScanDiskRunE2fsck();
        break;
    case CMD_SCANDISK_FINISH:
        generateScanDiskFinish();
        break;
    case CMD_VE_LIST:
        generateVeList();
        break;
    case CMD_VE_PWD_CHECK:
        generateVePwdCheck();
        break;
    case CMD_VE_VERIFY_KEYFILE:
        generateVeVerifyKeyfile();
        break;
    case CMD_VE_MODIFY:
        generateVeModify();
        break;
    case CMD_VE_SAVE_FILE:
        generateVeSaveFile();
        break;
    case CMD_NONE:
    default:
        break;
    }

}

void RenderResponseDisk::generateVolumeStatus() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " system_get_disk_volume_status", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("flag");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode(m_pReq->parameter("f_flag"));
    tag1.appendChild(t1);
    QDomElement tag2 = doc.createElement("state");
    root.appendChild(tag2);
    QDomText t2 = doc.createTextNode(apiOut.value(0));
    tag2.appendChild(t2);

    m_var = doc.toString();
}

void RenderResponseDisk::generateFMTGetSyncState() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DISK_API + " -g sync_state", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("res");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode(apiOut.value(0));
    tag1.appendChild(t1);
    QDomElement tag2 = doc.createElement("wait_sync");
    root.appendChild(tag2);
    QDomText t2 = doc.createTextNode(apiOut.value(1));
    tag2.appendChild(t2);

    m_var = doc.toString();
}

void RenderResponseDisk::generateFMTGetAutoRebuildInfo() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DISK_API + " -g auto_sync", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("auto_sync");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode(apiOut.value(0));
    tag1.appendChild(t1);
    m_var = doc.toString();

}

/* todo */
void RenderResponseDisk::generateAJAXPlorerStop() {
    QDomDocument doc;

//#ifndef SIMULATOR_MODE
//    QString apiOut = getAPIStdOut(API_PATH + DISK_API_SCRIPT + " -s ajaxplorer stop");
//#else
//    QString apiOut = "1";
//#endif

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("res");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode("1");
    tag1.appendChild(t1);

    m_var = doc.toString();

}

FMT_ARGS RenderResponseDisk::getFMTArgs(QStringList &fmtArgs) {

    FMT_ARGS args;
    args.volNameArg = "v" + fmtArgs.value(0);
    args.raidModeArg = "m1";
    if(fmtArgs.value(1).compare("standard") == 0)
        args.raidModeArg = "m1";
    else if (fmtArgs.value(1).compare("linar") == 0)
        args.raidModeArg ="m2";
    else if (fmtArgs.value(1).compare("raid0") == 0)
        args.raidModeArg ="m3";
    else if (fmtArgs.value(1).compare("raid1") == 0)
        args.raidModeArg ="m4";

    args.fileSystemTypeArg = "f2";
    if(fmtArgs.value(2).compare("ext3") == 0)
        args.fileSystemTypeArg = "f2";
    else if(fmtArgs.value(2).compare("ext4") == 0)
        args.fileSystemTypeArg ="f3";

    args.volSizeArg = "s" + fmtArgs.value(8);

    /* sdasdb -> sda,sdb */
    assert(fmtArgs.value(4).size() % 3 == 0);
    QString devName;
    for(int i = 0; i < fmtArgs.value(4).size(); i+=3) {
        if(!devName.isEmpty())
            devName += ",";
        devName += fmtArgs.value(4).midRef(i, 3);
    }

    args.devNameArg = "k" + devName;

    args.createVolume = false;
    if(fmtArgs.value(7).compare("1") == 0)
        args.createVolume = true;
    return args;
}

void RenderResponseDisk::generateFMTCreateDiskMGR() {
    QDomDocument doc;
    QString paraCreateType;
    QString paraCreateVolumeInfo;
    QString paraAutoSync;

    paraCreateType = m_pReq->parameter("f_create_type");
    paraCreateVolumeInfo = QUrl::fromPercentEncoding(m_pReq->parameter("f_create_volume_info").toLocal8Bit());
    paraAutoSync = m_pReq->parameter("f_auto_sync");

    QStringList apiOut;
    QStringList paraList = paraCreateVolumeInfo.split(",");

    tDebug("paraList size: %d", paraList.size());

    if(paraList.size() == 15 || paraList.size() == 30) {
        FMT_ARGS args1, args2;
        QStringList paraSubList1 = paraList.mid(0, 15);
        QStringList paraSubList2 = paraList.mid(15, 15);
        args1 = getFMTArgs(paraSubList1);
        if(paraList.size() == 30)
            args2 = getFMTArgs(paraSubList2);

        QString strArg1 =   "-" + args1.volNameArg + " " +
                            "-" + args1.raidModeArg + " " +
                            "-" + args1.fileSystemTypeArg + " " +
                            "-" + args1.volSizeArg + " " +
                            "-" + args1.devNameArg;

        QString strArg2;
        if(paraList.size() == 30)
            strArg2 =  args2.createVolume ?
                        "-" + args2.volNameArg + " " +
                        "-" + args2.raidModeArg + " " +
                        "-" + args2.fileSystemTypeArg + " " +
                        "-" + args2.volSizeArg + " " +
                        "-" + args2.devNameArg
                        : "";

        QString strArg2WithBlank;
        if(!strArg2.isEmpty())
            strArg2WithBlank = " " + strArg2;

        tDebug("strArg1: %s, strArg2: %s", strArg1.toLocal8Bit().data(), strArg2.toLocal8Bit().data());
        if(!QProcess::startDetached(SCRIPT_DISK_MANAGER, QStringList() << strArg1 << strArg2))
            ;
//        apiOut = getAPIStdOut(API_PATH + SCRIPT_DISK_MANAGER + " " +
//                                         strArg1 + strArg2WithBlank,
//                                         true
//                                     );
    }

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("res");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode("1" /*apiOut.value(0)*/);
    tag1.appendChild(t1);
    m_var = doc.toString();

}

void RenderResponseDisk::generateSmartHDList() {
    QDomDocument doc;

    QString paraPage;
    QString paraRp;
    QString paraQuery;
    QString paraQtype;
    QString paraField;
    QString paraUser;

    if(m_pReq->allParameters().contains("page"))
        paraPage = m_pReq->allParameters().value("page").toString();
    if(m_pReq->allParameters().contains("rp"))
        paraRp = m_pReq->allParameters().value("rp").toString();
    if(m_pReq->allParameters().contains("query"))
        paraQuery = m_pReq->allParameters().value("query").toString();
    if(m_pReq->allParameters().contains("qtype"))
        paraQtype = m_pReq->allParameters().value("qtype").toString();
    if(m_pReq->allParameters().contains("f_field"))
        paraField = m_pReq->allParameters().value("f_field").toString();
    if(m_pReq->allParameters().contains("user"))
        paraUser = m_pReq->allParameters().value("user").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_smart_disk_list");
    apiOut.removeLast();
    QString checkbox = "<input type=\"checkbox\" value=\"%1,%2,%3\" "
            "id=\"smart_hdd_num_0\" name=\"smart_hdd_num\" >";

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    for(QString e : apiOut) {
        QDomElement rowElement1 = doc.createElement("row");
        root.appendChild(rowElement1);
        rowElement1.setAttribute("id", e.split(";").value(0));

        QString checkboxValues = e.split(";").value(1);
        QString checkboxValue1 = checkboxValues.isEmpty() ? QString::null : checkboxValues.split(",").value(0);
        QString checkboxValue2 = checkboxValues.isEmpty() ? QString::null : checkboxValues.split(",").value(1);
        QString checkboxValue3 = checkboxValues.isEmpty() ? QString::null : checkboxValues.split(",").value(2);

        QDomElement cellElement1 = doc.createElement("cell");
        rowElement1.appendChild(cellElement1);
        cellElement1.appendChild(doc.createCDATASection(checkbox.arg(checkboxValue1)
                                                            .arg(checkboxValue2)
                                                            .arg(checkboxValue3)));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement1.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode(e.split(";").value(2)));
        QDomElement cellElement3 = doc.createElement("cell");
        rowElement1.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode(e.split(";").value(3)));
        QDomElement cellElement4 = doc.createElement("cell");
        rowElement1.appendChild(cellElement4);
        cellElement4.appendChild(doc.createTextNode(e.split(";").value(4)));
        QDomElement cellElement5 = doc.createElement("cell");
        rowElement1.appendChild(cellElement5);
        cellElement5.appendChild(doc.createTextNode(e.split(";").value(5)));
        QDomElement cellElement6 = doc.createElement("cell");
        rowElement1.appendChild(cellElement6);
        cellElement6.appendChild(doc.createTextNode(e.split(";").value(6)));
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode(QString::number(apiOut.size())));
    m_var = doc.toString();

}

void RenderResponseDisk::generateCreateTestList() {
    QDomDocument doc;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_smart_test_list", true, ";");
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement sendElement = doc.createElement("send_mail");
    root.appendChild(sendElement);
    sendElement.appendChild(doc.createTextNode(apiOut.value(0)));
    QDomElement smartElement = doc.createElement("smart_mail");
    root.appendChild(smartElement);
    smartElement.appendChild(doc.createTextNode(apiOut.value(1)));
    m_var = doc.toString();

}

void RenderResponseDisk::generateSmartScheduleList() {
    QDomDocument doc;
    QString paraPage;
    QString paraRp;
    QString paraQuery;
    QString paraQtype;
    QString paraField;
    QString paraUser;

    if(m_pReq->allParameters().contains("page"))
        paraPage = m_pReq->allParameters().value("page").toString();
    if(m_pReq->allParameters().contains("rp"))
        paraRp = m_pReq->allParameters().value("rp").toString();
    if(m_pReq->allParameters().contains("query"))
        paraQuery = m_pReq->allParameters().value("query").toString();
    if(m_pReq->allParameters().contains("qtype"))
        paraQtype = m_pReq->allParameters().value("qtype").toString();
    if(m_pReq->allParameters().contains("f_field"))
        paraField = m_pReq->allParameters().value("f_field").toString();
    if(m_pReq->allParameters().contains("user"))
        paraUser = m_pReq->allParameters().value("user").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_smart_schedule_list");
    QString onClick = "<a href=javascript:onclick=create_schedule_wait(0)>"
            "<IMG border='0' src='/web/images/delete_over.png'></a>";

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    if(apiOut.isEmpty()) {

        QDomElement rowElement1 = doc.createElement("row");
        root.appendChild(rowElement1);
        rowElement1.setAttribute("id", "1");

        QDomElement cellElement1 = doc.createElement("cell");
        rowElement1.appendChild(cellElement1);
        cellElement1.appendChild(doc.createTextNode("-"));
        QDomElement cellElement2 = doc.createElement("cell");
        rowElement1.appendChild(cellElement2);
        cellElement2.appendChild(doc.createTextNode("-"));
        QDomElement cellElement3 = doc.createElement("cell");
        rowElement1.appendChild(cellElement3);
        cellElement3.appendChild(doc.createTextNode("-"));

    }
    else {
        for(int i; i < apiOut.size(); i++) {
            QDomElement rowElement1 = doc.createElement("row");
            root.appendChild(rowElement1);
            rowElement1.setAttribute("id", QString::number(i+1));

            QDomElement cellElement1 = doc.createElement("cell");
            rowElement1.appendChild(cellElement1);
            cellElement1.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(0)));
            QDomElement cellElement2 = doc.createElement("cell");
            rowElement1.appendChild(cellElement2);
            cellElement2.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(1)));
            QDomElement cellElement3 = doc.createElement("cell");
            rowElement1.appendChild(cellElement3);
            cellElement3.appendChild(doc.createTextNode(apiOut.value(i).split(";").value(2)));

            QDomElement cellElement4 = doc.createElement("cell");
            rowElement1.appendChild(cellElement4);
            cellElement4.appendChild(doc.createCDATASection(onClick));
        }
    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("1"));
    m_var = doc.toString();

}

void RenderResponseDisk::generateGetTestStatus() {
    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_smart_test_status", true);

    QDomElement root = doc.createElement("Button");
    doc.appendChild(root);
    QDomElement stateElement = doc.createElement("State");
    root.appendChild(stateElement);
    stateElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseDisk::generateSmartSetSchedule() {
    QDomDocument doc;

    QString paraFlag = m_pReq->allParameters().value("f_flag").toString();
    QString paraDevice = m_pReq->allParameters().value("f_device").toString();
    QString paraType = m_pReq->allParameters().value("f_type").toString();
    QString paraHour = m_pReq->allParameters().value("f_hour").toString();
    QString paraMin = m_pReq->allParameters().value("f_min").toString();
    QString paraWeekly = m_pReq->allParameters().value("f_weekly").toString();
    QString paraDay = m_pReq->allParameters().value("f_day").toString();
    QString paraTestType = m_pReq->allParameters().value("f_test_type").toString();
    QString paraSlot = m_pReq->allParameters().value("f_slot").toString();
    QString paraMailFlag = m_pReq->allParameters().value("f_mail_flag").toString();

    QString allPara;
    allPara =   "f_flag=" + paraFlag + "#" +
                "f_device=" + paraDevice.replace(" ", ",") + "#" +
                "f_type=" + paraType + "#" +
                "f_hour=" + paraHour + "#" +
                "f_min=" + paraMin + "#" +
                "f_weekly=" + paraWeekly + "#" +
                "f_day=" + paraDay + "#" +
                "f_test_type=" + paraTestType;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_smart_schedule " + allPara);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement cmdElement = doc.createElement("cmd");
    root.appendChild(cmdElement);
    cmdElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseDisk::generateSmartTestStart() {
    QDomDocument doc;

    QString paraDevice;
    QString paraType;
    QString paraMailFlag;

    if(m_pReq->allParameters().contains("f_device"))
        paraDevice = m_pReq->allParameters().value("f_device").toString();
    if(m_pReq->allParameters().contains("f_type"))
        paraType = m_pReq->allParameters().value("f_type").toString();
    if(m_pReq->allParameters().contains("f_mail_flag"))
        paraMailFlag = m_pReq->allParameters().value("f_mail_flag").toString();

    QString allPara;
    allPara =   "f_device=" + paraDevice.replace(" ", ",") + "#" +
                "f_type=" + paraType + "#" +
                "f_mail_flag=" + paraMailFlag;

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_set_smart_test_start " + allPara);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseDisk::generateScanDiskInfo() {
    QDomDocument doc;
    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_SCANDISK_API + " -i", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    if(!apiOutList.isEmpty()) {

        QDomElement resElement = doc.createElement("res");
        root.appendChild(resElement);
        resElement.appendChild(doc.createTextNode("1"));

        QDomElement itemElement = doc.createElement("item");
        root.appendChild(itemElement);
        QDomElement optElement = doc.createElement("opt_value");
        itemElement.appendChild(optElement);
        optElement.appendChild(doc.createTextNode("a"));
        QDomElement guiElement = doc.createElement("gui_value");
        itemElement.appendChild(guiElement);
        guiElement.appendChild(doc.createTextNode("All Volume(s)"));

        for (QString e: apiOutList) {
            QDomElement itemElement1 = doc.createElement("item");
            root.appendChild(itemElement1);
            QDomElement optElement1 = doc.createElement("opt_value");
            itemElement1.appendChild(optElement1);
            optElement1.appendChild(doc.createTextNode(e));
            QDomElement guiElement1 = doc.createElement("gui_value");
            itemElement1.appendChild(guiElement1);
            guiElement1.appendChild(doc.createTextNode(e));
        }
    }
    m_var = doc.toString();

}

void RenderResponseDisk::generateCheckDiskRemountState() {
    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_SCANDISK_API + " -c", true);
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

void RenderResponseDisk::generateScanDiskRunE2fsck() {
    QDomDocument doc;
    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_SCANDISK_API + " -r", true);
    QDomElement root = doc.createElement("script");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode("location.href='/web/dsk_mgr/hd_scandisk_state.html'"));
    m_var = doc.toString();

}

void RenderResponseDisk::generateScanDiskFinish() {
    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_SCANDISK_API + " -f", true);
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.value(0)));
    m_var = doc.toString();

}

/* todo */
void RenderResponseDisk::generateVeList() {
    QDomDocument doc;
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_MANAGER_API + " service_get_smart_schedule_list");

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

//    if(apiOut.isEmpty()) {

//        QDomElement rowElement1 = doc.createElement("row");
//        root.appendChild(rowElement1);
//        rowElement1.setAttribute("id", "1");

//        QDomElement cellElement1 = doc.createElement("cell");
//        rowElement1.appendChild(cellElement1);
//        cellElement1.appendChild(doc.createTextNode("-"));
//        QDomElement cellElement2 = doc.createElement("cell");
//        rowElement1.appendChild(cellElement2);
//        cellElement2.appendChild(doc.createTextNode("-"));
//        QDomElement cellElement3 = doc.createElement("cell");
//        rowElement1.appendChild(cellElement3);
//        cellElement3.appendChild(doc.createTextNode("-"));

//    }

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("0"));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("1"));
    m_var = doc.toString();

}

/* todo */
void RenderResponseDisk::generateVePwdCheck() {
    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_SCANDISK_API + " -f", true);
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("0"));
    m_var = doc.toString();

}

/* todo */
void RenderResponseDisk::generateVeVerifyKeyfile() {
    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_SCANDISK_API + " -f", true);
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("0"));
    m_var = doc.toString();

}

/* todo */
void RenderResponseDisk::generateVeModify() {
    QDomDocument doc;
    //QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_SCANDISK_API + " -f", true);
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("5"));
    m_var = doc.toString();

}

/* todo */
void RenderResponseDisk::generateVeSaveFile() {
//    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_CONFIG_API + " save", true);
//    QString filePath = apiOut.value(0);
//    tDebug("file: %s", filePath.toLocal8Bit().data());
//    QFileInfo file(filePath);
//    if(file.exists() && file.isFile())
//        str = filePath;
}
