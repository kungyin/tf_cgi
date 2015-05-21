#ifndef RENDERRESPONSEDISK_H
#define RENDERRESPONSEDISK_H

#include "RenderResponse.h"


/*
volume_para1 : 1 | 2 | 3 | 4 (int) #Volume Name,ex:v1,v2,v3,v4
volume_para2 : standard | linar | raid0 | raid1 (string) #RAID Level,ex:standard,linear,raid0,raid1, //raid5,raid10(2bay not support)
volume_para3 : ext3 | ext4 (string) #File Tyle,ex:ext3,ext4
volume_para4 : 1 or number (int) #RAID Size,ex:1 to n
volume_para5 : sdasdb (string) #Deive Name,ex:sda,adasdb, //adasdbsdc,adasdbsdcsdd(2bay not support)
volume_para6 : none (string) #Spare Disk,ex:none,sda,sdb, //sdc,sdd(2bay not support)
volume_para7 : 0 | 1 (int) #linear on partitions 3,ex:0->false,1->true
volume_para8 : 0 | 1 (int) #status,ex:0->don't create volume,1->create volume
volume_para9 : 1 or number (int) #raid size by user set,1 to n
volume_para10: 0 | 1 (int) #format type,ex: 0 -> cereate all disk(s) or newly insert hd, 1 -> STD To RAID1, //2 -> STD To RAID5, 3 -> RAID5 Spare Disk(2bay not support)
volume_para11: none (string) #source device for STD2R1,STD2R5 or R5 Spare Disk,ex:sda,adasdb //adasdbsdc,adasdbsdcsdd(2bay not support)
volume_para12: 0 () #same device size,ex:sda == sdb
volume_para13: 0 | 1 (int) #Volume Encryption,ex:0 -> no, 1 -> yes
volume_para14: 0 | 1 (int) #Volume Encryption's Auto-Mount,ex:0 -> no, 1 -> yes
volume_para15: 000000 (string) #Volume Encryption's Password,ex:str
*/
typedef struct {
    QString volNameArg;             // volume_para1
    QString raidModeArg;            // volume_para2
    QString fileSystemTypeArg;      // volume_para3
    QString volSizeArg;             // volume_para9
    QString devNameArg;             // volume_para5
    bool    createVolume;           // volume_para8
    QString volEnc;                 // volume_para13
    QString volEncAutoMount;        // volume_para14
    QString volEncPwd;              // volume_para15
}FMT_ARGS;


class T_CONTROLLER_EXPORT RenderResponseDisk : public RenderResponse {
    Q_OBJECT
public:
    RenderResponseDisk(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseDisk();

    virtual RENDER_TYPE preRender();

private:

    FMT_ARGS getFMTArgs(QStringList &);

    void generateVolumeStatus(QDomDocument &);
    void generateFMTGetSyncState(QDomDocument &);
    void generateFMTGetAutoRebuildInfo(QDomDocument &);
    void generateAJAXPlorerStop(QDomDocument &);
    void generateFMTCreateDiskMGR(QDomDocument &);
    void generateSmartHDList(QDomDocument &);
    void generateCreateTestList(QDomDocument &);
    void generateSmartScheduleList(QDomDocument &);
    void generateGetTestStatus(QDomDocument &);
    void generateSmartSetSchedule(QDomDocument &);
    void generateSmartDelSchedule(QDomDocument &);
    void generateSmartTestStart(QDomDocument &);
    void generateScanDiskInfo(QDomDocument &);
    void generateCheckDiskRemountState(QDomDocument &);
    void generateScanDiskRunE2fsck(QDomDocument &);
    void generateScanDiskFinish(QDomDocument &);

};

#endif // RENDERRESPONSEDISK_H
