#include "window_tcpclient.h"
#include "ui_window_tcpclient.h"

Window_TCPClient::Window_TCPClient(QWidget *parent, int _gameType) :
    QMainWindow(parent),
    ui(new Ui::Window_TCPClient)
{
    ui->setupUi(this);
    gameType = _gameType;
}

Window_TCPClient::~Window_TCPClient()
{
    delete ui;
}

