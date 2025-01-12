#include "picview.h"
#include "ui_picview.h"

#include <QPixmap>
#include <QPainter>

PicView::PicView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicView)
{
    ui->setupUi(this);
}

PicView::~PicView()
{
    delete ui;
}

void PicView::paintEvent(QPaintEvent *paintEvent)
{

}

void PicView::ShowPic(QPixmap pix)
{
    this->m_pPix=pix;
    this->show();
}


