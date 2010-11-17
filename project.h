#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include "interfaces.h"

class QAbstractItemModel;

class Project
    :public QObject, public IProject
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
public slots:
    void loadFile(const QString &fileName);
    virtual QWidget *projectView();
    virtual const QString& name();
    virtual void addBookmark(const QString &path);
signals:
    void bookmarkAdded(const QString &path);

};

#endif 

