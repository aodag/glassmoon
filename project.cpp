#include "project.h"

#include <QMdiArea>
#include <QMdiSubWindow>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

#include "glassmoon.h"
#include "bookmark.h"
#include "editor.h"

struct Project::Impl
{
    QString name;
    QMdiArea *view;
    QStringList bookmarks;
    BookmarkModel *bookmarkModel;
};


Project::Project(QWidget *parent, const QString &name)
    :QObject(parent)
{
    pImpl = new Impl();
    pImpl->name = name;
    pImpl->view = new QMdiArea(parent);
    pImpl->bookmarkModel = new BookmarkModel(this);
}

Project::~Project()
{
    delete pImpl;
}

QAbstractItemModel *
Project::bookmarkModel()
{
    return pImpl->bookmarkModel;
}
const QString &
Project::name()
{
    return pImpl->name;
}

void
Project::newFile()
{
    TextEditor *editor = new TextEditor(pImpl->view);
    QMdiSubWindow *sub = pImpl->view->addSubWindow(editor);
    sub->show();
}

void
Project::loadFile(const QString &fileName)
{

    TextEditor *editor = new TextEditor(pImpl->view);
    editor->open(fileName);

    QMdiSubWindow *sub = pImpl->view->addSubWindow(editor);
    sub->show();
}

Editor *
Project::currentEditor()
{
    QMdiSubWindow *sub = pImpl->view->activeSubWindow();
    if (sub == 0) {
        return 0;
    }
    Editor *editor = reinterpret_cast<Editor *>(sub->widget());
    return editor;
}

void
Project::saveFile(const QString &fileName)
{
    Editor *editor = currentEditor();
    editor->save(fileName);
}

void
Project::saveFile()
{
    Editor *editor = currentEditor();
    if (editor->hasFileName()) {
        editor->save();
    } else {
        QString fileName = Glassmoon::getSaveFileName();
        if (fileName.isNull() || fileName.isEmpty()) {
            return;
        }
        editor->save(fileName);
    }
}

void
Project::closeCurrentFile()
{
    QMdiSubWindow *sub = pImpl->view->activeSubWindow();
    if (sub == 0) {
        return;
    }
    sub->close();
}

QWidget *
Project::projectView()
{
    return pImpl->view;
}

void
Project::addBookmark(const QString &path)
{
    QFileInfo info(path);
    if (!info.isDir()) {
        return;
    }
    QString abspath = info.absoluteFilePath();
    pImpl->bookmarks << abspath;
    emit bookmarkAdded(abspath);
}

int
Project::bookmarkCount()
{
    return pImpl->bookmarks.size();
}

const QString &
Project::bookmark(int index)
{
    return pImpl->bookmarks[index];
}

int
Project::indexOfBookmark(const QString &path)
{
    return pImpl->bookmarks.lastIndexOf(path);
}

void
Project::activateNext()
{
    pImpl->view->activateNextSubWindow();
}

void
Project::activatePrevious()
{
    pImpl->view->activatePreviousSubWindow();
}

