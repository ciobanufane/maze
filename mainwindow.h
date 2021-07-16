#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class AStar;
class AStarWrapper;
class WallGenerator;
class Maze;
class MazeModel;
class MazeDelegate;
class QTableView;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Maze* maze;
    AStar* astar;
    AStarWrapper* asw;
    WallGenerator* wallgen;
    MazeModel* model;
    QTableView* view;
};

#endif // MAINWINDOW_H
