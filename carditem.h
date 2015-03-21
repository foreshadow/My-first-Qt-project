#ifndef CARDITEM_H
#define CARDITEM_H

#include "card.h"
#include <QGraphicsItem>

class CardItem : public QGraphicsItem
{
public:
    CardItem(QPixmap &pokerPic, Card *card, int x = 0, int y = 0);
    ~CardItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

    inline bool isMyCard() const { return _myCard; }
    inline bool isMySelected() const { return _mySelected; }
    inline bool isTurnedover() const { return _turnover; }
    inline int getCardId() const { return _card->getId(); }
    void setMyCard(bool boo = true);
    void setMySelected(bool boo);
    void changeMySelected();
    void turnOver();

private:
    QPixmap getCardPic() const;

protected:
    Card *_card;
    QPixmap &pokerPic;
    QPixmap _pic;
    bool _mySelected;
    bool _myCard;
    bool _turnover;
    QRect paintRect() const;
};

#endif // CARDITEM_H
