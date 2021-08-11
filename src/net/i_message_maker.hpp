#ifndef I_MESSAGE_MAKER_HPP
#define I_MESSAGE_MAKER_HPP

#include <memory>

namespace bm {
class Message;

class IMessageMaker
{
public:
    virtual ~IMessageMaker() = default;

    virtual std::unique_ptr<Message> create() const = 0;
};

} // namespace bm
#endif // I_MESSAGE_MAKER_HPP
