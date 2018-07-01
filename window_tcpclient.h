#ifndef WINDOW_TCPCLIENT_H
#define WINDOW_TCPCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonDocument>
#include <QTimer>
#include <vector>

#include "goGamePlatform.h"


namespace Ui {
class Window_TCPClient;
}

class Window_TCPClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_TCPClient(goGamePlatform *_gameplatform, int _gameType, QWidget *parent = 0);
    ~Window_TCPClient();

private slots:
    void on_pushButton_Back_clicked();

    void on_pushButton_Connect_clicked();

    void on_pushButton_Disconnect_clicked();

    void on_pushButton_Ready_clicked();

    void receiveMouseData(QString x, QString y);

    void closeNet();

public slots:
    void connected();
    void disconnected();
    void readyRead();

signals:
    void sendNetData(int x, int y);
    void closeWhenDisconnect();

private:
    Ui::Window_TCPClient *ui;

    goGamePlatform *gameplatform;

    QString gameType;
    QString ip;
    QString port;
    QTcpSocket *tcpSocket;

    bool readyFlag = 0;
    bool isStart = 0;



};

#endif // WINDOW_TCPCLIENT_H
