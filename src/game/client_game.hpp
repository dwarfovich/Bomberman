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
    explicit ClientGame(Client* client, QObject* parent = nullptr);

    void start() override;
    void addPlayer(const std::shared_ptr<Bomberman>& player) override;
    void movePlayer(size_t player, Direction direction) override;
    void stopPlayer(size_t player) override;
    void placeBomb(size_t player) override;

private slots:
    void onReadyToStart();
    void onMessageReceived(const std::unique_ptr<Message>& message);

private:
    Client* client_;
    QTimer  moveTimer_;

    // Game interface
public:
    const std::shared_ptr<Bomberman>& bomberman(uint8_t playerId) const override;

    // IMessageVisitor interface
public:
    void visit(const StartGameMessage& message) override;

    // Game interface
public:
    void setMap(const std::shared_ptr<Map>& map) override;

    // Game interface
public:
    uint8_t playerId() const override;
};

} // namespace bm

#endif // BM_CLIENTGAME_HPP
