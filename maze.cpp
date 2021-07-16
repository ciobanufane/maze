#include "maze.h"

#include <stdexcept>
#include <cmath>
#include <chrono>
#include <random>

Maze::Maze(int rows, int columns)
    : m_rows(rows), m_columns(columns)
{
    m_maze = std::vector<int>(rows*columns, 0);
}

int Maze::rows() const
{
    return m_rows;
}

int Maze::columns() const
{
    return m_columns;
}

int Maze::position(Point currentPoint) const
{
    return position(pointToIndex1D(currentPoint));
}

int Maze::position(int index1D) const
{
    isValidIndex1D(index1D);
    return m_maze[index1D];
}

bool Maze::setPart(Point currentPoint, int part)
{
    return setPart(pointToIndex1D(currentPoint), part);
}

bool Maze::setPart(int index1D, int part)
{
    isValidIndex1D(index1D);
    m_maze[index1D] = part;
    return true;
}

int Maze::getCost(Point currentPoint, Point neighborPoint) const
{

    isValidPoint(currentPoint);
    isValidPoint(neighborPoint);

    int length = 0;
    int diffRow = (neighborPoint.x - currentPoint.x);
    int diffColumn = (neighborPoint.y - currentPoint.y);
    length += diffRow >= 0 ? diffRow : -1*diffRow;
    length += diffColumn >= 0 ? diffColumn : -1*diffColumn;
    return length;
}

int Maze::getCost(int current1D, int neighbor1D) const
{
    return getCost(index1DToPoint(current1D), index1DToPoint(neighbor1D));
}

std::vector<Point> Maze::getNeighbors(Point currentPoint) const
{

    isValidPoint(currentPoint);

    if (m_maze[pointToIndex1D(currentPoint)] == Maze::WALL)
        return std::vector<Point>();

    std::vector<Point> neighbors;

    int index = pointToIndex1D({currentPoint.x, currentPoint.y-1});
    if (currentPoint.y-1 >= 0 && m_maze[index] != Maze::WALL)
        neighbors.push_back({currentPoint.x, currentPoint.y-1});

    index = pointToIndex1D({currentPoint.x, currentPoint.y+1});
    if (currentPoint.y+1 != m_columns && m_maze[index] != Maze::WALL)
        neighbors.push_back({currentPoint.x, currentPoint.y+1});

    index = pointToIndex1D({currentPoint.x-1, currentPoint.y});
    if (currentPoint.x-1 >= 0 && m_maze[index] != Maze::WALL)
        neighbors.push_back({currentPoint.x-1, currentPoint.y});

    index = pointToIndex1D({currentPoint.x+1, currentPoint.y});
    if (currentPoint.x+1 != m_rows && m_maze[index] != Maze::WALL)
        neighbors.push_back({currentPoint.x+1, currentPoint.y});

    return neighbors;
}

std::vector<int> Maze::getNeighbors(int current1D) const
{

    isValidIndex1D(current1D);

    if (m_maze[current1D] == Maze::WALL)
        return std::vector<int>();

    std::vector<int> neighbors;
    std::vector<Point> temp = getNeighbors(index1DToPoint(current1D));

    for (auto it = temp.begin(); it != temp.end(); ++it)
        neighbors.push_back(pointToIndex1D(*it));

    return neighbors;
}

void Maze::isValidIndex1D(int index1D) const
{
    if (index1D >= 0 && index1D < m_rows*m_columns)
        return;
    throw std::out_of_range("invalid index: " + std::to_string(index1D));
}

void Maze::isValidPoint(Point point) const
{
    isValidIndex1D(pointToIndex1D(point));
}

Point Maze::index1DToPoint(int index1D) const
{
    int column = index1D % m_columns;
    int row = index1D / m_columns;
    return {row, column};
}

int Maze::pointToIndex1D(Point point) const
{
    return point.x*m_columns+point.y;
}

