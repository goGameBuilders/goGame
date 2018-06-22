#include "window_tcpclient.h"
#include "ui_window_tcpclient.h"

Window_TCPClient::Window_TCPClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window_TCPClient)
{
    ui->setupUi(this);
}

Window_TCPClient::~Window_TCPClient()
{
    delete ui;
}
