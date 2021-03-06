#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>

class QAbstractItemModel;
class Editor;

class Project
    :public QObject
{
    Q_OBJECT
    struct Impl;
    Impl *pImpl;
public:
    Project(QWidget *parent, const QString &name);
    ~Project();
    virtual int bookmarkCount();
    virtual const QString &bookmark(int index);
    virtual QAbstractItemModel *bookmarkModel();
    virtual int indexOfBookmark(const QString &path);
    virtual Editor *currentEditor();
public slots:
    void newFile();
    void loadFile(const QString &fileName);
    void saveFile(const QString &fileName);
    void saveFile();
    void closeCurrentFile();
    virtual QWidget *projectView();
    virtual const QString& name();
    virtual void addBookmark(const QString &path);
    void activateNext();
    void activatePrevious();
signals:
    void bookmarkAdded(const QString &path);

};

#endif 

