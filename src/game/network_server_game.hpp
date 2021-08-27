#ifndef BM_NETWORKSERVERGAME_HPP
#define BM_NETWORKSERVERGAME_HPP

#include "server_game.hpp"

namespace bm {
class Server;

class NetworkServerGame : public ServerGame
{
    Q_OBJECT

public:
    NetworkServerGame();

private:
    Server* server_;
};

} // namespace bm

#endif // BM_NETWORKSERVERGAME_HPP
