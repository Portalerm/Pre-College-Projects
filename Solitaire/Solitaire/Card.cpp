#include "Card.h"

Card::Card(SUIT s, int r) : m_suit{ s }, m_rank{ r }
{
}

Card::Card(const Card& other) : Card{ other.suit(), other.rank() }
{
}

bool Card::isBlack() const
{
    return (m_suit == SUIT::SPADE || m_suit == SUIT::CLUB);
}

SUIT Card::suit() const
{
    return m_suit;
}

int Card::rank() const
{
    return m_rank;
}

bool Card::canPlaceOn(const Card& other) const
{
    return other.isBlack() != this->isBlack()
        && this->m_rank - other.m_rank == 1;
}

char Card::suitString() const
{
    char s{};
    switch (suit())
    {
    case SUIT::CLUB:
        s = 'C';
        break;
    case SUIT::HEART:
        s = 'H';
        break;
    case SUIT::DIAMOND:
        s = 'D';
        break;
    case SUIT::SPADE:
        s = 'S';
        break;
    default:
        s = '?';
    }
    return s;
}

char Card::rankString() const
{
    char r{};
    switch (rank())
    {
    case 1:
        r = 'A';
        break;
    case 2:
        r = '2';
        break;
    case 3:
        r = '3';
        break;
    case 4:
        r = '4';
        break;
    case 5:
        r = '5';
        break;
    case 6:
        r = '6';
        break;
    case 7:
        r = '7';
        break;
    case 8:
        r = '8';
        break;
    case 9:
        r = '9';
        break;
    case 10:
        r = 'T';
        break;
    case 11:
        r = 'J';
        break;
    case 12:
        r = 'Q';
        break;
    case 13:
        r = 'K';
        break;
    default:
        r = '?';
    }
    return r;
}

std::ostream& operator<<(std::ostream& out, const Card& card)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(!card.isBlack())
        SetConsoleTextAttribute(hConsole, 12); //set console color to red
    out << card.rankString() << card.suitString();
    SetConsoleTextAttribute(hConsole, 15); //set it back to white
    return out;
}
