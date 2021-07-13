#ifndef ASTARWRAPPER_H
#define ASTARWRAPPER_H

#include <QObject>

class AStar;
class Maze;
class MazeModel;

class AStarWrapper : public QObject
{
    Q_OBJECT
public:
    explicit AStarWrapper(AStar* astar, Maze* maze, MazeModel* mazeModel, QObject *parent = nullptr);
signals:
    void continueCalculate();
    void finishCalculate();
    void noPathCalculate();
public slots:
    void setPathAndCalculate();
private:
    AStar* astar;
    Maze* maze;
    MazeModel* mazeModel;
    std::vector<int> lastPath;
};

#endif // ASTARWRAPPER_H
