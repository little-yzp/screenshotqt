﻿#include "snipasteapp.h"
#include <QMenu>
#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QDebug>
#include <QFileDialog>
#include <memory>
#include <windows.h>
#include <QKeySequence>
#include <QDesktopWidget>
#include <QTimer>
#include "staticdata.h"

QString SnipasteApp::m_lastOpenDir{ "." };
SnipasteApp::SnipasteApp(QObject *parent) : QObject(parent)
                                            ,sysMenu(new QSystemTrayIcon(this))
                                            ,m_transparentMask(new TransparentMask)
{
    this->sysMenu->setIcon(QIcon(":/icon/icon/icon.svg"));
    InitMenu();
    InitToolBar();
    this->sysMenu->show();
    connect(this, SIGNAL(Finished(QPixmap)), m_transparentMask, SLOT(ShowPic(QPixmap)),Qt::DirectConnection);
    //lambada表达式值传递和引用传递
    connect(this->m_transparentMask, &TransparentMask::FinishShot, this, [&](QRect rect) {

        m_toolBar->show(); 
        m_toolBar->raise();
        int startX = 0, startY = 0;
        if (StaticData::Instance().s_curScreenPtr != nullptr)
        {
            startX = StaticData::Instance().s_curScreenPtr->geometry().x();
            startY = StaticData::Instance().s_curScreenPtr->geometry().y();
        }
        startX += rect.x() + rect.width() - m_toolBar->width();
        startY+=rect.y()+rect.height();
        m_toolBar->move(startX,startY);
        });
    connect(this->m_transparentMask, &TransparentMask::ScreenShotStart, this, [&]() {m_toolBar->hide(); });
    connect(this, SIGNAL(SavePic(QString)), this->m_transparentMask,SLOT(SavePic(QString)));
    connect(this, SIGNAL(ClipPic()),this->m_transparentMask, SLOT(ClipPic()));
    //showFullScreen与showMaximized的区别
    //m_picView->showFullScreen();
    connect(this, SIGNAL(PinPic()), this->m_transparentMask, SLOT(PinPic()));
}
SnipasteApp::~SnipasteApp()
{
    if (m_menu!=nullptr)
    {
		delete m_menu;
    }
    if (sysMenu!=nullptr)
    {
		delete sysMenu;
    }
    if (m_transparentMask!=nullptr)
    {
	   delete m_transparentMask;
    }
    if (m_toolBar!=nullptr)
    {
        delete m_toolBar;
    }
    qDebug() << "snipasteapp deleted";
}
void SnipasteApp::ScreenShotInterface()
{
    this->ScreenShot();
}
QString SnipasteApp::getLastOpenDir()
{
    return m_lastOpenDir;
}
void SnipasteApp::setLastOpenDir(QString path)
{
    m_lastOpenDir = path;
    
}
void SnipasteApp::ScreenShot()
{
    //截图开始前先将已有的截图界面动态切换到非始终置顶显示

    //解决多次按截图键,多次阴影问题
    if (m_transparentMask->isVisible())
    {
        return;
    }
    QList<QScreen*>screens = QGuiApplication::screens();//qApp->screens();
    QDesktopWidget* desktopWidget = qApp->desktop();
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
            StaticData::Instance().s_rect = screen->geometry();
            StaticData::Instance().s_curScreenPtr = screen;
            pix = screen->grabWindow(0);
            break;
        }

    }
    if (pix.isNull())
    {
        qDebug() << "pixels were not obtained here";
    }
    emit Finished(pix);

}
void SnipasteApp::funcHandler(QAction *action)
{

	if (action == nullptr)
	{
		return;
	}
	if (action->text() == "save")
	{
        //保存文件对话框响应速度太慢
        QString FullPathName = QFileDialog::getSaveFileName(nullptr,"picture saving",m_lastOpenDir,tr("*.png"));
        qDebug() << "pic absoluate path is:" << FullPathName;
        if (FullPathName.isEmpty()) {
            return;
        }
        //获取路径
        m_lastOpenDir = FullPathName.left(FullPathName.lastIndexOf('/'));
        emit SavePic(FullPathName);
	}
	else if (action->text() == "quit")
	{
        //此退出并非退出截图程序，只退出当前截图
	}
	else if(action->text()=="finish")
	{
        emit ClipPic();
	}
    else if(action->text()=="pin")
    {
        emit PinPic();
    }
    else 
    {
    }
	this->m_transparentMask->Hide();
	m_toolBar->hide();
}
void SnipasteApp::InitMenu()
{
    m_menu=new QMenu();
    m_menu->addAction("screenshot",this,SLOT(ScreenShot()));
    m_menu->addAction("quit",qApp,SLOT(quit()));
    this->sysMenu->setContextMenu(m_menu);
}
void SnipasteApp::InitToolBar()
{
	m_toolBar = new QToolBar;
	m_toolBar->addAction(QIcon(":/icon/icon/save.svg"), "save");
    m_toolBar->addAction(QIcon(":/icon/icon/pin.svg"), "pin");
    m_toolBar->addSeparator();
	m_toolBar->addAction(QIcon(":/icon/icon/delete.svg"), "quit");
    m_toolBar->addAction(QIcon(":/icon/icon/trick.svg"),"finish");
	connect(m_toolBar, &QToolBar::actionTriggered, this, &SnipasteApp::funcHandler);
    m_toolBar->setWindowFlags(Qt::FramelessWindowHint);
}

