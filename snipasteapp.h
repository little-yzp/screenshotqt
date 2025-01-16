#ifndef SNIPASTEAPP_H
#define SNIPASTEAPP_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QPointer>
#include "transparentmask.h"
#include "picview.h"
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
private slots:
    void ScreenShot();
    void funcHandler(QAction *action);
    void timeoutHandler();
private:
    QPointer<QSystemTrayIcon>sysMenu;
    QPointer<QMenu>m_menu;
    QPointer<QToolBar>m_toolBar;
    void InitMenu();
    void InitToolBar();
    QPointer<TransparentMask>m_transparentMask;
    QPixmap m_targetPixmap;
    QPointer<PicView> m_picView;
    QPointer<QTimer> m_timer;
    QString m_lastOpenDir;
};
//问题:QPointer与QScopedPointer的区别?
//体会:QPointer只能保证使用空指针时不会崩溃
#endif // SNIPASTEAPP_H
