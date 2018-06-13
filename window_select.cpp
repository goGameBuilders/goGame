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
    Window_Play* game = new Window_Play(gameplatform);
    game->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    gameplatform->gameSelect(1, 2);
    game->show();
}   //Select界面中五子棋按钮
