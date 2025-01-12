#ifndef PICVIEW_H
#define PICVIEW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPixmap;
QT_END_NAMESPACE
namespace Ui {
class PicView;
}

class PicView : public QWidget
{
    Q_OBJECT

public:
    explicit PicView(QWidget *parent = nullptr);
    ~PicView();
    void paintEvent(QPaintEvent *paintEvent)override;
    void ShowPic(QPixmap pix);

private:
    Ui::PicView *ui;
    QPixmap m_pPix;
};

#endif // PICVIEW_H
