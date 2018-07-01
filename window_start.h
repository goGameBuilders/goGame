#ifndef WINDOW_START_H
#define WINDOW_START_H

#include <QMainWindow>
#include "goGamePlatform.h"
namespace Ui {
class Window_Start;
}

class Window_Start : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_Start(QWidget *parent = 0);
    ~Window_Start();

private slots:
    void on_pushButton_3_clicked();

    void on_actionExit_2_triggered();

    void on_pushButton_clicked();

private:
    Ui::Window_Start *ui;
    goGamePlatform* gameplatform;
};

#endif // WINDOW_START_H
