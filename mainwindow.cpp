#include "mainwindow.h"
#include "project.h"

#include <QTabWidget>
#include <QMap>


struct MainWindow::Impl
{
    QTabWidget *tabWidget;
    QMap<QString, Project *> projects;
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

Project *
MainWindow::currentProject()
{
    int currentIndex = pImpl->tabWidget->currentIndex();
    const QString &name = pImpl->tabWidget->tabText(currentIndex);
    return pImpl->projects[name];
}

void
MainWindow::addProject(Project *project)
{
    const QString &projectName = project->name();
    QWidget *projectView = project->projectView();
    pImpl->tabWidget->addTab(projectView, projectName);
    pImpl->projects[projectName] = project;
    pImpl->projectViews[projectName] = projectView;
}

void
MainWindow::setCurrentProject(Project *project)
{
    QWidget *view = pImpl->projectViews[project->name()];
    pImpl->tabWidget->setCurrentWidget(view);
}
