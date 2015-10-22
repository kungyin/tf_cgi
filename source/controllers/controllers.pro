TARGET = controller
TEMPLATE = lib
CONFIG += shared c++11
QT += network sql xml
QT -= gui
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH += ../helpers ../models \
               ext_libs/inc
DEPENDPATH  += ../helpers ../models
LIBS += -L../lib -lhelper -lmodel

VERSION = $$system("git rev-parse --abbrev-ref HEAD")_r$$system("git rev-list HEAD --count")_$$system(date +"%m-%d-%y")

unix:!macx {

    linux-arm-gnueabihf-g++ {
        LIBS += -L$$PWD/ext_libs/arm -lhttpftpdownload
        #QMAKE_RPATHDIR += /opt/app/lib
    }
    else {
	LIBS += -L$$PWD/ext_libs/x86 -lhttpftpdownload
        QMAKE_RPATHDIR += $$PWD/ext_libs/x86

        #QMAKE_LFLAGS += '-Wl,-rpath=/home/ian/work/cgitf/source/controllers/ext_libs/x86'
        #QMAKE_LFLAGS_RPATH += $$PWD/ext_libs/x86

        DEFINES += SIMULATOR_MODE
    }

}

include(../appbase.pri)

HEADERS += applicationcontroller.h \
    CgiController.h \
    ParseCmd.h \
    CommandDefine.h \
    AppDefine.h \
    RenderResponseNetwork.h \
    RenderResponseHome.h \
    RenderResponseDisk.h \
    RenderResponseAccount.h \
    RenderResponse.h \
    RenderResponseAppMngm.h \
    RenderResponseNetShare.h \
    RenderResponseSysMngm.h \
    RenderResponseSysStatus.h \
    RenderResponseFtp.h \
    RenderResponseTimeMachine.h \
    RenderResponseSetupWizard.h \
    ext_libs/inc/http_ftp_download.h \
    RenderResponseAddOn.h \
    Databaseobject.h \
    RenderResponseDashboard.h \
    RenderResponseFileStation.h \
    RenderResponseP2pDownloads.h \
    RenderResponseMyDlink.h \
    FileSuffixDescription.h \
    RenderResponseS3.h \
    RenderResponseGoogleDrive.h \
    RenderResponseDropbox.h \
    RenderResponseAirplay.h \
    RenderResponseFileOpBase.h \
    RenderResponseMyDlinkAccount.h \
    RenderResponseNasSharing.h
SOURCES += applicationcontroller.cpp \
    CgiController.cpp \
    ParseCmd.cpp \
    RenderResponseNetwork.cpp \
    RenderResponseHome.cpp \
    RenderResponseDisk.cpp \
    RenderResponseAccount.cpp \
    RenderResponse.cpp \
    RenderResponseAppMngm.cpp \
    RenderResponseNetShare.cpp \
    RenderResponseSysMngm.cpp \
    RenderResponseSysStatus.cpp \
    RenderResponseFtp.cpp \
    RenderResponseTimeMachine.cpp \
    RenderResponseSetupWizard.cpp \
    RenderResponseAddOn.cpp \
    Databaseobject.cpp \
    RenderResponseDashboard.cpp \
    RenderResponseFileStation.cpp \
    RenderResponseP2pDownloads.cpp \
    RenderResponseMyDlink.cpp \
    RenderResponseS3.cpp \
    RenderResponseGoogleDrive.cpp \
    RenderResponseDropbox.cpp \
    RenderResponseAirplay.cpp \
    RenderResponseFileOpBase.cpp \
    RenderResponseMyDlinkAccount.cpp \
    RenderResponseNasSharing.cpp
