#include "maze.h"

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
    if (!validIndex1D(index1D))
        return -1;

    return m_maze[index1D];
}

bool Maze::setPart(Point currentPoint, int part)
{
    return setPart(pointToIndex1D(currentPoint), part);
}

bool Maze::setPart(int index1D, int part)
{
    if (!validIndex1D(index1D))
        return false;

    m_maze[index1D] = part;
    return true;
}

int Maze::getCost(Point currentPoint, Point neighborPoint) const
{
    if (!validPoint(currentPoint) || !validPoint(neighborPoint))
        return -1;

    int length = 0;
    int diffRow = (neighborPoint.row - currentPoint.row);
    int diffColumn = (neighborPoint.column - currentPoint.column);
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
    if (!validPoint(currentPoint) ||
            m_maze[pointToIndex1D(currentPoint)] == Maze::WALL)
        return std::vector<Point>();

    std::vector<Point> neighbors;

    int index = pointToIndex1D({currentPoint.row, currentPoint.column-1});
    if (currentPoint.column-1 >= 0 && m_maze[index] != Maze::WALL)
        neighbors.push_back({currentPoint.row, currentPoint.column-1});

    index = pointToIndex1D({currentPoint.row, currentPoint.column+1});
    if (currentPoint.column+1 != m_columns && m_maze[index] != Maze::WALL)
        neighbors.push_back({currentPoint.row, currentPoint.column+1});

    index = pointToIndex1D({currentPoint.row-1, currentPoint.column});
    if (currentPoint.row-1 >= 0 && m_maze[index] != Maze::WALL)
        neighbors.push_back({currentPoint.row-1, currentPoint.column});

    index = pointToIndex1D({currentPoint.row+1, currentPoint.column});
    if (currentPoint.row+1 != m_rows && m_maze[index] != Maze::WALL)
        neighbors.push_back({currentPoint.row+1, currentPoint.column});

    return neighbors;
}

std::vector<int> Maze::getNeighbors(int current1D) const
{
    if (!validIndex1D(current1D) || m_maze[current1D] == Maze::WALL)
        return std::vector<int>();

    std::vector<int> neighbors;

    if (current1D % m_columns != 0 && m_maze[current1D-1] != Maze::WALL)
        neighbors.push_back(current1D-1);

    if ((current1D+1) % m_columns != 0 && m_maze[current1D+1] != Maze::WALL)
        neighbors.push_back(current1D+1);

    if (current1D+m_columns < m_rows*m_columns && m_maze[current1D+m_columns] != Maze::WALL)
        neighbors.push_back(current1D+m_columns);

    if (current1D-m_columns >= 0 && m_maze[current1D-m_columns] != Maze::WALL)
        neighbors.push_back(current1D-m_columns);

    return neighbors;
}

bool Maze::validIndex1D(int index1D) const
{
    if (index1D >= 0 && index1D < m_rows*m_columns)
        return true;
    return false;
}

bool Maze::validPoint(Point point) const
{
    if (point.row >= 0 && point.row < m_rows &&
            point.column >= 0 && point.column < m_columns)
        return true;
    return false;
}

Point Maze::index1DToPoint(int index1D) const
{
    int column = index1D % m_columns;
    int row = index1D / m_columns;
    return {row, column};
}

int Maze::pointToIndex1D(Point point) const
{
    return point.row*m_columns+point.column;
}

bool Maze::generateWalls()
{
    std::queue<Point> q;
    return true;
}
