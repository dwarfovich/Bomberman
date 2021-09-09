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

    CharacterMoved,
    BombPlaced,
    CellChanged,

    GameObjectAdded,
    GameObjectChanged,
    GameObjectDestroyed,
    TypesCount
};

} // namespace bm

#endif // BM_MESSAGETYPE_HPP