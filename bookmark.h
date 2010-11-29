#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <QAbstractItemModel>

class Project;

class BookmarkModel
    :public QAbstractItemModel
{
    Q_OBJECT
    struct Impl;
    Impl *pImpl;
public:
    BookmarkModel(Project *);
    ~BookmarkModel();
    virtual int	columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    virtual QVariant	data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    virtual QModelIndex	index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    virtual QModelIndex	parent ( const QModelIndex & index ) const;
    virtual int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
public slots:
    void onBookmarkAdded(const QString &path);
};

#endif

