#include "gogameui.h"
#include <QApplication>
#include <iostream>
#include <stdlib.h>
#include "goGameBase.h"
#include "difGame.h"
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    goGameUI w;
    w.show();

    return a.exec();
}

