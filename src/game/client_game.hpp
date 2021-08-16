#ifndef BM_CLIENTGAME_HPP
#define BM_CLIENTGAME_HPP

#include "game.hpp"

namespace bm {
class Socket;

class ClientGame : public Game
{
    Q_OBJECT

public:
    explicit ClientGame(Socket* socket, QObject* parent = nullptr);

private:
    Socket* socket_;
};

} // namespace bm

#endif // BM_CLIENTGAME_HPP
