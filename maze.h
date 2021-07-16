#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <algorithm>
#include <random>

#include "point.h"

class Maze
{
public:
    Maze(int rows, int columns);

    enum Part {EMPTY = 0, WALL = 1, LAST_PART = 128};

    int rows() const;
    int columns() const;
    int position(Point currentPoint) const;
    int position(int index1D) const;

    bool setPart(Point currentPoint, int part);
    bool setPart(int index1D, int part);

    int getCost(Point currentPoint, Point neighborPoint) const;
    int getCost(int current1D, int neighbor1D) const;

    std::vector<Point> getNeighbors(Point currentPoint) const;
    std::vector<int> getNeighbors(int index1D) const;

    Point index1DToPoint(int index1D) const;
    int pointToIndex1D(Point point) const;

private:

    void isValidIndex1D(int index1D) const;
    void isValidPoint(Point point) const;

    int m_rows;
    int m_columns;
    std::vector<int> m_maze;
};

#endif
