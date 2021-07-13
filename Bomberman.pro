QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/src

SOURCES += \
    src/game/bomb_explosion_event.cpp \
    src/game/bomberman.cpp \
    src/game/cell.cpp \
    src/game/enemy.cpp \
    src/game/game.cpp \
    src/game/imovable.cpp \
    src/game/map.cpp \
    src/game/map_loader.cpp \
    src/game/modifiers/imodifier.cpp \
    src/gui/cell_item.cpp \
    src/gui/character_graphics_item.cpp \
    src/gui/game_scene.cpp \
    src/gui/game_view.cpp \
    src/gui/main_window.cpp \
    src/gui/map_widget.cpp \
    src/main.cpp \
    src/timer_queue.cpp

HEADERS += \
    src/direction.hpp \
    src/game/bomb.hpp \
    src/game/bomb_explosion_event.hpp \
    src/game/bomberman.hpp \
    src/game/cell.hpp \
    src/game/cell_type.hpp \
    src/game/character.hpp \
    src/game/enemy.hpp \
    src/game/game.hpp \
    src/game/imovable.hpp \
    src/game/interval.hpp \
    src/game/map.hpp \
    src/game/map_loader.hpp \
    src/game/modifiers/imodifier.hpp \
    src/game/modifiers/modifier_type.hpp \
    src/game/move_data.hpp \
    src/gui/cell_item.hpp \
    src/gui/character_graphics_item.hpp \
    src/gui/game_scene.hpp \
    src/gui/game_view.hpp \
    src/gui/main_window.hpp \
    src/gui/map_widget.hpp \
    src/time.hpp \
    src/timer_event.hpp \
    src/timer_queue.hpp

FORMS += \
    src/gui/main_window.ui \
    src/gui/map_widget.ui

TRANSLATIONS += \
    Bomberman_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
