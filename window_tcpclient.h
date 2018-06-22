#ifndef WINDOW_TCPCLIENT_H
#define WINDOW_TCPCLIENT_H

#include <QMainWindow>

namespace Ui {
class Window_TCPClient;
}

class Window_TCPClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_TCPClient(QWidget *parent = 0);
    ~Window_TCPClient();

private:
    Ui::Window_TCPClient *ui;
};

#endif // WINDOW_TCPCLIENT_H
