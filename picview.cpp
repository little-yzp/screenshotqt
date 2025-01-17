#include "picview.h"
#include "ui_picview.h"

#include <QPixmap>
#include <QPainter>
#include <QScreen>
#include <QDebug>
#include <QMouseEvent>

PicView::PicView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicView)
{
    ui->setupUi(this);
    //Qt::FramelessWindowHint剔除窗口标题栏
    //Qt::Tool剔除任务栏出现的可执行程序标识
    this->setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->installEventFilter(this);

}

PicView::~PicView()
{
    delete ui;
}

