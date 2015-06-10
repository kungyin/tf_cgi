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

include(../appbase.pri)

unix:!macx {

    linux-arm-gnueabihf-g++ {

    } else {
        LIBS += -L$$PWD/ext_libs/x86/ -lhttpftpdownload
        DEPENDPATH += $$PWD/ext_libs/x86
        DEFINES += SIMULATOR_MODE
    }

}

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
    RenderResponseAppDownloads.h \
    ext_libs/inc/http_ftp_download.h
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
    RenderResponseAppDownloads.cpp
