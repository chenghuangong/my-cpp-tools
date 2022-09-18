#include "simple_tcp_server.h"

simple_tcp_server::simple_tcp_server(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.btn_start, &QPushButton::clicked, this, 
        [this]() 
        {
            ui.pte_commands->appendPlainText("> start server btn clicked");
            start_server();
        });

    connect(ui.btn_stop, &QPushButton::clicked, this,
        [this]()
        {
            ui.pte_commands->appendPlainText("> stop server btn clicked");
            stop_server();
        });

    connect(ui.btn_send, &QPushButton::clicked, this,
        [this]()
        {
            ui.pte_commands->appendPlainText("> send msg btn clicked");
            write_to_clients();
        });

    connect(ui.btn_get_clients, &QPushButton::clicked, this,
        [this]()
        {
            ui.pte_commands->appendPlainText("> client number btn clicked, active client number is " + QString::number(sockets_.size()));
        });
}


void simple_tcp_server::start_server()
{
    if (server_)
    {
        if (server_->isListening())
        {
            ui.pte_commands->appendPlainText("> server is already listening");
        }
        else
        {
            ui.pte_commands->appendPlainText("> server is in error state");
        }
    }
    else
    {
        server_ = new QTcpServer(this);
        QHostAddress addr(ui.le_addr->text());
        if (server_->listen(addr, ui.le_port->text().toInt()))
        {
            ui.pte_commands->appendPlainText("> server is listening...");
            connect(server_, &QTcpServer::newConnection, this, &simple_tcp_server::handle_new_client);
        }
        else
        {
            ui.pte_commands->appendPlainText("> start listening failed, please check TCP/IP addr and port number");
        }
    }
}


simple_tcp_server::~simple_tcp_server()
{
    stop_server();
}

void simple_tcp_server::stop_server()
{
    // 删除所有已经连接的客户端
    sockets_.erase(sockets_.begin(), sockets_.end());
    if (server_)
    {
        server_->close();
        server_ = nullptr;
    }
    ui.pte_commands->appendPlainText("> server is closed");
}


void simple_tcp_server::write_to_clients()
{
    if (server_)
    {
        for (auto socket : sockets_)
        {
            socket->write(ui.le_msg->text().toLocal8Bit());
        }
        ui.pte_commands->appendPlainText("> msg has sent to all clients");
    }
}


void simple_tcp_server::handle_new_client()
{
    if (server_)
    {
        auto socket = server_->nextPendingConnection();
        sockets_.push_back(socket);
        ui.pte_commands->appendPlainText("> new client came in, current client number is " + QString::number(sockets_.size()));
        connect(socket, &QTcpSocket::readyRead, this, &simple_tcp_server::read_data);
        connect(socket, &QTcpSocket::stateChanged, this, &simple_tcp_server::client_state_changed);
    } 
}


void simple_tcp_server::client_state_changed(QAbstractSocket::SocketState state)
{
    auto socket = qobject_cast<QTcpSocket*>(sender());
    if (state == QAbstractSocket::SocketState::UnconnectedState)
    {
        auto result = std::find(sockets_.begin(), sockets_.end(), socket);
        if (result != sockets_.end())
        {
            sockets_.erase(result);
        }
    }
}


void simple_tcp_server::read_data()
{
    auto socket = qobject_cast<QTcpSocket*>(sender());
    QString data(socket->readAll());

    // 是否可以这样写？也许QTcpsocket*没有实现 ==，测试是否可以打印出clients的序号
    auto result = std::find(sockets_.begin(), sockets_.end(), socket);    
    ptrdiff_t pos;
    if (result != sockets_.end())
    {
        pos = result - sockets_.begin();
    }
    
    ui.pte_recv->appendPlainText("> client" + QString::number(pos) + " msg: " + data);
}
