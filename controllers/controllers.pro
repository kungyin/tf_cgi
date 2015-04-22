TARGET = controller
TEMPLATE = lib
CONFIG += shared c++11
QT += network sql xml
QT -= gui
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH += ../helpers ../models
DEPENDPATH  += ../helpers ../models
LIBS += -L../lib -lhelper -lmodel

include(../appbase.pri)

HEADERS += applicationcontroller.h \
    CgiController.h \
    ParseCmd.h \
    CommandDefine.h \
    RenderResponseBase.h \
    RenderResponse.h \
    AppDefine.h \
    RenderResponseNetwork.h
SOURCES += applicationcontroller.cpp \
    CgiController.cpp \
    ParseCmd.cpp \
    RenderResponse.cpp \
    RenderResponseBase.cpp \
    RenderResponseNetwork.cpp
