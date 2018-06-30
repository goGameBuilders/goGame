#include "window_select.h"
#include "ui_window_select.h"
#include "window_play.h"
#include "ui_window_play.h"
#include "window_tcpclient.h"
//#include "ui_tcpclient.h"

Window_Select::Window_Select(goGamePlatform* _gameplatform, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Window_Select),
    gameplatform(_gameplatform)
{
    ui->setupUi(this);
    ui->radioButton->click();
}

Window_Select::~Window_Select()
{
    delete ui;
}

void Window_Select::on_pushButton_clicked()
{
   OpenGameWindow(1);
}   //Select界面中五子棋按钮


void Window_Select::on_pushButton_3_clicked()
{
    OpenGameWindow(3);

}       //Select界面中黑白棋按钮

void Window_Select::on_radioButton_clicked()
{
    myvsWho = 1;
}   //Select界面中PVE按钮

void Window_Select::on_radioButton_2_clicked()
{
    myvsWho = 2;
}   //Select界面PVP(本地)按钮

void Window_Select::on_radioButton_3_clicked()
{
    myvsWho = 3;
}   //Select界面中PVP(网络主机)按钮



void Window_Select::on_radioButton_4_clicked()
{
    myvsWho = 4;
}   //Select界面中PVP(网络子机)按钮



void Window_Select::OpenGameWindow(int GameType)
{
    if(myvsWho == 1 || myvsWho == 2)
    {
        this->close();
        gameplatform->gameSelect(GameType, myvsWho);
        Window_Play* game = new Window_Play(gameplatform, GameType);
        game->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
        game->show();
    }

    if(myvsWho == 3)
    {
        Window_TCPServer* tcpserver_win = new Window_TCPServer(gameplatform, GameType);
        tcpserver_win->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
        tcpserver_win->setWindowFlags(tcpserver_win->windowFlags() | Qt::WindowStaysOnTopHint);
        tcpserver_win->setWindowModality(Qt::ApplicationModal);
        tcpserver_win->show();
    }

    if(myvsWho == 4)
    {
        Window_TCPClient* tcpclient_win = new Window_TCPClient(gameplatform, GameType);
        tcpclient_win->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
        tcpclient_win->setWindowFlags(tcpclient_win->windowFlags() | Qt::WindowStaysOnTopHint);
        tcpclient_win->setWindowModality(Qt::ApplicationModal);
        tcpclient_win->show();
    }
}
