#include "project.h"

#include <QMdiArea>
#include <QMdiSubWindow>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>

struct Project::Impl
{
    QString name;
    QMdiArea *view;
};


Project::Project(QWidget *parent, const QString &name)
    :QObject(parent)
{
    pImpl = new Impl();
    pImpl->name = name;
    pImpl->view = new QMdiArea(parent);
}

Project::~Project()
{
    delete pImpl;
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
