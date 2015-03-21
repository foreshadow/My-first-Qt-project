#include "gameprogress.h"
#include "ui_gameprogress.h"
#include <QImage>
#include <QPushButton>
#include <QGraphicsScene>
#include "universal.h"
#include "network.h"
#include "button.h"
#include "cardarray.h"
#include "cardcontainer.h"

Card *card[108];
CardItem *cardItem[108];
CardContainer deck(400, 300);
CardContainer self(400, 525, CardContainer::WideHorizontal);
CardContainer mate(400, 75, CardContainer::WideHorizontal);
CardContainer lft(50, 300, CardContainer::Vertical);
CardContainer rht(750, 300, CardContainer::Vertical);
CardContainer selfUse(400, 400, CardContainer::WideHorizontal);
CardContainer mateUse(400, 200, CardContainer::WideHorizontal);
CardContainer lftUse(150, 300, CardContainer::WideHorizontal, CardContainer::Left);
CardContainer rhtUse(650, 300, CardContainer::WideHorizontal, CardContainer::Right);
CardContainer discarded;
CardArray myCardArray, myLastArray, currentArray;
QGraphicsTextItem *txtCardCnt[4];
int cardRemained[4]; //中左右上

GameProgress::GameProgress(QTcpSocket *tcpSocket, quint16 &blockSize, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), scene(new QGraphicsScene),
    tcpSocket(tcpSocket), blockSize(blockSize),
    call(new Button(tr("Call"), 263, 425)),
    ready(new Button(tr("Ready"), 363, 425)),
    fold(new Button(tr("Fold"), 463, 425))
{
    scene->setSceneRect(0, 0, 795, 595);

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));

    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap("background.png"));

    QPixmap pokerPic;
    pokerPic.load("poker.jpg");

    FOR_DOWNTO(53, 0)
        for (int j=i+54; j>=i; j-=54)
        {
            card[j] = new Card(j);
            cardItem[j] = new CardItem(pokerPic, card[j]);
            deck.addCard(cardItem[j]);
            scene->addItem(cardItem[j]);
        }

    FOR_TO(0, 3)
        txtCardCnt[i] = scene->addText(QString::number(cardRemained[i]),
                                       QFont("微软雅黑", 20));

    call->setVisible(false);
    fold->setVisible(false);
    connect(call, SIGNAL(clicked()), this, SLOT(onCallClicked()));
    connect(ready, SIGNAL(clicked()), this, SLOT(onReadyClicked()));
    connect(fold, SIGNAL(clicked()), this, SLOT(onFoldClicked()));
    scene->addItem(call);
    scene->addItem(ready);
    scene->addItem(fold);

    scene->update();
    currentArray.clear();
}

GameProgress::~GameProgress()
{
#ifndef GAMETEST
    splash(":/res/img/bye.jpg", 2.5, 720, 450);
#endif
    FOR_TO(0, 107)
    {
        delete card[i];
        delete cardItem[i];
    }
    delete fold;
    delete ready;
    delete call;
    delete scene;
    delete ui;
}

void GameProgress::imitate()
{
    onReadyClicked();
    bool assigned[108];
    qsrand(QTime::currentTime().msec());
    FOR_TO(0, 107) assigned[i] = false;
    FOR_TO(1, 27)
        FOR_TO_2(0, 3)
        {
            int c;
            while (assigned[ c = qrand() % 108 ]);
            assigned[c] = true;
            QString typer = "CRML";
            handleEvent(typer[j].toLatin1(), QString::number(c));
        }
    placeLabel();
}

void GameProgress::onReadyClicked()
{
    send(tcpSocket, "R");
    ready->setVisible(false);
}

