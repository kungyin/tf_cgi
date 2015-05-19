#include <cassert>

#include "RenderResponseDisk.h"
#include "AppDefine.h"

RenderResponseDisk::RenderResponseDisk(QVariantMap &map, CGI_COMMAND cmd)
{
    m_cmd = cmd;
    m_renderType = RENDER_TYPE_UNKNOWN;
    m_pMap = &map;
}

RenderResponseDisk::~RenderResponseDisk() {
}

RENDER_TYPE RenderResponseDisk::preRender() {

    if(!m_pMap)
        return RENDER_TYPE_UNKNOWN;

    QDomDocument doc = QDomDocument();
    QString str = QString();

    switch(m_cmd) {
    case CMD_VOLUME_STATUS:
        generateVolumeStatus(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_FMT_GET_SYNC_SATTE:
        generateFMTGetSyncState(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_FMT_GET_AUTO_REBUILD_INFO:
        generateFMTGetAutoRebuildInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_AJAXPLORER_STOP:
        generateAJAXPlorerStop(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_FMT_CREATE_DISKMGR:
        generateFMTCreateDiskMGR(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SMART_HD_LIST:
        generateSmartHDList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SMART_XML_CREATE_TEST_LIST:
        generateCreateTestList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SMART_SCHEDULE_LIST:
        generateSmartScheduleList(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SMART_GET_TEST_STATUS:
        generateGetTestStatus(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SMART_SET_SCHEDULE:
    {
        if(m_pMap->contains("f_flag")) {
            QString paraFlag = m_pMap->value("f_flag").toString();
            if(paraFlag.compare("1") == 0)
                generateSmartSetSchedule(doc);
            else if(paraFlag.compare("0") == 0)
                generateSmartDelSchedule(doc);
        }
        m_renderType = RENDER_TYPE_XML;
        break;
    }
    case CMD_SCANDISK_INFO:
        generateScanDiskInfo(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SMART_TEST_START:
        generateSmartTestStart(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_CHECK_DISK_REMOUNT_STATUS:
        generateCheckDiskRemountState(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SCANDISK_RUN_E2FSCK:
        generateScanDiskRunE2fsck(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_SCANDISK_FINISH:
        generateScanDiskFinish(doc);
        m_renderType = RENDER_TYPE_XML;
        break;
    case CMD_NONE:
    default:
        break;
    }

    m_doc = doc;
    m_str = str;

    return m_renderType;
}

void RenderResponseDisk::generateVolumeStatus(QDomDocument &doc) {
//    QString paraFlag;
//    if(m_pMap->contains("f_flag"))
//        paraFlag = m_pMap->value("f_flag").toString();

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DISK_API + " -g volume_status", true);
    if(apiOut.size() < 2)
        return;

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("flag");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode(apiOut.at(0));
    tag1.appendChild(t1);
    QDomElement tag2 = doc.createElement("state");
    root.appendChild(tag2);
    QDomText t2 = doc.createTextNode(apiOut.at(1));
    tag2.appendChild(t2);
}

void RenderResponseDisk::generateFMTGetSyncState(QDomDocument &doc) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DISK_API + " -g sync_state", true);

    if(apiOut.size() < 2)
        return;

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("res");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode(apiOut.at(0));
    tag1.appendChild(t1);
    QDomElement tag2 = doc.createElement("wait_sync");
    root.appendChild(tag2);
    QDomText t2 = doc.createTextNode(apiOut.at(1));
    tag2.appendChild(t2);
}

void RenderResponseDisk::generateFMTGetAutoRebuildInfo(QDomDocument &doc) {

    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DISK_API + " -g auto_sync", true);

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("auto_sync");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode(apiOut.isEmpty() ? "" : apiOut.at(0));
    tag1.appendChild(t1);
}

/* todo */
void RenderResponseDisk::generateAJAXPlorerStop(QDomDocument &doc) {

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
}

FMT_ARGS RenderResponseDisk::getFMTArgs(QStringList &fmtArgs) {

    FMT_ARGS args;
    args.volNameArg = fmtArgs.value(0);
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

void RenderResponseDisk::generateFMTCreateDiskMGR(QDomDocument &doc) {
    QString paraCreateType;
    QString paraCreateVolumeInfo;
    QString paraAutoSync;

    if(m_pMap->contains("f_create_type"))
        paraCreateType = m_pMap->value("f_create_type").toString();
    if(m_pMap->contains("f_create_volume_info"))
        paraCreateVolumeInfo = m_pMap->value("f_create_volume_info").toString();
    if(m_pMap->contains("f_auto_sync"))
        paraAutoSync = m_pMap->value("f_auto_sync").toString();

    QStringList apiOut;
    QStringList paraList = paraCreateVolumeInfo.split("%2C");
    if(paraList.size() != 30) {
        return;
    }
    else {
        FMT_ARGS args1, args2;
        QStringList paraSubList1 = paraList.mid(0, 15);
        QStringList paraSubList2 = paraList.mid(15, 15);
        args1 = getFMTArgs(paraSubList1);
        args2 = getFMTArgs(paraSubList2);

        QString strArg1 =   "-" + args1.volNameArg + " " +
                            "-" + args1.raidModeArg + " " +
                            "-" + args1.fileSystemTypeArg + " " +
                            "-" + args1.volSizeArg + " " +
                            "-" + args1.devNameArg;

        QString strArg2 =  args2.createVolume ?
                            "-" + args2.volNameArg + " " +
                            "-" + args2.raidModeArg + " " +
                            "-" + args2.fileSystemTypeArg + " " +
                            "-" + args2.volSizeArg + " " +
                            "-" + args2.devNameArg
                            : "";

        apiOut = getAPIStdOut(API_PATH + SCRIPT_DISK_MANAGER + " " +
                                         strArg1 + " " +
                                         strArg2,
                                         true
                                     );
    }

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement tag1 = doc.createElement("res");
    root.appendChild(tag1);
    QDomText t1 = doc.createTextNode(apiOut.value(0));
    tag1.appendChild(t1);
}

/* todo */
void RenderResponseDisk::generateSmartHDList(QDomDocument &doc) {

    if(!m_pMap)
        return;

    QString paraPage;
    QString paraRp;
    QString paraQuery;
    QString paraQtype;
    QString paraField;
    QString paraUser;

    if(m_pMap->contains("page"))
        paraPage = m_pMap->value("page").toString();
    if(m_pMap->contains("rp"))
        paraRp = m_pMap->value("rp").toString();
    if(m_pMap->contains("query"))
        paraQuery = m_pMap->value("query").toString();
    if(m_pMap->contains("qtype"))
        paraQtype = m_pMap->value("qtype").toString();
    if(m_pMap->contains("f_field"))
        paraField = m_pMap->value("f_field").toString();
    if(m_pMap->contains("user"))
        paraUser = m_pMap->value("user").toString();

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QDomElement rowElement1 = doc.createElement("row");
    root.appendChild(rowElement1);
    rowElement1.setAttribute("id", "1");

    QDomElement cellElement1 = doc.createElement("cell");
    rowElement1.appendChild(cellElement1);
    QDomElement inputElement1 = doc.createElement("input");
    cellElement1.appendChild(inputElement1);
    inputElement1.setAttribute("type", "checkbox");
    inputElement1.setAttribute("value", "0,sda,S1F0HDP7");
    inputElement1.setAttribute("id", "smart_hdd_num_0");
    inputElement1.setAttribute("name", "smart_hdd_num");
    QDomElement cellElement2 = doc.createElement("cell");
    rowElement1.appendChild(cellElement2);
    cellElement2.appendChild(doc.createTextNode("Disk1"));
    QDomElement cellElement3 = doc.createElement("cell");
    rowElement1.appendChild(cellElement3);
    cellElement3.appendChild(doc.createTextNode("Seagate"));
    QDomElement cellElement4 = doc.createElement("cell");
    rowElement1.appendChild(cellElement4);
    cellElement4.appendChild(doc.createTextNode("ST3000DM001-9YN166"));
    QDomElement cellElement5 = doc.createElement("cell");
    rowElement1.appendChild(cellElement5);
    cellElement5.appendChild(doc.createTextNode("-"));
    QDomElement cellElement6 = doc.createElement("cell");
    rowElement1.appendChild(cellElement6);
    cellElement6.appendChild(doc.createTextNode("-"));

    QDomElement rowElement2 = doc.createElement("row");
    root.appendChild(rowElement2);
    rowElement2.setAttribute("id", "2");

    QDomElement cellElement7 = doc.createElement("cell");
    rowElement2.appendChild(cellElement7);
    QDomElement inputElement2 = doc.createElement("input");
    cellElement7.appendChild(inputElement2);
    inputElement2.setAttribute("type", "checkbox");
    inputElement2.setAttribute("value", "1,sdb,S1F0HDP9");
    inputElement2.setAttribute("id", "smart_hdd_num_0");
    inputElement2.setAttribute("name", "smart_hdd_num");
    QDomElement cellElement8 = doc.createElement("cell");
    rowElement2.appendChild(cellElement8);
    cellElement8.appendChild(doc.createTextNode("Disk2"));
    QDomElement cellElement9 = doc.createElement("cell");
    rowElement2.appendChild(cellElement9);
    cellElement9.appendChild(doc.createTextNode("Seagate"));
    QDomElement cellElement10 = doc.createElement("cell");
    rowElement2.appendChild(cellElement10);
    cellElement10.appendChild(doc.createTextNode("ST3000DM001-9YN166"));
    QDomElement cellElement11 = doc.createElement("cell");
    rowElement2.appendChild(cellElement11);
    cellElement11.appendChild(doc.createTextNode("-"));
    QDomElement cellElement12 = doc.createElement("cell");
    rowElement2.appendChild(cellElement12);
    cellElement12.appendChild(doc.createTextNode("-"));

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("2"));

}

/* todo */
void RenderResponseDisk::generateCreateTestList(QDomDocument &doc) {
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement sendElement = doc.createElement("send_mail");
    root.appendChild(sendElement);
    sendElement.appendChild(doc.createTextNode("0"));
    QDomElement smartElement = doc.createElement("smart_mail");
    root.appendChild(smartElement);
    smartElement.appendChild(doc.createTextNode("0"));
}

/* todo */
void RenderResponseDisk::generateSmartScheduleList(QDomDocument &doc) {

    if(!m_pMap)
        return;

    QString paraPage;
    QString paraRp;
    QString paraQuery;
    QString paraQtype;
    QString paraField;
    QString paraUser;

    if(m_pMap->contains("page"))
        paraPage = m_pMap->value("page").toString();
    if(m_pMap->contains("rp"))
        paraRp = m_pMap->value("rp").toString();
    if(m_pMap->contains("query"))
        paraQuery = m_pMap->value("query").toString();
    if(m_pMap->contains("qtype"))
        paraQtype = m_pMap->value("qtype").toString();
    if(m_pMap->contains("f_field"))
        paraField = m_pMap->value("f_field").toString();
    if(m_pMap->contains("user"))
        paraUser = m_pMap->value("user").toString();

    QDomElement root = doc.createElement("rows");
    doc.appendChild(root);

    QDomElement rowElement1 = doc.createElement("row");
    root.appendChild(rowElement1);
    rowElement1.setAttribute("id", "1");

    QDomElement cellElement1 = doc.createElement("cell");
    rowElement1.appendChild(cellElement1);
    cellElement1.appendChild(doc.createTextNode("S.M.A.R.T - Quick"));
    QDomElement cellElement2 = doc.createElement("cell");
    rowElement1.appendChild(cellElement2);
    cellElement2.appendChild(doc.createTextNode("Disk1,Disk2"));
    QDomElement cellElement3 = doc.createElement("cell");
    rowElement1.appendChild(cellElement3);
    cellElement3.appendChild(doc.createTextNode("MON 17:00 / Weekly"));
    QDomElement cellElement4 = doc.createElement("cell");
    rowElement1.appendChild(cellElement4);
    QDomElement aElement = doc.createElement("a");
    rowElement1.appendChild(aElement);
    aElement.setAttribute("href", "javascript:onclick=create_schedule_wait(0)><IMG border='0' src='/web/images/delete_over.png'");

    QDomElement pageElement = doc.createElement("page");
    root.appendChild(pageElement);
    pageElement.appendChild(doc.createTextNode("1"));
    QDomElement totalElement = doc.createElement("total");
    root.appendChild(totalElement);
    totalElement.appendChild(doc.createTextNode("1"));
}

/* todo */
void RenderResponseDisk::generateGetTestStatus(QDomDocument &doc) {
    QDomElement root = doc.createElement("Button");
    doc.appendChild(root);
    QDomElement stateElement = doc.createElement("State");
    root.appendChild(stateElement);
    stateElement.appendChild(doc.createTextNode("0:"));
}

/* todo */
void RenderResponseDisk::generateSmartSetSchedule(QDomDocument &doc) {

    if(!m_pMap)
        return;

    QString paraDevice;
    QString paraType;
    QString paraHour;
    QString paraMin;
    QString paraWeekly;
    QString paraDay;
    QString paraTestType;
    QString paraSlot;
    QString paraMailFlag;

    if(m_pMap->contains("f_device"))
        paraDevice = m_pMap->value("f_device").toString();
    if(m_pMap->contains("f_type"))
        paraType = m_pMap->value("f_type").toString();
    if(m_pMap->contains("f_hour"))
        paraHour = m_pMap->value("f_hour").toString();
    if(m_pMap->contains("f_min"))
        paraMin = m_pMap->value("f_min").toString();
    if(m_pMap->contains("f_weekly"))
        paraWeekly = m_pMap->value("f_weekly").toString();
    if(m_pMap->contains("f_day"))
        paraDay = m_pMap->value("f_day").toString();
    if(m_pMap->contains("f_test_type"))
        paraTestType = m_pMap->value("f_test_type").toString();
    if(m_pMap->contains("f_slot"))
        paraSlot = m_pMap->value("f_slot").toString();
    if(m_pMap->contains("f_mail_flag"))
        paraMailFlag = m_pMap->value("f_mail_flag").toString();

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement cmdElement = doc.createElement("cmd");
    root.appendChild(cmdElement);
    cmdElement.appendChild(doc.createTextNode("1:short:0 :00:00:1:06"));
}

/* todo */
void RenderResponseDisk::generateSmartDelSchedule(QDomDocument &doc) {
    if(!m_pMap)
        return;

    QString paraMailFlag;
    if(m_pMap->contains("f_mail_flag"))
        paraMailFlag = m_pMap->value("f_mail_flag").toString();

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement cmdElement = doc.createElement("cmd");
    root.appendChild(cmdElement);
    cmdElement.appendChild(doc.createTextNode("null"));
}

/* todo */
void RenderResponseDisk::generateSmartTestStart(QDomDocument &doc) {

    if(!m_pMap)
        return;

    QString paraDevice;
    QString paraType;
    QString paraMailFlag;

    if(m_pMap->contains("f_device"))
        paraDevice = m_pMap->value("f_device").toString();
    if(m_pMap->contains("f_type"))
        paraType = m_pMap->value("f_type").toString();
    if(m_pMap->contains("f_mail_flag"))
        paraMailFlag = m_pMap->value("f_mail_flag").toString();

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));
}

void RenderResponseDisk::generateScanDiskInfo(QDomDocument &doc) {
    QStringList apiOutList = getAPIStdOut(API_PATH + SCRIPT_DISK_API + " -g scandsk_info");

    QStringList line1 = apiOutList.at(0).split(",");
    QStringList line2 = apiOutList.at(1).split(",");
    QStringList line3 = apiOutList.at(2).split(",");
    if(line1.size() < 2 || line2.size() < 2 || line3.size() < 2)
        return;

    QDomElement root = doc.createElement("config");
    doc.appendChild(root);

    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode("1"));

    for (int i=0; i<apiOutList.size(); i++) {
        QStringList line = apiOutList.at(i).split(",");
        if(line.size() < 2)
            continue;
        QDomElement itemElement1 = doc.createElement("item");
        root.appendChild(itemElement1);
        QDomElement optElement1 = doc.createElement("opt_value");
        itemElement1.appendChild(optElement1);
        optElement1.appendChild(doc.createTextNode(line.at(0)));
        QDomElement guiElement1 = doc.createElement("gui_value");
        itemElement1.appendChild(guiElement1);
        guiElement1.appendChild(doc.createTextNode(line.at(1)));
    }
}

void RenderResponseDisk::generateCheckDiskRemountState(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DISK_API + " -g dsk_remount_state", true);
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.isEmpty() ? "" : apiOut.at(0)));
}

void RenderResponseDisk::generateScanDiskRunE2fsck(QDomDocument &doc) {
    QDomElement root = doc.createElement("script");
    doc.appendChild(root);
    root.appendChild(doc.createTextNode("location.href='/web/dsk_mgr/hd_scandisk_state.html'"));
}

void RenderResponseDisk::generateScanDiskFinish(QDomDocument &doc) {
    QStringList apiOut = getAPIStdOut(API_PATH + SCRIPT_DISK_API + " -g scandsk_finish", true);
    QDomElement root = doc.createElement("config");
    doc.appendChild(root);
    QDomElement resElement = doc.createElement("res");
    root.appendChild(resElement);
    resElement.appendChild(doc.createTextNode(apiOut.isEmpty() ? "" : apiOut.at(0)));
}

