#ifndef MAZEMODEL_H
#define MAZEMODEL_H

#include <QAbstractTableModel>

class Maze;
class AStar;

class MazeModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MazeModel(Maze* maze, AStar* astar, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::EditRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
private:
    Maze* maze;
    AStar* astar;
    std::vector<int> lastPath;
};

#endif // MAZEMODEL_H
