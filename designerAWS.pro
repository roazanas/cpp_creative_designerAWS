QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    applyMethods.cpp \
    buttonEventsMainWindow.cpp \
    customview.cpp \
    info.cpp \
    main.cpp \
    mainwindow.cpp \
    noisegenerator.cpp \
    serviceFunctions.cpp \
    sliderEventsMainWindow.cpp

HEADERS += \
    customview.h \
    info.h \
    mainwindow.h \
    noisegenerator.h

FORMS += \
    info.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    res/1.jpeg \
    res/2.jpg \
    res/icon.svg \
    res/stub.jpg
