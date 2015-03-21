#include "button.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>

Button::Button(QString text, int x, int y, int w, int h, QString path) :
    w(w), h(h), text(text)
{
    setPos(x, y);
    pix.load(path);
    this->setFlag(ItemIsSelectable);
}

Button::~Button()
{

}

QRectF Button::boundingRect() const
{
    return QRectF(0, 0, w, h);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->fillRect(boundingRect(), QBrush(Qt::lightGray));
    if (!pix.isNull()) painter->drawPixmap(0, 0, pix.scaled(w, h));
    if (!this->isActive())
    {
        painter->fillRect(boundingRect(), QColor(127, 127, 127, 255*opacity()));
        painter->setOpacity(0.7 * opacity());
    }
    painter->drawText(boundingRect(), Qt::AlignCenter, text);
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button()!=Qt::LeftButton)
        event->ignore();
    else
        emit clicked();
}
