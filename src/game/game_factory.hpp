#ifndef BM_GAMEFACTORY_HPP
#define BM_GAMEFACTORY_HPP

#include "game.hpp"

#include <memory>

namespace bm {

std::unique_ptr<Game> createSinglePlayerGame(const std::shared_ptr<Map>& map);

} // namespace bm

#endif // BM_GAMEFACTORY_HPP
