#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T16:45:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WindowsTools
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += $${_PRO_FILE_PWD_}/ScanAlgorithms
INCLUDEPATH += $${_PRO_FILE_PWD_}/ScanWidgets



DEPENDPATH += $$INCLUDEPATH

SOURCES += main.cpp \
    Scanner.cpp \
    ScanAlgorithms/EventScanAlgorithm.cpp \
    ScanAlgorithms/TempScanAlgorithm.cpp \
    ScanWidgets/DialogScan.cpp \
    ScanWidgets/regcleaner.cpp \
    ScanWidgets/ScanWindow.cpp

HEADERS  += Scanner.h \
    ScanAlgorithms/EventScanAlgorithm.h \
    ScanAlgorithms/ScanAlgorithm.h \
    ScanAlgorithms/TempScanAlgorithm.h \
    ScanWidgets/DialogScan.h \
    ScanWidgets/RegCleaner.h \
    ScanWidgets/ScanWindow.h

FORMS += ScanWidgets/dialogscan.ui \
    ScanWidgets/ScanWindow.ui


RESOURCES += \
    res.qrc
