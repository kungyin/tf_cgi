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

    void generateCheckDiskFreeSize();
    void generateGetHdInfo();

    void generateGetVolumeInfo();

    bool isLogin();
    void generatePrefix(QDomDocument &);
    bool m_bLoginStatus;

};

#endif // RENDERRESPONSENASSHARING_H
