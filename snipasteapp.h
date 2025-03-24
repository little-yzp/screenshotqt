#ifndef SNIPASTEAPP_H
#define SNIPASTEAPP_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QPointer>
#include "transparentmask.h"
#include "picview.h"
#include "tipwh.h"
#include <QShortCut>
class PicView;//前向声明

class SnipasteApp : public QObject
{
    Q_OBJECT
public:
    explicit SnipasteApp(QObject *parent = nullptr);
    ~SnipasteApp();
    void ScreenShotInterface();

signals:
    void Finished(QPixmap pix);
    void SavePic(QString path);
    void ClipPic();
    void PinPic();
private slots:
    void ScreenShot();
    void funcHandler(QAction *action);
private:
    QPointer<QSystemTrayIcon>sysMenu;
    QPointer<QMenu>m_menu;
    QPointer<QToolBar>m_toolBar;
    QPointer<Tipwh>m_tipwh;
    void InitMenu();
    void InitToolBar();
    QPointer<TransparentMask>m_transparentMask;
    QString m_lastOpenDir;
};
//问题:QPointer与QScopedPointer的区别?
//体会:QPointer只能保证使用空指针时不会崩溃
#endif // SNIPASTEAPP_H
