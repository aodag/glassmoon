#include "glassmoon.h"
#include "mainwindow.h"
#include "project.h"

#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QKeySequence>

#include <QInputDialog>
#include <QFileDialog>
#include <QListView>
#include <QDockWidget>
#include <QDebug>

#include <QScriptEngine>


struct Glassmoon::Impl
{
    MainWindow *mainWindow;
    QListView *bookmarkView;
    QScriptEngine *engine;
};

Glassmoon *Glassmoon::application = 0;

QString
Glassmoon::getOpenFileName()
{
    return QFileDialog::getOpenFileName(application->pImpl->mainWindow);
}

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
    pImpl->engine = new QScriptEngine(this);
    QScriptValue me = pImpl->engine->newQObject(this);
    pImpl->engine->globalObject().setProperty("application", me);
    Glassmoon::application = this;
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
    fileOpenAction->setShortcut(QKeySequence::Open);
    connect(fileOpenAction, SIGNAL(triggered()),
            this, SLOT(openFile()));
    QAction *fileSaveAction = fileMenu->addAction(tr("&Save"));
    fileSaveAction->setShortcut(QKeySequence::Save);
    connect(fileSaveAction, SIGNAL(triggered()),
            this, SLOT(saveFile()));
    QAction *fileSaveAsAction = fileMenu->addAction(tr("Save &As"));
    fileSaveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(fileSaveAsAction, SIGNAL(triggered()),
            this, SLOT(saveFileAs()));
    QMenu *projectMenu = mbar->addMenu(tr("&Project"));
    QAction *projectAddAction = projectMenu->addAction(tr("&Add"));
    connect(projectAddAction, SIGNAL(triggered()),
            this, SLOT(addProject()));
    QAction *addBookmarkAction = projectMenu->addAction(tr("Add &Bookmark"));
    connect(addBookmarkAction, SIGNAL(triggered()),
            this, SLOT(addBookmark()));
    QMenu *scriptMenu = mbar->addMenu(tr("&Script"));
    QAction *executeFileAction = scriptMenu->addAction(tr("Execute File"));
    connect(executeFileAction, SIGNAL(triggered()),
            this, SLOT(executeScriptFile()));
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
    Project *project = currentProject();
    project->addBookmark(path);
    qDebug() << path;
}

Project *
Glassmoon::currentProject()
{
    Project *project = pImpl->mainWindow->currentProject();
    return project;
}

void
Glassmoon::openFile()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty() || fileName.isNull()) {
        return;
    }

    Project *project = currentProject();
    project->loadFile(fileName);
}

void
Glassmoon::saveFile()
{
    Project *project = currentProject();
    project->saveFile();
}


void 
Glassmoon::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName();
    if (fileName.isEmpty() || fileName.isNull()) {
        return;
    }

    Project *project = currentProject();
    project->saveFile(fileName);
}

void
Glassmoon::executeScript(const QString &script)
{
}

void
Glassmoon::executeScriptFile()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isNull() || fileName.isEmpty()) {
        return;
    }
    executeScriptFile(fileName);
}

void
Glassmoon::executeScriptFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        return;
    }
    
    QTextStream st(&file);
    QString contents = st.readAll();
    file.close();
    pImpl->engine->evaluate(contents, fileName);
}

void 
Glassmoon::addScriptPath(const QString &path)
{
}

