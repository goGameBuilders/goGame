#ifndef WINDOW_TCPSERVER_H
#define WINDOW_TCPSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QThreadPool>

#include "goGamePlatform.h"

namespace Ui {
class Window_TCPServer;
}

class Window_TCPServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_TCPServer(goGamePlatform* _gameplatform, int gametype, QWidget *parent = 0);
    ~Window_TCPServer();

private slots:
    void on_pushButton_Listen_clicked();

    void on_pushButton_Start_clicked();

    void on_pushButton_Back_clicked();

    void on_pushButton_Disconnect_clicked();

    void newConnection();

    void disconnected();

    void readyRead();

    void timeout();
private:
    Ui::Window_TCPServer *ui;


    QTcpServer *tcpServer; //监听套接字
    QTcpSocket *tcpSocket; //通信套接字

    QString port;           //要监听的端口

    QTimer timer;          //定时器

    goGamePlatform* gameplatform;       //游戏平台类指针
    int gameType;                       //游戏类型(相同者才可以开始游戏)

    bool listenFlag = 0;                //侦听按钮flag
};

#endif // WINDOW_TCPSERVER_H
