#include "i_message_visitor.hpp"

namespace bm {

void IMessageVisitor::visit(const Message &message)
{}

void IMessageVisitor::visit(const TextMessage &message)
{}

void IMessageVisitor::visit(const ClientNameMessage &message)
{}

void IMessageVisitor::visit(const ClientReadyMessage &message)
{}

void IMessageVisitor::visit(const MapInitializationMessage &message)
{}

void IMessageVisitor::visit(const MapInitializedMessage &message)
{}

void IMessageVisitor::visit(const PrepareToStartGame &message)
{}

void IMessageVisitor::visit(const StartGameMessage &message)
{}

void IMessageVisitor::visit(const ClientIdMessage &message)
{}

} // namespace bm
