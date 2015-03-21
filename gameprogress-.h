#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QtNetwork>

class QGraphicsScene;

namespace Ui {
class GameProgress;
}

class GameProgress : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameProgress(QTcpSocket *tcpSocket, quint16 &blockSize, QWidget *parent = 0);
	~GameProgress();

private slots:
    void on_pushButton_clicked();
    void readMessage();
    void replace();

private:
	Ui::GameProgress *ui;
    QGraphicsScene *scene;
    QTcpSocket *tcpSocket;
    quint16 &blockSize;

protected:
    double xCard;
    double yCard;
};

#endif // MAINWINDOW_H
