#include "message_factory.hpp"
#include "i_message_maker.hpp"

namespace bm {

MessageFactory& MessageFactory::get()
{
    static MessageFactory factory;
    return factory;
}

void MessageFactory::registerMaker(MessageType type, IMessageMaker* maker)
{
    auto index = static_cast<size_t>(type);
    if (index >= makers_.size()) {
        makers_.resize(index + 1);
    }
    makers_[index] = maker;
}

std::unique_ptr<Message> MessageFactory::createMessage(MessageType type) const
{
    const auto index = static_cast<size_t>(type);
    if (index < makers_.size()) {
        return makers_[index]->create();
    } else {
        assert(false);
        return nullptr;
    }
}

MessageFactory::MessageFactory()
{
    makers_.reserve(static_cast<size_t>(MessageType::TypesCount));
}

} // namespace bm
