#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_simple_tcp_server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include <algorithm>


class simple_tcp_server : public QMainWindow
{
    Q_OBJECT

public:
    simple_tcp_server(QWidget *parent = Q_NULLPTR);
    ~simple_tcp_server();


private slots:
    void start_server();
    void stop_server();
    void write_to_clients();

    void handle_new_client();                                   // handle new coming clients
    void client_state_changed(QAbstractSocket::SocketState);    // delete disconnected client
    void read_data();                                           // read from clients

private:
    Ui::simple_tcp_serverClass ui;
    QTcpServer* server_ = nullptr;
    std::vector<QTcpSocket*> sockets_;
};
