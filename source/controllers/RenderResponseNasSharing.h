#ifndef RENDERRESPONSENASSHARING_H
#define RENDERRESPONSENASSHARING_H

#include "RenderResponseFileOpBase.h"

class T_CONTROLLER_EXPORT RenderResponseNasSharing : public RenderResponseFileOpBase {
    Q_OBJECT

public:
    RenderResponseNasSharing(THttpRequest &, CGI_COMMAND);
    virtual ~RenderResponseNasSharing();

    virtual void preRender();

private:
    /* 1~16 */
    void generateLogin();
    void generateScanFolder();
    void generateCreateFolder();
    void generateDelete();
    void generateRename();
    void generateDownload();
    void generateDiskInfo();
    void generateListAll();
    void generateCheckVolume();

    /* 55 */
    void generateDeviceInfo();

    /* 70~80 */
    void generateCheckDiskFreeSize();
    void generateGetHdInfo();
    void generateGetHddokInfo();
    void generateGetVolumeInfo();
    void generateUnusedVolInfo();
    void generateSetDiskVolume();
    void generateGetVolProgressBar();
    void generateRemountVolume();
    void generateRaidRoaming();

    /* 81~89 */
    void generateGetDbStatus();
    void generateControlDb();
    void generateGetServerState();
    void generateSetServerState();
    void generateGetMediaPathList();
    void generateAddMediaPath();
    void generateDelMediaPath();
    void generateRefreshMediaPath();
    void generateGetMediaProgress();

    void generateCgiProxy();

    bool isLogin();
    void generatePrefix(QDomDocument &);

private:
    bool m_bLoginStatus;
    QByteArray m_responseData;

};

#endif // RENDERRESPONSENASSHARING_H
