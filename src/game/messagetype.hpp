#ifndef BM_MESSAGETYPE_HPP
    #define BM_MESSAGETYPE_HPP

#include <cinttypes>

namespace bm {

enum class MessageType : uint8_t{
    ServerReady,

    CellChanged,
    GameObjectAdded,
    GameObjectChanged,
    GameObjectDestroyed
};

} // namespace bm

#endif // BM_MESSAGETYPE_HPP
