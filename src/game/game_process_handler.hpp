#ifndef BM_GAMEPROCESSHANDLER_HPP
#define BM_GAMEPROCESSHANDLER_HPP

#include "game_status.hpp"

#include <QObject>

#include <memory>

namespace bm {
class Game;
class GameResult;
class Player;

class GameProcessHandler : public QObject
{
    Q_OBJECT

public:
    virtual ~GameProcessHandler() = default;

    virtual void setGame(const std::shared_ptr<Game>& game);

protected: // methods
    const std::vector<std::shared_ptr<Player>>& gamePlayers() const;
    void                                        changeGameStatus(GameStatus newStatus);
    void                                        assignGameResultToGame(const GameResult& result);

protected: // data
    std::shared_ptr<Game> game_;
};

} // namespace bm

#endif // BM_GAMEPROCESSHANDLER_HPP
