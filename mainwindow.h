#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Project;

class QMdiArea;

class MainWindow
    :public QMainWindow
{
    Q_OBJECT
    struct Impl;
    Impl *pImpl;
public:
    MainWindow();
    virtual ~MainWindow();
public slots:
    virtual Project *currentProject();
    virtual void addProject(Project *);
    virtual void setCurrentProject(Project *);
};

#endif

