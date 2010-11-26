#include "editor.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Editor::Editor(QWidget *parent)
    :QWidget(parent)
{
}

Editor::~Editor()
{
}

struct TextEditor::Impl
{
    QTextEdit *textEdit;
    QLayout *layout;
    QString fileName;
};

TextEditor::TextEditor(QWidget *parent)
    :Editor(parent)
{
    pImpl = new Impl();
    pImpl->textEdit = new QTextEdit(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(pImpl->textEdit);
    this->setLayout(layout);
}

TextEditor::~TextEditor()
{
    delete pImpl;
}

bool
TextEditor::hasFileName()
{
    return !pImpl->fileName.isNull() && !pImpl->fileName.isEmpty();
}

const QString &
TextEditor::fileName()
{
    return pImpl->fileName;
}

void
TextEditor::open(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        // TODO: show error
        return;
    }
    QTextStream st(&file);
    QString contents = st.readAll();
    file.close();
    pImpl->textEdit->setPlainText(contents);
    pImpl->fileName = fileName;
}

void
TextEditor::save()
{
    QFile file(pImpl->fileName);
    if (!file.open(QFile::WriteOnly)) {
        // TODO: show error
        return;
    }
    QTextStream st(&file);
    st << pImpl->textEdit->document()->toPlainText();
    file.close();
}

void
TextEditor::save(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("file open error"),
                tr("can't open file:"));
        return;
    }
    QTextStream st(&file);
    st << pImpl->textEdit->document()->toPlainText();
    st.flush();
    file.close();
    pImpl->fileName = fileName;
}

