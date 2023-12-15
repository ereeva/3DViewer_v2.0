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
    3rdparty/QtGifImage/gifimage/qgifimage.cc \
    3rdparty/QtGifImage/giflib/dgif_lib.c \
    3rdparty/QtGifImage/giflib/egif_lib.c \
    3rdparty/QtGifImage/giflib/gif_err.c \
    3rdparty/QtGifImage/giflib/gif_font.c \
    3rdparty/QtGifImage/giflib/gif_hash.c \
    3rdparty/QtGifImage/giflib/gifalloc.c \
    3rdparty/QtGifImage/giflib/quantize.c \
    controller/controller.cc \
    main.cc \
    model/3D_object.cc \
    model/parser.cc \
    view/mainwindow.cc \
    view/oglwidget.cc \
    view/record.cc \
    view/settings.cc

HEADERS += \
    3rdparty/QtGifImage/gifimage/qgifglobal.h \
    3rdparty/QtGifImage/gifimage/qgifimage.h \
    3rdparty/QtGifImage/gifimage/qgifimage_p.h \
    3rdparty/QtGifImage/giflib/gif_hash.h \
    3rdparty/QtGifImage/giflib/gif_lib.h \
    3rdparty/QtGifImage/giflib/gif_lib_private.h \
    controller/controller.h \
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
