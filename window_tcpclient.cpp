#include "window_tcpclient.h"
#include "ui_window_tcpclient.h"

Window_TCPClient::Window_TCPClient(goGamePlatform* _gameplatform, int _gameType, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window_TCPClient), gameplatform(_gameplatform)
{
    ui->setupUi(this);
    gameType = _gameType;
    tcpSocket = nullptr;
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    setWindowTitle("客户端");

    ui->pushButton_Disconnect->setEnabled(false);

}

Window_TCPClient::~Window_TCPClient()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    delete ui;
}

void Window_TCPClient::on_pushButton_Connect_clicked()
{
    //获取服务器IP和端口
    ip = ui->lineEdit_IP->text();
    port = ui->lineEdit_Port->text();
    qint16 _port = port.toInt();

    ui->pushButton_Disconnect->setEnabled(true);
    ui->pushButton_Connect->setEnabled(false);

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),_port);
}       //TCPClient界面中Connect按钮


void Window_TCPClient::on_pushButton_Back_clicked()
{
    this->close();
}       //TCPClient界面中Back按钮

void Window_TCPClient::on_pushButton_Disconnect_clicked()
{
    if(tcpSocket == nullptr)return;
    //主动和对方断开连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

    ui->pushButton_Connect->setEnabled(true);
    ui->pushButton_Disconnect->setEnabled(false);

}       //TCPClient界面中Disconnect按钮


void Window_TCPClient::connected()
{
    QString msg;
    msg.append("<b>Message: </b>Successfully connect to ");
    msg = msg + ip + " : " + port + "\n";
    ui->textEdit_Read->append(msg);
}       //SLOT"connected" connect with SIGNAL"connected"


void Window_TCPClient::disconnected()
{
    QString msg;
    msg.append("<b>Message: </b>Successfully disconnect from ");
    msg = msg + ip + " : " + port + "\n";
    ui->textEdit_Read->append(msg);
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    ui->pushButton_Connect->setEnabled(true);
    ui->pushButton_Disconnect->setEnabled(false);

}       //SLOT"disconnected" connect with SIGNAL"disconnected"

void Window_TCPClient::readyRead()
{

}       //SLOT"readyRead" connect with SIGNAL"readyRead"











