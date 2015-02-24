#include "logindlg.h"
#include "ui_logindlg.h"
#include <QMessageBox>
#include <QPainter>
#include <QtNetwork>

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{

    ui->setupUi(this);

    QString localHostName = QHostInfo::localHostName();
    //qDebug() <<"localHostName: "<<localHostName;
    QHostInfo info = QHostInfo::fromName(localHostName);
    //qDebug() <<"IP Address: "<<info.addresses();
    foreach(QHostAddress address,info.addresses())
    {
         if(address.protocol() == QAbstractSocket::IPv4Protocol)
         qDebug() << address.toString();
         //ui->??->setWindowTitle(address.toString());
         //this->repaint();
    }

    //sender = new QUdpSocket(this);
    //udp

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));
    //tcp
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_loginButton_clicked()
{
    if(ui->usrlineEdit->text() == "")
    {
        QMessageBox::warning(this, "提示",
            "你叫什么名字？",
            QMessageBox::Yes);
        ui->usrlineEdit->setFocus();
    } else if(ui->pswlineEdit->text() == "233")
    {
//        if(message=="ACEnter")
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
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_4);
    if(blockSize==0) //如果是刚开始接收数据
    {
       if(tcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
       in >> blockSize;
    }
    if(tcpSocket->bytesAvailable() < blockSize) return;
    in >> message;
    ui->statusLabel->setText(message);
}

void LoginDlg::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpSocket->errorString();
}

void LoginDlg::on_remoteHostPortLineEdit_editingFinished()
{
    ui->statusLabel->setText("连接中");
    newConnect();
}
