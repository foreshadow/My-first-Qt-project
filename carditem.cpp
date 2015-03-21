#include "carditem.h"
#include "universal.h"
#include <QPainter>
#include <QtCore>

CardItem::CardItem(QPixmap &pokerPic, Card *card, int x, int y) :
    _card(card), pokerPic(pokerPic),
    _mySelected(false), _myCard(false), _turnover(true)
{
    setPos(x,y);
    int a = _card->getX();
    if (a>14) { a=14; }
    int b = _card->getY();
    _pic = pokerPic.copy(
                a * CARD_WIDTH_IN_PIC,
                b * CARD_HEIGHT_IN_PIC,
                CARD_WIDTH_IN_PIC,
                CARD_HEIGHT_IN_PIC)
                    .scaled(
                CARD_WIDTH,
                CARD_HEIGHT);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

CardItem::~CardItem()
{

}

QRectF CardItem::boundingRect() const
{
    return QRect(0, 0, CARD_WIDTH, CARD_HEIGHT);
}

void CardItem::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter->drawPixmap(paintRect(), _pic);
    if (isTurnedover()) painter->fillRect(boundingRect(), Qt::darkRed);
    QPen *pen = new QPen(Qt::black);
    painter->setPen(*pen);
    painter->drawRect(boundingRect());
}

void CardItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    changeMySelected();
    this->update();
}

void CardItem::setMyCard(bool boo)
{
    _myCard = boo;
}

void CardItem::turnOver()
{
     _turnover = !_turnover;
    if (_turnover) _mySelected = false;
}

void CardItem::setMySelected(bool boo)
{
    if (_mySelected!=boo) changeMySelected();
}

void CardItem::changeMySelected()
{
    if (!isMyCard()) return;
    _mySelected = !_mySelected;
    if (_mySelected) setPos(this->x(), this->y()-CARD_POP_DY);
    else setPos(this->x(), this->y()+CARD_POP_DY);
}

QRect CardItem::paintRect() const
{
    return QRect(0, 0, CARD_WIDTH, CARD_HEIGHT);
}
