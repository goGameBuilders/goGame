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
    explicit Window_TCPClient(QWidget *parent = 0, int _gameType);
    ~Window_TCPClient();

private slots:
    void on_pushButton_Back_clicked();

private:
    Ui::Window_TCPClient *ui;
    int gameType;
};

#endif // WINDOW_TCPCLIENT_H
