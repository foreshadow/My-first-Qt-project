#include "gameprogress.h"
#include "ui_gameprogress.h"
#include <QImage>
#include "universal.h"
#include "network.h"
#include "carditem.h"

Card *card[108];
CardItem *cardItem[108];

GameProgress::GameProgress(QTcpSocket *tcpSocket, quint16 &blockSize, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameProgress),
    scene(new QGraphicsScene),
    tcpSocket(tcpSocket), blockSize(blockSize),
    xCard(75), yCard(200)
{
    scene->setSceneRect(0, 0, 795, 595);

    connect(tcpSocket, SIGNAL(readyRead()),
            this, SLOT(readMessage()));

    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    QPixmap pokerPic;
    pokerPic.load("poker.jpg");

    FOR_DOWNTO(53, 0)
        for (int j=i+54; j>=i; j-=54)
        {
            card[j] = new Card(j);
            cardItem[j] = new CardItem(pokerPic, card[j],
                                     xCard+=5, yCard);
            scene->addItem(cardItem[j]);
        }
    scene->update();
}

GameProgress::~GameProgress()
{
#ifndef GAMETEST
    splash(":/res/img/bye.jpg", 2.5, 720, 450);
#endif
    delete scene;
    delete ui;
}

void GameProgress::on_pushButton_clicked()
{
    send(tcpSocket, "R");
}

void GameProgress::readMessage()
{
    QString msg;  //存放从服务器接收到的字符串
    QDataStream in(tcpSocket);
    in.setVersion(DATA_STREAM_VERSION);
    if(blockSize==0) //如果是刚开始接收数据
    {
       if(tcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
       in >> blockSize;
    }
    if(tcpSocket->bytesAvailable() < blockSize) return;
    in >> msg;
    blockSize = 0;

    char c =  msg[0].toLatin1();
    msg = msg.right(msg.length()-1);
    switch (c) {
    case 'T':
        ui->textEdit->append(msg);
        break;
    case 'C':
        card[msg.toInt()]->turnOver();
        cardItem[msg.toInt()]->setAbstractPos(CardItem::Self);
        scene->update();
        break;
    case 'L':
        cardItem[msg.toInt()]->setAbstractPos(CardItem::Left);
        scene->update();
        break;
    case 'R':
        cardItem[msg.toInt()]->setAbstractPos(CardItem::Right);
        scene->update();
        break;
    case 'M':
        cardItem[msg.toInt()]->setAbstractPos(CardItem::Mate);
        scene->update();
        break;
    case 'S':
        replace();
        scene->update();
    default:
        break;
    }
    readMessage();
}

void GameProgress::replace()
{
    int xDeck = 500;    int yDeck = 200;
    int xSelf = 650;    int ySelf = 450;
    int xMate = 650;    int yMate = 25;
    int xLeft = 25;     int yLeft = 150;
    int xRight = 625;   int yRight = 150;

    FOR_TO(0, 53)
        for (int j=i; j<=i+54; j+=54)
            switch (cardItem[j]->getAbstractPos()) {
            case CardItem::Deck:
                cardItem[j]->setPos(xDeck-=CARD_OVERLAP, yDeck);
                break;
            case CardItem::Self:
                cardItem[j]->setPos(xSelf-=CARD_OVERLAP_DX, ySelf);
                break;
            case CardItem::Mate:
                cardItem[j]->setPos(xMate-=CARD_OVERLAP_DX, yMate);
                break;
            case CardItem::Left:
                cardItem[j]->setPos(xLeft, yLeft+=CARD_OVERLAP);
                break;
            case CardItem::Right:
                cardItem[j]->setPos(xRight, yRight+=CARD_OVERLAP);
                break;
            case CardItem::Discard:
                scene->removeItem(cardItem[j]);
            default:
                break;
            }
}