void GameProgress::readMessage()
{
    QString msg;
    QDataStream in(tcpSocket);
    in.setVersion(DATA_STREAM_VERSION);
    if(blockSize==0)
    {
       if(tcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
       in >> blockSize;
    }
    if(tcpSocket->bytesAvailable() < blockSize) return;
    in >> msg;
    blockSize = 0;

    char c =  msg[0].toLatin1();
    msg = msg.right(msg.length()-1);
    handleEvent(c, msg);
    readMessage();
}

void GameProgress::placeLabel()
{
    int xLabel[4] = {650+CARD_WIDTH, 25+CARD_WIDTH/6,
                     770-5*CARD_WIDTH/6, 650};
    int yLabel[4] = {450+CARD_HEIGHT/2, 150+CARD_HEIGHT/3,
                     150+CARD_HEIGHT/3, 25+CARD_HEIGHT/3};

    FOR_TO(0, 3)
    {
        txtCardCnt[i]->setPos(xLabel[i], yLabel[i]);
        txtCardCnt[i]->setPlainText(QString::number(cardRemained[i]));
        txtCardCnt[i]->setDefaultTextColor(Qt::white);
    }
}

void GameProgress::replaceContainers()
{
    deck.resetItem();
    self.resetItem();
    selfUse.resetItem();
    mate.resetItem();
    mateUse.resetItem();
    lft.resetItem();
    lftUse.resetItem();
    rht.resetItem();
    rhtUse.resetItem();
}

void GameProgress::on_lineEdit_returnPressed()
{
    send(tcpSocket, ui->lineEdit->text().append('T'));
    ui->lineEdit->clear();
}

void GameProgress::handleEvent(char c, QString str)
{
    switch (c) {
    case 'T':
        ui->textEdit->append(str);
        break;
    case 'C':
        cardRemained[0]++;
        cardItem[str.toInt()]->turnOver();
        cardItem[str.toInt()]->setMyCard();
        deck.moveCardTo(cardItem[str.toInt()], self);
        break;
    case 'L':
        cardRemained[1]++;
        deck.moveCardTo(cardItem[str.toInt()], lft);
        break;
    case 'R':
        cardRemained[2]++;
        deck.moveCardTo(cardItem[str.toInt()], rht);
        break;
    case 'M':
        cardRemained[3]++;
        deck.moveCardTo(cardItem[str.toInt()], mate);
        break;
    case 'S':
        ready->setVisible(false);
        call->setVisible(false);
        fold->setVisible(false);
        placeLabel();
        break;
    case 'A':
    {
        char p = str[0].toLatin1();
        str = str.right(str.length()-1);
        switch (p) {
        case 'C':
            selfUse.moveAllTo(discarded);
            ui->textEdit->append("Accepted call.");
            call->setVisible(true);
            fold->setVisible(true);
            if (cardRemained[0]==0)
                onFoldClicked();
            break;
        case 'L':
            lftUse.moveAllTo(discarded);
            break;
        case 'R':
            rhtUse.moveAllTo(discarded);
            break;
        case 'M':
            mateUse.moveAllTo(discarded);
            break;
        default:
            break;
        }
        break;
        placeLabel();
    }
    case 'N': // !!
    {
        currentArray.clear();
        char p = str[0].toLatin1();
        str = str.right(str.length()-1);
        switch (p) {
        case 'C':
            selfUse.moveAllTo(discarded);
            ui->textEdit->append("Accepted call.");
            call->setVisible(true);
            fold->setVisible(false);
            if (cardRemained[0]==0)
            {
                send(tcpSocket, "J");
                call->setVisible(false);
                fold->setVisible(false);
                FOR_TO(0, 107)
                        cardItem[i]->setMySelected(false);
                placeLabel();;
            }
            break;
        case 'L':
            lftUse.moveAllTo(discarded);
            break;
        case 'R':
            rhtUse.moveAllTo(discarded);
            break;
        case 'M':
            mateUse.moveAllTo(discarded);
            break;
        default:
            break;
        }
        break;
        placeLabel();
    }
    case 'G':
    {
        char p = str[0].toLatin1();
        str = str.right(str.length()-1);
        char c = str[0].toLatin1();
        str = str.right(str.length()-1);
        switch (p) {
        case 'C':
            selfUse.moveAllTo(discarded);
            break;
        case 'L':
            lftUse.moveAllTo(discarded);
            break;
        case 'R':
            rhtUse.moveAllTo(discarded);
            break;
        case 'M':
            mateUse.moveAllTo(discarded);
            break;
        default:
            break;
        }

        if (c=='V')
        {
            currentArray.clear();
            int n = str.section('.', 0, 0).toInt();
            int cn;

            FOR_TO(1, n)
            {
                cn = str.section('.', i, i).toInt();
                if (cardItem[cn]->isTurnedover())
                    cardItem[cn]->turnOver();
                currentArray.addCard(card[cn]->getChar());

                switch (p) {
                case 'C':
                    cardRemained[0]--;
                    cardItem[cn]->setMyCard(false);
                    self.moveCardTo(cardItem[cn], selfUse);
                    break;
                case 'L':
                    cardRemained[1]--;
                    lft.moveCardTo(cardItem[cn], lftUse);
                    break;
                case 'R':
                    cardRemained[2]--;
                    rht.moveCardTo(cardItem[cn], rhtUse);
                    break;
                case 'M':
                    cardRemained[3]--;
                    mate.moveCardTo(cardItem[cn], mateUse);
                    break;
                default:
                    break;
                }
            }
        }
        placeLabel();
        break;
    }
    default:
        break;
    }
    discarded.setAllInvisible();
    replaceContainers();
    scene->update();
}

void GameProgress::onFoldClicked()
{
    send(tcpSocket, "F");
    call->setVisible(false);
    fold->setVisible(false);
    FOR_TO(0, 107)
            cardItem[i]->setMySelected(false);
    placeLabel();
}

void GameProgress::onCallClicked()
{
    myCardArray.clear();
    FOR_TO(0, 107)
        if (cardItem[i]->isMySelected())
        {
            char str[] = "34567890JQKA2-+";
            int j = i % 54 / 4;
            if (i%54==53) j++;
            myCardArray.addCard(str[j]);
        }
    if (myCardArray.isBiggerThan(currentArray))
    {
        myCardArray.copyArrayTo(myLastArray);
        QString msg = "V";
        msg.append(QString::number(myCardArray.getArrayLength()));
        FOR_TO(0, 107)
            if (cardItem[i]->isMySelected())
                msg.append(".").append(QString::number(i));
        send(tcpSocket, msg);
        call->setVisible(false);
        fold->setVisible(false);
        FOR_TO(0, 107)
            cardItem[i]->setMySelected(false);
    }
}
