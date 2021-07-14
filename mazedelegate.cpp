#include "mazedelegate.h"
#include "maze.h"
#include "astar.h"

#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>

MazeDelegate::MazeDelegate(QObject *parent)
    : QAbstractItemDelegate(parent), row(0), col(0)
{
    colorMap.insert({Maze::EMPTY, Qt::white});
    colorMap.insert({Maze::WALL, Qt::gray});
    colorMap.insert({AStar::CURRENT_PATH, Qt::red});
    colorMap.insert({AStar::VISITED, Qt::green});
}

void MazeDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{

    bool ok;
    int value = index.model()->data(index, Qt::DisplayRole).toInt(&ok);

    if (!ok)
        return;

    painter->save();
    painter->fillRect(option.rect, colorMap.at(value));
    painter->restore();

    painter->drawRect(option.rect);
}

QSize MazeDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& /* index */) const
{
    return QSize(option.rect.width(), option.rect.height());
}

bool MazeDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& /* option */, const QModelIndex& index)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
        if (model->data(index, Qt::DisplayRole) != AStar::CURRENT_PATH)
            model->setData(index, Maze::WALL);
        return true;
    case QEvent::MouseMove:
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->buttons() & Qt::LeftButton && model->data(index, Qt::DisplayRole) != AStar::CURRENT_PATH)
            model->setData(index, Maze::WALL);
        return true;
    }
    case QEvent::KeyPress:
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_A:
        {
            QTimer *timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, [this,model](){testWall(model);});
            timer->start(10);
            return true;
        }
        default:
            return true;
        }
    }
    default:
        return true;
    }
}

void MazeDelegate::testWall(QAbstractItemModel* model)
{
    if (col == model->columnCount()) {
        col = 0;
        row++;
    }
    if (row == model->rowCount())
        return;
    model->setData(model->index(row,col++), Maze::WALL);
}
