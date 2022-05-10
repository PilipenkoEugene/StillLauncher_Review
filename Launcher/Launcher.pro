QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addonadmuserinfo.cpp \
    auth.cpp \
    main.cpp \
    mainwindow.cpp \
    moduleadm.cpp \
    moduleimplement.cpp \
    modulesqr.cpp \
    modulesqrt.cpp \
    tabs.cpp

HEADERS += \
    addonadmuserinfo.h \
    auth.h \
    mainwindow.h \
    moduleadm.h \
    moduleimplement.h \
    modulesqr.h \
    modulesqrt.h \
    tabs.h

FORMS += \
    addonadmuserinfo.ui \
    auth.ui \
    mainwindow.ui \
    moduleadm.ui \
    moduleimplement.ui \
    modulesqr.ui \
    modulesqrt.ui \
    tabs.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
