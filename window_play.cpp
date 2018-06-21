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

Window_Play::Window_Play(goGamePlatform* _gameplatform, int gameType, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window_Play),
    gameplatform(_gameplatform)
{
    ui->setupUi(this);
    ui->centralwidget->setMouseTracking(true);
    ui->label->setMouseTracking(true);
    ui->label_reversiboard->setMouseTracking(true);
    setMouseTracking(true);
    setFixedSize(this->width(), this->height());


    if(gameType == 1 || gameType == 2)
    {
        SIZE = 10;
        block_size = 40;
        margin_x = 20;
        margin_y = 20;
        mouse_delta = 10;
    }

    else
    {
        SIZE = 9;
        block_size = 50;
        margin_x = 50;
        margin_y = 50;
        mouse_delta = 10;
        QPixmapCache::setCacheLimit(1);  //设置图片缓冲区最大容量
    }


    //--------------For Animation-------------------//
    ani = new QPropertyAnimation(this,"transformY",this);
    ani->setDuration(3000);
    ani->setStartValue(0);
    ani->setEndValue(180);
    ani->setEasingCurve(QEasingCurve::InCurve);
    connect(ani,&QPropertyAnimation::finished,[&]{ani->setDirection(QPropertyAnimation::Direction(!ani->direction()));});
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

 myPaint(paint, 1);


  paint->end();

}       //绘图函数的实现


void Window_Play::mousePressEvent(QMouseEvent *event)
{
    myMousePress(event, 1);
}               //鼠标点击事件函数


void Window_Play::mouseMoveEvent(QMouseEvent *event)
{

    myMouseMove(event, 1);
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
    QMessageBox::StandardButton reply;

      reply = QMessageBox::question(this,
                            "My Title",
                              "Do you really want to quit?",
                            QMessageBox::No | QMessageBox::Yes);
      if(reply == QMessageBox::Yes)
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

    QString dir = QFileDialog::getOpenFileName(this, "Open Directory",
                               "./","Saves(*.dat)");        //只可以打开dat文件

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


void Window_Play::myPaint(QPainter *paint, int gameType)
{
    if(gameType == 1 || gameType == 2)
    {

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
    }//if                   //五子棋、围棋绘图函数

    if(gameType == 3)
    {
        if(!msgFirst)
        {
            QString gameinfo = gameplatform->getgame()->getinfo().c_str();
            ui->label->setText(gameinfo);
            msgFirst = true;
            ui->label_reversiboard->setPixmap(QPixmap(":/MyChessPng/ResourcesForReversi/ReversiBoard.png"));
            ui->label_reversiboard->show(); //绘制棋盘
            for(int i = 0; i <= SIZE; i++)
                for(int j = 0; j <=SIZE; j++)
                    if(chessPoint[i][j] == nullptr)
                        delete chessPoint[i][j];
            for(int i = 0; i < SIZE - 1; i++)
                for(int j = 0; j< SIZE - 1; j++)
                {
                    chessPoint[i][j] = new QLabel();
                    chessPoint[i][j]->setGeometry(margin_x + block_size * i, margin_y + block_size * j, block_size, block_size);
                    chessPoint[i][j]->setParent(this);
                    chessPoint[i][j]->setMouseTracking(true);
                    chessPoint[i][j]->show();
                }
        }               //以上为第一次初始化发生的事件

//        // 绘制落子标记
//           if (nowPosCol > 0 && nowPosRow <= SIZE &&
//               nowPosRow > 0 && nowPosCol <= SIZE &&
//               gameplatform->getgame()->getMatrix(nowPosRow, nowPosCol) == -1)
//           {
//               QPixmap tmpPix;
//               if (gameplatform->getgame()->getWhoTurn())
//                   tmpPix.load(":/MyChessPng/ResourcesForReversi/ReversiBlack_Trans.png");
//               else
//                   tmpPix.load(":/MyChessPng/ResourcesForReversi/ReversiWhite_Trans.png");

//               chessPoint[nowPosRow][nowPosCol]->setPixmap(tmpPix);

//               if(isPointed)
//                  chessPoint[nowPosRow][nowPosCol]->show();
//           }


       //绘制落子标记
        if(nowPosCol > 0 && nowPosRow <= SIZE - 1 &&
           nowPosRow > 0 && nowPosCol <= SIZE - 1)
        {
            for(int i = 0; i < SIZE - 1; i++)
                for(int j = 0; j < SIZE - 1; j++)
                {
                    if(i == nowPosRow && j == nowPosCol)
                    {
                        QPixmap tmpPix;
                        if (gameplatform->getgame()->getWhoTurn())
                            tmpPix.load(":/MyChessPng/ResourcesForReversi/ReversiBlack_Trans.png");
                        else
                            tmpPix.load(":/MyChessPng/ResourcesForReversi/ReversiWhite_Trans.png");
                       if(isPointed)
                        {
                           chessPoint[nowPosRow][nowPosCol]->setPixmap(tmpPix);
                           continue;
                        }
                       else
                        continue;
                    }
                    else
                    {
                        chessPoint[i][j]->clear();
                    }
                }
        }




    }
}       //不同游戏种类的不同绘制函数逻辑



void Window_Play::myMousePress(QMouseEvent *event, int gameType)
{
    if(gameType == 1 || gameType == 2)
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
    }   //五子棋、围棋鼠标按下函数

    if(gameType == 3)
    {

    }   //黑白棋鼠标按下函数


}       //不同种类游戏的不同鼠标按下后的逻辑





void Window_Play::myMouseMove(QMouseEvent *event, int gameType)
{
    if(gameType == 1 || gameType == 2)
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
    }       //围棋、五子棋跟随鼠标移动逻辑

    if(gameType == 3)
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




    }       //黑白棋跟随鼠标移动逻辑
}       //不同种类的棋子的鼠标移动逻辑






//---------------For Animation------------------------------//
inline void Window_Play::setFront(QPixmap front)
{
    if(!front)
        return ;
    aniMap["front"] = front;    //添加前面图片部分
}

inline void Window_Play::setBack(QPixmap back)
{
    if(!back)
        return ;
    aniMap["back"] = back;     //添加后面图片部分
}

void Window_Play::setTransformY(qreal angle)
{
    if(aniMap.count() != 2)
    {
        QMessageBox::information(this, "Error!", "Something does not work well with the animation effect, please contact the devolper::heguande17@163.com");
        return ;
    }

    if(angle != _angle)
        emit transformYChanged();
    _angle = angle;
    update();
}

qreal Window_Play::transformY() const
{
    return _angle;
}

void Window_Play:: myAnimationPaint()
{

    if(_angle > 90)
    {
        aniPng = aniMap.value("back");
    }
    else
    {
        aniPng = aniMap.value("front");
    }

   // anipaint = new QPainter(this);
    QTransform fm;
    fm.translate(aniPng.width() >> 1, 0);
    fm.rotate(_angle, Qt::YAxis);
    fm.translate(-aniPng.width() >> 1, 0);
//    anipaint->setTransform(fm);
//    anipaint->drawPixmap(10, 10, 40, 40, aniPng);
    update();
}

void Window_Play::start()
{
    ani->start();
}

void Window_Play::setMyAnimation()
{
    setFront(QPixmap(":/MyChessPng/ChessForReversi/BlackForReversi.png"));
    setBack(QPixmap(":/MyChessPng/ChessForReversi/WhiteForReversi.png"));
    tm.setInterval(3500);
    QObject::connect(&tm, &QTimer::timeout, [&]{this->start();});
    tm.start();
}






