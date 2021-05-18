#include "vouage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Vouage w;
    w.show();
    return a.exec();
}
