#include "universal.h"
#include "network.h"

void send(QTcpSocket *socket, QString msg)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(DATA_STREAM_VERSION);
    out<<(quint16) 0;
    out<<msg;
    out.device()->seek(0);
    out<<(quint16) (block.size() - sizeof(quint16));
    socket->write(block);
}
