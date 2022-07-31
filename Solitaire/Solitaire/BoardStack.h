#pragma once
#include<iostream>
#include<vector>
#include"Card.h"
class BoardStack
{
public:
	std::vector<Card> hidden;
	std::vector<Card> shown;
	BoardStack();
	BoardStack(std::vector<Card>& hidden, std::vector<Card>& shown);
	BoardStack( BoardStack& other);
	Card pop();
	std::vector<Card> pop(int num);
	bool canAdd(const Card& card);
	bool add(std::vector<Card> &stack);
	bool add(Card& card);
	friend std::ostream& operator<<(std::ostream& out,const BoardStack& stack);
};