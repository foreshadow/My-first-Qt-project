#ifndef CARDARRAY_H
#define CARDARRAY_H

#include <QObject>

class CardArray
{
public:
    enum cardType { Invalid, Empty, Single, Pair, Triple, Bomb,
                    Straight, StraightPair, StraightTriple };

    CardArray(QString arr = "");
    ~CardArray();

    void clear();
    void addCard(char cd);
    void copyArrayTo(CardArray obj); //-.-
    bool isSameAs(CardArray obj); //-.-
    bool isBiggerThan(CardArray obj) const;
    inline int getArrayLength() const { return _cardCnt; }

protected:
    QString _arr;
    int _cardCnt;
    int _maxn;
    cardType type;
    int count[20];

    void refresh();
    bool isStraight(int l, int r, int n) const;
    inline cardType getType() const { return type; }
    inline int getMaxN() const { return _maxn; }
    inline int getN() const { return _cardCnt; }
};

#endif // CARDARRAY_H
