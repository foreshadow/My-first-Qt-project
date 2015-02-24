#ifndef UNIVERSAL
#define UNIVERSAL

#include <QElapsedTimer>
#include <QSplashScreen>
#include <QImage>
#include <QtCore>
#include <QLabel>

#define CARD_WIDTH 90
#define CARD_HEIGHT 120
#define CARD_POP_DY 30
#define CARD_OVERLAP_DX 22.5
#define CARD_WIDTH_IN_PIC 540
#define CARD_HEIGHT_IN_PIC 720

static void delay(int s)
{
    QElapsedTimer *t = new QElapsedTimer;
    t->start();
    while(t->elapsed()<s)
    {
        QCoreApplication::processEvents();
    }
    delete t;
}

static void splash(QString path, int delaySecond, int x, int y)
{
    QSplashScreen *spl = new QSplashScreen;
    spl->setPixmap(QPixmap(path).scaled(x,y));
    spl->show();
    delay(delaySecond*1000);
    delete spl;
}


#endif // UNIVERSAL
