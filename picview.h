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
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent*event);
    void mouseRelaseEvent(QMouseEvent* event);
    void contextMenuEvent(QContextMenuEvent* event);
private:
    Ui::PicView *ui;
    QPixmap m_pixmap;
    QToolBar m_toolbar;
    bool m_dragging;
    QPoint m_offset;
    QMenu *m_menu;
    
};

#endif // PICVIEW_H
