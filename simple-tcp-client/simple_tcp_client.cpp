#include "simple_tcp_client.h"

simple_tcp_client::simple_tcp_client(QWidget *parent)
    : QMainWindow(parent)
    , socket_(nullptr)
{
    ui.setupUi(this);
    connect(ui.btn_connect, &QPushButton::clicked, this,
        [this]()
        {
            ui.pte_commands->appendPlainText("> connect btn clicked");
            connect_to_server();
        });

    connect(ui.btn_disconnect, &QPushButton::clicked, this,
        [this]()
        {
            ui.pte_commands->appendPlainText("> disconnect btn clicked");
            disconnect_from_server();
        });

    connect(ui.btn_send, &QPushButton::clicked, this,
        [this]()
        {
            ui.pte_commands->appendPlainText("> send msg to server");
            write_to_server();
        });
}


void simple_tcp_client::connect_to_server()
{
    if (socket_) 
    {
        ui.pte_commands->appendPlainText("> socket is already started");
    }
    else
    {
        QHostAddress addr(ui.le_addr->text());
        socket_ = new QTcpSocket(this);
        connect(socket_, &QTcpSocket::readyRead, this, &simple_tcp_client::read_data);
        connect(socket_, &QTcpSocket::stateChanged, this,
            [this](QAbstractSocket::SocketState state)
            {
                if (state == QAbstractSocket::SocketState::ConnectedState)
                {
                    ui.pte_commands->appendPlainText("> connected to server");
                }
            }
        );
        socket_->connectToHost(addr, ui.le_port->text().toInt()); 
    }
}

simple_tcp_client::~simple_tcp_client()
{
    disconnect_from_server();
}

void simple_tcp_client::disconnect_from_server()
{
    if (socket_)
    {
        socket_->disconnectFromHost();
        ui.pte_commands->appendPlainText("> disconnect from server");
        socket_ = nullptr;
    }
}

void simple_tcp_client::write_to_server()
{
    if (socket_)
    {
        socket_->write(ui.le_msg->text().toLocal8Bit());
        ui.pte_commands->appendPlainText("> write to server");
    }
}

void simple_tcp_client::read_data()
{
    QString data(socket_->readAll());
    ui.pte_recv->appendPlainText("> received " + data);
}
