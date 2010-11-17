#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interfaces.h"

class QMdiArea;

class MainWindow
    :public QMainWindow, public IProjectContainer
{
    Q_OBJECT
    struct Impl;
    Impl *pImpl;
public:
    MainWindow();
    virtual ~MainWindow();
public slots:
    virtual IProject *currentProject();
    virtual void addProject(IProject *);
    virtual void setCurrentProject(IProject *);
};

#endif

