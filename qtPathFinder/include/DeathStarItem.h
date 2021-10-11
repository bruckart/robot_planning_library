

#ifndef DEATHSTARITEM_H
#define DEATHSTARITEM_H

#include <QGraphicsEllipseItem>
// #include <QKeyEvent>
#include <QColor>


class DeathStarItem : public QGraphicsEllipseItem
{
public:
    DeathStarItem(int x, int y, double r);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *item, 
               QWidget *widget) override;
    
    double radius() const;

private:
    int m_x;
    int m_y;

    double m_radius;

    QColor m_color;
};

#endif // DEATHSTARITEM_H