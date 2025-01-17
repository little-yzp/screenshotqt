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
private:
    Ui::PicView *ui;
};

#endif // PICVIEW_H
