#include "transparentmask.h"
#include <QDebug>
#include <QPainter>
#include <QClipboard>
#include <QScreen>
#include "staticdata.h"

TransparentMask::TransparentMask(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TransparentMaskClass())
	,m_bReleaseFlag(true)
	,m_bIsMovingFlag(false)
	,m_prePoint(0,0)
	,m_endPoint(0,0)
{
	ui->setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	//mask不设置FramelessWindowHint,ToolBar与截图区域存在间隙
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowIcon(QIcon(":/icon/icon/pic.svg"));
}

TransparentMask::~TransparentMask()
{
	delete ui;
	qDebug() << "遮罩析构";
}

void TransparentMask::setBgColor(const QColor& color)
{
	QPalette palette = this->palette();
	palette.setBrush(QPalette::Window, color);
	this->setPalette(palette);
}

void TransparentMask::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bReleaseFlag = false;
		m_prePoint=event->pos();
		emit ScreenShotStart();
	}
}

void TransparentMask::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bReleaseFlag = true;
		m_bIsMovingFlag = false;
		emit FinishShot(handler(m_prePoint,m_endPoint));
	}
}

void TransparentMask::mouseMoveEvent(QMouseEvent* event)
{
	if (m_bReleaseFlag==false)
	{
		m_endPoint = event->pos();
		m_bIsMovingFlag = true;
		update();
	}
}

void TransparentMask::ShowPic(QPixmap pix)
{
	this->m_pixmap = pix;
	this->ShowAllScreen();
	//this->showFullScreen();
}

void TransparentMask::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.drawPixmap(0,0,m_pixmap);
	painter.fillRect(this->rect(), QColor(0, 0, 0, 130));
	QPen pen(Qt::red,3);
	painter.setPen(pen);
	QBrush transparentBrush;
	transparentBrush.setColor(Qt::transparent);
	painter.setBrush(transparentBrush);
	painter.drawRect(handler(m_prePoint, m_endPoint));
	DrawTransparentRect(&painter);
}

void TransparentMask::Hide()
{
	m_prePoint = m_endPoint = QPoint(0, 0);
	this->hide();
}

void TransparentMask::DrawTransparentRect(QPainter* painter)
{
	int startX = 1, startY = 1;
	int width = 1, height = 1;//消除但选择起点与终点相同时,右下角跳出整个界面的bug
	//是一个点，一条横线和竖线时都return
	if (!(m_prePoint.x() != m_endPoint.x() && m_prePoint.y() != m_endPoint.y()))
	{
		return;
	}
	if (m_prePoint.x() > m_endPoint.x())
	{
		startX = m_endPoint.x();
		width = m_prePoint.x() - m_endPoint.x();
	}
	else
	{
		startX = m_prePoint.x();
		width = m_endPoint.x() - m_prePoint.x();
	}
	if (m_prePoint.y() > m_endPoint.y())
	{
		startY = m_endPoint.y();
		height = m_prePoint.y() - m_endPoint.y();
	}
	else
	{
		startY = m_prePoint.y();
		height = m_endPoint.y() - m_prePoint.y();
	}
	m_targetPixmap = m_pixmap.copy(startX, startY, width, height);
	painter->drawPixmap(startX,startY, m_targetPixmap);
}

QRect TransparentMask::handler(QPoint a, QPoint b)
{

	int startX = 0, startY = 0;
	int width = 0, height = 0;
	if (a.x() == b.x() && a.y() == b.y())
	{
		return QRect();
	}
	if (a.x() == b.x() && a.y() == b.y())
	{
		return QRect();
	}
	if (a.x() > b.x())
	{
		startX = b.x();
		width = a.x() - b.x();
	}
	else
	{
		startX = a.x();
		width = b.x() - a.x();
	}
	if (a.y() > b.y())
	{
		startY = b.y();
		height = a.y() - b.y();
	}
	else
	{
		startY = a.y();
		height = b.y() - a.y();
	}
	return QRect(startX, startY, width, height);
}

void TransparentMask::ShowAllScreen()
{
	QRect rect = StaticData::Instance().s_rect;
	this->setGeometry(rect);
    this->showFullScreen();
}

void TransparentMask::SavePic(QString path)
{
	m_targetPixmap.save(path);
}

void TransparentMask::ClipPic()
{
	QClipboard* tmpClipboard = QApplication::clipboard();
	tmpClipboard->setPixmap(m_targetPixmap);
}

