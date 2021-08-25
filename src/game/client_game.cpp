#include "client_game.hpp"
#include "net/client.hpp"

namespace bm {

ClientGame::ClientGame(Client *client, QObject *parent) : Game { parent }, client_ { client }
{
    client_->setParent(this);

    connect(client_, &Client::messageReceived, this, &ClientGame::onMessageReceived);
    connect(client_, &Client::readyToStartGame, this, &ClientGame::onReadyToStart);
}

void ClientGame::start()
{}

void ClientGame::addPlayer(const std::shared_ptr<Bomberman> &player)
{}

void ClientGame::movePlayer(size_t player, Direction direction)
{
    playerBomberman_->setSpeed(defaultBombermanSpeed);
    playerBomberman_->setDirection(direction);
}

void ClientGame::stopPlayer(size_t player)
{
    playerBomberman_->setSpeed(0);
}

void ClientGame::placeBomb(size_t player)
{
    std::shared_ptr<Bomb> bomb = playerBomberman_->createBomb();
    if (bomb) {
        auto index = map_->coordinatesToIndex(playerBomberman_->movementData().coordinates);
        if (map_->isProperIndex(index)) {
            bomb->cellIndex = index;
            map_->placeBomb(bomb);
            addExplosionEvent(bomb);
        }
    }
}

void ClientGame::onReadyToStart()
{
    // Game::start();
}

void ClientGame::onMessageReceived(const std::unique_ptr<Message> &message)
{
    message->accept(*this);
}

const std::shared_ptr<Bomberman> &ClientGame::bomberman(uint8_t playerId) const
{
    const auto &bombermans = map_->bombermans();
    auto        iter       = std::find_if(bombermans.cbegin(), bombermans.cend(), [playerId](const auto &iter) {
        return iter.second->id() == playerId;
    });
    if (iter != bombermans.cend()) {
        return iter->second;
    } else {
        const static std::shared_ptr<Bomberman> empty;
        return empty;
    }
}

void ClientGame::visit(const StartGameMessage &message)
{
    if (!moveTimer_.isActive()) {
        moveTimer_.start(42);
    }
}

void ClientGame::setMap(const std::shared_ptr<Map> &map)
{
    Game::setMap(map);
    connect(&moveTimer_, &QTimer::timeout, [this]() {
        map_->moveObjects(42);
    });

    playerBomberman_ = bomberman(client_->playerId());
}

uint8_t ClientGame::playerId() const
{
    return client_->playerId();
}

} // namespace bm
