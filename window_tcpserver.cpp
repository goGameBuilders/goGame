#include "window_tcpserver.h"
#include "ui_window_tcpserver.h"

Window_TCPServer::Window_TCPServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window_TCPServer)
{
    ui->setupUi(this);
    QThreadPool::globalInstance()->setMaxThreadCount(2);        //设置服务器最大线程数
    tcpServer = nullptr;
    tcpSocket = nullptr;
    tcpServer = new QTcpServer(this);

    //禁用某些按钮
    ui->pushButton_Start->setEnabled(false);
    ui->pushButton_Disconnect->setEnabled(false);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));


}

Window_TCPServer::~Window_TCPServer()
{
    delete ui;
}

void Window_TCPServer::on_pushButton_Listen_clicked()
{

}       //TcpServer界面中侦听按钮

void Window_TCPServer::on_pushButton_Start_clicked()
{

}       //TcpServer界面中Start按钮

void Window_TCPServer::on_pushButton_Back_clicked()
{

}       //TcpServer界面中Back按钮

void Window_TCPServer::on_pushButton_Disconnect_clicked()
{

}       //TcpServer界面中Disconnect按钮

void Window_TCPServer::newConnection()
{

}       //TcpServer中SLOT"newConnection"

void Window_TCPServer::readyRead()
{

}       //TcpServer中SLOT"readyRead"

void Window_TCPServer::timeout()
{

}       //TcpServer中SLOT"timeout"
