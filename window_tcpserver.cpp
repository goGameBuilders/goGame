#include "window_tcpserver.h"
#include "ui_window_tcpserver.h"

Window_TCPServer::Window_TCPServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window_TCPServer)
{
    ui->setupUi(this);
}

Window_TCPServer::~Window_TCPServer()
{
    delete ui;
}
