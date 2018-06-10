#ifndef WINDOW_PLAY_H
#define WINDOW_PLAY_H

#include <QMainWindow>

namespace Ui {
class Window_Play;
}

class Window_Play : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_Play(QWidget *parent = 0);
    ~Window_Play();

    void paintEvent(QPaintEvent *);         //绘图函数声明
    void mousePressEvent(QMouseEvent *event);    //监视鼠标移动情况函数


private:
    Ui::Window_Play *ui;
    const int SIZE = 10;           //棋盘大小
    const int block_size = 40;     //棋盘格子间宽度
    const int margin_x = 20;       //棋盘起始x坐标(边界值)
    const int margin_y = 20;       //棋盘起始y坐标(边界值)
    const int mouse_delta = 10;    //判定有效点击的最小误差
    int ClickPosRow = -1;          //鼠标点击的行数
    int ClickPosCol = -1;          //鼠标点击的列数

    //-------for test------------
    int borw = 0;
    //---------------------------

    QPainter *paint;
};

#endif // WINDOW_PLAY_H
