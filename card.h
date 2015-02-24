#ifndef CARD_H
#define CARD_H

class Card
{

    //Q_ENUMS(Suit)

public:
    enum Suit { Spade, Club, Heart, Diamond, Joker, Vice };

    Card(Suit suit, int number, bool selected = false);
    ~Card();

    int getId() const;
    int getNumber() const;
    Suit getSuit() const;
    int getSuitN() const;

protected:
    Suit _suit;
    int _number;
    bool _selected;
    int _id;
};

#endif // CARD_H
