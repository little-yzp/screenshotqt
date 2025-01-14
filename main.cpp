#include "snipasteapp.h"
#include <QApplication>
#include "vld.h"
#include "picview.h"
#include "transparentmask.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SnipasteApp app;
    //showFullScreen在多屏幕情况下不会显示所有屏幕
    return a.exec();
}
