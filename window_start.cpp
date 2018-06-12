#include "window_start.h"
#include "ui_window_start.h"
#include "window_select.h"
#include "ui_window_select.h"
#include <QWidget>
#include <QtWidgets>
#include <QtCore>

Window_Start::Window_Start(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window_Start)
{
    ui->setupUi(this);
    gameplatform = new goGamePlatform();
}

Window_Start::~Window_Start()
{
    delete gameplatform;
    delete ui;
}

void Window_Start::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton reply;

      reply = QMessageBox::question(this,
                            "My Title",
                              "Do you really want to quit?",
                            QMessageBox::No | QMessageBox::Yes);
      if(reply == QMessageBox::Yes)
          this->close();


}   //主界面Exit按钮


void Window_Start::on_actionExit_2_triggered()
{
    QMessageBox::StandardButton reply;

      reply = QMessageBox::question(this,
                            "My Title",
                              "Do you really want to quit?",
                            QMessageBox::No | QMessageBox::Yes);
      if(reply == QMessageBox::Yes)
          this->close();
}       //工具栏Exit按钮

void Window_Start::on_pushButton_clicked()
{
    Window_Select* select_win = new Window_Select(gameplatform, this);
    select_win->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    connect(select_win, SIGNAL(destroyed(QObject*)), this, SLOT(close()));
    select_win->setModal(true);
    select_win->exec();
}                           //主界面Start按钮
