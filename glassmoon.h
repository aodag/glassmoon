#ifndef GLASSMOON_H
#define GLASSMOON_H

#include <QObject>

class Project;

class Glassmoon
    :public QObject
{
    Q_OBJECT
    struct Impl;
    Impl *pImpl;
    static Glassmoon *application;
public:
    static QString getOpenFileName();
    static QString getSaveFileName();
    Glassmoon();
    virtual ~Glassmoon();
    const QStringList scriptPath();
protected:
    void initMenu();
    Project* currentProject();
    
public slots:
    void addProject();
    void addBookmark();
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void closeFile();
    void moveNextFile();
    void movePreviousFile();
    void executeScript(const QString &script);
    void executeScriptFile();
    void executeScriptFile(const QString &fileName);
    void addScriptPath(const QString &path);
    void show();
};

#endif

