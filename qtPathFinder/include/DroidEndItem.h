

#ifndef DROIDENDITEM_H
#define DROIDENDITEM_H

#include <QGraphicsEllipseItem>
// #include <QKeyEvent>
#include <QColor>


class DroidEndItem : public QGraphicsEllipseItem
{
public:
    DroidEndItem(int x, int y, double r);

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

#endif // DROIDENDITEM_H