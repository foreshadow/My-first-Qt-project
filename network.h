#ifndef NETWORK
#define NETWORK

#include <QtCore>
#include <QtNetwork>

void send(QTcpSocket socket, QString msg)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);
    out<<(quint16) 0;
    out<<msg;
    out.device()->seek(0);
    out<<(quint16) (block.size() - sizeof(quint16));
    socket->write(block);
}

#endif // NETWORK

