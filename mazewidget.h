#ifndef MAZEWIDGET_H
#define MAZEWIDGET_H

#include <memory>
#include <QWidget>
#include <QImage>
#include "maze.h"

class QPaintEvent;

class MazeWidget : public QWidget
{
    Q_OBJECT
public:
    MazeWidget(int rows, int cols, QWidget* parent = nullptr);
    virtual ~MazeWidget() {};
protected:
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
private:

    void drawMaze();
    void drawBorderLines();
    void fillRectangle(const QRect& rect);
    QPoint pixelToMazeCoordinates(const QPoint& pixel) const;
    QRect  mazeCoordsToRect(const QPoint& mazeCoords) const;

    int rowBorderLineInterval;
    int colBorderLineInterval;

    bool drawing = false;
    QPoint lastMazeCoord;

    std::unique_ptr<Maze> m_maze;
    QImage mazeImage;
};


#endif
