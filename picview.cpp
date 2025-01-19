#include "picview.h"
#include "ui_picview.h"

#include <QPixmap>
#include <QPainter>
#include <QScreen>
#include <QDebug>
#include <QMouseEvent>

PicView::PicView(QWidget *parent) :PicView(QPixmap(), nullptr)
{
}

PicView::PicView(QPixmap pixmap, QWidget* parent) :
    m_pixmap(pixmap),
    m_dragging(false),
    m_offset(),
    m_menu(new QMenu(this)),
    m_toolbar(new QToolBar(this)),
    QWidget(parent),
    ui(new Ui::PicView)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_menu->addAction("删除",this, SLOT(close()));
}

PicView::~PicView()
{
    qDebug() << "显示被析构";
    delete ui;
}

void PicView::InitToolBar()
{
}

void PicView::paintEvent(QPaintEvent* event)
{
    qDebug() << "固定显示绘图";
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_pixmap);
}


void PicView::ShowPic(QPixmap pixmap)
{
    this->m_pixmap = pixmap;
    if (!m_pixmap.isNull())
    {
        this->setFixedSize(pixmap.size());
		this->show();
		return;
    }
    qDebug() << "截取像素为空";
}

void PicView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = true;
        m_offset = event->globalPos()-pos();
        event->accept();
    }
}

void PicView::mouseMoveEvent(QMouseEvent* event)
{
    if (m_dragging)
    {
        move(event->globalPos() - m_offset);
        event->accept();
    }
}

void PicView::mouseRelaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = false;
        //当前事件已经被处理，不喜欢该事件在传播给其他事件处理器
        event->accept();
    }
}

void PicView::contextMenuEvent(QContextMenuEvent* event)
{
    m_menu->show();
    m_menu->move(event->globalPos());
}
