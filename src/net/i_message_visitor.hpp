#ifndef BM_IMESSAGEVISITOR_HPP
#define BM_IMESSAGEVISITOR_HPP

namespace bm {
class Message;
class TextMessage;
class ClientNameMessage;
class ClientReadyMessage;
class MapInitializationMessage;
class MapInitializedMessage;
class PrepareToStartGame;
class ClientIdMessage;

class IMessageVisitor
{
public:
    virtual ~IMessageVisitor() = default;

    virtual void visit(const Message& message);
    virtual void visit(const TextMessage& message);
    virtual void visit(const ClientNameMessage& message);
    virtual void visit(const ClientReadyMessage& message);
    virtual void visit(const MapInitializationMessage& message);
    virtual void visit(const MapInitializedMessage& message);
    virtual void visit(const PrepareToStartGame& message);
    virtual void visit(const ClientIdMessage& message);
};

} // namespace bm

#endif // BM_IMESSAGEVISITOR_HPP
