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
    void setMap(const std::shared_ptr<Map>& map) override;

    void visit(const ClientReadyMessage& message) override;

private slots:
    void onMessageReceived(const std::unique_ptr<Message>& message);

private: // methods
    void makeConnections();
    void sendMapInitializationMessage();
    void startGame();

private: // data
    Server*                     server_;
    bool                        connectionsMade_ = false;
    std::unordered_set<uint8_t> playersReady_;
    uint8_t                     playersToWait_ = 0;
};

} // namespace bm

#endif // BM_NETWORKGAME_HPP
