#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_simple_tcp_client.h"
#include <QTcpSocket>

class simple_tcp_client : public QMainWindow
{
    Q_OBJECT

public:
    simple_tcp_client(QWidget *parent = Q_NULLPTR);
    ~simple_tcp_client();

private slots:
    void connect_to_server();
    void disconnect_from_server();
    void write_to_server();                                     // write line edit string to server
    void read_data();                                           // read from server

private:
    Ui::simple_tcp_clientClass ui;
    QTcpSocket* socket_;
};
