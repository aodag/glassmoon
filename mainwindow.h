#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMdiArea;

class MainWindow
    :public QMainWindow
{
    Q_OBJECT
    struct Impl;
    Impl *pImpl;
protected:
    void initMenu();
    QMdiArea *activeArea();
    void openFile(const QString &fileName);
public:
    MainWindow();
    virtual ~MainWindow();
public slots:
    void on_fileOpenAction_triggered();
};

#endif

