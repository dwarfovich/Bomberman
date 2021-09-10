#include "i_message_visitor.hpp"

namespace bm {

void IMessageVisitor::visit(const message_ns::Message &message)
{}

void IMessageVisitor::visit(const message_ns::TextMessage &message)
{}

void IMessageVisitor::visit(const message_ns::ClientNameMessage &message)
{}

void IMessageVisitor::visit(const message_ns::ClientJoiningGameMessage &message)
{}

void IMessageVisitor::visit(const message_ns::SelectMapRequestMessage &message)
{}

void IMessageVisitor::visit(const message_ns::MapInitializationMessage &message)
{}

void IMessageVisitor::visit(const message_ns::PlayerReadyMessage &message)
{}

void IMessageVisitor::visit(const message_ns::CharacterMovedMessage &message)
{}

void IMessageVisitor::visit(const message_ns::BombPlacedMessage &message)
{}

void IMessageVisitor::visit(const message_ns::BombExplodedMessage &message)
{}

void IMessageVisitor::visit(const message_ns::ExplosionFinishedMessage &message)
{}

void IMessageVisitor::visit(const message_ns::CellChangedMessage &message)
{}

void IMessageVisitor::visit(const message_ns::PrepareToStartGame &message)
{}

void IMessageVisitor::visit(const message_ns::StartGameMessage &message)
{}

void IMessageVisitor::visit(const message_ns::SetPlayerIdMessage &message)
{}

} // namespace bm
