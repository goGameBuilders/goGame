#ifndef WINDOW_TCPSERVER_H
#define WINDOW_TCPSERVER_H

/*
 *  服务器与客户端传输指令说明：
 * 00# + gameType + isReady         服务器判断游戏是否可以开始
 * 01#                              服务器向客户端发送开始游戏指令
 * 02# + x + # + y + #              服务器向客户端传输游戏内容
 * 03# + x + # + y + #              客户端向服务器传输游戏内容
 *
 * 0F#                              客户端取消准备
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */






#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QThreadPool>
#include <vector>


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

    void receiveMouseData(QString x, QString y);

signals:
    void sendNetData(int x, int y);
    void closeWhenDisconnect();

private:
    Ui::Window_TCPServer *ui;


    QTcpServer *tcpServer; //监听套接字
    QTcpSocket *tcpSocket; //通信套接字

    QString port;           //要监听的端口

    goGamePlatform* gameplatform;       //游戏平台类指针
    QString gameType;                       //游戏类型(相同者才可以开始游戏)

    bool listenFlag = 0;                //侦听按钮flag
    bool isStart = 0;
};

#endif // WINDOW_TCPSERVER_H
