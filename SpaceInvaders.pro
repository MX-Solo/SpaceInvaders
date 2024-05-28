greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia


SOURCES += \
    src/animation.cpp \
    src/enemy.cpp \
    src/game.cpp \
    src/gamescene.cpp \
    src/level.cpp \
    src/main.cpp \
    src/projectile.cpp \
    src/spaceship.cpp \
    src/view.cpp

HEADERS += \
    src/animation.h \
    src/enemy.h \
    src/game.h \
    src/gamescene.h \
    src/level.h \
    src/projectile.h \
    src/spaceship.h \
    src/view.h

RESOURCES += \
    resource.qrc
