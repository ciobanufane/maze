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

    isValidPoint(currentPoint);

    if (m_maze[pointToIndex1D(currentPoint)] == Maze::WALL)
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
    return point.row*m_columns+point.column;
}


void Maze::generateWalls(int x1, int y1, int x2, int y2, int orientation)
{
    static std::random_device rd;
    static std::mt19937 gen{ rd() ^ (
    (std::mt19937::result_type)std::chrono::system_clock::now().time_since_epoch().count() +
    (std::mt19937::result_type)std::chrono::high_resolution_clock::now().time_since_epoch().count()) };

    if (x2-x1 <= 1 || y2-y1 <= 1)
        return;

    if (orientation == 0) { // vertical
        // find number x3 between x1 and x2
        std::uniform_int_distribution<> vertical(y1+1,y2-1);
        int y3 = vertical(gen);
        // for i in rows, set {i,x3} to WALL
        for (int i = x1; i <= x2; ++i)
            setPart({i,y3}, Maze::WALL);
        // find number y3 between y1 and y2
        std::uniform_int_distribution<> passage(x1,x2);
        int x3 = passage(gen);
        // set {y3,x3} to EMPTY
        setPart({x3,y3}, Maze::EMPTY);
        // recurse horizontal on two sub rectangles (maybe four?)
        generateWalls(x1,y3+1,x3,y2,1);
        generateWalls(x1,y1,x3,y3-1,1);
        generateWalls(x3,y1,x2,y3-1,1);
        generateWalls(x3,y3+1,x2,y2,1);
    } else { // horizontal
        std::uniform_int_distribution<> horizontal(x1+1,x2-1);
        int x3 = horizontal(gen);
        for (int i = y1; i <= y2; ++i)
            setPart({x3,i}, Maze::WALL);
        std::uniform_int_distribution<> passage(y1,y2);
        int y3 = passage(gen);
        setPart({x3,y3}, Maze::EMPTY);
        generateWalls(x1,y3,x3-1,y2,0);
        generateWalls(x1,y1,x3-1,y3,0);
        generateWalls(x3+1,y1,x2,y3,0);
        generateWalls(x3+1,y3,x2,y2,0);
    }

}
