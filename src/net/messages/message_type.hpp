#ifndef BM_MESSAGETYPE_HPP
#define BM_MESSAGETYPE_HPP

#include <cinttypes>

namespace bm {

enum class MessageType : uint8_t
{
    ServerReady,
    Text,
    ClientName,
    SetPlayerId,
    ClientJoiningGame,
    SelectMapRequest,
    MapInitialization,
    MapInitialized,
    PrepareToStartGame,
    StartGame,
    GameOver,

    CharacterMoved,
    BombPlaced,
    BombExploded,
    ExplosionFinished,
    CellChanged,

    GameObjectAdded,
    GameObjectChanged,
    GameObjectDestroyed,
    TypesCount
};

} // namespace bm

#endif // BM_MESSAGETYPE_HPP
