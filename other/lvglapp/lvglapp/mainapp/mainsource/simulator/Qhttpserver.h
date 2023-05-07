#ifndef QHTTPSERVER_H
#define QHTTPSERVER_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"

#if QTSIM_PLATFORM
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include "mainstart/customer_config.h"

class httpserver : public QObject
{
    Q_OBJECT
public:
    //explicit httpserver(QObject *parent = nullptr);
    httpserver(quint16 port);
    ~httpserver();

    bool GetState(QString &Info);
    bool RespondClient(QTcpSocket* Sock, const QByteArray &data);
    QString GetMsgText(const QByteArray &data, QByteArray &Content);

signals:
    void SendMsg(int flag, QByteArray &data, QString Url = "");

public slots:
    void DealDisconnection();
    void NewConnection();
    void ReadData();
    void RecvNewPort(quint16 Port);
    void OnConnectionDisc(QAbstractSocket::SocketError error);

private:
    bool m_blistened;
    quint16 m_Port;
    QByteArray m_MsgData;
    QString m_Info;
    QTcpServer* m_pServer;
    QList<QTcpSocket*> m_SockClient;
};

#endif

#endif // QHTTPSERVER_H
