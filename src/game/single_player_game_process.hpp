#ifndef BM_SINGLEPLAYERGAMEPROCESS_HPP
#define BM_SINGLEPLAYERGAMEPROCESS_HPP

#include "game_process_handler.hpp"

namespace bm {
class Character;

class SinglePlayerGameProcess : public GameProcessHandler
{
    Q_OBJECT

public:
    SinglePlayerGameProcess();

    void setGame(const std::shared_ptr<Game>& game) override;

private slots:
    void onBotRemoved();
    void onCharacterIndexChanged(const std::shared_ptr<Character>& character, size_t index);
};

} // namespace bm

#endif // BM_SINGLEPLAYERGAMEPROCESS_HPP
