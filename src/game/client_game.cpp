#include "client_game.hpp"

namespace bm {

ClientGame::ClientGame(Socket *socket, QObject *parent) : Game { parent }, socket_ { socket }
{}

} // namespace bm
