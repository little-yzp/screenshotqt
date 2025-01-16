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
    ,m_shortCut(new QShortcut(QKeySequence(Qt::CTRL+Qt::ALT+Qt::Key_S),this))
{
    ui->setupUi(this);
    this->setWindowTitle(tr("透明层截取快捷键"));
    //Qt::FramelessWindowHint剔除窗口标题栏
    //Qt::Tool剔除任务栏出现的可执行程序标识
    this->setWindowFlags(this->windowFlags()|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool);
    //背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);
    //鼠标穿透,快捷键不穿透,但是此窗口不在激活后，无法拦截快捷键
    //this->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->setAttribute(Qt::WA_DeleteOnClose);
    connect(m_shortCut, &QShortcut::activated, this, [&]() {
        qDebug() << "快捷键被触发";
        emit ExeStart();
        });
    this->installEventFilter(this);

}

PicView::~PicView()
{
    delete ui;
    qDebug() << "透明膜被处理了";
}

void PicView::ShowAllScreen()
{
    QList<QScreen*>screens = qApp->screens();
    if (screens.size() < 2)
    {
        this->showMaximized();
        return;
    }
    int startX = INT_MAX;
    int startY = INT_MAX;
    int width = 0;
    int height = 0;
    for (QScreen* item : screens)
    {
        QRect firstGeometry = item->geometry();
        startX = startX < firstGeometry.left() ? startX : firstGeometry.left();
        startY = startY < firstGeometry.top() ? startY : firstGeometry.top();
        width+= item->geometry().width();
        int tmpHeight = item->geometry().height();
        height = tmpHeight > height ? tmpHeight : height;
    }
    this->setGeometry(startX, startY, width, height);
    this->showMaximized();
}

void PicView::mouseMoveEvent(QMouseEvent* event)
{
    qDebug() << event->pos();
}

bool PicView::eventFilter(QObject* obj, QEvent* event)
{
 if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && keyEvent->key() == Qt::Key_S) {
                qDebug() << "CTRL+SHIFT+S shortcut detected";
                return true; // 事件已处理，不再传递给原对象
            }
        }
    return QObject::eventFilter(obj,event);
}


