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
    explicit LoginDlg(QWidget *parent = 0);
    ~LoginDlg();

private slots:
    void on_loginButton_clicked();
    void newConnect(); //连接服务器
    void readMessage();  //接收数据
    void displayError(QAbstractSocket::SocketError);  //显示错误

    void on_remoteHostPortLineEdit_editingFinished();

private:
    Ui::LoginDlg *ui;
    QTcpSocket *tcpSocket;
    QString message;  //存放从服务器接收到的字符串
    quint16 blockSize; //存放文件的大小信息

protected:
    void paintEvent(QPaintEvent *);
};

#endif // LOGINDLG_H
