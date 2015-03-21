#include <QApplication>
#include <QTextCodec>
#include "logindlg.h"
#include "gameprogress.h"
#include "universal.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   QTcpSocket *tcpSocket = new QTcpSocket;
   quint16 blockSize = 0;
#ifndef GAMETEST
   LoginDlg dlg(tcpSocket, blockSize);
   if(dlg.exec() == QDialog::Accepted)
   {
#else
#ifdef ONLINE
#include "network.h"
   tcpSocket->connectToHost("localhost", 23333);
   tcpSocket->waitForConnected();
   send(tcpSocket, "ITester");
#endif
#endif
       GameProgress mainWnd(tcpSocket, blockSize);
       mainWnd.show();
#ifndef ONLINE
   mainWnd.imitate();
#endif
       return a.exec();
#ifndef GAMETEST
   }
   else return 0;
#endif
}
