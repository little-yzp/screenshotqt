#include "tipwh.h"
#include "ui_tipwh.h"

Tipwh::Tipwh(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tipwh)
{
    ui->setupUi(this);
    
}

Tipwh::~Tipwh()
{
    delete ui;
}

void Tipwh::Refresh(int width, int height)
{
    ui->lwidth->setText(QString("%1").arg(width));
    ui->lheight->setText(QString("%1").arg(height));
}
