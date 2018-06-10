#include "gogameui.h"
#include "ui_gogameui.h"

goGameUI::goGameUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::goGameUI)
{
    ui->setupUi(this);
}

goGameUI::~goGameUI()
{
    delete ui;
}
