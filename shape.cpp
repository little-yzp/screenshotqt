#include "shape.h"

Shape::Shape(QObject* obj):
	QObject(obj),
	m_topLeft(0,0),
	m_rightBottom(0,0)
{

}
Shape::~Shape()
{

}
ShapeRect::ShapeRect(QObject*obj)
{

}
ShapeRect::~ShapeRect()
{
}

ShapeEillpse::~ShapeEillpse()
{
}
ShapeEillpse::ShapeEillpse(QObject* parent)
{

}
