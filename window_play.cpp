#include "window_play.h"
#include "ui_window_play.h"
#include "window_start.h"
#include "ui_window_start.h"


#include <QWidget>
#include <QtWidgets>
#include <QtCore>
#include <QPainter>
#include <QMouseEvent>
#include <math.h>

Window_Play::Window_Play(goGamePlatform* _gameplatform,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window_Play),
    gameplatform(_gameplatform)
{
    ui->setupUi(this);
}

Window_Play::~Window_Play()
{
    delete ui;
}

void Window_Play::paintEvent(QPaintEvent *)
{
  paint=new QPainter(this);
  paint->begin(this);//主窗口

 if(!msgFirst)
 {
     QString gameinfo = gameplatform->getgame()->getinfo().c_str();
     ui->label->setText(gameinfo);
     msgFirst = true;
 }

  paint->setPen(QPen(Qt::darkMagenta,2,Qt::SolidLine));//钢笔工具：颜色，线号，实线
  //画SIZE+1条横线
  for(int i=1;i<SIZE+1;i++)
    {
      paint->drawLine(margin_x+block_size,margin_y+(block_size)*i,margin_x+(block_size)*(SIZE),margin_y+(block_size)*i);//画线函数：x1,y1,x2,y2:画从(x1,y1)到(x2,y2)的线
    }
  //画SIZE+1条竖线
  for(int i=1;i<SIZE+1;i++)
    {
      paint->drawLine(margin_x+(block_size)*i,margin_y+block_size,margin_x+(block_size)*i,margin_y+(block_size)*(SIZE));
    }
  QBrush brush;
  brush.setStyle(Qt::SolidPattern);

  for(int i = 1; i <=SIZE; i ++)
    for(int j = 1; j <=SIZE; j ++)
    {
        if(gameplatform->getgame()->getMatrix(i, j)==0){
            brush.setColor(Qt::black);
            paint->setBrush(brush);
            paint->drawEllipse(margin_x + j * block_size - block_size/4,margin_y + i * block_size - block_size/4,block_size/2,block_size/2); //画椭圆：中心点X,Y,宽度，高度
        }
        else if(gameplatform->getgame()->getMatrix(i, j)==1){
            brush.setColor(Qt::white);
            paint->setBrush(brush);
            paint->drawEllipse(margin_x + j * block_size - block_size/4,margin_y + i * block_size - block_size/4,block_size/2,block_size/2); //画椭圆：中心点X,Y,宽度，高度
        }
    }

//  //在棋盘正中做一个黑棋子
//  paint->setBrush(QBrush(Qt::black,Qt::SolidPattern));//毛刷：颜色，实图案
//  paint->drawEllipse((SIZE+0.5)*WIDTH/2,(SIZE+0.5)*WIDTH/2,WIDTH/2,WIDTH/2);//画椭圆：中心点X,Y,宽度，高度
//  paint->end();                   //a model for making chesspiece

  paint->end();

}       //绘图函数的实现


void Window_Play::mousePressEvent(QMouseEvent *event)
{
    ClickPosCol = -1;
    ClickPosRow = -1;               //默认值

    int tmpx = event->x();
    int tmpy = event->y();
    if(tmpx >= margin_x + block_size / 2 && tmpx < margin_x + (block_size) * (SIZE - 1/2)
    && tmpy >= margin_y + block_size / 2 && tmpy < margin_y + (block_size) * (SIZE - 1/2) )        //棋盘边界判断
    {
        int col = (tmpx - margin_x) / block_size;
        int row = (tmpy - margin_y) / block_size;        //获取离点击点最近的棋盘点坐标(左上角)

        int leftTopx = margin_x + block_size * col;
        int leftTopy = margin_y + block_size * row; //获取左上角真实坐标


        int len = 0;        //误差值

        len = sqrt((tmpx - leftTopx) * (tmpx - leftTopx) + (tmpy - leftTopy) * (tmpy - leftTopy));
               if (len < mouse_delta)
               {
                   ClickPosRow = row;
                   ClickPosCol = col;
               }
               len = sqrt((tmpx - leftTopx - block_size) * (tmpx - leftTopx - block_size) + (tmpy - leftTopy) * (tmpy - leftTopy));
               if (len < mouse_delta)
               {
                   ClickPosRow = row;
                   ClickPosCol = col + 1;
               }
               len = sqrt((tmpx - leftTopx) * (tmpx - leftTopx) + (tmpy - leftTopy - block_size) * (tmpy - leftTopy - block_size));
               if (len < mouse_delta)
               {
                   ClickPosRow = row + 1;
                   ClickPosCol = col;
               }
               len = sqrt((tmpx - leftTopx - block_size) * (tmpx - leftTopx - block_size) + (tmpy - leftTopy - block_size) * (tmpy - leftTopy - block_size));
               if (len < mouse_delta)
               {
                   ClickPosRow = row + 1;
                   ClickPosCol = col + 1;
               }
    }   //if
    if(ClickPosCol != -1 && ClickPosRow != -1 && !gameplatform->getgame()->isEnd()) //点击有效并且没有结束游戏
    {
        if(gameplatform->getgame()->judge(ClickPosRow, ClickPosCol))
            gameplatform->getgame()->changeMatrix(ClickPosRow,ClickPosCol);
        if(gameplatform->getgame()->isEnd()){
            int state = gameplatform->getgame()->isEnd();
             QMessageBox::StandardButton reply;
             switch(state){
            case -1:
                reply = QMessageBox::information(this, "游戏结束", "黑棋胜利");
                break;
            case 1:
                reply = QMessageBox::information(this, "游戏结束", "白棋胜利");
                break;
            case 2:
                reply = QMessageBox::information(this, "游戏结束", "平局");
                break;
             }
        }
    }
    QString gameinfo = gameplatform->getgame()->getinfo().c_str();
    ui->label->setText(gameinfo);
    update();
}               //鼠标事件函数




void Window_Play::on_pushButton_5_clicked()
{
    this->close();
}       //游戏界面中Exit Game 按钮

void Window_Play::on_pushButton_6_clicked()
{
    this->close();
    Window_Start* start = new Window_Start();
    start->show();
}       //游戏界面中MainWindow按钮

void Window_Play::on_pushButton_3_clicked()
{
    if(!gameplatform->getgame()->regret())
    {
        QString gameinfo = gameplatform->getgame()->getinfo().c_str();
        gameinfo += " \nYou can't regret now!";
        ui->label->setText(gameinfo);
        ui->label->repaint();
    }
    else
    {
        QString gameinfo = gameplatform->getgame()->getinfo().c_str();
        gameinfo += " \nRegret successful!";
        ui->label->setText(gameinfo);
        ui->label->repaint();
    }
    update();

}   //游戏界面中Regret按钮

void Window_Play::on_pushButton_4_clicked()
{
    gameplatform->restartGame();
    msgFirst = false;
    update();
}   //游戏界面中Restart按钮

void Window_Play::on_pushButton_clicked()
{
    gameplatform->getgame()->saveGame(goGameBase::Binary);
}   //游戏界面中Save按钮



void Window_Play::on_pushButton_2_clicked()
{
    gameplatform->getgame()->loadGame(goGameBase::Binary);
    gameplatform->getgame()->updateMatrixTotal();

    QString gameinfo = gameplatform->getgame()->getinfo().c_str();
    gameinfo += " \nLoad Successful!";
    ui->label->setText(gameinfo);
    ui->label->repaint();
    update();
}   //游戏界面中Load按钮
