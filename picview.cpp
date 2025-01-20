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
    m_toolbar(new QToolBar(this)),
    QWidget(parent),
    ui(new Ui::PicView())
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction* action1 = new QAction("关闭", this);
    connect(action1, &QAction::triggered, this, &QWidget::close);
    this->addAction(action1);
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
        qDebug() << event->button();
        move(event->globalPos() - m_offset);
        event->accept();
    }
}

void PicView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = false;
        //当前事件已经被处理，不喜欢该事件在传播给其他事件处理器
        event->accept();
    }
}
