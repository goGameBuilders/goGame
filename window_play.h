#ifndef WINDOW_PLAY_H
#define WINDOW_PLAY_H
#include "goGamePlatform.h"

#include <QMainWindow>
#include <QMap>
#include <QWidget>

QT_FORWARD_DECLARE_CLASS(QPropertyAnimation)

namespace Ui {
class Window_Play;
}

class Window_Play : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(qreal transformY READ transformY WRITE setTransformY NOTIFY transformYChanged)

public:
    explicit Window_Play(goGamePlatform* _gameplatform, int gameType , QWidget *parent = 0);
    ~Window_Play();

    //------------------------动画有关-----------------------//
    QPixmap *front() const;             //加载动画时前面一面
    QPixmap *back() const;              //加载动画时后面一面
    inline void setFront(QPixmap front);
    inline void setBack(QPixmap back);
    void start();
    //-----------------------------------------------------//

    void myPaint(QPainter* paint, int gameType);
    void myMousePress(QMouseEvent *event, int gameType);
    void myMouseMove(QMouseEvent *event, int gameType);
    void myAnimationPaint();
    void setMyAnimation();

    bool IsEnd();


private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

 signals:
    void transformYChanged();       //For animation

 protected:
    void setTransformY(qreal angle = 0);    //用来旋转一定角度
    qreal transformY() const;
    void paintEvent(QPaintEvent *);         //绘图函数声明
    void mousePressEvent(QMouseEvent *event);    //监视鼠标点击情况函数
    void mouseMoveEvent(QMouseEvent *event);    //监视鼠标移动状况函数


private:
    Ui::Window_Play *ui;
    goGamePlatform* gameplatform;
    int SIZE;           //棋盘大小
    int block_size;     //棋盘格子间宽度
    int margin_x;       //棋盘起始x坐标(边界值)
    int margin_y;       //棋盘起始y坐标(边界值)
    int mouse_delta ;    //判定有效点击的最小误差
    int ClickPosRow = -1;          //鼠标点击的行数
    int ClickPosCol = -1;          //鼠标点击的列数
    int nowPosRow = -1;            //目前鼠标所在行数
    int nowPosCol = -1;            //目前鼠标所在列数
    int nowPosx_accurate = -1;     //目前鼠标所在位置x(精确)
    int nowPosy_accurate = -1;     //目前鼠标所在位置y(精确)

    QLabel* chessPoint[10][10];     //加载黑白棋棋子的载体label

    bool msgFirst = false;         //是否已经显示起始信息
    bool isPointed = false;        //鼠标是否在格点上
    QPainter *paint;

    //--------For Animation-----------//
    qreal _angle{0};
    QPropertyAnimation *ani{nullptr};
    QTimer tm;
    QPixmap aniPng;
    QMap<QString, QPixmap> aniMap;
    bool test = 0;
    //--------------------------------//
};

#endif // WINDOW_PLAY_H
