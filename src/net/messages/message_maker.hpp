#ifndef BM_MESSAGEMAKER_HPP
#define BM_MESSAGEMAKER_HPP

#include "message_type.hpp"
#include "i_message_maker.hpp"
#include "message_factory.hpp"

#define REGISTER_MESSAGE_MAKER(messageType, T)             \
    namespace {                                            \
    static MessageMaker<message_ns::T> maker(messageType); \
    } // namespace

namespace bm {

template<typename Type>
class MessageMaker : public IMessageMaker
{
public:
    MessageMaker(MessageType type) { MessageFactory::get().registerMaker(type, this); }

    std::unique_ptr<message_ns::Message> create() const override { return std::make_unique<Type>(); }
};

} // namespace bm

#endif // BM_MESSAGEMAKER_HPP
