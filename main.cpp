#include <QApplication>
#include <QMainWindow>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QMainWindow *win = new QMainWindow();
    win->show();
    return app.exec();
}
