#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>

namespace Ui {
class TCPServer;
}

class TCPServer : public QWidget
{
    Q_OBJECT

public:
    explicit TCPServer(QWidget *parent = 0);
    ~TCPServer();

private:
    Ui::TCPServer *ui;
};

#endif // TCPSERVER_H
