#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

#include <QMainWindow>
#include <QtNetwork>
#include "universal.h"
#include "button.h"

class QGraphicsScene;

namespace Ui {
class MainWindow;
}

class GameProgress : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameProgress(QTcpSocket *tcpSocket, quint16 &blockSize, QWidget *parent = 0);
    ~GameProgress();

    void imitate(); //used on offline mode

private slots:
    void readMessage();
    void placeLabel();
    void replaceContainers();

    void onReadyClicked();
    void onCallClicked();
    void onFoldClicked();
    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTcpSocket *tcpSocket;
    quint16 &blockSize;

    Button *call;
    Button *ready;
    Button *fold;

protected:
    void handleEvent(char c, QString msg);
};

#endif // GAMEPROGRESS_H
