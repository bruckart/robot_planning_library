

#ifndef DROIDSTARTITEM_H
#define DROIDSTARTITEM_H

#include <QGraphicsEllipseItem>
#include <QColor>


class DroidStartItem : public QGraphicsEllipseItem
{
public:
    DroidStartItem(int x, int y, double r);

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

#endif // DROIDSTARITEM_H