#ifndef WINDOW_SELECT_H
#define WINDOW_SELECT_H

#include <QDialog>
#include "goGamePlatform.h"
namespace Ui {
class Window_Select;
}

class Window_Select : public QDialog
{
    Q_OBJECT

public:
    explicit Window_Select(goGamePlatform* _game, QWidget *parent = 0);
    ~Window_Select();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::Window_Select *ui;
    int myvsWho = 2; //人机还是人人
    goGamePlatform* gameplatform;
};

#endif // WINDOW_SELECT_H
