#ifndef MAZEDELEGATE_H
#define MAZEDELEGATE_H

#include <QAbstractItemDelegate>
#include <map>

class MazeDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    MazeDelegate(QObject* parent = nullptr);
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;
private slots:
    void testWall(QAbstractItemModel* model);
private:
    int row;
    int col;
    std::map<int, Qt::GlobalColor> colorMap;
};

#endif // MAZEDELEGATE_H
