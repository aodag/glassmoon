#include "editor.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QKeyEvent>

class MyTextEdit
    :public QTextEdit
{
    bool _expandTab;
protected:
    virtual void keyPressEvent(QKeyEvent *keyEvent);
public:
    MyTextEdit(QWidget *parent);
    virtual ~MyTextEdit();
    bool expandTab();
    void setExpandTab(bool expand);
};

bool
MyTextEdit::expandTab()
{
    return _expandTab;
}

void 
MyTextEdit::setExpandTab(bool expand)
{
    _expandTab = expand;
}

void 
MyTextEdit::keyPressEvent(QKeyEvent *keyEvent)
{
    if (_expandTab && keyEvent->key() == Qt::Key_Tab) {
        insertPlainText("    ");
    } else {
        QTextEdit::keyPressEvent(keyEvent);
    }
}

MyTextEdit::MyTextEdit(QWidget *parent)
    :QTextEdit(parent), _expandTab(true)
{
}

MyTextEdit::~MyTextEdit()
{
}


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
    pImpl->textEdit = new MyTextEdit(this);
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
        QMessageBox::warning(this, tr("file open error"),
                tr("can't open file:"));
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
        QMessageBox::warning(this, tr("file open error"),
                tr("can't open file:"));
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

