#ifndef PICVIEW_H
#define PICVIEW_H

#include <QWidget>
#include <QToolBar>
#include <QMenu>

namespace Ui {
class PicView;
}

class PicView : public QWidget
{
    Q_OBJECT

public:
    explicit PicView(QWidget *parent = nullptr);
    PicView(QPixmap pixmap, QWidget* parent = nullptr);
    ~PicView();
    void InitToolBar();
    void paintEvent(QPaintEvent* event);
    void ShowPic(QPixmap pixmap);
    void mousePressEvent(QMouseEvent* event)override;
    void mouseMoveEvent(QMouseEvent*event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;

    void closeEvent(QCloseEvent* event)override;
    void wheelEvent(QWheelEvent* event)override;

    void focusOutEvent(QFocusEvent* event)override;
    void focusInEvent(QFocusEvent* event)override;

    void leaveEvent(QEvent* event)override; //鼠标移出窗口事件
    void enterEvent(QEvent* event)override; //鼠标移入窗口事件
    //override的作用:
    //发现错误，当你重写父类函数函数名错误时，若不加override,你可能重写错了，产生你不知道奇怪的bug
    //而添加override在编译时，就会提供静态检查
private:
    Ui::PicView *ui;
    QPixmap m_pixmap;
    QToolBar m_toolbar;
    bool m_dragging;
    QPoint m_offset;
    double m_zoomFactor;//实现图片的放大缩小

    void SetZoomFactor(double factor);
   
};

#endif // PICVIEW_H
