#ifndef BM_IMESSAGEVISITOR_HPP
#define BM_IMESSAGEVISITOR_HPP

namespace bm {
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
class GameOverMessage;

class IMessageVisitor
{
public:
    virtual ~IMessageVisitor() = default;

    virtual void visit(const Message& message);
    virtual void visit(const TextMessage& message);
    virtual void visit(const ClientNameMessage& message);
    virtual void visit(const ClientJoiningGameMessage& message);
    virtual void visit(const SelectMapRequestMessage& message);
    virtual void visit(const MapInitializationMessage& message);
    virtual void visit(const PlayerReadyMessage& message);
    virtual void visit(const CharacterMovedMessage& message);
    virtual void visit(const BombPlacedMessage& message);
    virtual void visit(const BombExplodedMessage& message);
    virtual void visit(const ExplosionFinishedMessage& message);
    virtual void visit(const CellChangedMessage& message);
    virtual void visit(const PrepareToStartGame& message);
    virtual void visit(const StartGameMessage& message);
    virtual void visit(const SetPlayerIdMessage& message);
    virtual void visit(const GameOverMessage& message);
};

} // namespace bm

#endif // BM_IMESSAGEVISITOR_HPP
