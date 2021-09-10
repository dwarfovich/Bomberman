#ifndef I_MESSAGE_MAKER_H
#define I_MESSAGE_MAKER_H

#include <memory>

namespace bm {
namespace message_ns {

class Message;
}

class IMessageMaker
{
public:
    virtual ~IMessageMaker() = default;

    virtual std::unique_ptr<Message> create() const = 0;
};

} // namespace bm
#endif // I_MESSAGE_MAKER_H
