#ifndef NETWORK
#define NETWORK

#include <QtCore>
#include <QtNetwork>

void send(QTcpSocket *socket, QString msg);

#define DATA_STREAM_VERSION QDataStream::Qt_5_4

#endif // NETWORK

