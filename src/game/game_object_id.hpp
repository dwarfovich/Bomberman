#ifndef BM_GAMEOBJECTID_HPP
#define BM_GAMEOBJECTID_HPP

#include <cinttypes>

namespace bm {

using object_id_t                            = uint16_t;
inline constexpr object_id_t invalidObjectId = -1;

} // namespace bm

#endif // BM_GAMEOBJECTID_HPP
