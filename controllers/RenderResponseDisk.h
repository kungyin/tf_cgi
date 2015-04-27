#ifndef RENDERRESPONSE_H
#define RENDERRESPONSE_H

#include "RenderResponseBase.h"

typedef struct {
    QString volNameArg;
    QString raidModeArg;
    QString fileSystemTypeArg;
    QString volSizeArg;
    QString devNameArg;
    QString partition3Arg;
}FMT_ARGS;

class T_CONTROLLER_EXPORT RenderResponseDisk : public RenderResponseBase {
    Q_OBJECT
public:
    RenderResponseDisk(QVariantMap &, CGI_COMMAND);
    RenderResponseDisk(const RenderResponseDisk &other) {}
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

#endif // RENDERRESPONSE_H
