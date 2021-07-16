#ifndef ASTARWRAPPER_H
#define ASTARWRAPPER_H

#include <QObject>
#include "point.h"

class AStar;
class Maze;
class MazeModel;

class AStarWrapper : public QObject
{
    Q_OBJECT
public:
    explicit AStarWrapper(AStar* astar, MazeModel* mazeModel, QObject *parent = nullptr);
signals:
    void continueCalculate();
    void finishCalculate();
    void noPathCalculate();
public slots:
    void setPathAndCalculate();
private:
    void setLastPathToModel(int value);

    AStar* m_astar;
    MazeModel* m_mazeModel;
    std::vector<Point> m_lastPath;
};

#endif // ASTARWRAPPER_H
