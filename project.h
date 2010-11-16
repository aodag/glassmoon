#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include "interfaces.h"

class Project
    :public QObject, public IProject
{
    Q_OBJECT
    struct Impl;
    Impl *pImpl;
public:
    Project(QWidget *parent, const QString &name);
    ~Project();
public slots:
    void loadFile(const QString &fileName);
    virtual QWidget *projectView();
    virtual const QString& name();

};

#endif 

