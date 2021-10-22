#ifndef BM_GAMERESULT_HPP
#define BM_GAMERESULT_HPP

#include "character_type.hpp"
#include "game_object_id.hpp"

#include <vector>

namespace bm {

class GameResult
{
public:
    bool                     gameWon = false;
    bool                     timeExpired;
    CharacterType            characterTypeWon;
    object_id_t              characterIdWon = invalidObjectId;
    std::vector<object_id_t> characterIdsLoose;
};

} // namespace bm

#endif // BM_GAMERESULT_HPP
