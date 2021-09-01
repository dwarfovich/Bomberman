#ifndef BM_CLIENTGAME_HPP
#define BM_CLIENTGAME_HPP

#include "game.hpp"
#include "net/i_message_visitor.hpp"
#include "net/message.hpp"

namespace bm {
class Socket;
class Client;

class ClientGame : public Game, public IMessageVisitor
{
    Q_OBJECT

public:
    explicit ClientGame(Client* client);

    void start() override;
    //    void                  addPlayer(const std::shared_ptr<Bomberman>& player) override;
    void                  movePlayer(object_id_t player, Direction direction) override;
    void                  stopPlayer(object_id_t player) override;
    std::shared_ptr<Bomb> placeBomb(object_id_t player) override;

private slots:
    void onReadyToStart();
    void onMessageReceived(const std::unique_ptr<Message>& message);

private:
    Client* client_;
    QTimer  moveTimer_;

    // Game interface
public:
    const std::shared_ptr<Bomberman>& bomberman(object_id_t playerId) const override;

    // IMessageVisitor interface
public:
    void visit(const StartGameMessage& message) override;

    // Game interface
public:
    void setMap(const std::shared_ptr<Map>& map) override;

    // Game interface
public:
    object_id_t playerId() const override;

    // IMessageVisitor interface
public:
    void visit(const CharacterMovedMessage& message) override;

    // IMessageVisitor interface
public:
    void visit(const BombPlacedMessage& message) override;

    // IMessageVisitor interface
public:
    void visit(const CellChangedMessage& message) override;
};

} // namespace bm

#endif // BM_CLIENTGAME_HPP
