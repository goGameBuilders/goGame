#include "window_select.h"
#include "ui_window_select.h"
#include "window_play.h"
#include "ui_window_play.h"

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
    this->close();
    gameplatform->gameSelect(1, myvsWho);
    Window_Play* game = new Window_Play(gameplatform, 1);
    game->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    game->show();
}   //Select界面中五子棋按钮


void Window_Select::on_pushButton_3_clicked()
{
    this->close();
    gameplatform->gameSelect(3, myvsWho);
    Window_Play* game = new Window_Play(gameplatform, 3);
    game->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    game->show();
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



void Window_Select::OpenNetWorkWindow(int GameType)
{

}
