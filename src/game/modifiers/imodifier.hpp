#ifndef IMODIFIER_HPP
#define IMODIFIER_HPP

namespace bm {
struct Bomberman;

class IModifier {
public:
    virtual void activate(Bomberman& bomberman) = 0;
    virtual void deactivate(Bomberman& bomberman) = 0;
};
}  // namespace bm

#endif  // IMODIFIER_HPP
