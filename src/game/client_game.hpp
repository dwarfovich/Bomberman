#ifndef BM_CLIENTGAME_HPP
#define BM_CLIENTGAME_HPP

#include "game.hpp"
#include "net/messages/i_message_visitor.hpp"
#include "net/messages/message.hpp"
#include "net/messages/set_player_id_message.hpp"

namespace bm {
class Socket;
class Client;

class ClientGame : public Game, public IMessageVisitor
{
    Q_OBJECT

public:
    explicit ClientGame(Client* client);

    void                  setMap(const std::shared_ptr<Map>& map) override;
    void                  start() override;
    void                  movePlayer(object_id_t player, Direction direction) override;
    void                  stopPlayer(object_id_t player) override;
    std::shared_ptr<Bomb> placeBomb(object_id_t player) override;

    void visit(const message_ns::SetPlayerIdMessage& message) override;
    void visit(const message_ns::MapInitializationMessage& message) override;
    void visit(const message_ns::StartGameMessage& message) override;
    void visit(const message_ns::CharacterMovedMessage& message) override;
    void visit(const message_ns::BombPlacedMessage& message) override;
    void visit(const message_ns::CellChangedMessage& message) override;
    void visit(const message_ns::BombExplodedMessage& message) override;
    void visit(const message_ns::ExplosionFinishedMessage& message) override;

private slots:
    void onMessageReceived(const std::unique_ptr<message_ns::Message>& message);

private:
    Client* client_;
};

} // namespace bm

#endif // BM_CLIENTGAME_HPP
