#include "mainwindow.h"
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QTextEdit>
#include <QTabWidget>
#include <QAction>
#include <QMenuBar>
#include <QMenu>


#include <QFileDialog>
#include <QFile>
#include <QTextStream>

struct MainWindow::Impl
{
    QTabWidget *tabWidget;
};

MainWindow::MainWindow()
{
    pImpl = new Impl();
    pImpl->tabWidget = new QTabWidget(this);
    QMdiArea *mdiArea = new QMdiArea(pImpl->tabWidget);
    pImpl->tabWidget->addTab(mdiArea, tr("default"));
    setCentralWidget(pImpl->tabWidget);
    initMenu();
}

MainWindow::~MainWindow()
{
}

void
MainWindow::initMenu()
{
    QMenuBar *mbar = menuBar();
    QMenu *fileMenu = mbar->addMenu(tr("&File"));
    QAction *fileOpenAction = fileMenu->addAction(tr("&Open"));
    connect(fileOpenAction, SIGNAL(triggered()),
            this, SLOT(on_fileOpenAction_triggered()));
}

QMdiArea *
MainWindow::activeArea()
{
    return reinterpret_cast<QMdiArea *>(pImpl->tabWidget->currentWidget());
}

void
MainWindow::on_fileOpenAction_triggered()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (fileName.isEmpty() || fileName.isNull()) {
        return;
    }
    openFile(fileName);
}

void
MainWindow::openFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly)) {
        return;
    }

    QTextStream stream(&file);
    QMdiArea *area = activeArea();
    QTextEdit *textEdit = new QTextEdit(area);
    textEdit->setDocumentTitle(fileName);
    textEdit->setPlainText(stream.readAll());

    QMdiSubWindow *sub = area->addSubWindow(textEdit);
    sub->show();

}

