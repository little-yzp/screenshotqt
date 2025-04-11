#include <QApplication>
#include <QSharedMemory>
#include "shortcutfilter.h"
#include "picview.h"
#include "qdebug.h"
#include "qmessagebox.h"
#define APP


int main(int argc, char *argv[])
{

    QSharedMemory shareMemory("com.github.yzp");

    QApplication a(argc, argv);
    //解决bug截图后删除最后一个固定截图程序推出问题
    a.setQuitOnLastWindowClosed(false);
    if (shareMemory.attach())
    {
        //已经有一个程序实例被启动,使用窗口api提示已经有一个实例化进程
        QMessageBox::warning(nullptr, QString("WARNNING"), QString("screenshot is already exists!!"), QMessageBox::Ok, QMessageBox::NoButton);
        return -1;
    }
    if (!shareMemory.create(sizeof(int)))
    {
        qDebug() << shareMemory.error();
    }
    QFile styleFile(":/styles/styles/styles.qss");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString styleSheet = QLatin1String(styleFile.readAll());
        a.setStyleSheet(styleSheet);
        styleFile.close();
    }
    else
    {
        qWarning() << "无法加载样式表";
    }
#ifdef APP
    ShortcutFilter filter;
    // 注册Ctrl+Alt+S作为快捷键
    const quint32 SHORTCUT_ID = 1;
    const quint32 MODIFIERS = MOD_CONTROL | MOD_SHIFT;
    const quint32 KEY = 'S';
    if (!filter.registerShortcut(SHORTCUT_ID, MODIFIERS, KEY)) {
        qDebug("Failed to register hotkey.");
    }
    a.installNativeEventFilter(&filter);
#else
    QPixmap pixmap(":/icon/icon/testpixmap.jpg");
    //PicView picView(pixmap);
    PicView picView;
    //picView.show();
    picView.ShowPic(pixmap);

#endif
    //showFullScreen在多屏幕情况下不会显示所有屏幕
    a.exec();
    shareMemory.detach();
    return 0;
}
