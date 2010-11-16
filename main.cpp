#include <QApplication>
#include "glassmoon.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Glassmoon *glassmoon = new Glassmoon();
    glassmoon->show();
    return app.exec();
}
