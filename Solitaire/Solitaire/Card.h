#pragma once
#include<iostream>
#include<windows.h>
enum class SUIT
{
	CLUB,
	HEART,
	SPADE,
	DIAMOND,
};

class Card
{
private:
	SUIT m_suit;
	int m_rank;
public:
	Card() = default;
	Card(SUIT s, int r);
	Card(const Card& other);
	SUIT suit() const;
	int rank() const;
	bool isBlack() const;
	bool canPlaceOn(const Card& other) const;
	char suitString() const;
	char rankString() const;
	friend std::ostream& operator<< (std::ostream& out, const Card& card);
}; 
