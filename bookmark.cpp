#include "bookmark.h"

struct BookmarkModel::Impl
{
    IBookmarkContainer *bookmarkContainer;
};



BookmarkModel::BookmarkModel(QObject *parent, IBookmarkContainer *bookmarkContainer)
    :QAbstractItemModel(parent)
{
    pImpl = new Impl();
    pImpl->bookmarkContainer = bookmarkContainer;
    connect(parent, SIGNAL(bookmarkAdded(const QString &)),
            this, SLOT(onBookmarkAdded(const QString &)));
}


BookmarkModel::~BookmarkModel()
{
    delete pImpl;
}

int	
BookmarkModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant	
BookmarkModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() < rowCount()) {
        if (role == Qt::DisplayRole) {
            return QVariant(pImpl->bookmarkContainer->bookmark(index.row()));
        } else {
            return QVariant();
        }
    } else {
        return QVariant();
    }

}

QModelIndex	
BookmarkModel::index(int row, int column, const QModelIndex &parent) const
{
    if (column == 1 && row < rowCount()) {
        return createIndex(row, column);
    }
    return QModelIndex();
}

QModelIndex	
BookmarkModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int	
BookmarkModel::rowCount(const QModelIndex &parent) const
{
    return pImpl->bookmarkContainer->bookmarkCount();
}

void
BookmarkModel::onBookmarkAdded(const QString &path)
{
    int pos = pImpl->bookmarkContainer->indexOfBookmark(path);
    if (pos > -1) {
        QModelIndex index = createIndex(pos, 0);
        emit dataChanged(index, index);
    }
}
