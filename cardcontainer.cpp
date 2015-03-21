#include "cardcontainer.h"
#include "universal.h"

CardContainer::CardContainer(int x, int y, Direct dir, Align hori, Align vert) :
    _x(x), _y(y), Halign(hori), Valign(vert), direct(dir)
{
    cardList.clear();
}

CardContainer::~CardContainer()
{

}

void CardContainer::addCard(CardItem* cd)
{
    cardList << cd;
    resetItem();
}

void CardContainer::addCard(QList<CardItem *> cds)
{
    cardList += cds;
    resetItem(); //z-level!!
}

void CardContainer::removeCard(CardItem* cd)
{
    cardList.removeOne(cd);
    resetItem();
}

void CardContainer::moveCardTo(CardItem *cd, CardContainer &ct)
{
    int i = cardList.indexOf(cd);
    if (i==-1) return;
    ct.addCard(cardList.takeAt(i));
    ct.resetItem();
}

void CardContainer::moveAllTo(CardContainer &ct)
{
    ct.addCard(cardList);
    cardList.clear();
}

void CardContainer::setAllInvisible()
{
    for (int i=0; i<cardList.size(); ++i)
        cardList.at(i)->setVisible(false);
}

void CardContainer::resetItem()
{
    int x = _x-CARD_WIDTH/2;
    int y = _y-CARD_HEIGHT/2;
    int dx = 0;
    int dy = 0;
    int n = cardList.size();
    switch (direct) {
    case Vertical:
        dy = -CARD_OVERLAP;
        break;
    case Horizontal:
        dx = -CARD_OVERLAP;
        break;
    case WideHorizontal:
        dx = -CARD_OVERLAP_DX;
        break;
    }

    switch (direct){
    case Vertical:
        switch (Valign)
        {
        case Up:
            y += n * CARD_OVERLAP + CARD_HEIGHT / 2;
            break;
        case Down:
            y -= CARD_HEIGHT / 2;
            break;
        case Center:
            y += n * CARD_OVERLAP /2;
            break;
        default:
            break;
        }
        break;
    case Horizontal:
        switch (Halign)
        {
        case Left:
            x += n * CARD_OVERLAP + CARD_WIDTH / 2;
            break;
        case Right:
            x -= CARD_WIDTH / 2;
            break;
        case Center:
            x += n * CARD_OVERLAP / 2;
            break;
        default:
            break;
        }
        break;
    case WideHorizontal:
        switch (Halign)
        {
        case Left:
            x += n * CARD_OVERLAP_DX + CARD_WIDTH / 2;
            break;
        case Right:
            x -= CARD_WIDTH / 2;
            break;
        case Center:
            x += n * CARD_OVERLAP_DX / 2;
            break;
        default:
            break;
        }
        break;
    }

    qSortList();
    for (int i=0; i<n; ++i)
        cardList.at(i)->setPos(x+=dx, y+=dy);
}

void CardContainer::qSortList()
{
    qSort(cardList.begin(), cardList.end(), compare);
}

bool CardContainer::compare(CardItem *s1, CardItem *s2)
{
    int a = s1->getCardId();
    int b = s2->getCardId();
    if (a%54==b%54) return a < b;
    else return a%54 < b%54;
}

