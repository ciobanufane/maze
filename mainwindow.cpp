#include "mainwindow.h"
#include "maze.h"
#include "mazemodel.h"
#include "mazedelegate.h"
#include "astar.h"
#include "astarwrapper.h"

#include <QTableView>
#include <QHeaderView>
#include <QEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QSize size(1000,1000);
    int rows = 50, columns = 50;
    int height = size.height() / rows;
    int width = size.width() / columns;

    maze    = new Maze(rows, columns);
    astar   = new AStar(maze, 0, rows*columns-1);
    model   = new MazeModel(maze, astar, this);
    asw     = new AStarWrapper(astar, maze, model, this);

    view = new QTableView;
    view->setShowGrid(false);
    view->horizontalHeader()->hide();
    view->verticalHeader()->hide();
    view->horizontalHeader()->setMinimumSectionSize(1);
    view->verticalHeader()->setMinimumSectionSize(1);
    view->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(size);
    view->setModel(model);

    for(int i = 0; i < rows; ++i)
        view->setRowHeight(i, height);
    for(int i = 0; i < columns; ++i)
        view->setColumnWidth(i, width);

    MazeDelegate* delegate = new MazeDelegate(this);
    view->setItemDelegate(delegate);

    setCentralWidget(view);
    setFixedSize(size);

    maze->generateWalls(0,0,maze->rows()-1, maze->columns()-1, 0);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]{asw->setPathAndCalculate();});
    connect(asw, SIGNAL(finishCalculate()), timer, SLOT(stop()));
    connect(asw, SIGNAL(noPathCalculate()), timer, SLOT(stop()));
    timer->start(10);
}

MainWindow::~MainWindow()
{
    delete maze;
    delete astar;
    delete asw;
}

