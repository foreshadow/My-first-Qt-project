#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QtNetwork>
#include <QSplashScreen>
#include <QTime>
#include "universal.h"
//#include "card.h"
//#include "carditem.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);

    scene->setSceneRect(0, 0, 795, 595);
//    scene->addPixmap(QPixmap(":/res/img/c++.png"));
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    splash(":/res/img/bye.jpg", 2.5, 720, 450);

    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
#ifdef CARD_H
    Card *card1 = new Card(Card::Spade, 5);
    CardItem *item1 = new CardItem(card1, 0, 0);
    scene->addItem(item1);
    item1->update();
#endif
}
