#ifndef BM_GAMERESULT_HPP
#define BM_GAMERESULT_HPP

#include "character_type.hpp"
#include "game_object_id.hpp"

#include <QString>

#include <vector>

namespace bm {

class GameResult
{
public:
    friend QDataStream& operator<<(QDataStream& stream, const GameResult& result);
    friend QDataStream& operator>>(QDataStream& stream, GameResult& result);

    bool                     gameWon = false;
    bool                     timeExpired;
    CharacterType            characterTypeWon;
    object_id_t              characterIdWon = invalidObjectId;
    std::vector<object_id_t> characterIdsLoose;
    std::vector<QString>     losePlayers;
};

} // namespace bm

#endif // BM_GAMERESULT_HPP
