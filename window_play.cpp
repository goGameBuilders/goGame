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
    ui->centralwidget->setMouseTracking(true);
    ui->label->setMouseTracking(true);
    setMouseTracking(true);
}

Window_Play::~Window_Play()
{
    delete ui;
}

void Window_Play::paintEvent(QPaintEvent *)
{
  paint=new QPainter(this);
  paint->begin(this);//主窗口
  this->setMouseTracking(true);
  paint->setRenderHint(QPainter::Antialiasing, true);   //抗锯齿

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

  // 绘制落子标记
     if (nowPosCol > 0 && nowPosRow <= SIZE &&
         nowPosRow > 0 && nowPosCol <= SIZE &&
         gameplatform->getgame()->getMatrix(nowPosRow, nowPosCol) == -1)
     {
         if (gameplatform->getgame()->getWhoTurn())
             brush.setColor(QColor(0, 0, 0, 150));
         else
             brush.setColor(QColor(255, 255, 255, 150));

         paint->setBrush(brush);

         if(isPointed)
            paint->drawEllipse(margin_x + nowPosCol * block_size - block_size/4,margin_y + nowPosRow * block_size - block_size/4,block_size/2,block_size/2);
         else
            paint->drawEllipse(nowPosx_accurate - block_size/4,nowPosy_accurate - block_size/4,block_size/2,block_size/2);
     }



  for(int i = 1; i <=SIZE; i ++)
    for(int j = 1; j <=SIZE; j ++)
    {
        if(gameplatform->getgame()->getMatrix(i, j)==0){
            brush.setColor(QColor(0, 0, 0, 255));
            paint->setBrush(brush);
            paint->drawEllipse(margin_x + j * block_size - block_size/4,margin_y + i * block_size - block_size/4,block_size/2,block_size/2); //画椭圆：中心点X,Y,宽度，高度
        }
        else if(gameplatform->getgame()->getMatrix(i, j)==1){
            brush.setColor(QColor(255, 255, 255, 255));
            paint->setBrush(brush);
            paint->drawEllipse(margin_x + j * block_size - block_size/4,margin_y + i * block_size - block_size/4,block_size/2,block_size/2); //画椭圆：中心点X,Y,宽度，高度
        }
    }

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
        if(gameplatform->getgame()->judge(ClickPosRow, ClickPosCol)){
            gameplatform->getgame()->changeMatrix(ClickPosRow,ClickPosCol);
            bool state = IsEnd();
            if(gameplatform->isPVE()&&!state){
                int xy = gameplatform->getgameAI()->valueAll();
                gameplatform->getgame()->changeMatrix(xy/100, xy%100);
                IsEnd();
            }
        }

    }
    QString gameinfo = gameplatform->getgame()->getinfo().c_str();
    ui->label->setText(gameinfo);
    update();
}               //鼠标点击事件函数


void Window_Play::mouseMoveEvent(QMouseEvent *event)
{
    int tmpx = event->pos().x();
    int tmpy = event->pos().y();
    nowPosx_accurate = event->pos().x();
    nowPosy_accurate = event->pos().y();
    isPointed = false;
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
                   nowPosRow = row;
                   nowPosCol = col;
                   isPointed = true;
               }
               len = sqrt((tmpx - leftTopx - block_size) * (tmpx - leftTopx - block_size) + (tmpy - leftTopy) * (tmpy - leftTopy));
               if (len < mouse_delta)
               {
                   nowPosRow = row;
                   nowPosCol = col + 1;
                   isPointed = true;
               }
               len = sqrt((tmpx - leftTopx) * (tmpx - leftTopx) + (tmpy - leftTopy - block_size) * (tmpy - leftTopy - block_size));
               if (len < mouse_delta)
               {
                   nowPosRow = row + 1;
                   nowPosCol = col;
                   isPointed = true;
               }
               len = sqrt((tmpx - leftTopx - block_size) * (tmpx - leftTopx - block_size) + (tmpy - leftTopy - block_size) * (tmpy - leftTopy - block_size));
               if (len < mouse_delta)
               {
                   nowPosRow = row + 1;
                   nowPosCol = col + 1;
                   isPointed = true;
               }

    }   //if

    else
    {
        nowPosRow = -1;
        nowPosCol = -1;
    }

     update();

}



bool Window_Play::IsEnd(){
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
         return true;
    }
    return false;
}


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
    bool whetherEnd=false;
    if(gameplatform->getgame()->isEnd()){whetherEnd=true;}

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
    QString dir = QFileDialog::getExistingDirectory(this, "Open Directory",
                               "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    gameplatform->getgame()->saveGame(goGameBase::Binary, dir);

    QString gameinfo = gameplatform->getgame()->getinfo().c_str();
    gameinfo += " \nSave Successful!";
    ui->label->setText(gameinfo);
    ui->label->repaint();
    update();

}   //游戏界面中Save按钮



void Window_Play::on_pushButton_2_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Open Directory",
                               "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(gameplatform->getgame()->loadGame(goGameBase::Binary, dir))
    {
        QString gameinfo = gameplatform->getgame()->getinfo().c_str();
        gameinfo += " \nLoad Successful!";
        ui->label->setText(gameinfo);
        ui->label->repaint();
        gameplatform->getgame()->updateMatrixTotal();
    }
    else
    {
        QString gameinfo = gameplatform->getgame()->getinfo().c_str();
        gameinfo += " \nCan't find the save file in this path!";
        ui->label->setText(gameinfo);
        ui->label->repaint();
    }
    update();
}   //游戏界面中Load按钮
