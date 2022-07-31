#pragma once
#include "Stack.h"
#include "Card.h"
class DrawPile
{
public:
	Stack<Card> m_drawn;
	Stack<Card> m_toDraw;
	DrawPile();
	DrawPile(Stack<Card>& d, Stack<Card>& t);
	Card& peek() const;
	Card& pull();
	void draw();
};