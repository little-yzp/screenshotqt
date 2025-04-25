#include "picview.h"
#include "snipasteapp.h"
#include "shape.h"
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
#include <QApplication>

PicView::PicView(QWidget *parent) :PicView(QPixmap(), nullptr)
{
}

PicView::PicView(QPixmap pixmap, QWidget* parent) :
    m_pixmap(pixmap),
    m_dragging(false),
    m_offset(),
    m_menu(new QMenu(this)),
    m_toolbar(new QToolBar(this)),
    m_bDrawRectStart(false),
    m_bDrawEllipse(false),
    m_bDrawLine(false),
    m_bInputText(false),
    QWidget(parent),
    m_zoomFactor(1.0),
    ui(new Ui::PicView())
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    //设置无边框,保持顶部窗口状态
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Window);

    m_menu = new QMenu(this);

    QAction* action1 = new QAction("close", this);
    QAction* action2 = new QAction("save", this);
    QAction* action3 = new QAction("copy to clipboard", this);
    QAction* action4 = new QAction("draw rect", this);
    QAction* action5 = new QAction("undo", this);
    QAction* action6 = new QAction("redo", this);
    QAction* action7 = new QAction("draw Eillpse", this);
    QAction* action8 = new QAction("draw straight Line", this);
    QAction* action9 = new QAction("inputText", this);

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
        snapshot();
        });
    connect(action4, &QAction::triggered, this, [&]() {
        m_bDrawRectStart = true;
        m_bDrawEllipse = false;
        m_bDrawLine = false;
        QApplication::setOverrideCursor(Qt::CrossCursor);
        });
    connect(action5, &QAction::triggered, this, [&]() {
        undo();
        });
    connect(action6, &QAction::triggered, this, [&]() {
        redo();
        });
    connect(action7, &QAction::triggered, this, [&]() {
        m_bDrawEllipse = true;
        m_bDrawRectStart = false;
        m_bDrawLine = false;
        QApplication::setOverrideCursor(Qt::CrossCursor);

        });
    connect(action8, &QAction::triggered, this, [&]() {
        m_bDrawLine = true;
        m_bDrawRectStart = false;
        m_bDrawEllipse = false;
        QApplication::setOverrideCursor(Qt::CrossCursor);
        });
    connect(action9, &QAction::triggered, this, [&]() {
        m_bInputText = true;
        m_bDrawLine = false;
        m_bDrawRectStart = false;
        m_bDrawEllipse = false;
        QApplication::setOverrideCursor(Qt::CrossCursor);
        });

    m_menu->addAction(action1);
    m_menu->addAction(action2);
    m_menu->addAction(action3);
    m_menu->addSeparator();
    m_menu->addAction(action7);
    m_menu->addAction(action8);
    m_menu->addAction(action4);
    m_menu->addAction(action9);
    m_menu->addSeparator();
    m_menu->addAction(action5);
    m_menu->addAction(action6);


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

    this->setGraphicsEffect(shadow);

    this->installEventFilter(this);

    this->setWindowTitle(QString("%1").arg(this->winId()));
    this->setAttribute(Qt::WA_InputMethodEnabled, true);

}

PicView::~PicView()
{
    qDebug() << "picview obj were deleted"<<this->winId();
    for (int i = 0; i < m_shapeList.length(); i++)
    {
        delete m_shapeList.at(i);
    }
    delete ui;
}

void PicView::InitToolBar()
{
}

