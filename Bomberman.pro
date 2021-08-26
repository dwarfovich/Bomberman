QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++2a

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32: QMAKE_POST_LINK += copy /y "$$shell_path($$OUT_PWD/debug/Bomberman.exe)" "$$shell_path(C:/Tim/Code/Bomberman-temp/Bomberman.exe)"

INCLUDEPATH += $$PWD/src

SOURCES += \
    src/game/bomb.cpp \
    src/game/bomb_explosion.cpp \
    src/game/bomb_explosion_event.cpp \
    src/game/bomberman.cpp \
    src/game/bot.cpp \
    src/game/bot_ai.cpp \
    src/game/bot_factory.cpp \
    src/game/cell.cpp \
    src/game/cell_location.cpp \
    src/game/character.cpp \
    src/game/character_factory.cpp \
    src/game/client_game.cpp \
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
    src/game/modifiers/modifier_factory.cpp \
    src/game/modifiers/permanent_bomb_radius_increase.cpp \
    src/game/modifiers/permanent_modifier.cpp \
    src/game/move_data.cpp \
    src/game/moving_object.cpp \
    src/game/network_game.cpp \
    src/game/server_game.cpp \
    src/gui/animated_sprite_graphics_object.cpp \
    src/gui/bot_graphics_item.cpp \
    src/gui/cell_item.cpp \
    src/gui/character_graphics_item.cpp \
    src/gui/character_sprite_object.cpp \
    src/gui/client_game_dialog.cpp \
    src/gui/create_network_game_dialog.cpp \
    src/gui/game_scene.cpp \
    src/gui/game_view.cpp \
    src/gui/main_menu_widget.cpp \
    src/gui/main_window.cpp \
    src/gui/map_widget.cpp \
    src/gui/player_key_controls.cpp \
    src/gui/sprite_factory.cpp \
    src/gui/sprite_graphics_object.cpp \
    src/main.cpp \
    src/net/bomb_placed_message.cpp \
    src/net/cell_changed_message.cpp \
    src/net/character_moved_message.cpp \
    src/net/client.cpp \
    src/net/client_id_message.cpp \
    src/net/client_name_message.cpp \
    src/net/client_ready_message.cpp \
    src/net/i_message_visitor.cpp \
    src/net/map_initialization_message.cpp \
    src/net/map_initialized_message.cpp \
    src/net/message.cpp \
    src/net/message_factory.cpp \
    src/net/notifying_message.cpp \
    src/net/prepare_to_start_game_message.cpp \
    src/net/server.cpp \
    src/net/server_worker.cpp \
    src/net/socket.cpp \
    src/net/start_game_message.cpp \
    src/net/text_message.cpp \
    src/timer_queue.cpp \
    src/utils.cpp

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
    src/game/character_factory.hpp \
    src/game/client_game.hpp \
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
    src/game/modifiers/modifier_factory.hpp \
    src/game/modifiers/modifier_type.hpp \
    src/game/modifiers/permanent_bomb_radius_increase.hpp \
    src/game/modifiers/permanent_modifier.hpp \
    src/game/move_data.hpp \
    src/game/moving_object.hpp \
    src/game/network_game.hpp \
    src/game/object_type.hpp \
    src/game/respawn_type.hpp \
    src/game/server_game.hpp \
    src/gui/animated_sprite_graphics_object.hpp \
    src/gui/bot_graphics_item.hpp \
    src/gui/cell_item.hpp \
    src/gui/character_graphics_item.hpp \
    src/gui/character_sprite_object.hpp \
    src/gui/client_game_dialog.hpp \
    src/gui/create_network_game_dialog.hpp \
    src/gui/game_scene.hpp \
    src/gui/game_view.hpp \
    src/gui/main_menu_widget.hpp \
    src/gui/main_window.hpp \
    src/gui/map_widget.hpp \
    src/gui/player_key_controls.hpp \
    src/gui/sprite_factory.hpp \
    src/gui/sprite_graphics_object.hpp \
    src/net/bomb_placed_message.hpp \
    src/net/cell_changed_message.hpp \
    src/net/character_moved_message.hpp \
    src/net/client.hpp \
    src/net/client_id_message.hpp \
    src/net/client_name_message.hpp \
    src/net/client_ready_message.hpp \
    src/net/i_message_maker.hpp \
    src/net/i_message_visitor.hpp \
    src/net/map_initialization_message.hpp \
    src/net/map_initialized_message.hpp \
    src/net/message.hpp \
    src/net/message_factory.hpp \
    src/net/message_maker.hpp \
    src/net/message_type.hpp \
    src/net/notifying_message.hpp \
    src/net/prepare_to_start_game_message.hpp \
    src/net/server.hpp \
    src/net/server_worker.hpp \
    src/net/socket.hpp \
    src/net/start_game_message.hpp \
    src/net/text_message.hpp \
    src/time.hpp \
    src/timer_event.hpp \
    src/timer_queue.hpp \
    src/utils.hpp

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
