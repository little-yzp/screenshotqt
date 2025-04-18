#ifndef SHAPE_H
#define SHAPE_H

#include <QPoint>
#include <QObject>

class Shape : public QObject
{
    Q_OBJECT

public:
     Shape(QObject* parent = nullptr);
    ~Shape();
    QPoint m_topLeft;
    QPoint m_rightBottom;
    
};

class ShapeRect :public Shape
{
    Q_OBJECT
public:
     ShapeRect(QObject* parent = nullptr);
    ~ShapeRect();
};

#endif // Shape_H

