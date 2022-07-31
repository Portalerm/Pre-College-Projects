#pragma once
#include"Stack.h"
#include "Card.h"
class AceStack
{
public:
	Stack<Card> m_stack;
	SUIT m_suit;
public:
	AceStack(SUIT suit);
	bool canAdd(const Card& other);
	bool add(const Card& other);
	Card& peek();
	bool empty();
};