void PicView::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    //Qt::KeepAspectRatio 保持长宽比,保持图片与QWidget大小一致
    QPixmap scaledPixmap = m_pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaledPixmap);
    QPen pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);

    painter.save();
    pen.setColor(Qt::green);
    painter.setPen(pen);
    //绘制截图边框
    painter.drawRect(0, 0, this->width()-1,this->height()-1);
    painter.restore();

    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int i = 0; i < m_shapeList.length(); i++)
    {
        ShapeRect* tmpRect = dynamic_cast<ShapeRect*>(m_shapeList.at(i));
        if (tmpRect != NULL)
        {
            painter.drawRect(QRect(tmpRect->m_topLeft, tmpRect->m_rightBottom));
        }

        ShapeEillpse* tmpEillpse = dynamic_cast<ShapeEillpse*>(m_shapeList.at(i));
        if (tmpEillpse != NULL)
        {
            QPointF center((tmpEillpse->m_topLeft.x() + tmpEillpse->m_rightBottom.x()) / 2.0,
                (tmpEillpse->m_topLeft.y() + tmpEillpse->m_rightBottom.y()) / 2.0);
            qreal rx = (qreal)abs(
                (tmpEillpse->m_topLeft.x() - tmpEillpse->m_rightBottom.x()) / 2.0
            );
            qreal ry = (qreal)abs(
                (tmpEillpse->m_topLeft.y() - tmpEillpse->m_rightBottom.y()) / 2.0
            );
            painter.drawEllipse(center,rx,ry);
        }
        
        ShapeLine* tmpLine = dynamic_cast<ShapeLine*>(m_shapeList.at(i));
        if (tmpLine != NULL)
        {
            painter.drawLine(tmpLine->m_topLeft, tmpLine->m_rightBottom);
        }
        ShapeText* tmpText = dynamic_cast<ShapeText*>(m_shapeList.at(i));
        if (tmpText != NULL)
        {
            qDebug() << QApplication::font();
            painter.drawRect(QRectF(tmpText->m_topLeft, QSizeF(QApplication::font().pixelSize(),QApplication::font().pixelSize())));
            painter.drawText(tmpText->m_topLeft, tmpText->text);
        }
    }  
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
       
        m_offset = event->globalPos()-pos();
        if (m_bDrawRectStart)
        {
            Shape* tmp = new ShapeRect;
            tmp->m_topLeft = event->pos();
            m_shapeList.push_back(tmp);
        }
        else if (m_bDrawEllipse)
        {
            Shape* tmp = new ShapeEillpse;
            tmp->m_topLeft = event->pos();
            m_shapeList.push_back(tmp);
        }
        else if (m_bDrawLine)
        {
            Shape* tmp = new ShapeLine;
            tmp->m_topLeft = event->pos();
            m_shapeList.push_back(tmp);
        }
        else if (m_bInputText)
        {
            Shape* tmp = new ShapeText;
            tmp->m_topLeft = event->pos();
            m_shapeList.push_back(tmp);
            update();
        }
        else
        {
            m_dragging = true;
        }
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

    if (m_bDrawRectStart)
    {
       m_shapeList.last()->m_rightBottom = event->pos();
       update();
    }
    else if (m_bDrawEllipse)
    {
        m_shapeList.last()->m_rightBottom = event->pos();
        update();
    }
    else if (m_bDrawLine)
    {
        m_shapeList.last()->m_rightBottom = event->pos();
        update();
    }
}

void PicView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = false;
        if (m_bDrawRectStart)
        {
            this->saveState();
            m_bDrawRectStart = false;
        }
        else if (m_bDrawEllipse)
        {
            m_bDrawEllipse = false;
        }
        else if (m_bDrawLine)
        {
            m_bDrawLine = false;
        }
        QApplication::restoreOverrideCursor();
    }
}

void PicView::inputMethodEvent(QInputMethodEvent* event)
{
    if (!event->commitString().isEmpty()&&m_bInputText==true)
    {
        QString text = event->commitString();
        ShapeText* tmpText = dynamic_cast<ShapeText*>(m_shapeList.last());
        if (tmpText != NULL)
        {
            tmpText->text.append(text);
            update();
        }
        
    }
    event->accept();
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
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyevent = static_cast<QKeyEvent*>(event);
        if (keyevent->key() == Qt::Key_Escape)
        {
            this->close();
        }
        if (keyevent->modifiers() == Qt::ControlModifier && keyevent->key() == Qt::Key_Z)
        {
            undo();
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

void PicView::saveState()
{
}

void PicView::undo() 
{
    if (m_shapeList.count() < 0)return;
}

void PicView::redo()
{
    update();
}

void PicView::snapshot()
{
    QScreen* screen = QGuiApplication::primaryScreen();
    if (!screen)
    {
        return;
    }
    QPixmap pixmap = screen->grabWindow(this->winId());
    QApplication::clipboard()->setPixmap(pixmap);
    this->close();
}
