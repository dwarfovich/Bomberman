#ifndef BM_MESSAGEMAKER_HPP
#define BM_MESSAGEMAKER_HPP

#include "message_type.hpp"
#include "i_message_maker.hpp"
#include "message_factory.hpp"

namespace bm {

template<typename Type>
class MessageMaker : public IMessageMaker
{
public:
    MessageMaker(MessageType type) { MessageFactory::get().registerMaker(type, this); }

    std::unique_ptr<Message> create() const override { return std::make_unique<Type>(); }
};

} // namespace bm

#endif // BM_MESSAGEMAKER_HPP
