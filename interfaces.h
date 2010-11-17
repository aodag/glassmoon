#ifndef INTERFACES_H
#define INTERFACES_H

class QWidget;

class IProject
{
public slots:
    virtual QWidget *projectView() = 0;
    virtual const QString &name() = 0;
    virtual void loadFile(const QString& fileName) = 0;
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

