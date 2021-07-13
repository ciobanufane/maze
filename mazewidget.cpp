#include <QImage>
#include <QPainter>
#include <QPaintEvent>

#include "mazewidget.h"

MazeWidget::MazeWidget(int rows, int cols, QWidget* parent)
    : QWidget(parent), m_maze(std::make_unique<Maze>(rows, cols))
{
    mazeImage = QImage(width(),height(),QImage::Format_RGB32);
    mazeImage.fill(Qt::white);

    colBorderLineInterval = (width() % cols) ? width()/cols+1 : width()/cols;
    rowBorderLineInterval = (height() % rows) ? height()/rows+1 : height()/rows;

    drawBorderLines();
    drawMaze();
}

void MazeWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, mazeImage, dirtyRect);
}

void MazeWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        lastMazeCoord = pixelToMazeCoordinates(event->pos());
        drawing = true;
    }
}

void MazeWidget::mouseMoveEvent(QMouseEvent* event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPoint nextMazeCoord = pixelToMazeCoordinates(event->pos());
        if (lastMazeCoord != nextMazeCoord){
        //maze->setWall(lastMazeCoord);
            fillRectangle(mazeCoordsToRect(lastMazeCoord));
            lastMazeCoord = nextMazeCoord;
        }
    }
}

void MazeWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        //maze->setWall(lastMazeCoord);
        fillRectangle(mazeCoordsToRect(lastMazeCoord));
        drawing = false;
    }
}

void MazeWidget::drawMaze()
{

}

void MazeWidget::drawBorderLines()
{
    QPainter painter(&mazeImage);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    for(int count = 0; count < m_maze->rows()+1; ++count)
        painter.drawLine(0,rowBorderLineInterval*count, width(),rowBorderLineInterval*count);
     for(int count = 0; count < m_maze->columns()+1; ++count)
         painter.drawLine(colBorderLineInterval*count,0,colBorderLineInterval*count,height());
    update();
}

void MazeWidget::fillRectangle(const QRect& rect)
{
    QPainter painter(&mazeImage);
    painter.fillRect(rect, QBrush(Qt::red, Qt::SolidPattern));
    update(rect);
}

QPoint MazeWidget::pixelToMazeCoordinates(const QPoint& pixel) const
{
    QPoint mazeCoords;
    mazeCoords.setX(pixel.y() / rowBorderLineInterval);
    mazeCoords.setY(pixel.x() / colBorderLineInterval);
    return mazeCoords;
}

QRect MazeWidget::mazeCoordsToRect(const QPoint& mazeCoords) const
{
    QPoint topLeft;
    topLeft.setX(mazeCoords.y()*colBorderLineInterval+1);
    topLeft.setY(mazeCoords.x()*rowBorderLineInterval+1);

    QPoint botRight;
    botRight.setX((mazeCoords.y()+1)*colBorderLineInterval-1);
    botRight.setY((mazeCoords.x()+1)*rowBorderLineInterval-1);

    return QRect(topLeft, botRight);
}
