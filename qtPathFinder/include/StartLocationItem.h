

#ifndef STARTLOCATIONITEM_H
#define STARTLOCATIONITEM_H

#include <QGraphicsEllipseItem>
#include <QColor>


class StartLocationItem : public QGraphicsEllipseItem
{
public:
    StartLocationItem(int x, int y, double radius);

    void paint(QPainter *painter, 
               const QStyleOptionGraphicsItem *item,
               QWidget *widget) override;

    double radius() const;
    void setRadius(double r);

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

#endif // STARTLOCATIONITEM_H
