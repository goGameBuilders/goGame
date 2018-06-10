#ifndef GOGAMEUI_H
#define GOGAMEUI_H

#include <QMainWindow>

namespace Ui {
class goGameUI;
}

class goGameUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit goGameUI(QWidget *parent = 0);
    ~goGameUI();

private:
    Ui::goGameUI *ui;
};

#endif // GOGAMEUI_H
