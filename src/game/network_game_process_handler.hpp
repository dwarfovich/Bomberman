#ifndef BM_NETWORKGAMEPROCESSHANDLER_HPP
#define BM_NETWORKGAMEPROCESSHANDLER_HPP

#include "game_process_handler.hpp"
#include "game_object_id.hpp"

namespace bm {
class Character;

class NetworkGameProcessHandler : public GameProcessHandler
{
public:
    NetworkGameProcessHandler();

    void setGame(const std::shared_ptr<Game>& game) override;

private slots:
    void onCharacterDestroyed(const std::shared_ptr<Character>& character);

private: // methods
    GameResult generateGameResult();

private: // data
    std::vector<object_id_t> destroyedBombermans_;
};

} // namespace bm

#endif // BM_NETWORKGAMEPROCESSHANDLER_HPP
