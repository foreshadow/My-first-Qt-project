#include "network.h"
#include "logindlg.h"
#include "ui_logindlg.h"
#include <QMessageBox>
#include <QPainter>

LoginDlg::LoginDlg(QTcpSocket *tcpSocket, quint16 &blockSize,
                   QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg),
    tcpSocket(tcpSocket), blockSize(blockSize),
    identitySent(false)
{

    ui->setupUi(this);

    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    foreach(QHostAddress address, info.addresses())
    {
         if(address.protocol() == QAbstractSocket::IPv4Protocol)
         qDebug() << address.toString();

    }

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    //tcp
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_loginButton_clicked()
{
    if(ui->usrLineEdit->text() == "")
    {
        QMessageBox::warning(this, "提示",
            "你叫什么名字？",
            QMessageBox::Yes);
        ui->usrLineEdit->setFocus();
    } else if(ui->pswlineEdit->text() == "233") {
        if (tcpSocket->state()==QAbstractSocket::ConnectedState
            && ui->usrLineEdit->text()!="" && !identitySent)
        {
            send(tcpSocket, ui->usrLineEdit->text().prepend('I'));
            identitySent = true;
        }
        disconnect(tcpSocket, SIGNAL(readyRead()),
                   this, SLOT(readMessage()));
        accept();
    } else {
        QMessageBox::warning(this, "提示",
            "你怎么连密码都不知道= =",
            QMessageBox::Yes);
        ui->pswlineEdit->clear();
        ui->pswlineEdit->setFocus();
    }
}

void LoginDlg::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/img/newbloom.jpg");
    painter.drawPixmap(-100, -50, 600, 327, pix);
    ui->statusLabel->setStyleSheet("color: rgb(255, 255, 255)");
}

void LoginDlg::newConnect()
{
    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(ui->remoteHostIpAddressLineEdit->text(),
                             ui->remoteHostPortLineEdit->text().toInt());
}

void LoginDlg::readMessage()
{
    QString message;  //存放从服务器接收到的字符串
    QDataStream in(tcpSocket);
    in.setVersion(DATA_STREAM_VERSION);
    if(blockSize==0) //如果是刚开始接收数据
    {
       if(tcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
       in >> blockSize;
    }
    if(tcpSocket->bytesAvailable() < blockSize) return;
    in >> message;
    blockSize = 0;

    ui->statusLabel->setText(message.right(message.length()-1));
}

void LoginDlg::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpSocket->errorString();
}

void LoginDlg::on_remoteHostPortLineEdit_editingFinished()
{
    if (tcpSocket->state()==QAbstractSocket::UnconnectedState)
    {
        ui->statusLabel->setText("连接中");
        newConnect();
    }
}

void LoginDlg::on_usrLineEdit_editingFinished()
{
    if (tcpSocket->state()==QAbstractSocket::ConnectedState
        && ui->usrLineEdit->text()!="" && !identitySent)
    {
        send(tcpSocket, ui->usrLineEdit->text().prepend('I'));
        identitySent = true;
    }
}
