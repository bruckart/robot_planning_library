
#include "ObstacleItem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <iostream>


ObstacleItem::ObstacleItem(int x, int y, double r)
:
    QGraphicsEllipseItem(x, y, r*2, r*2)
{
    m_x = x;
    m_y = y;

    m_radius = r;
    m_color = QColor(102, 153, 255);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

double ObstacleItem::radius() const
{
    return m_radius;
}

void ObstacleItem::paint(QPainter* painter, 
                         const QStyleOptionGraphicsItem* option,
                         QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? m_color.darker(150) : m_color;
    if (option->state & QStyle::State_MouseOver)
    {
        fillColor = fillColor.lighter(125);
    }

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
    {
        width += 2;
    }
    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.darker(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawEllipse(m_x, m_y, m_radius*2, m_radius*2);

    painter->setBrush(b);
}

void ObstacleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void ObstacleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void ObstacleItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
