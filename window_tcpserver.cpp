#include "window_tcpserver.h"
#include "ui_window_tcpserver.h"
#include "window_play.h"
#include "ui_window_play.h"

Window_TCPServer::Window_TCPServer(goGamePlatform* _gameplatform, int gametype, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window_TCPServer), gameplatform(_gameplatform)
{
    ui->setupUi(this);
    QThreadPool::globalInstance()->setMaxThreadCount(3);        //设置服务器最大线程数
    tcpServer = nullptr;
    tcpSocket = nullptr;
    tcpServer = new QTcpServer(this);

    setWindowTitle("服务器端");

    gameType = gametype;

    //禁用某些按钮
    ui->pushButton_Start->setEnabled(false);
    ui->pushButton_Disconnect->setEnabled(false);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));


}

Window_TCPServer::~Window_TCPServer()
{
    delete ui;
}

void Window_TCPServer::on_pushButton_Listen_clicked()
{
    port = ui->lineEdit_Port->text();
    qint16 _port = port.toInt();
    if(listenFlag == 0)
    {

        if(tcpServer->listen(QHostAddress::Any, _port))
        {
            QString msg;
            msg = msg + "成功开启服务器!\nPort:" + port + " listening...\n";
            ui->textEdit_Message->append(msg);
            ui->pushButton_Listen->setText("取消侦听");
            ui->lineEdit_Port->setEnabled(false);
            listenFlag = 1;
        }
        else
        {
            QString msg;
            msg = "服务器开启失败，请检查端口或尝试更换端口。\n";
            msg += "错误信息:"+ tcpServer->errorString() +"\n";
            ui->textEdit_Message->append(msg);
        }
    }               //侦听功能

    else
    {
        tcpServer->close();
        if(tcpSocket != nullptr)
        {
            if(tcpSocket->state() == QAbstractSocket::ConnectedState)
            {
                //关闭连接
                tcpSocket->disconnectFromHost();
                tcpSocket->close();
            }
        }

         QString msg;
         msg = msg + "Port:" + port + " stop listening";
         ui->textEdit_Message->append(msg);
         ui->pushButton_Listen->setText("侦听");
         ui->lineEdit_Port->setEnabled(true);
         listenFlag = 0;

    }       //取消侦听功能

}       //TcpServer界面中侦听按钮

void Window_TCPServer::on_pushButton_Start_clicked()
{
    QString tmp;
    tmp.append("开始游戏！");
    ui->textEdit_Message->append(tmp);
    Window_Play* game = new Window_Play(gameplatform, gameplatform->getType());
    game->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    game->setWindowFlags(game->windowFlags() | Qt::WindowStaysOnTopHint);
    game->setWindowModality(Qt::ApplicationModal);
    game->show();
    QString temp;                //用来向服务器传送数据
    temp = "01#";    //01#为通知客户端游戏开始
    tcpSocket->write(temp.toUtf8().data());

}       //TcpServer界面中Start按钮

void Window_TCPServer::on_pushButton_Back_clicked()
{
    this->close();
}       //TcpServer界面中Back按钮

void Window_TCPServer::on_pushButton_Disconnect_clicked()
{
    tcpServer->close();
    if(tcpSocket != nullptr)
    {
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
        tcpSocket->deleteLater();
    }

}       //TcpServer界面中Disconnect按钮

void Window_TCPServer::newConnection()
{
    //取出建立好连接的套接字
    tcpSocket=tcpServer->nextPendingConnection();
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    //获取对方IP和端口
    QString ip=tcpSocket->peerAddress().toString();   //IP地址 字符串
    quint16 port = tcpSocket->peerPort();             //端口 无符号整型
    QString temp=QString("[%1:%2] 成功连接!\n").arg(ip).arg(port);
    ui->textEdit_Message->append(temp);//显示到编辑区

    //成功连接后，才可以使用相应按钮
    ui->pushButton_Disconnect->setEnabled(true);



}       //TcpServer中SLOT"newConnection"

void Window_TCPServer::readyRead()
{
    QByteArray buf = tcpSocket->readAll();
    QString msg = QString(buf);
    if(msg.left(3) == "00#")
    {
        if(msg[3] == gameType)
        {
            ui->pushButton_Start->setEnabled(true);
            QString tmp;
            tmp.append("子机已准备好！可以开始游戏！\n");
            ui->textEdit_Message->append(tmp);
        }
        else
        {
            QString tmp;
            tmp.append("<b>警告：</b>对方与您的游戏类型不一致，无法开始游戏。");
            ui->textEdit_Message->append(tmp);
        }

    }       //接受客户端传送过来的游戏类型
    else if(msg.left(3) == "0F#")
    {
        ui->pushButton_Start->setEnabled(false);
        QString tmp;
        tmp.append("对方取消准备。");
        ui->textEdit_Message->append(msg);

    }       //客户端取消准备后的行为

}       //TcpServer中SLOT"readyRead"

void Window_TCPServer::timeout()
{

}       //TcpServer中SLOT"timeout"

void Window_TCPServer::disconnected()
{
    QString ip = tcpSocket->peerAddress().toString();   //IP地址 字符串
    quint16 port = tcpSocket->peerPort();             //端口 无符号整型
    QString msg;
    msg = QString("失去了与客户端<b>[%1:%2]</b>的连接").arg(ip).arg(port);
    ui->textEdit_Message->append(msg);
    ui->pushButton_Disconnect->setEnabled(false);

}       //TcpServer中SLOT"disconnected"
