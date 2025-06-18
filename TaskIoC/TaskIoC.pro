QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        amdprocessor.cpp \
        computer.cpp \
        icomputer.cpp \
        intelprocessor.cpp \
        ioc/cfactory.cpp \
        ioc/factoryroot.cpp \
        ioc/iocconteiner.cpp \
        iprocessor.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    amdprocessor.h \
    computer.h \
    icomputer.h \
    intelprocessor.h \
    ioc/cfactory.h \
    ioc/factoryroot.h \
    ioc/iocconteiner.h \
    iprocessor.h

DISTFILES += \
    debug/cfactory.o
