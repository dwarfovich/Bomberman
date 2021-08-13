#ifndef BM_IMESSAGEVISITOR_HPP
#define BM_IMESSAGEVISITOR_HPP

namespace bm {
class Message;
class TextMessage;
class ClientNameMessage;

class IMessageVisitor
{
public:
    virtual ~IMessageVisitor() = default;

    virtual void visit(const Message& message);
    virtual void visit(const TextMessage& message);
    virtual void visit(const ClientNameMessage& message);
};

} // namespace bm

#endif // BM_IMESSAGEVISITOR_HPP
