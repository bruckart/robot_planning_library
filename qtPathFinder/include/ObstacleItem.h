

#ifndef OBSTACLEITEM_H
#define OBSTACLEITEM_H

#include <QGraphicsEllipseItem>
#include <QColor>


class ObstacleItem : public QGraphicsEllipseItem
{
public:
    ObstacleItem(int x, int y, double r);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    
    double radius() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int m_x;
    int m_y;

    double m_radius;

    QColor m_color;
};

#endif // OBSTACLEITEM_H