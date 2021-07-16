#ifndef WALLGENERATOR_H
#define WALLGENERATOR_H

#include <QObject>
#include <queue>
#include <random>
#include <chrono>

#include "point.h"

class MazeModel;

struct Rect{
    Point topLeft;
    Point bottomRight;
};

struct Wall
{
    Rect rect;
    int orientation;
};

class WallGenerator : public QObject
{
    Q_OBJECT
public:
    explicit WallGenerator(MazeModel* mazeModel, Point topLeft, Point bottomRight, QObject* parent = nullptr);
signals:
    void finishGeneration();
    void continueGeneration();
public slots:
    void generate();
private:

    void setHorizontalWall(int y1, int y2, int x);
    void setVerticalWall(int x1, int x2, int y);
    int chooseOrientation(Rect rect);

    MazeModel* m_mazeModel;
    std::queue<Wall> m_wallQueue;
    std::random_device m_rd;
    std::mt19937 m_gen {m_rd()^(
    (std::mt19937::result_type)std::chrono::system_clock::now().time_since_epoch().count() +
    (std::mt19937::result_type)std::chrono::high_resolution_clock::now().time_since_epoch().count())};
};

#endif // WALLGENERATOR_H
