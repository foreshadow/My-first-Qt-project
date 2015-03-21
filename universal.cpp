#include <QSplashScreen>
#include "universal.h"

void delay(int s)
{
    QElapsedTimer *t = new QElapsedTimer;
    t->start();
    while(t->elapsed()<s)
    {
        QCoreApplication::processEvents();
    }
    delete t;
}

void splash(QString path, int delaySecond, int x, int y)
{
    QSplashScreen *spl = new QSplashScreen;
    spl->setPixmap(QPixmap(path).scaled(x,y));
    spl->show();
    delay(delaySecond*1000);
    delete spl;
}
