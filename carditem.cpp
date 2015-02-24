#include "card.h"
#include "carditem.h"
#include "universal.h"
#include <QPainter>
#include <QtCore>

CardItem::CardItem(const Card *card, int x, int y)
{
    setcard(card);
    setPos(x,y);
    qDebug() << "CardItem(3) initialized.";
}

CardItem::~CardItem()
{

}

QRectF CardItem::boundingRect() const
{
    return QRectF(-CARD_WIDTH/2, -CARD_HEIGHT/2-CARD_POP_DY/2,
                  CARD_WIDTH, CARD_HEIGHT+CARD_POP_DY);
}

void CardItem::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawPixmap(0, 0, CARD_WIDTH, CARD_HEIGHT,
                        getCardPic(_card));
    qDebug() << "cardPaint activated.";
}

void CardItem::setcard(const Card *card)
{
    _card = *card;
}

QPixmap CardItem::getCardPic(Card card)
{

    int x = card.getNumber();
    if (x>14) { x=14; }
    int y = card.getSuitN();
    QPixmap *pix = new QPixmap;
    pix->load("poker.jpg");
    pix->copy((--x) * CARD_WIDTH_IN_PIC, y * CARD_HEIGHT_IN_PIC,
             CARD_WIDTH, CARD_HEIGHT);
    return *pix;
}
