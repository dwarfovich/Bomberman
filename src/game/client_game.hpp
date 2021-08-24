#ifndef BM_CLIENTGAME_HPP
#define BM_CLIENTGAME_HPP

#include "game.hpp"
#include "net/i_message_visitor.hpp"

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
    void movePlayer(size_t player, Direction) override;
    void stopPlayer(size_t player) override;
    void placeBomb(size_t player) override;

private slots:
    void onReadyToStart();

private:
    Client* client_;

    // Game interface
public:
    const std::shared_ptr<Bomberman>& bomberman(uint8_t playerId) const override;
};

} // namespace bm

#endif // BM_CLIENTGAME_HPP
