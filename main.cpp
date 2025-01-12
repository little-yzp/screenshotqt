#include "snipasteapp.h"
#include <QApplication>
#include "vld.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SnipasteApp app;
    return a.exec();
}
