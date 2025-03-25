#include "picview.h"
#include "snipasteapp.h"
#include "ui_picview.h"

#include <QPixmap>
#include <QPainter>
#include <QScreen>
#include <QDebug>
#include <QClipboard>
#include <QFileDialog>
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
    //this->setAttribute(Qt::WA_DeleteOnClose);
    //设置无边框,保持顶部窗口状态
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
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
    this->addAction(action1);
    this->addAction(action2);
    this->addAction(action3);

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
    qDebug() << "fixed display drawing";
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_pixmap);
    QPen pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);
    //绘制截图边框
    painter.drawRect(0, 0, m_pixmap.width()-1,m_pixmap.height()-1);
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
    qDebug() << "pixels were null";
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

void PicView::focusOutEvent(QFocusEvent* event)
{
    event->ignore();
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
