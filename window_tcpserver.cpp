#include "window_tcpserver.h"
#include "ui_window_tcpserver.h"

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
