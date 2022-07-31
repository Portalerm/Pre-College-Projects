#include "BoardStack.h"

BoardStack::BoardStack() : hidden(0), shown(0)
{

}

BoardStack::BoardStack(std::vector<Card>& h, std::vector<Card>& s) : BoardStack{}
{
	for (const Card& c : h)
	{
		hidden.push_back(c);
	}
	for (const Card& c : s)
	{
		shown.push_back(c);
	}
}

BoardStack::BoardStack( BoardStack& other) : BoardStack{other.hidden, other.shown}
{
}

Card BoardStack::pop()
{
	Card ret{ shown.back() };
	shown.pop_back();
	//if you've run out of shown cards, you have to show the last card in the hidden pile
	if (shown.empty() && !hidden.empty())
	{
		shown.push_back(hidden.back());
		hidden.pop_back();
	}
	return ret;
}


std::vector<Card> BoardStack::pop(int num)
{
	std::vector<Card> stack(0);
	for (int i{ 0 }; i < num; ++i)
	{
		stack.insert(stack.begin(), pop());
	}
	//if you've run out of shown cards, you have to show the last card in the hidden pile
	if (shown.empty() && !hidden.empty())
	{
		shown.push_back(hidden.back());
		hidden.pop_back();
	}
	return stack;
}

bool BoardStack::canAdd(const Card& card)
{
	//you may also add if the stack is empty and the card is a king
	if (hidden.empty() && shown.empty())
		return (card.rank() == 13);
	//if the added card and the stack card are different colors and the added card is a rank less than the stack card, it can be added
	if (card.isBlack() != shown.back().isBlack() && card.rank() - shown.back().rank() == -1)
		return true;
	return false;
}

bool BoardStack::add(std::vector<Card>& stack)
{
	if (!canAdd(stack.front()))
		return false;
	for (const Card& c : stack)
	{
		shown.push_back(c);
	}
	return true;
}

bool BoardStack::add(Card& card)
{
	if (!canAdd(card))
		return false;
	shown.push_back(card);
	return true;
}

std::ostream& operator<<(std::ostream& out, const BoardStack& stack)
{
	for (int i{ 0 }; i < stack.hidden.size(); ++i)
	{
		out << "X ";
	}
	for (int i{ 0 }; i < stack.shown.size(); ++i)
	{
		out << stack.shown[i] << ' ';
	}
	return out;
}
