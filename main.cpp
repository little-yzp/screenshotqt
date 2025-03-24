#include <QApplication>
#include "shortcutfilter.h"
#include "picview.h"
#define APP


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
#ifdef APP
    ShortcutFilter filter;
    // 注册Ctrl+Alt+S作为快捷键
    const quint32 SHORTCUT_ID = 1;
    const quint32 MODIFIERS = MOD_CONTROL | MOD_ALT;
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
    return a.exec();
}
