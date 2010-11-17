#include "mainwindow.h"

#include <QTabWidget>
#include <QMap>


struct MainWindow::Impl
{
    QTabWidget *tabWidget;
    QMap<QString, IProject *> projects;
    QMap<QString, QWidget *> projectViews;
};

MainWindow::MainWindow()
{
    pImpl = new Impl();
    pImpl->tabWidget = new QTabWidget(this);
    setCentralWidget(pImpl->tabWidget);
}

MainWindow::~MainWindow()
{
    delete pImpl;
}

IProject *
MainWindow::currentProject()
{
    int currentIndex = pImpl->tabWidget->currentIndex();
    const QString &name = pImpl->tabWidget->tabText(currentIndex);
    return pImpl->projects[name];
}

void
MainWindow::addProject(IProject *project)
{
    const QString &projectName = project->name();
    QWidget *projectView = project->projectView();
    pImpl->tabWidget->addTab(projectView, projectName);
    pImpl->projects[projectName] = project;
    pImpl->projectViews[projectName] = projectView;
}

void
MainWindow::setCurrentProject(IProject *project)
{
    QWidget *view = pImpl->projectViews[project->name()];
    pImpl->tabWidget->setCurrentWidget(view);
}
