#include "editor.h"
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLineEdit>
#include <QTextCursor>
#include <QTextFormat>
#include <QTextCharFormat>

#include "highlighter.h"


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
    QLineEdit *searchEdit;
    Highlighter *highlighter;
};

TextEditor::TextEditor(QWidget *parent)
    :Editor(parent)
{
    pImpl = new Impl();
    pImpl->textEdit = new MyTextEdit(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(pImpl->textEdit);
    this->setLayout(layout);
    pImpl->highlighter = new Highlighter(pImpl->textEdit->document());
    connect(pImpl->textEdit->document(), SIGNAL(modificationChanged(bool)),
        this, SLOT(onModificationChanged(bool)));
    pImpl->searchEdit = new QLineEdit(this);
    layout->addWidget(pImpl->searchEdit);
    connect(pImpl->searchEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(searchIncrementaly(const QString &)));
    connect(pImpl->searchEdit, SIGNAL(editingFinished()),
            this, SLOT(searchNext()));
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
    pImpl->textEdit->document()->setModified(false);
}

void
TextEditor::save()
{
    if (!hasFileName()) {
    }
    QFile file(pImpl->fileName);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("file open error"),
                tr("can't open file:"));
        return;
    }
    QTextStream st(&file);
    st << pImpl->textEdit->document()->toPlainText();
    file.close();
    pImpl->textEdit->document()->setModified(false);
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
    pImpl->textEdit->document()->setModified(false);
}

void
TextEditor::onModificationChanged(bool changed)
{
    if (changed) {
        setWindowTitle("* " + pImpl->fileName);
    } else {
        setWindowTitle(pImpl->fileName);
    }
}

void
TextEditor::searchIncrementaly(const QString &target)
{
    searchText(target);
}

void
TextEditor::searchNext()
{
    QString target = pImpl->searchEdit->text();
    searchText(target);
}

void
TextEditor::searchText(const QString &target)
{
    QTextCursor cursor = pImpl->textEdit->document()->find(target);
    cursor.setPosition(cursor.anchor() + target.length(), QTextCursor::KeepAnchor);
    QTextCharFormat cformat;
    cformat.setAnchor(true);
    cursor.mergeCharFormat(cformat);
    pImpl->textEdit->setTextCursor(cursor);
}
