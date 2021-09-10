#ifndef BM_MESSAGEFACTORY_HPP
#define BM_MESSAGEFACTORY_HPP

#include "message.hpp"
#include "message_type.hpp"

#include <memory>
#include <vector>

namespace bm {
class IMessageMaker;

class MessageFactory
{
public:
    MessageFactory(const MessageFactory&) = delete;
    MessageFactory(MessageFactory&&)      = delete;
    MessageFactory& operator=(const MessageFactory&) = delete;
    MessageFactory& operator=(MessageFactory&&) = delete;

    static MessageFactory& get();

    void                                 registerMaker(MessageType type, IMessageMaker* maker);
    std::unique_ptr<message_ns::Message> createMessage(MessageType type) const;

private: // methods
    MessageFactory();

private: // data
    std::vector<IMessageMaker*> makers_;
};

} // namespace bm

#endif // BM_MESSAGEFACTORY_HPP
