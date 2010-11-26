#ifndef INTERFACES_H
#define INTERFACES_H

class QWidget;

class IBookmarkContainer
{
public:
    virtual int bookmarkCount() = 0;
    virtual const QString &bookmark(int index) = 0;
    virtual int indexOfBookmark(const QString &path) = 0;
public slots:
    virtual void addBookmark(const QString& path) = 0;
signals:
    void bookmarkAdded(const QString &path);
};

class IProject
    :public IBookmarkContainer
{
public slots:
    virtual QWidget *projectView() = 0;
    virtual const QString &name() = 0;
    virtual void loadFile(const QString& fileName) = 0;
    virtual void saveFile(const QString& fileName) = 0;
    virtual void saveFile() = 0;
};

class IProjectContainer
{
public slots:
    virtual void addProject(IProject *) = 0;
    virtual IProject *currentProject() = 0;
    // �v���W�F�N�g�ꗗ�擾
    // �v���W�F�N�g���Ŏ擾
    // �J�����g�v���W�F�N�g��ύX
    virtual void setCurrentProject(IProject *) = 0;
};

#endif

