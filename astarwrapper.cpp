#include "astarwrapper.h"
#include "astar.h"
#include "maze.h"
#include "mazemodel.h"

AStarWrapper::AStarWrapper(AStar* astar, Maze* maze, MazeModel* mazeModel, QObject *parent)
    : QObject(parent), astar(astar), maze(maze), mazeModel(mazeModel)
{

}

void AStarWrapper::setPathAndCalculate()
{
    int result = astar->calculate();
    switch (result) {
    case AStar::FINISHED:
        for (int i : lastPath) {
            Point p = maze->index1DToPoint(i);
            mazeModel->setData(mazeModel->index(p.row, p.column), 3);
        }
        lastPath = astar->getCurrentPath();
        for(int i : lastPath) {
            Point p = maze->index1DToPoint(i);
            mazeModel->setData(mazeModel->index(p.row, p.column), 2);
        }
        emit finishCalculate();
        break;
    case AStar::CONTINUE:
        for (int i : lastPath) {
            Point p = maze->index1DToPoint(i);
            mazeModel->setData(mazeModel->index(p.row, p.column), 3);
        }
        lastPath = astar->getCurrentPath();
        for (int i : lastPath) {
            Point p = maze->index1DToPoint(i);
            mazeModel->setData(mazeModel->index(p.row, p.column), 2);
        }
        lastPath = astar->getCurrentPath();
        emit continueCalculate();
        break;
    case AStar::NO_PATH:
        emit noPathCalculate();
        break;
    }
}
