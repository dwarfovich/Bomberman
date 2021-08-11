QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/src

SOURCES += \
    src/game/bomb_explosion.cpp \
    src/game/bomb_explosion_event.cpp \
    src/game/bomberman.cpp \
    src/game/bot.cpp \
    src/game/bot_ai.cpp \
    src/game/bot_factory.cpp \
    src/game/cell.cpp \
    src/game/cell_location.cpp \
    src/game/character.cpp \
    src/game/collider.cpp \
    src/game/explosion.cpp \
    src/game/game.cpp \
    src/game/game_factory.cpp \
    src/game/game_initializer.cpp \
    src/game/game_object.cpp \
    src/game/game_over_conditions/game_over_condition.cpp \
    src/game/game_over_conditions/single_player_game_over_condition.cpp \
    src/game/game_result.cpp \
    src/game/map.cpp \
    src/game/map_loader.cpp \
    src/game/modifier_deactivation_event.cpp \
    src/game/modifiers/imodifier.cpp \
    src/game/modifiers/modifier_creator.cpp \
    src/game/modifiers/permanent_bomb_radius_increase.cpp \
    src/game/modifiers/permanent_modifier.cpp \
    src/game/moving_object.cpp \
    src/game/server_game.cpp \
    src/gui/bot_graphics_item.cpp \
    src/gui/cell_item.cpp \
    src/gui/character_graphics_item.cpp \
    src/gui/client_game_dialog.cpp \
    src/gui/create_network_game_dialog.cpp \
    src/gui/game_scene.cpp \
    src/gui/game_view.cpp \
    src/gui/main_menu_widget.cpp \
    src/gui/main_window.cpp \
    src/gui/map_widget.cpp \
    src/main.cpp \
    src/net/client.cpp \
    src/net/message.cpp \
    src/net/message_factory.cpp \
    src/net/server.cpp \
    src/net/server_worker.cpp \
    src/net/text_message.cpp \
    src/timer_queue.cpp

HEADERS += \
    src/direction.hpp \
    src/game/bomb.hpp \
    src/game/bomb_explosion.hpp \
    src/game/bomb_explosion_event.hpp \
    src/game/bomberman.hpp \
    src/game/bot.hpp \
    src/game/bot_ai.hpp \
    src/game/bot_constants.hpp \
    src/game/bot_factory.hpp \
    src/game/bot_type.hpp \
    src/game/cell.hpp \
    src/game/cell_location.hpp \
    src/game/cell_structure.hpp \
    src/game/character.hpp \
    src/game/collider.hpp \
    src/game/explosion.hpp \
    src/game/game.hpp \
    src/game/game_factory.hpp \
    src/game/game_initializer.hpp \
    src/game/game_object.hpp \
    src/game/game_over_conditions/game_over_condition.hpp \
    src/game/game_over_conditions/game_winner_type.hpp \
    src/game/game_over_conditions/single_player_game_over_condition.hpp \
    src/game/game_parameters.hpp \
    src/game/game_result.hpp \
    src/game/interval.hpp \
    src/game/map.hpp \
    src/game/map_constants.hpp \
    src/game/map_loader.hpp \
    src/game/modifier_deactivation_event.hpp \
    src/game/modifiers/imodifier.hpp \
    src/game/modifiers/modifier_creator.hpp \
    src/game/modifiers/modifier_type.hpp \
    src/game/modifiers/permanent_bomb_radius_increase.hpp \
    src/game/modifiers/permanent_modifier.hpp \
    src/game/move_data.hpp \
    src/game/moving_object.hpp \
    src/game/respawn_type.hpp \
    src/game/server_game.hpp \
    src/gui/bot_graphics_item.hpp \
    src/gui/cell_item.hpp \
    src/gui/character_graphics_item.hpp \
    src/gui/client_game_dialog.hpp \
    src/gui/create_network_game_dialog.hpp \
    src/gui/game_scene.hpp \
    src/gui/game_view.hpp \
    src/gui/main_menu_widget.hpp \
    src/gui/main_window.hpp \
    src/gui/map_widget.hpp \
    src/net/client.hpp \
    src/net/i_message_maker.hpp \
    src/net/message.hpp \
    src/net/message_factory.hpp \
    src/net/message_maker.hpp \
    src/net/message_type.hpp \
    src/net/server.hpp \
    src/net/server_worker.hpp \
    src/net/text_message.hpp \
    src/time.hpp \
    src/timer_event.hpp \
    src/timer_queue.hpp

FORMS += \
    src/gui/client_game_dialog.ui \
    src/gui/create_network_game_dialog.ui \
    src/gui/main_menu_widget.ui \
    src/gui/main_window.ui \
    src/gui/map_widget.ui

TRANSLATIONS += \
    Bomberman_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
