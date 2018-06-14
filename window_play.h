#ifndef WINDOW_PLAY_H
#define WINDOW_PLAY_H
#include "goGamePlatform.h"
#include <QMainWindow>

namespace Ui {
class Window_Play;
}

class Window_Play : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_Play(goGamePlatform* _gameplatform,QWidget *parent = 0);
    ~Window_Play();

    void paintEvent(QPaintEvent *);         //绘图函数声明
    void mousePressEvent(QMouseEvent *event);    //监视鼠标点击情况函数
    void mouseMoveEvent(QMouseEvent *event);    //监视鼠标移动状况函数


private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Window_Play *ui;
    goGamePlatform* gameplatform;
    const int SIZE = 10;           //棋盘大小
    const int block_size = 40;     //棋盘格子间宽度
    const int margin_x = 20;       //棋盘起始x坐标(边界值)
    const int margin_y = 20;       //棋盘起始y坐标(边界值)
    const int mouse_delta = 10;    //判定有效点击的最小误差
    int ClickPosRow = -1;          //鼠标点击的行数
    int ClickPosCol = -1;          //鼠标点击的列数
    int nowPosRow = -1;            //目前鼠标所在行数
    int nowPosCol = -1;            //目前鼠标所在列数
    int nowPosx_accurate = -1;  //目前鼠标所在位置x(精确)
    int nowPosy_accurate = -1;  //目前鼠标所在位置y(精确)

    bool msgFirst = false;         //是否已经显示起始信息
    bool isPointed = false;        //鼠标是否在格点上
    QPainter *paint;
};

#endif // WINDOW_PLAY_H
