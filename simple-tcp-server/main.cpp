#include "simple_tcp_server.h"
#include <QtWidgets/QApplication>

/*
1. ʹ��Qtcpsocket��д��tcp server�����࣬���ڽ���TCP�ͻ��˵���Ϣ����������TCP�ͻ��˷�����Ϣ

*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    simple_tcp_server w;
    w.show();
    return a.exec();
}
