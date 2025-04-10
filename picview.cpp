﻿#include "picview.h"
#include "snipasteapp.h"
#include "ui_picview.h"

#include <QPixmap>
#include <QPainter>
#include <QScreen>
#include <QDebug>
#include <QClipboard>
#include <QFileDialog>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <qpropertyanimation.h>

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
    m_zoomFactor(1.0),
    ui(new Ui::PicView())
{
    ui->setupUi(this);
    //this->setAttribute(Qt::WA_DeleteOnClose);
    //设置无边框,保持顶部窗口状态
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Window);

    m_menu = new QMenu(this);

    QAction* action1 = new QAction("close", this);
    QAction* action2 = new QAction("save", this);
    QAction* action3 = new QAction("copy to clipboard", this);
    connect(action1, &QAction::triggered, this, &QWidget::close);
    connect(action2, &QAction::triggered, this, [&]() {
        QString FullPathName=QFileDialog::getSaveFileName(nullptr,"picture saving",SnipasteApp::getLastOpenDir(),tr("*.png"));
        if (FullPathName.isEmpty())
        {
            return;
        }
        m_pixmap.save(FullPathName);
        SnipasteApp::setLastOpenDir(FullPathName.left(FullPathName.lastIndexOf('/')));
        this->close();
        });
    connect(action3, &QAction::triggered, this, [&]() {
        QApplication::clipboard()->setPixmap(m_pixmap);
        this->close();
        });
    m_menu->addAction(action1);
    m_menu->addAction(action2);
    m_menu->addAction(action3);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &QWidget::customContextMenuRequested, this, [&](const QPoint &pos) {
        m_menu->exec(mapToGlobal(pos));
        });

    m_menu->setWindowFlags(m_menu->windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    //translucent 透明的,通过透明可实现圆角
    m_menu->setAttribute(Qt::WA_TranslucentBackground, true);

    //blurEffect模糊效果 DropShadowEffect阴影效果
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#444444"));
    shadow->setBlurRadius(10);
    m_menu->setGraphicsEffect(shadow);

    this->installEventFilter(this);
}

PicView::~PicView()
{
    qDebug() << "picview obj were deleted"<<this->winId();
    delete ui;
}

void PicView::InitToolBar()
{
}

void PicView::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPixmap scaledPixmap = m_pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaledPixmap);
    QPen pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);
    //绘制截图边框
    painter.drawRect(0, 0, this->width()-1,this->height()-1);
}


void PicView::ShowPic(QPixmap pixmap)
{
    this->m_pixmap = pixmap;
    if (!m_pixmap.isNull())
    {
        this->setMinimumSize(pixmap.size());
		this->show();
		return;
    }
    qDebug() << "pixels were null";
}

void PicView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = true;
        m_offset = event->globalPos()-pos();
    }
}

void PicView::mouseMoveEvent(QMouseEvent* event)
{
    if (m_dragging)
    {
        qDebug() << event->button();
        move(event->globalPos() - m_offset);
    }
    //边界检测
    const int borderWidth = 5;
    QRect innerRect = rect().adjusted(borderWidth, borderWidth, -borderWidth, -borderWidth);

    if (!innerRect.contains(event->pos()))
    {
        qDebug() << "Mouse is on the border";
    }
    else
    {
        qDebug() << "Mouse is inside";
    }  
}

void PicView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = false;
    }
}

void PicView::focusOutEvent(QFocusEvent* event)
{
    
}

void PicView::focusInEvent(QFocusEvent* event)
{
    
}

void PicView::leaveEvent(QEvent* event)
{
    clearFocus();
}

void PicView::enterEvent(QEvent* event)
{
    setFocus();
}

bool PicView::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::ContextMenu)
    {
        QMenu* menu = qobject_cast<QMenu*>(obj);
        if (menu!=nullptr)
        {
            menu->setWindowFlags(menu->windowFlags() | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
            menu->setAttribute(Qt::WA_TranslucentBackground, true);
            QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
            shadow->setOffset(0, 0);
            shadow->setColor(QColor("#444444"));
        }
    }
    return false;
}

void PicView::closeEvent(QCloseEvent* event)
{
    //在静态数组中找到这个然后删除
    for (PicView* item:TransparentMask::s_picList)
    {
        if (item == this)
        {
            TransparentMask::s_picList.removeAll(this);
        }
    }
    if (this != nullptr)
    {
        this->deleteLater();
    }
    QWidget::closeEvent(event);
}

void PicView::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers() & Qt::ControlModifier)
    {
        int incrementHValue = static_cast<int>(height() * 0.1);
        int incrementWValue = static_cast<int>(width() * 0.1);

        int incrementH = event->angleDelta().y() > 0 ? incrementHValue : 0 - incrementHValue;
        int incrementW = event->angleDelta().y() > 0 ? incrementWValue : 0 - incrementWValue;
        int newH = incrementH + this->height();
        int newW = incrementW + this->width();


        //保持窗口中心位置不变
        QPoint oldCenter = geometry().center();
        resize(newW, newH);
        QRect newGeometry = geometry();
        newGeometry.moveCenter(oldCenter);

        setGeometry(newGeometry);

        //设置平滑动画效果
        QPropertyAnimation* animation = new QPropertyAnimation(this, "size");
        animation->setDuration(200);
        animation->setStartValue(size());
        animation->setEndValue(QSize(newW,newH));
        animation->setEasingCurve(QEasingCurve::OutQuad);
        animation->start(QPropertyAnimation::DeleteWhenStopped);

        event->accept();
    }
}

void PicView::SetZoomFactor(double factor)
{
  
}
