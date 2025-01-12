#include "snipasteapp.h"
#include "picview.h"
#include <QMenu>
#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QDebug>
#include <QFileDialog>
#include <memory>
#include <windows.h>
#include "vld.h"
#include "vld_def.h"

WId GetForegroundWindowId()
{
    HWND hwnd = GetForegroundWindow();
    return (WId)hwnd;
}

WId GetWholeScreenWindowId()
{
    HWND hwnd = GetDesktopWindow();
    return (WId)hwnd;
}
SnipasteApp::SnipasteApp(QObject *parent) : QObject(parent)
                                            ,sysMenu(new QSystemTrayIcon(this))
{
    m_transparentMask = new TransparentMask;
    this->sysMenu->setIcon(QIcon(":/icon/icon/icon.svg"));
    InitMenu();
    InitToolBar();
    this->sysMenu->show();
    connect(this, SIGNAL(Finished(QPixmap)), m_transparentMask, SLOT(ShowPic(QPixmap)));
    //lambada表达式值传递和引用传递
    connect(this->m_transparentMask, &TransparentMask::FinishShot, this, [&](QRect rect) {
        m_toolBar->show(); 
        m_toolBar->raise();
        m_toolBar->move(rect.x()+rect.width()-m_toolBar->width(), rect.y()+rect.height());
        });
    connect(this->m_transparentMask, &TransparentMask::ScreenShotStart, this, [&]() {m_toolBar->hide(); });
    connect(this, SIGNAL(SavePic(QString)), this->m_transparentMask,SLOT(SavePic(QString)));
}
SnipasteApp::~SnipasteApp()
{
    if (m_menu)
    {
		delete m_menu;
    }
    if (sysMenu)
    {
		delete sysMenu;
    }
    if (m_transparentMask)
    {
	   delete m_transparentMask;
    }
    if (m_toolBar)
    {
        delete m_toolBar;
    }
}
void SnipasteApp::ScreenShot()
{
    QList<QScreen*>screens = qApp->screens();
    if (!screens.empty())
    {
    }
    auto cursorPos = QCursor::pos();
    QPixmap pix;
    for (auto screen : screens)
    {
        QRect rect = screen->geometry();//geometry
        if (rect.contains(cursorPos))
        {
            pix = screen->grabWindow(GetWholeScreenWindowId());
        }

    }
    if (pix.isNull())
    {
        qDebug() << "没有截取到像素";
    }
    emit Finished(pix);
}
void SnipasteApp::funcHandler(QAction *action)
{

	if (action == nullptr)
	{
		return;
	}
	if (action->text() == "保存")
	{
        //保存文件对话框响应速度太慢
        QString FullPathName = QFileDialog::getSaveFileName(nullptr,"保存截图图片","",tr("*.png"));
        qDebug() << "保存图片完整路径名称为:" << FullPathName;
        emit SavePic(FullPathName);
        this->m_transparentMask->Hide();
	}
	else if (action->text() == "退出")
	{
        this->m_transparentMask->Hide();
        //此退出并非退出截图程序，只退出当前截图
	}
	else if(action->text()=="完成")
	{

	}
    else
    {
        return;

    }
	m_toolBar->hide();
}
void SnipasteApp::InitMenu()
{
    m_menu=new QMenu();
    m_menu->addAction("截图",this,SLOT(ScreenShot()));
    m_menu->addAction("退出",qApp,SLOT(quit()));
    this->sysMenu->setContextMenu(m_menu);
}
void SnipasteApp::InitToolBar()
{
	m_toolBar = new QToolBar;
	m_toolBar->addAction(QIcon(":/icon/icon/save.svg"), "保存");
    m_toolBar->addAction(QIcon(":/icon/icon/pin.svg"), "固定");
    m_toolBar->addSeparator();
	m_toolBar->addAction(QIcon(":/icon/icon/delete.svg"), "退出");
    m_toolBar->addAction(QIcon(":/icon/icon/trick.svg"),"完成");
	connect(m_toolBar, &QToolBar::actionTriggered, this, &SnipasteApp::funcHandler);
    m_toolBar->setWindowFlags(Qt::FramelessWindowHint);
}

