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

private:
    Ui::Window_Select *ui;
    goGamePlatform* gameplatform;
};

#endif // WINDOW_SELECT_H
