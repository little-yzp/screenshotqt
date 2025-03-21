#ifndef __SHORTCUTFILTER_H__
#define __SHORTCUTFILTER_H__
#include <QAbstractNativeEventFilter>
#include <windows.h>
#include "snipasteapp.h"
class ShortcutFilter : public QAbstractNativeEventFilter {
public:
    ~ShortcutFilter() {
        this->unregisterShortcut(m_shortcutId);
    }
    bool nativeEventFilter(const QByteArray& eventType, void* message, long*) override {
        if (eventType == "windows_generic_MSG") {
            MSG* msg = static_cast<MSG*>(message);
            if (msg->message == WM_HOTKEY) {
                // 在这里处理快捷键触发的事件
                switch (msg->wParam)
                {
                case 1:
                    m_app.ScreenShotInterface();
                    break;
                default:
                    break;
                }
                return true;
            }
        }
        return false;
    }

    bool registerShortcut(quint32 shortcutId, quint32 modifiers, quint32 key) {
        m_shortcutId = shortcutId;
        return RegisterHotKey(nullptr, shortcutId, modifiers, key);
    }

    bool unregisterShortcut(quint32 shortcutId) {
        return UnregisterHotKey(nullptr, shortcutId);
    }
private:
    SnipasteApp m_app;
    quint32 m_shortcutId;
};

#endif
