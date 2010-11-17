#ifndef GLASSMOON_H
#define GLASSMOON_H

#include <QObject>
#include "interfaces.h"

class Glassmoon
    :public QObject
{
    Q_OBJECT
    struct Impl;
    Impl *pImpl;
public:
    Glassmoon();
    virtual ~Glassmoon();
    const QStringList scriptPath();
protected:
    void initMenu();
    IProject* currentProject();
    
public slots:
    void addProject();
    void addBookmark();
    void openFile();
    void saveFile();
    void saveFileAs();
    void executeScript(const QString &script);
    void executeScriptFile(const QString &fileName);
    void addScriptPath(const QString &path);
    void show();
};

#endif

