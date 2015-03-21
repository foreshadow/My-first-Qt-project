#ifndef CARDCONTAINER_H
#define CARDCONTAINER_H

#include "carditem.h"


class CardContainer
{
public:
    enum Align { Center, Left, Right, Up, Down };
    enum Direct { Vertical, Horizontal, WideHorizontal };

    CardContainer(int _x = 0, int _y = 0, Direct dir = Horizontal, Align hori = Center, Align vertical = Center);
    ~CardContainer();

    void addCard(CardItem* cd);
    void addCard(QList<CardItem *> cds);
    void removeCard(CardItem* cd);
    void moveCardTo(CardItem* cd, CardContainer &ct);
    void moveAllTo(CardContainer &ct);
    void setAllInvisible();
    void resetItem();
    void qSortList();

protected:
    int _x;
    int _y;
    Align Halign;
    Align Valign;
    Direct direct;
    QList<CardItem*> cardList;
    static bool compare(CardItem *s1, CardItem *s2);
};

#endif // CARDCONTAINER_H
