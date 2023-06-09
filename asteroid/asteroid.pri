message("You are running qmake on a generated .pro file. This may not work!")


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
