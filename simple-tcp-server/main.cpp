#include "simple_tcp_server.h"
#include <QtWidgets/QApplication>

/*
1. 使用Qtcpsocket编写的tcp server工具类，用于接受TCP客户端的信息，并可以向TCP客户端发送信息

*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    simple_tcp_server w;
    w.show();
    return a.exec();
}
