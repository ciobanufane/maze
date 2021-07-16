#include "astarwrapper.h"
#include "astar.h"
#include "maze.h"
#include "mazemodel.h"

AStarWrapper::AStarWrapper(AStar* astar, MazeModel* mazeModel, QObject *parent)
    : QObject(parent), m_astar(astar), m_mazeModel(mazeModel)
{

}

void AStarWrapper::setPathAndCalculate()
{
    int result = m_astar->calculate();
    switch (result) {
    case AStar::FINISHED:
        setLastPathToModel(AStar::VISITED);
        m_lastPath = m_astar->getCurrentPath();
        setLastPathToModel(AStar::CURRENT_PATH);
        emit finishCalculate();
        break;
    case AStar::CONTINUE:
        setLastPathToModel(AStar::VISITED);
        m_lastPath = m_astar->getCurrentPath();
        setLastPathToModel(AStar::CURRENT_PATH);
        emit continueCalculate();
        break;
    case AStar::NO_PATH:
        emit noPathCalculate();
        break;
    }
}

void AStarWrapper::setLastPathToModel(int value)
{
    for (Point p : m_lastPath) {
        m_mazeModel->setData(m_mazeModel->index(p.x, p.y), value);
    }
}
