#ifndef PICVIEW_H
#define PICVIEW_H

#include <QWidget>
#include <QToolBar>
#include <QMenu>
#include <qapplication.h>
#include "util.h"
#include <QDir.h>
#include "textshowdialog.h"
#include "qtimer.h"

namespace Ui {
class PicView;
}

class Shape;
class ShapeRect;

class PicView : public QWidget
{
    Q_OBJECT

public:
    explicit PicView(QWidget *parent = nullptr);
    PicView(QPixmap pixmap, QWidget* parent = nullptr);
    ~PicView();
    void paintEvent(QPaintEvent* event);
    void ShowPic(QPixmap pixmap);
    void mousePressEvent(QMouseEvent* event)override;
    void mouseMoveEvent(QMouseEvent*event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;
    void inputMethodEvent(QInputMethodEvent* event)override;
    void mouseDoubleClickEvent(QMouseEvent* event)override;

    void closeEvent(QCloseEvent* event)override;
    void wheelEvent(QWheelEvent* event)override;

    void focusOutEvent(QFocusEvent* event)override;
    void focusInEvent(QFocusEvent* event)override;

    void leaveEvent(QEvent* event)override; //鼠标移出窗口事件
    void enterEvent(QEvent* event)override; //鼠标移入窗口事件

    void keyPressEvent(QKeyEvent* event)override; //文字识别中的英文输入
    bool eventFilter(QObject* obj, QEvent* event)override;

    //override的作用:
    //发现错误，当你重写父类函数函数名错误时，若不加override,你可能重写错了，产生你不知道奇怪的bug
    //而添加override在编译时，就会提供静态检查
private:
    Ui::PicView *ui;
    QPixmap m_pixmap;
    QToolBar m_toolbar;
    bool m_dragging;
    QPoint m_offset;
    QMenu* m_menu;
    double m_zoomFactor;//实现图片的放大缩小
    QFont m_font;
    TextShowDialog* m_textShowDialog;
    //输入光标
    QTimer* m_timer;
    bool m_bCursorVisible;
    int m_nInputH;

    //图片矩形绘制
    bool m_bDrawRectStart;

    //圆形绘制
    bool m_bDrawEllipse;

    //直线绘制
    bool m_bDrawLine;

    //文字输入
    bool m_bInputText;

    //绘制图形的放大与缩小
    double m_scale;

    //图片的长宽比
    double m_aspectRatio;

    //原因大小
    QSize m_size;
    void undo(); //撤销
    void redo(); //恢复

    QList<Shape*>m_shapeList;
    QList<Shape*>m_redoShapeList;
    void snapshot();
};

#endif // PICVIEW_H
