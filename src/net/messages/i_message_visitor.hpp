#ifndef BM_IMESSAGEVISITOR_HPP
#define BM_IMESSAGEVISITOR_HPP

namespace bm {
namespace message_ns {
class Message;
class TextMessage;
class ClientNameMessage;
class ClientJoiningGameMessage;
class SelectMapRequestMessage;
class MapInitializationMessage;
class PlayerReadyMessage;
class PrepareToStartGame;
class StartGameMessage;
class SetPlayerIdMessage;
class CharacterMovedMessage;
class BombPlacedMessage;
class BombExplodedMessage;
class ExplosionFinishedMessage;
class CellChangedMessage;
} // namespace message_ns

class IMessageVisitor
{
public:
    virtual ~IMessageVisitor() = default;

    virtual void visit(const message_ns::Message& message);
    virtual void visit(const message_ns::TextMessage& message);
    virtual void visit(const message_ns::ClientNameMessage& message);
    virtual void visit(const message_ns::ClientJoiningGameMessage& message);
    virtual void visit(const message_ns::SelectMapRequestMessage& message);

    virtual void visit(const message_ns::MapInitializationMessage& message);
    virtual void visit(const message_ns::PlayerReadyMessage& message);
    virtual void visit(const message_ns::CharacterMovedMessage& message);
    virtual void visit(const message_ns::BombPlacedMessage& message);
    virtual void visit(const message_ns::BombExplodedMessage& message);
    virtual void visit(const message_ns::ExplosionFinishedMessage& message);
    virtual void visit(const message_ns::CellChangedMessage& message);

    virtual void visit(const message_ns::PrepareToStartGame& message);
    virtual void visit(const message_ns::StartGameMessage& message);
    virtual void visit(const message_ns::SetPlayerIdMessage& message);
};

} // namespace bm

#endif // BM_IMESSAGEVISITOR_HPP
