#ifndef BM_SINGLEPLAYERGAMEPROCESS_HPP
#define BM_SINGLEPLAYERGAMEPROCESS_HPP

#include "game_process_handler.hpp"
#include "game_result.hpp"

namespace bm {
class Character;

class SinglePlayerGameProcess : public GameProcessHandler
{
    Q_OBJECT

public:
    SinglePlayerGameProcess();

    void setGame(const std::shared_ptr<Game>& game) override;

private slots:
    void onCharacterDestroyed(const std::shared_ptr<Character>& character);
    void onCharacterIndexChanged(const std::shared_ptr<Character>& character, size_t index);

private: // methods
    GameResult generateGameResult();

private: // data
    std::vector<object_id_t> botsKilled_;
};

} // namespace bm

#endif // BM_SINGLEPLAYERGAMEPROCESS_HPP
