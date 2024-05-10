#include "info.h"
#include "ui_info.h"

Info::Info(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Info)
{
    ui->setupUi(this);
    setFixedSize(300, 350);
}

Info::~Info()
{
    delete ui;
}
