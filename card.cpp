#include "card.h"
#include <QtCore>

Card::Card(int id):
    _id(id), _number(id % 54 / 4)
{
    Suit suitMap[] = { Heart, Diamond, Spade, Club };
    _suit = suitMap[id % 54 % 4];
}

Card::~Card()
{

}

int Card::getNumber() const
{
    int n = _number;
    if (_id % 54 == 53) n++;
    return n;
}

int Card::getY() const
{
    switch (_suit) {
    case Heart:
    case Joker:
        return 0;   break;
    case Diamond:
    case Vice:
        return 1;   break;
    case Spade:
        return 2;   break;
    case Club:
        return 3;   break;
    default:
        return -1;  break;
    }
}

char Card::getChar() const
{
    char str[] = "34567890JQKA2-+";
    return str[getNumber()];
}
