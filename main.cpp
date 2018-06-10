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


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Window_Start* mainwindow = new Window_Start();
    mainwindow->show();


    return a.exec();
}

