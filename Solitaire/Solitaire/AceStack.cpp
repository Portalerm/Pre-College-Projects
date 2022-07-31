#include "AceStack.h"

AceStack::AceStack(SUIT s) : m_stack(13), m_suit{ s }
{

}

bool AceStack::canAdd(const Card& other)
{
	if (m_stack.empty())
		return ((other.rank() == 1) && (other.suit() == m_suit));
	if (other.rank() - m_stack.peek().rank() == 1 && other.suit() == m_suit)
		return true;
	return false;
}

bool AceStack::add(const Card& other)
{
	if (!canAdd(other))
		return false;
	m_stack.push(other);
	return true;
}

Card& AceStack::peek()
{
	return m_stack.peek();
}

bool AceStack::empty()
{
	return m_stack.empty();
}
