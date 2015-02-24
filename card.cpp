#include "card.h"
#include <QtCore>

Card::Card(Suit suit, int number, bool selected):
    _suit(suit), _number(number), _selected(selected)
{
    qDebug() << "Card initialized.";
}

Card::~Card()
{

}

int Card::getId() const{
    return _id;
}

int Card::getNumber() const{
    return _number;
}

Card::Suit Card::getSuit() const
{
    return _suit;
}

int Card::getSuitN() const
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

