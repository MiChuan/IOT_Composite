#-------------------------------------------------
#
# Project created by QtCreator 2020-09-16T20:03:11
#
#-------------------------------------------------

QT       += core gui \
        sql \
        serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudentCardSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tools/tools.cpp \
    serialThread/serialportthread.cpp \
    database/dbmanager.cpp \
    database/rechargetablemodel.cpp \
    serialThread/serialportthread.cpp \
    tools/tools.cpp \
    main.cpp \
    mainwindow.cpp \
    database/user_tablemodel.cpp \
    database/consume_tablemodel.cpp \
    database/product_tablemodel.cpp \
    database/merchant_tablemodel.cpp \
    database/dormitory_tablemodel.cpp \
    database/libary_tablemodel.cpp \
    database/school_tablemodel.cpp \
    pages/connect/settingsdialog.cpp

HEADERS += \
        mainwindow.h \
    tools/tools.h \
    inc/m1356dll.h \
    inc/m1356dll_global.h \
    serialThread/serialportthread.h \
    database/database_api.h \
    database/dbmanager.h \
    database/rechargetablemodel.h \
    inc/m1356dll.h \
    inc/m1356dll_global.h \
    serialThread/serialportthread.h \
    tools/tools.h \
    mainwindow.h \
    database/user_tablemodel.h \
    database/consume_tablemodel.h \
    database/product_tablemodel.h \
    database/merchant_tablemodel.h \
    database/dormitory_tablemodel.h \
    database/libary_tablemodel.h \
    database/school_tablemodel.h \
    pages/connect/settingsdialog.h \
    pages/pages.h

FORMS += \
        mainwindow.ui \
    pages/connect/settingsdialog.ui

RESOURCES += \
    resource/res.qrc

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lM1356Dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lM1356Dlld

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
