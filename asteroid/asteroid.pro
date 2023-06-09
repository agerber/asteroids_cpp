TEMPLATE = app
TARGET = asteroid
DESTDIR = ./release
CONFIG += release


QT  += core gui network widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++17  -fpermissive

INCLUDEPATH +=  ../mvc/controller    \
        ../mvc/model                   \
        ../mvc/view                     \
        ./tmp/ui                        \
        ./tmp/moc

HEADERS += ../mvc/model/Asteroid.h \
    ../mvc/model/Brick.h \
    ../mvc/model/Bullet.h \
    ./Global.h \
    ../mvc/model/Falcon.h \
    ../mvc/model/Floater.h \
    ../mvc/controller/GameOp.h \
    ../mvc/controller/GameOpsQueue.h \
    ../mvc/model/NewWallFloater.h \
    ../mvc/model/Nuke.h \
    ../mvc/model/NukeFloater.h \
    ../mvc/model/PolarPoint.h \
    ../mvc/model/ShieldFloater.h \
    ../mvc/controller/Sound.h \
    ../mvc/controller/Utils.h \
    ../mvc/controller/CommandCenter.h \
    ../mvc/controller/Game.h \
    ../mvc/view/GameFrame.h \
    ../mvc/view/GamePanel.h \
    ../mvc/model/Movable.h \
    ../mvc/model/Sprite.h \
    ../mvc/model/Star.h \
    ../mvc/model/WhiteCloudDebris.h
SOURCES += ../mvc/model/Asteroid.cpp \
    ../mvc/model/Brick.cpp \
    ../mvc/model/Bullet.cpp \
    ../mvc/controller/CommandCenter.cpp \
    ../mvc/model/Falcon.cpp \
    ../mvc/model/Floater.cpp \
    ../mvc/controller/Game.cpp \
    ../mvc/model/PolarPoint.cpp \
    ../mvc/view/GameFrame.cpp \
    ../mvc/controller/GameOp.cpp \
    ../mvc/controller/GameOpsQueue.cpp \
    ../mvc/view/GamePanel.cpp \
    ../mvc/model/NewWallFloater.cpp \
    ../mvc/model/Nuke.cpp \
    ../mvc/model/NukeFloater.cpp \
    ../mvc/model/Sprite.cpp \
    ../mvc/model/Star.cpp \
    ../mvc/controller/Utils.cpp \
    ../mvc/model/WhiteCloudDebris.cpp \
    ./main.cpp
FORMS += ./mainwindow.ui
RESOURCES += asteroid.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


MOC_DIR += ./tmp/moc
UI_DIR += ./tmp/ui
RCC_DIR += ./tmp/rcc