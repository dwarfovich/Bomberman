#ifndef BM_GAMEINITIALIZER_HPP
#define BM_GAMEINITIALIZER_HPP

#include <QStringList>

namespace bm {

class Game;
class GameInitializationData;

namespace game_ns {

QStringList initializeGame(const GameInitializationData& data);

namespace details {
void initializeBots(const GameInitializationData& data, QStringList& errors);
void initializeBombermans(const GameInitializationData& data, QStringList& errors);
} // namespace details

} // namespace game_ns

} // namespace bm

#endif // BM_GAMEINITIALIZER_HPP
