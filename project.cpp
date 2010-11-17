#include "project.h"

#include <QMdiArea>
#include <QMdiSubWindow>
#include <QTextEdit>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "bookmark.h"

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
    pImpl->bookmarkModel = new BookmarkModel(this, this);
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
Project::loadFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly)) {
        return;
    }

    QTextStream stream(&file);
    QTextEdit *textEdit = new QTextEdit(pImpl->view);
    textEdit->setDocumentTitle(fileName);
    textEdit->setPlainText(stream.readAll());

    QMdiSubWindow *sub = pImpl->view->addSubWindow(textEdit);
    sub->setWindowTitle(fileName);
    sub->show();

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
