#include "Qhttpserver.h"

#if QTSIM_PLATFORM

httpserver::httpserver(quint16 port)
{
    m_Info = "";
    m_SockClient.clear();
    m_MsgData.clear();
    m_pServer = new QTcpServer(this);
    if(false == m_pServer->listen(QHostAddress::Any, port))
    {
        m_Info = m_pServer->errorString();
        m_pServer->close();
        m_blistened = false;
    }
    else
    {
        m_blistened = true;
        connect(m_pServer, &QTcpServer::newConnection, this, &httpserver::NewConnection);
        connect(m_pServer, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(OnConnectionDisc(QAbstractSocket::SocketError)));
    }
}

httpserver::~httpserver()
{
    for(int i = 0; i < m_SockClient.size(); i ++)
    {
        m_SockClient[i]->deleteLater();
    }

    if(nullptr != m_pServer)
    {
        m_pServer->close();
        delete m_pServer;
        m_pServer = nullptr;
    }
}

void httpserver::OnConnectionDisc(QAbstractSocket::SocketError error)
{
    qDebug() << "Http server error:" << error;
}

/*===============================================
 * 函数：GetState
 * 功能：获取http服务器的状态
 * 参数：Info         消息提示
 * 返回：true         监听成功
 *      false        监听失败
===============================================*/
bool httpserver::GetState(QString &Info)
{
   Info = m_Info;
   return m_blistened;
}

/*===============================================
 * 函数：RecvNewPort
 * 功能：获取新的端口号
 * 参数：Port         端口号
 * 返回：
===============================================*/
void httpserver::RecvNewPort(quint16 Port)
{
    m_Port = Port;
    if(m_pServer->isListening())
    {
        m_pServer->close();
        m_pServer->listen(QHostAddress::Any, m_Port);
    }
}

/*===============================================
 * 函数：NewConnection
 * 功能：处理新发来的http客户端申请，并回应
 * 参数：
 * 返回：
===============================================*/
void httpserver::NewConnection()
{
    if(m_pServer->hasPendingConnections())
    {
        QTcpSocket* Sock = m_pServer->nextPendingConnection();
        RespondClient(Sock, "");
        m_SockClient<<Sock;

        emit SendMsg(MSG_CLIENT_IN, m_MsgData);
        connect(Sock, &QTcpSocket::disconnected, this, &httpserver::DealDisconnection);
        connect(Sock, &QTcpSocket::readyRead, this, &httpserver::ReadData);
    }
}

/*===============================================
 * 函数：DealDisconnection
 * 功能：处理客户端断开问题
 * 参数：
 * 返回：
===============================================*/
void httpserver::DealDisconnection()
{
    for(int i = 0; i < m_SockClient.size(); )
    {
        if(QAbstractSocket::ConnectedState != m_SockClient[i]->state())
        {
            m_SockClient.removeAt(i);

            emit SendMsg(MSG_CLIENT_OUT, m_MsgData);
            continue;
        }
        i ++;
    }
}

/*===============================================
 * 函数：RespondClient
 * 功能：回应（发送）客户端消息
 * 参数：Sock          客户端
 *      data          数据
 * 返回：true          发送成功
 *      false         发送失败
===============================================*/
bool httpserver::RespondClient(QTcpSocket* Sock, const QByteArray &data)
{
    if(nullptr == Sock)
    {
        return false;
    }

    char length[32];
    memset(length, 0 ,sizeof(length));
    sprintf(length, "Content-Length:%d\r\n", data.size());
    Sock->write("HTTP/1.1 200 OK\r\n");
    Sock->write("Access-Control-Allow-Origin: *\r\n");
    Sock->write(length);
    Sock->write("Content-Type: application/octet-stream\r\n");
    Sock->write("Keep-Alive: timeout=5, max=5\r\n\r\n");
    if(0 != data.size())
    {
        Sock->write(data.data(), data.size());
    }

    return true;
}

/*===============================================
 * 函数：ReadData
 * 功能：读取数据
 * 参数：
 * 返回：
===============================================*/
void httpserver::ReadData()
{
    QByteArray data;
    QByteArray Msg;
    data.clear();
    Msg.clear();
    QTcpSocket* Sock = nullptr;
    for(int i = 0; i < m_SockClient.size(); i ++)
    {
        data.clear();
        Sock = m_SockClient.at(i);
        data = Sock->readAll();
        if(data.length() != 0)
        {
            qDebug()<<data;
            QString url = Sock->peerAddress().toString() + ":" + QString::number(Sock->peerPort()) + "/" + GetMsgText(data, Msg);
            emit SendMsg(MSG_CLIENT_MSG, Msg, url);
            qDebug()<<Msg;
            qDebug()<<url;
            data.clear();

            RespondClient(Sock, data);
        }
    }
}

/*===============================================
 * 函数：GetMsgText
 * 功能：获取客户端发送的内容
 * 参数：data            原始数据
 *      Content         客户端发送的内容
 * 返回：客户端的url
===============================================*/
QString httpserver::GetMsgText(const QByteArray &data, QByteArray &Content)
{
    if(data.isEmpty())
    {
        return "";
    }
    QString strData = data;

    // 获取url
    int Start = strData.indexOf("/");
    int End = strData.indexOf("HTTP/");
    QString Url = strData.mid(Start + 1, End - Start - 2);

    // 获取长度
    int locat_length = strData.indexOf("Content-Length:");
    int Locat_Content = strData.indexOf("\r\n\r\n");
    locat_length += qstrlen("Content-Length:");
    QString len = strData.mid(locat_length, Locat_Content - locat_length);

    // 获取内容
    Locat_Content += qstrlen("\r\n\r\n");
    Content = strData.mid(Locat_Content, len.toInt()).toLatin1();

    return Url;
}

#endif
