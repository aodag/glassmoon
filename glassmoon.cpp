#include "glassmoon.h"
#include "interfaces.h"
#include "mainwindow.h"
#include "project.h"

#include <QAction>
#include <QMenuBar>
#include <QMenu>

#include <QInputDialog>
#include <QFileDialog>
#include <QListView>
#include <QDockWidget>
#include <QDebug>

struct Glassmoon::Impl
{
    MainWindow *mainWindow;
    QListView *bookmarkView;
};

Glassmoon::Glassmoon()
{
    pImpl = new Impl();
    pImpl->mainWindow = new MainWindow();
    initMenu();
    Project *defaultProject = new Project(pImpl->mainWindow,
                tr("default"));
    pImpl->mainWindow->addProject(defaultProject);
    QDockWidget *dock = new QDockWidget(tr("bookmark"), pImpl->mainWindow);
    pImpl->bookmarkView = new QListView(dock);
    dock->setWidget(pImpl->bookmarkView);
    pImpl->mainWindow->addDockWidget(Qt::LeftDockWidgetArea, dock);
}

Glassmoon::~Glassmoon()
{
    delete pImpl;
}


void
Glassmoon::show()
{
    pImpl->mainWindow->show();
}

void
Glassmoon::initMenu()
{
    QMenuBar *mbar = pImpl->mainWindow->menuBar();

    QMenu *fileMenu = mbar->addMenu(tr("&File"));
    QAction *fileOpenAction = fileMenu->addAction(tr("&Open"));
    connect(fileOpenAction, SIGNAL(triggered()),
            this, SLOT(openFile()));
    QMenu *projectMenu = mbar->addMenu(tr("&Project"));
    QAction *projectAddAction = projectMenu->addAction(tr("&Add"));
    connect(projectAddAction, SIGNAL(triggered()),
            this, SLOT(addProject()));
    QAction *addBookmarkAction = projectMenu->addAction(tr("Add &Bookmark"));
    connect(addBookmarkAction, SIGNAL(triggered()),
            this, SLOT(addBookmark()));
}

void
Glassmoon::addProject()
{
    QString projectName = QInputDialog::getText(pImpl->mainWindow,
            tr("new project"),
            tr("project name"));

    if (projectName.isNull() || projectName.isEmpty()) {
        return;
    }

    // プロジェクト名の重複チェックが必要
    Project *project = new Project(pImpl->mainWindow, projectName);
    pImpl->mainWindow->addProject(project);
    pImpl->mainWindow->setCurrentProject(project);
}

void
Glassmoon::addBookmark()
{
    QString path = QFileDialog::getExistingDirectory(pImpl->mainWindow);
    IProject *project = currentProject();
    project->addBookmark(path);
    qDebug() << path;
}

IProject *
Glassmoon::currentProject()
{
    IProject *project = pImpl->mainWindow->currentProject();
    return project;
}

void
Glassmoon::openFile()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty() || fileName.isNull()) {
        return;
    }

    IProject *project = currentProject();
    project->loadFile(fileName);
}

void
Glassmoon::saveFile()
{
}


void 
Glassmoon::saveFileAs()
{
}

void
Glassmoon::executeScript(const QString &script)
{
}

void
Glassmoon::executeScriptFile(const QString &fileName)
{
}

void 
Glassmoon::addScriptPath(const QString &path)
{
}

