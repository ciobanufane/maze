#include "mazemodel.h"
#include "maze.h"
#include "astar.h"

#include <QSize>

MazeModel::MazeModel(Maze* maze, AStar* astar, QObject* parent)
    : QAbstractTableModel(parent), maze(maze), astar(astar)
{
}

int MazeModel::rowCount(const QModelIndex& /* parent */) const
{
    return maze->rows();
}

int MazeModel::columnCount(const QModelIndex& /* parent */) const
{
    return maze->columns();
}

QVariant MazeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()    || role != Qt::DisplayRole ||
        index.row() < 0     || index.row() >= maze->rows() ||
        index.column() < 0  || index.column() >= maze->columns())
        return QVariant();
    return maze->position({index.row(), index.column()});
}

QVariant MazeModel::headerData(int /*section*/, Qt::Orientation /*orientation*/, int role) const
{
    if (role == Qt::SizeHintRole)
        return QSize(1,1);
    return QVariant();
}

Qt::ItemFlags MazeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool MazeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()    || role != Qt::EditRole ||
        index.row() < 0     || index.row() >= maze->rows() ||
        index.column() < 0  || index.column() >= maze->columns())
        return false;

    bool ok;
    int mazePart = value.toInt(&ok);
    if (!ok)
        return false;

    if (!maze->setPart({index.row(), index.column()}, mazePart))
        return false;

    emit dataChanged(index,index);
    return true;
}





