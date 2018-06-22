#include "tcpserver.h"
#include "ui_tcpserver.h"

TCPServer::TCPServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TCPServer)
{
    ui->setupUi(this);
}

TCPServer::~TCPServer()
{
    delete ui;
}
