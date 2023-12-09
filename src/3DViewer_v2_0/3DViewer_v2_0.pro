QT       += core gui

win32 {
    LIBS += -lopengl32
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets openglwidgets gui

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cc \
    controller/settings.cc \
    main.cpp \
    model/3D_object.cc \
    model/parser.cc \
    view/mainwindow.cpp \
    view/oglwidget.cpp

HEADERS += \
    controller/controller.h \
    controller/settings.h \
    model/3D_object.h \
    model/parser.h \
    view/mainwindow.h \
    view/oglwidget.h

FORMS += \
    view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Makefile
