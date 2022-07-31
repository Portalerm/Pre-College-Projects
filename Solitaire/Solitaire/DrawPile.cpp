#include "DrawPile.h"

DrawPile::DrawPile() : m_drawn(52), m_toDraw(52)
{
}

DrawPile::DrawPile(Stack<Card>& d, Stack<Card>& t) : m_drawn(d), m_toDraw(t)
{
}

Card& DrawPile::peek() const
{
	return m_drawn.peek();
}

Card& DrawPile::pull()
{
	return m_drawn.pop();
}

void DrawPile::draw()
{
	if(!m_toDraw.empty())
		m_drawn.push( m_toDraw.pop() );
	//if toDraw is empty, flip
	else
	{
		while (!m_drawn.empty())
			m_toDraw.push(m_drawn.pop());
	}
}
