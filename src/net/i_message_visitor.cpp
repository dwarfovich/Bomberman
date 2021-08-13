#include "i_message_visitor.hpp"

namespace bm {

void IMessageVisitor::visit(const Message &message)
{}

void IMessageVisitor::visit(const TextMessage &message)
{}

void IMessageVisitor::visit(const ClientNameMessage &message)
{}

} // namespace bm
