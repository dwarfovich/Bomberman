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
    src/game/bomb_explosion_finished_event.cpp \
    src/game/bomberman.cpp \
    src/game/bot.cpp \
    src/game/bot_ai.cpp \
    src/game/bot_factory.cpp \
    src/game/campaign.cpp \
    src/game/cell.cpp \
    src/game/cell_location.cpp \
    src/game/character.cpp \
    src/game/character_factory.cpp \
    src/game/client_game.cpp \
    src/game/collider.cpp \
    src/game/explosion.cpp \
    src/game/game.cpp \
    src/game/game_factory.cpp \
    src/game/game_initialization_data.cpp \
    src/game/game_initializer.cpp \
    src/game/game_object.cpp \
    src/game/game_object_id.cpp \
    src/game/game_over_conditions/game_over_condition.cpp \
    src/game/game_over_conditions/single_player_game_over_condition.cpp \
    src/game/game_result.cpp \
    src/game/game_status.cpp \
    src/game/map.cpp \
    src/game/map_loader.cpp \
    src/game/modifier_deactivation_event.cpp \
    src/game/modifiers/imodifier.cpp \
    src/game/modifiers/modifier_creator.cpp \
    src/game/modifiers/modifier_factory.cpp \
    src/game/modifiers/permanent_bomb_radius_increase.cpp \
    src/game/modifiers/permanent_modifier.cpp \
    src/game/move_data.cpp \
    src/game/network_game.cpp \
    src/game/player.cpp \
    src/game/server_game.cpp \
    src/gui/cell_sprite_item.cpp \
    src/gui/character_sprite_item.cpp \
    src/gui/client_game_dialog.cpp \
    src/gui/create_network_game_dialog.cpp \
    src/gui/create_player_dialog.cpp \
    src/gui/explosion_sprite_item.cpp \
    src/gui/game_creation_dialog.cpp \
    src/gui/game_gui_initializer.cpp \
    src/gui/game_scene.cpp \
    src/gui/game_view.cpp \
    src/gui/main_menu_widget.cpp \
    src/gui/main_window.cpp \
    src/gui/map_widget.cpp \
    src/gui/modifier_sprite_item.cpp \
    src/gui/player_key_controls.cpp \
    src/gui/sprite_factory.cpp \
    src/gui/sprite_item.cpp \
    src/gui/sprite_item_callbacks.cpp \
    src/main.cpp \
    src/net/client.cpp \
    src/net/messages/bomb_exploded_message.cpp \
    src/net/messages/bomb_placed_message.cpp \
    src/net/messages/byte_array_message.cpp \
    src/net/messages/cell_changed_message.cpp \
    src/net/messages/character_moved_message.cpp \
    src/net/messages/client_joining_game_message.cpp \
    src/net/messages/client_name_message.cpp \
    src/net/messages/explosion_finished_message.cpp \
    src/net/messages/i_message_visitor.cpp \
    src/net/messages/map_initialization_message.cpp \
    src/net/messages/message.cpp \
    src/net/messages/message_factory.cpp \
    src/net/messages/notifying_message.cpp \
    src/net/messages/player_ready_message.cpp \
    src/net/messages/prepare_to_start_game_message.cpp \
    src/net/messages/select_map_request_message.cpp \
    src/net/messages/set_player_id_message.cpp \
    src/net/messages/start_game_message.cpp \
    src/net/messages/text_message.cpp \
    src/net/server.cpp \
    src/net/server_worker.cpp \
    src/net/socket.cpp \
    src/timer_queue.cpp \
    src/utils.cpp

HEADERS += \
    src/direction.hpp \
    src/game/bomb.hpp \
    src/game/bomb_explosion.hpp \
    src/game/bomb_explosion_event.hpp \
    src/game/bomb_explosion_finished_event.hpp \
    src/game/bomberman.hpp \
    src/game/bot.hpp \
    src/game/bot_ai.hpp \
    src/game/bot_factory.hpp \
    src/game/bot_type.hpp \
    src/game/campaign.hpp \
    src/game/cell.hpp \
    src/game/cell_location.hpp \
    src/game/cell_structure.hpp \
    src/game/character.hpp \
    src/game/character_factory.hpp \
    src/game/character_type.hpp \
    src/game/client_game.hpp \
    src/game/collider.hpp \
    src/game/explosion.hpp \
    src/game/game.hpp \
    src/game/game_factory.hpp \
    src/game/game_initialization_data.hpp \
    src/game/game_initializer.hpp \
    src/game/game_object.hpp \
    src/game/game_object_id.hpp \
    src/game/game_over_conditions/game_over_condition.hpp \
    src/game/game_over_conditions/game_winner_type.hpp \
    src/game/game_over_conditions/single_player_game_over_condition.hpp \
    src/game/game_result.hpp \
    src/game/game_status.hpp \
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
    src/game/network_game.hpp \
    src/game/player.hpp \
    src/game/respawn_type.hpp \
    src/game/server_game.hpp \
    src/gui/cell_sprite_item.hpp \
    src/gui/character_sprite_item.hpp \
    src/gui/client_game_dialog.hpp \
    src/gui/create_network_game_dialog.hpp \
    src/gui/create_player_dialog.hpp \
    src/gui/explosion_sprite_item.hpp \
    src/gui/game_creation_dialog.hpp \
    src/gui/game_gui_initializer.hpp \
    src/gui/game_scene.hpp \
    src/gui/game_view.hpp \
    src/gui/main_menu_widget.hpp \
    src/gui/main_window.hpp \
    src/gui/map_widget.hpp \
    src/gui/modifier_sprite_item.hpp \
    src/gui/player_key_controls.hpp \
    src/gui/sprite_factory.hpp \
    src/gui/sprite_item.hpp \
    src/gui/sprite_item_callbacks.hpp \
    src/net/client.hpp \
    src/net/messages/bomb_exploded_message.hpp \
    src/net/messages/bomb_placed_message.hpp \
    src/net/messages/byte_array_message.hpp \
    src/net/messages/cell_changed_message.hpp \
    src/net/messages/character_moved_message.hpp \
    src/net/messages/client_joining_game_message.hpp \
    src/net/messages/client_name_message.hpp \
    src/net/messages/explosion_finished_message.hpp \
    src/net/messages/i_message_maker.hpp \
    src/net/messages/i_message_visitor.hpp \
    src/net/messages/map_initialization_message.hpp \
    src/net/messages/message.hpp \
    src/net/messages/message_factory.hpp \
    src/net/messages/message_maker.hpp \
    src/net/messages/message_type.hpp \
    src/net/messages/notifying_message.hpp \
    src/net/messages/player_ready_message.hpp \
    src/net/messages/prepare_to_start_game_message.hpp \
    src/net/messages/select_map_request_message.hpp \
    src/net/messages/set_player_id_message.hpp \
    src/net/messages/start_game_message.hpp \
    src/net/messages/text_message.hpp \
    src/net/server.hpp \
    src/net/server_worker.hpp \
    src/net/socket.hpp \
    src/time.hpp \
    src/timer_event.hpp \
    src/timer_queue.hpp \
    src/utils.hpp

FORMS += \
    src/gui/client_game_dialog.ui \
    src/gui/create_network_game_dialog.ui \
    src/gui/create_player_dialog.ui \
    src/gui/main_menu_widget.ui \
    src/gui/main_window.ui \
    src/gui/map_widget.ui

TRANSLATIONS += \
    Bomberman_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
