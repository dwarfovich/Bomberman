#ifndef BM_MESSAGETYPE_HPP
#define BM_MESSAGETYPE_HPP

#include <cinttypes>

namespace bm {

enum class MessageType : uint8_t
{
    ServerReady,
    Text,
    ClientName,
    ClientId,
    ClientReady,
    MapInitialization,
    MapInitialized,
    PrepareToStartGame,
    StartGame,

    CharacterMoved,
    CellChanged,
    GameObjectAdded,
    GameObjectChanged,
    GameObjectDestroyed,
    TypesCount
};

} // namespace bm

#endif // BM_MESSAGETYPE_HPP
