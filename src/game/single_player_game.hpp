#ifndef BM_SINGLEPLAYERGAME_HPP
#define BM_SINGLEPLAYERGAME_HPP

#include "game.hpp"

namespace bm {

class SinglePlayerGame : public Game
{
    Q_OBJECT

public:
    SinglePlayerGame();

    void start() override;

    void movePlayer(int player, Direction) override;
    void stopPlayer(int player) override;
    void placeBomb(int player) override;

    void setMap(const std::shared_ptr<Map>& map);
};

} // namespace bm

#endif // BM_SINGLEPLAYERGAME_HPP
