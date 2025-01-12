#ifndef SNIPASTEAPP_H
#define SNIPASTEAPP_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QPointer>
#include "transparentmask.h"
class PicView;//前向声明

class SnipasteApp : public QObject
{
    Q_OBJECT
public:
    explicit SnipasteApp(QObject *parent = nullptr);
    ~SnipasteApp();

signals:
    void Finished(QPixmap pix);
    void SavePic(QString path);
private slots:
    void ScreenShot();
    void funcHandler(QAction *action);
private:
    QPointer<QSystemTrayIcon>sysMenu;
    QPointer<QMenu>m_menu;
    QPointer<QToolBar>m_toolBar;
    void InitMenu();
    void InitToolBar();
    QPointer<TransparentMask>m_transparentMask;
    QPixmap m_targetPixmap;
};
//问题:QPointer与QScopedPointer的区别?
//体会:QPointer只能保证使用空指针时不会崩溃
#endif // SNIPASTEAPP_H
