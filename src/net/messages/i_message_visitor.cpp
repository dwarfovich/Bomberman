#include "i_message_visitor.hpp"

namespace bm {

void IMessageVisitor::visit(const Message &message)
{}

void IMessageVisitor::visit(const TextMessage &message)
{}

void IMessageVisitor::visit(const ClientNameMessage &message)
{}

void IMessageVisitor::visit(const ClientJoiningGameMessage &message)
{}

void IMessageVisitor::visit(const SelectMapRequestMessage &message)
{}

void IMessageVisitor::visit(const MapInitializationMessage &message)
{}

void IMessageVisitor::visit(const PlayerReadyMessage &message)
{}

void IMessageVisitor::visit(const CharacterMovedMessage &message)
{}

void IMessageVisitor::visit(const BombPlacedMessage &message)
{}

void IMessageVisitor::visit(const CellChangedMessage &message)
{}

void IMessageVisitor::visit(const PrepareToStartGame &message)
{}

void IMessageVisitor::visit(const StartGameMessage &message)
{}

void IMessageVisitor::visit(const SetPlayerIdMessage &message)
{}

} // namespace bm
