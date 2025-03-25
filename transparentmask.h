#pragma once

#include <QMainWindow>
#include <QMouseEvent>
#include <QPixmap>
#include <QToolBar>
#include "picview.h"
#include "ui_transparentmask.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TransparentMaskClass; };
QT_END_NAMESPACE



class TransparentMask : public QWidget
{
	Q_OBJECT

public:
	
	static QList<PicView*>s_picList;
	TransparentMask(QWidget *parent = nullptr);
	~TransparentMask();
	void setBgColor(const QColor& color);
	void mousePressEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void paintEvent(QPaintEvent* event)override;
	void Hide();
	bool eventFilter(QObject* obj, QEvent* event)override;
private:
	Ui::TransparentMaskClass *ui;
	QPoint m_prePoint;
	QPoint m_endPoint;
	bool m_bReleaseFlag;
	bool m_bIsMovingFlag;
	QPixmap m_pixmap;//整个屏幕
	QPixmap m_targetPixmap;//最终的截图区域

	void DrawTransparentRect(QPainter* painter);
	QRect handler(QPoint a, QPoint b);
	void ShowAllScreen();
private slots:
	void ShowPic(QPixmap pic);
	void SavePic(QString path);
	void ClipPic();
	void PinPic();
signals:
	void FinishShot(QRect rect);
	void ScreenShotStart();
};
