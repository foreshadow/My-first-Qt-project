#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
class LoginDlg;
}

class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDlg(QTcpSocket *tcpSocket, quint16 &blockSize, QWidget *parent = 0);
    ~LoginDlg();

private slots:
    void on_loginButton_clicked();
    void newConnect(); //连接服务器
    void readMessage();  //接收数据
    void displayError(QAbstractSocket::SocketError);  //显示错误
    void on_remoteHostPortLineEdit_editingFinished();
    void on_usrLineEdit_editingFinished();

private:
    Ui::LoginDlg *ui;
    QTcpSocket *tcpSocket;
    quint16 &blockSize;

protected:
    void paintEvent(QPaintEvent *);
    bool identitySent;
};

#endif // LOGINDLG_H
