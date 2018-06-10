#include "window_select.h"
#include "ui_window_select.h"
#include "window_play.h"
#include "ui_window_play.h"

Window_Select::Window_Select(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Window_Select)
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
    Window_Play* game = new Window_Play();
    game->show();
}   //Select界面中五子棋按钮
