#include "network_game.hpp"
#include "bomb_explosion.hpp"
#include "bomb_explosion_finished_event.hpp"
#include "net/server.hpp"
#include "net/messages/player_ready_message.hpp"
#include "net/messages/map_initialization_message.hpp"
#include "net/messages/start_game_message.hpp"
#include "net/messages/character_moved_message.hpp"
#include "net/messages/bomb_placed_message.hpp"
#include "net/messages/cell_changed_message.hpp"
#include "net/messages/set_player_id_message.hpp"
#include "net/messages/bomb_exploded_message.hpp"
#include "net/messages/explosion_finished_message.hpp"
#include "net/messages/client_joining_game_message.hpp"
#include "net/messages/game_over_message.hpp"

namespace bm {

NetworkGame::NetworkGame(Server *server) : server_ { server }
{
    server->setParent(this);

    auto bomberman = std::make_shared<Bomberman>();
    playersBombermans_.push_back(bomberman);
    playerId_ = bomberman->id();
    playersPreparingToStartGame_.insert(bomberman->id());

    connect(server_, &Server::messageReceived, this, &NetworkGame::onMessageReceived);
}

void NetworkGame::start()
{
    qDebug() << "Starting game";
    prepareToStart();
}

void NetworkGame::prepareToStart()
{
    setGameStatus(GameStatus::Preparing);
    playersReady_.insert(playerId());

    qDebug() << "Prepare to start";
    if (allPlayersReady()) {
        qDebug() << "all players ready - starting game";
        startGame();
    } else {
        qDebug() << "Not all players ready - sending ClientJoiningGameMessage";
        ClientJoiningGameMessage message { *players_.front() };
        server_->broadcastMessage(message);
        sendMapInitializationMessage();
    }
}

void NetworkGame::setMap(const std::shared_ptr<Map> &map)
{
    if (map_) {
        disconnect(map_.get(), &Map::cellStructureChanged, this, &NetworkGame::onMapCellChanged);
        disconnect(map_.get(), &Map::modifierAdded, this, &NetworkGame::onMapCellChanged);
        disconnect(map_.get(), &Map::modifierRemoved, this, &NetworkGame::onMapCellChanged);
    }
    ServerGame::setMap(map);
    connect(map_.get(), &Map::cellStructureChanged, this, &NetworkGame::onMapCellChanged);
    connect(map_.get(), &Map::modifierAdded, this, &NetworkGame::onMapCellChanged);
    connect(map_.get(), &Map::modifierRemoved, this, &NetworkGame::onMapCellChanged);
}

void NetworkGame::onMessageReceived(const std::unique_ptr<Message> &message)
{
    message->accept(*this);
}

void NetworkGame::onMapCellChanged(size_t index)
{
    const auto &       cell = map_->cell(index);
    CellChangedMessage message { cell };
    server_->broadcastMessage(message);
}

void NetworkGame::sendMapInitializationMessage()
{
    MapInitializationMessage message { *map_ };
    server_->broadcastMessage(message);
}

void NetworkGame::startGame()
{
    StartGameMessage message;
    server_->broadcastMessage(message);
    Game::start();
}

bool NetworkGame::allPlayersReady()
{
    return (playersReady_ == playersPreparingToStartGame_);
}

const std::vector<std::shared_ptr<Bomberman>> &NetworkGame::playersBombermans() const
{
    return playersBombermans_;
}

void NetworkGame::reset()
{
    playersReady_.clear();
    playersPreparingToStartGame_.clear();
    playersBombermans_.clear();
    players_.clear();

    setGameStatus(GameStatus::Waiting);

    auto bomberman = std::make_shared<Bomberman>();
    playersBombermans_.push_back(bomberman);
    playerId_ = bomberman->id();
    playersPreparingToStartGame_.insert(bomberman->id());
}

void NetworkGame::movePlayer(object_id_t player, Direction direction)
{
    auto bomberman = map_->bomberman(player);
    if (bomberman) {
        ServerGame::movePlayer(player, direction);
        CharacterMovedMessage message(*bomberman);
        server_->broadcastMessage(message);
    }
}

void NetworkGame::stopPlayer(object_id_t player)
{
    auto bomberman = map_->bomberman(player);
    if (bomberman) {
        ServerGame::stopPlayer(player);
        CharacterMovedMessage message(*bomberman);
        server_->broadcastMessage(message);
    }
}

std::shared_ptr<Bomb> NetworkGame::placeBomb(object_id_t player)
{
    const auto &bomb = ServerGame::placeBomb(player);
    if (bomb) {
        BombPlacedMessage message { *bomb };
        server_->broadcastMessage(message);
    }

    return bomb;
}

void NetworkGame::visit(const CharacterMovedMessage &message)
{
    const auto &[objectId, moveData] = message.moveData();
    map_->moveCharacter(objectId, moveData);
    server_->broadcastMessage(message, server_->currentMessageClient());
    const auto &character = map_->character(objectId);
    if (moveData.speed == 0) {
        emit characterStopped(character);
    } else {
        emit characterStartedMoving(character);
    }
}

void NetworkGame::visit(const BombPlacedMessage &message)
{
    placeBomb(message.bomb()->ownerId);
}

void NetworkGame::visit(const ClientJoiningGameMessage &message)
{
    if (currentStatus() == GameStatus::Waiting) {
        auto bomberman = std::make_shared<Bomberman>();
        playersPreparingToStartGame_.insert(bomberman->id());
        playersBombermans_.push_back(bomberman);
        auto player = std::make_shared<Player>(message.payload());
        player->setCurrentGameBombermanId(bomberman->id());
        addPlayer(player);

        SetPlayerIdMessage idMessage(bomberman->id());
        server_->sendMessage(idMessage, server_->currentMessageClient());
        emit server_->logMessageRequest("Adding bomberman for client " + QString::number(bomberman->id()));

        ClientJoiningGameMessage newMessage { *player };
        server_->broadcastMessage(newMessage, server_->currentMessageClient());
        qDebug() << "ClientJoiningGameMessage: added new player";
    } else {
        qDebug() << "ClientJoiningGameMessage: not added player due wrong gamestatus";
    }
}

void NetworkGame::visit(const PlayerReadyMessage &message)
{
    playersReady_.insert(message.payload());
    emit server_->logMessageRequest("Player ready: " + QString::number(message.payload()));
    if (allPlayersReady()) {
        startGame();
    }
}

void NetworkGame::explodeBomb(const std::shared_ptr<Bomb> &bomb)
{
    auto explosionData = bm::explodeBomb(*map_, *bomb);
    auto explosion     = explosionData.explosion;
    auto callback      = std::bind(&NetworkGame::onExplosionFinished, this, std::placeholders::_1);
    timerEventsQueue.addEvent(createDelay(bomb->explosionPeriod),
                              std::make_unique<BombExplosionFinishedEvent>(explosion, callback));

    auto bomberman = map_->bomberman(bomb->ownerId);
    if (bomberman) {
        bomberman->decreaseActiveBombs();
    }

    // TODO: Remove one of this signals.
    emit bombExploded(bomb);
    emit explosionHappened(explosion);

    BombExplodedMessage message { *bomb, *explosion };
    server_->broadcastMessage(message);
}

void NetworkGame::onExplosionFinished(const std::shared_ptr<Explosion> &explosion)
{
    Game::onExplosionFinished(explosion);
    emit                     explosionFinished(explosion);
    ExplosionFinishedMessage message { explosion->id() };
    server_->broadcastMessage(message);
}

void NetworkGame::setGameStatus(GameStatus status)
{
    if (status == GameStatus::GameOver) {
        GameOverMessage message { gameResult_ };
        server_->broadcastMessage(message);
    }

    Game::setGameStatus(status);
}

} // namespace bm
