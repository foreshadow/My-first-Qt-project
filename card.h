#ifndef CARD_H
#define CARD_H

class Card
{
public:
    enum Suit { Spade, Club, Heart, Diamond, Joker, Vice };

    explicit Card(int id);
    ~Card();

    inline int getId() const { return _id; }
    inline Suit getSuit() const { return _suit; }
    inline int getX() const { return _number; }
    int getNumber() const;
    int getY() const;
    char getChar() const;

protected:
    int _id;
    Suit _suit;
    int _number;
};

#endif // CARD_H
