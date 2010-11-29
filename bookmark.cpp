#include "bookmark.h"
#include "project.h"

struct BookmarkModel::Impl
{
    Project *project;
};



BookmarkModel::BookmarkModel(Project *project)
    :QAbstractItemModel(project)
{
    pImpl = new Impl();
    pImpl->project = project;
    connect(project, SIGNAL(bookmarkAdded(const QString &)),
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
            return QVariant(pImpl->project->bookmark(index.row()));
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
    return pImpl->project->bookmarkCount();
}

void
BookmarkModel::onBookmarkAdded(const QString &path)
{
    int pos = pImpl->project->indexOfBookmark(path);
    if (pos > -1) {
        QModelIndex index = createIndex(pos, 0);
        emit dataChanged(index, index);
    }
}
