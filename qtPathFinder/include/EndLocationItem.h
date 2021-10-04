

#ifndef ENDLOCATIONITEM_H
#define ENDLOCATIONITEM_H

#include <QGraphicsEllipseItem>
#include <QColor>


class EndLocationItem : public QGraphicsEllipseItem
{
public:
    EndLocationItem(int x, int y, double radius);
    
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

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

#endif // ENDLOCATIONITEM_H
