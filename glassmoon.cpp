#include "glassmoon.h"
#include "interfaces.h"
#include "mainwindow.h"
#include "project.h"

#include <QAction>
#include <QMenuBar>
#include <QMenu>

#include <QFileDialog>

struct Glassmoon::Impl
{
    MainWindow *mainWindow;
};

Glassmoon::Glassmoon()
{
    pImpl = new Impl();
    pImpl->mainWindow = new MainWindow();
    initMenu();
    Project *defaultProject = new Project(pImpl->mainWindow,
                tr("default"));
    pImpl->mainWindow->addProject(defaultProject);
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
}

void
Glassmoon::addProject()
{
    // プロジェクト名取得

}

void
Glassmoon::openFile()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty() || fileName.isNull()) {
        return;
    }

    IProject *project = pImpl->mainWindow->currentProject();
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

