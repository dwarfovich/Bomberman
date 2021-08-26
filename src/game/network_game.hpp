#ifndef BM_NETWORKGAME_HPP
#define BM_NETWORKGAME_HPP

#include "server_game.hpp"
#include "net/message.hpp"
#include "net/i_message_visitor.hpp"

#include "unordered_set"

namespace bm {
class Server;
class ClientReadyMessage;

class NetworkGame : public ServerGame, public IMessageVisitor
{
    Q_OBJECT

public:
    explicit NetworkGame(Server* server, QObject* parent = nullptr);

    void start() override;
    void startPreparing();
    void setMap(const std::shared_ptr<Map>& map) override;

private slots:
    void onMessageReceived(const std::unique_ptr<Message>& message);
    void onMapCellChanged(size_t index);

private: // methods
    void makeConnections();
    void sendMapInitializationMessage();
    void startGame();

private: // data
    Server* server_;
    bool    connectionsMade_ = false;

    // Game interface
public:
    void                  movePlayer(size_t player, Direction direction) override;
    void                  stopPlayer(size_t player) override;
    std::shared_ptr<Bomb> placeBomb(size_t player) override;

    // IMessageVisitor interface
public:
    void visit(const CharacterMovedMessage& message) override;

    // IMessageVisitor interface
public:
    void visit(const BombPlacedMessage& message) override;
};

} // namespace bm

#endif // BM_NETWORKGAME_HPP
