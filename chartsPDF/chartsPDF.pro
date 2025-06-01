QT       += core gui
QT       += sql
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ChartCreators/barchartcreator.cpp \
    ChartCreators/ichartcreator.cpp \
    ChartData/chartdata.cpp \
    DataReaders/idatareader.cpp \
    DataReaders/jsondatareader.cpp \
    Widgets/chartwidget.cpp \
    Widgets/filesystemwidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ChartCreators/barchartcreator.h \
    ChartCreators/ichartcreator.h \
    ChartData/chartdata.h \
    DataReaders/idatareader.h \
    DataReaders/jsondatareader.h \
    Widgets/chartwidget.h \
    Widgets/filesystemwidget.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
