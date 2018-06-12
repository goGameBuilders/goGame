#include "window_play.h"
#include "ui_window_play.h"

#include <QWidget>
#include <QtWidgets>
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
  if(ClickPosCol != -1 && ClickPosRow != -1)
  {
      if(gameplatform->getgame()->judge(ClickPosRow, ClickPosCol))
          gameplatform->getgame()->changeMatrix(ClickPosRow,ClickPosCol);
    }
  QBrush brush;
  brush.setStyle(Qt::SolidPattern);

  for(int i = 1; i <=SIZE; i ++)
    for(int j = 1; j <=SIZE; j ++)
    {
        if(gameplatform->getgame()->getMatrix(i, j)==0){
            paint->save();
             brush.setColor(Qt::black);
             paint->setBrush(brush);
             paint->drawEllipse(margin_x + j * block_size - block_size/4,margin_y + i * block_size - block_size/4,block_size/2,block_size/2); //画椭圆：中心点X,Y,宽度，高度
            paint->restore();
        }
        else if(gameplatform->getgame()->getMatrix(i, j)==1){
            paint->save();
            brush.setColor(Qt::white);
            paint->setBrush(brush);
            paint->drawEllipse(margin_x + j * block_size - block_size/4,margin_y + i * block_size - block_size/4,block_size/2,block_size/2); //画椭圆：中心点X,Y,宽度，高度
            paint->restore();
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
    int tmpx = event->x();
    int tmpy = event->y();
    if(tmpx >= margin_x + block_size / 2 && tmpx < margin_x + (block_size) * (SIZE - 1/2)
    && tmpy >= margin_y + block_size / 2 && tmpy < margin_y + (block_size) * (SIZE - 1/2) )        //棋盘边界判断
    {
        int col = (tmpx - margin_x) / block_size;
        int row = (tmpy - margin_y) / block_size;        //获取离点击点最近的棋盘点坐标(左上角)

        int leftTopx = margin_x + block_size * col;
        int leftTopy = margin_y + block_size * row; //获取左上角真实坐标

        ClickPosCol = -1;
        ClickPosRow = -1;               //默认值

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
    update();
}










