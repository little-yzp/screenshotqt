#ifndef PICVIEW_H
#define PICVIEW_H

#include <QWidget>
#include <QShortcut>

namespace Ui {
class PicView;
}

class PicView : public QWidget
{
    Q_OBJECT

public:
    explicit PicView(QWidget *parent = nullptr);
    ~PicView();
    void ShowAllScreen();
    void mouseMoveEvent(QMouseEvent* event);
private:
    Ui::PicView *ui;
    QShortcut *m_shortCut;
signals:
    void ExeStart();
};

#endif // PICVIEW_H
