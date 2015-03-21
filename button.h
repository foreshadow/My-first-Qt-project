#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QGraphicsItem>

class Button : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Button(QString text, int x, int y, int w = 75, int h = 25, QString path = "");
    ~Button();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

protected:
    int w;
    int h;
    QString text;
    QPixmap pix;

signals:
    void clicked();
};

#endif // BUTTON_H
