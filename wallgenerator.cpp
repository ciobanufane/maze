#include "wallgenerator.h"
#include "maze.h"
#include "mazemodel.h"

#include <chrono>

WallGenerator::WallGenerator(MazeModel* mazeModel, Point topLeft, Point bottomRight, QObject* parent)
    : QObject(parent), m_mazeModel(mazeModel)
{
    m_wallQueue.push(Wall{Rect{topLeft, bottomRight}, 0});
}

void WallGenerator::generate()
{
    if (m_wallQueue.empty())
        emit finishGeneration();

    Wall wall = m_wallQueue.front();
    Rect rect = wall.rect;
    m_wallQueue.pop();

    if (rect.bottomRight.x-rect.topLeft.x <= 1 ||
        rect.bottomRight.y-rect.topLeft.y <= 1)
        return;

    Rect quadrant1, quadrant2, quadrant3, quadrant4;
    int wallY, wallX;

    if (wall.orientation == 0) { //vertical wall
        std::uniform_int_distribution<> vertical(rect.topLeft.y+1, rect.bottomRight.y-1);
        std::uniform_int_distribution<> passage(rect.topLeft.x, rect.bottomRight.x);
        wallY = vertical(m_gen);
        wallX = passage(m_gen);

        setVerticalWall(rect.topLeft.x, rect.bottomRight.x, wallY);
        m_mazeModel->setData(m_mazeModel->index(wallX, wallY), Maze::EMPTY);

        // x = height, y = width
        quadrant1 = Rect{Point{rect.topLeft.x, wallY+1}, Point{wallX, rect.bottomRight.y}};
        quadrant2 = Rect{rect.topLeft, Point{wallX, wallY-1}};
        quadrant3 = Rect{Point{wallX, rect.topLeft.y}, Point{rect.bottomRight.x, wallY-1}};
        quadrant4 = Rect{Point{wallX, wallY+1}, rect.bottomRight};

    } else { // horizontal wall
        std::uniform_int_distribution<> horizontal(rect.topLeft.x+1, rect.bottomRight.x-1);
        std::uniform_int_distribution<> passage(rect.topLeft.y, rect.bottomRight.y);
        wallX = horizontal(m_gen);
        wallY = passage(m_gen);

        setHorizontalWall(rect.topLeft.y, rect.bottomRight.y, wallX);
        m_mazeModel->setData(m_mazeModel->index(wallX, wallY), Maze::EMPTY);

        quadrant1 = Rect{Point{rect.topLeft.x, wallY}, Point{wallX-1, rect.bottomRight.y}};
        quadrant2 = Rect{rect.topLeft, Point{wallX-1, wallY}};
        quadrant3 = Rect{Point{wallX+1, rect.topLeft.y}, Point{rect.bottomRight.x, wallY}};
        quadrant4 = Rect{Point{wallX+1, wallY}, rect.bottomRight};

    }
    m_wallQueue.push(Wall{quadrant1, chooseOrientation(quadrant1)});
    m_wallQueue.push(Wall{quadrant2, chooseOrientation(quadrant2)});
    m_wallQueue.push(Wall{quadrant3, chooseOrientation(quadrant3)});
    m_wallQueue.push(Wall{quadrant4, chooseOrientation(quadrant4)});

    emit continueGeneration();
}

void WallGenerator::setHorizontalWall(int y1, int y2, int x)
{
    for (int yIndex = y1; yIndex <= y2; ++yIndex)
        m_mazeModel->setData(m_mazeModel->index(x, yIndex), Maze::WALL);
}

void WallGenerator::setVerticalWall(int x1, int x2, int y)
{
    for (int xIndex = x1; xIndex <= x2; ++xIndex)
        m_mazeModel->setData(m_mazeModel->index(xIndex, y), Maze::WALL);
}

int WallGenerator::chooseOrientation(Rect rect)
{
    int width = rect.bottomRight.y - rect.topLeft.y;
    int height = rect.bottomRight.x - rect.topLeft.x;

    if (width < height)
        return 1;
    else
        return 0;
}
