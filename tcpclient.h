#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>

namespace Ui {
class TCPClient;
}

class TCPClient : public QWidget
{
    Q_OBJECT

public:
    explicit TCPClient(QWidget *parent = 0);
    ~TCPClient();

private:
    Ui::TCPClient *ui;
};

#endif // TCPCLIENT_H
