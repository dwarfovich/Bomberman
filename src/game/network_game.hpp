#ifndef BM_NETWORKGAME_HPP
#define BM_NETWORKGAME_HPP

#include "server_game.hpp"
#include "net/messages/message.hpp"
#include "net/messages/i_message_visitor.hpp"

#include "unordered_set"

namespace bm {
class Server;
class ClientJoiningGameMessage;

class NetworkGame : public ServerGame, public IMessageVisitor
{
    Q_OBJECT

public:
    explicit NetworkGame(Server* server);

    void                  start() override;
    void                  setMap(const std::shared_ptr<Map>& map) override;
    void                  movePlayer(object_id_t player, Direction direction) override;
    void                  stopPlayer(object_id_t player) override;
    std::shared_ptr<Bomb> placeBomb(object_id_t player) override;

    void visit(const ClientJoiningGameMessage& message) override;
    void visit(const PlayerReadyMessage& message) override;
    void visit(const CharacterMovedMessage& message) override;
    void visit(const BombPlacedMessage& message) override;

    const std::vector<std::shared_ptr<Bomberman>>& playersBombermans() const;
    void                                           reset();

protected:
    void prepareToStart() override;
    void explodeBomb(const std::shared_ptr<Bomb>& bomb) override;
    void onExplosionFinished(const std::shared_ptr<Explosion>& explosion) override;
    void setGameStatus(GameStatus status) override;

private slots:
    void onMessageReceived(const std::unique_ptr<Message>& message);
    void onMapCellChanged(size_t index);

private: // methods
    void makeConnections();
    void sendMapInitializationMessage();
    void startGame();
    bool allPlayersReady();

private: // data
    Server* server_;
    // TODO: Check if connectionsMade_ var is actually used.
    bool                                    connectionsMade_ = false;
    std::unordered_set<uint8_t>             playersPreparingToStartGame_;
    std::unordered_set<uint8_t>             playersReady_;
    std::vector<std::shared_ptr<Bomberman>> playersBombermans_;
};

} // namespace bm

#endif // BM_NETWORKGAME_HPP
