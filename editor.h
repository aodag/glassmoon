#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>

class Editor
    :public QWidget
{
Q_OBJECT
public:
    Editor(QWidget *parent);
    virtual ~Editor();
    virtual bool hasFileName() = 0;    
    virtual const QString &fileName() = 0;
public slots:
    virtual void open(const QString &fileName) = 0;
    virtual void save() = 0;
    virtual void save(const QString &fileName) = 0;
};

class QTextCursor;

class TextEditor
    :public Editor
{
Q_OBJECT
    struct Impl;
    Impl *pImpl;
public:
    TextEditor(QWidget *parent);
    virtual ~TextEditor();
public:
    virtual bool hasFileName();    
    virtual const QString &fileName();
    virtual void searchText(const QString &target);
public slots:
    virtual void open(const QString &fileName);
    virtual void save();
    virtual void save(const QString &fileName);
    virtual void onModificationChanged(bool changed);
    virtual void searchIncrementaly(const QString &target);
    virtual void searchNext();

};

#endif
