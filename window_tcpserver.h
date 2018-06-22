#ifndef WINDOW_TCPSERVER_H
#define WINDOW_TCPSERVER_H

#include <QMainWindow>

namespace Ui {
class Window_TCPServer;
}

class Window_TCPServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_TCPServer(QWidget *parent = 0);
    ~Window_TCPServer();

private:
    Ui::Window_TCPServer *ui;
};

#endif // WINDOW_TCPSERVER_H
