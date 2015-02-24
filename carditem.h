#ifndef CARDITEM_H
#define CARDITEM_H

#include "card.h"
#include <QObject>
#include <QGraphicsItem>

class CardItem : public QGraphicsItem
{
public:
    CardItem(const Card *card, int x, int y);
    ~CardItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void setcard(const Card *card);

private:
    QPixmap getCardPic(Card card);

protected:
    Card _card;

signals:

public slots:
};

#endif // CARDITEM_H
