#include <QApplication>
#include <iostream>
#include <stdlib.h>
#include <QtCore>
#include <QWidget>
#include <QtWidgets>
#include <QDebug>

#include "window_play.h"
#include "window_select.h"
#include "window_start.h"
#include "goGameBase.h"
#include "difGame.h"
#include "style.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    CommonHelper::setStyle(":/MyStyles/WhiteStyle.qss");       //加载qss样式

//    QPixmap pixmap(50, 50);
//    pixmap.fill(Qt::transparent);
//    QPainter p(&pixmap);
//    p.setRenderHint(QPainter::Antialiasing, true);
//    p.setPen(QPen(Qt::darkMagenta,3,Qt::SolidLine));//钢笔工具：颜色，线号，实线
//    QBrush brush;
//    brush.setStyle(Qt::SolidPattern);
//    brush.setColor(QColor(255, 255, 255, 150));
//    p.setBrush(brush);
//    p.drawEllipse(5, 5, 40, 40);
//    pixmap.save("yourIamgeFile", "png");
//    p.end();                                          //画png的结构

    Window_Start* mainwindow = new Window_Start();
    mainwindow->show();


    return a.exec();
}

