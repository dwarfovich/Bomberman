#include "client_game.hpp"
#include "net/client.hpp"

namespace bm {

ClientGame::ClientGame(Client *client, QObject *parent) : Game { parent }, client_ { client }
{
    client_->setParent(this);

    connect(client, &Client::readyToStartGame, this, &ClientGame::onReadyToStart);
}

void ClientGame::start()
{}

void ClientGame::addPlayer(const std::shared_ptr<Bomberman> &player)
{}

void ClientGame::movePlayer(size_t player, Direction)
{}

void ClientGame::stopPlayer(size_t player)
{}

void ClientGame::placeBomb(size_t player)
{}

void ClientGame::onReadyToStart()
{
    Game::start();
}

const std::shared_ptr<Bomberman> &ClientGame::bomberman(uint8_t playerId) const
{
    const auto &bombermans = map_->bombermans();
    auto        iter       = std::find_if(bombermans.cbegin(), bombermans.cend(), [playerId](const auto &iter) {
        return iter.second->playerId() == playerId;
    });
    if (iter != bombermans.cend()) {
        return iter->second;
    } else {
        const static std::shared_ptr<Bomberman> empty;
        return empty;
    }
}

} // namespace bm
