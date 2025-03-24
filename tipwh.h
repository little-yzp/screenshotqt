#ifndef TIPWH_H
#define TIPWH_H

#include <QWidget>

namespace Ui {
class Tipwh;
}

class Tipwh : public QWidget
{
    Q_OBJECT

public:
    explicit Tipwh(QWidget *parent = nullptr);
    ~Tipwh();
private slots:
    void Refresh(int width, int height);
private:
    Ui::Tipwh *ui;

};

#endif // TIPWH_H
