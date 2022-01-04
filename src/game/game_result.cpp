#include "game_result.hpp"
#include "utils.hpp"

#include <QDataStream>

namespace bm {

QDataStream& operator<<(QDataStream& stream, const GameResult& result)
{
    stream << result.gameWon;
    stream << result.timeExpired;
    stream << result.characterTypeWon;
    stream << result.characterIdWon;
    stream << result.characterIdsLoose;
    stream << result.losePlayers;

    return stream;
}

QDataStream& operator>>(QDataStream& stream, GameResult& result)
{
    stream >> result.gameWon;
    stream >> result.timeExpired;
    stream >> result.characterTypeWon;
    stream >> result.characterIdWon;
    stream >> result.characterIdsLoose;
    stream >> result.losePlayers;

    return stream;
}

} // namespace bm
