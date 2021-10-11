
#include "DroidStartItem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

#include <iostream>


DroidStartItem::DroidStartItem(int x, int y, double r)
:
    QGraphicsEllipseItem(x, y, r*2, r*2)
{
    m_x = x;
    m_y = y;

    m_radius = r;

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

double DroidStartItem::radius() const
{
    return m_radius;
}

QRectF DroidStartItem::boundingRect() const
{
    return QRectF(m_x, m_y, m_radius*2, m_radius*2);
}

QPainterPath DroidStartItem::shape() const
{
    QPainterPath path;
    path.addRect(m_x, m_y, m_radius*2, m_radius*2);
    return path;
}

void DroidStartItem::paint(QPainter* painter, 
                         const QStyleOptionGraphicsItem* option,
                         QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? m_color.darker(150) : m_color;
    if (option->state & QStyle::State_MouseOver)
    {
        fillColor = fillColor.lighter(125);
    }

    // draw a bounding rect around the object for debugging purposes
    {
        painter->drawRect(m_x, m_y, m_radius*2, m_radius*2);
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

    // painter->drawEllipse(m_x, m_y, m_radius*2, m_radius*2);
    QImage  image(":/bb8.jpg");
    // image.scaledToHeight(boundingRect().height());
    // QPixmap pixmap(":/deathstar.png");

    // the image is 64x64.
    // qreal scaleFactor =  boundingRect().width() / pixmap.size().width();
    // pixmap.setScale(scaleFactor);
    // std::clog << "the scale factor is: " << scaleFactor << std::endl;
    // std::clog << "the pixmap size is: " << pixmap.size().width() << ", " << pixmap.size().height() << std::endl;
    // std::clog << "the size of the rr: " << boundingRect().width() << ", " << boundingRect().height() << std::endl;
    
    // QPixmap pixmap(m_radius*2, m_radius*2);
    // pixmap.load(":/deathstar.png");
    // pixmap.scaledToWidth(100);
    // pixmap.scaledToHeight(m_radius*2);
    // painter->drawPixmap(m_x, m_y, pixmap);
    painter->drawImage(QRectF(m_x, m_y, m_radius*2, m_radius*2), image);

    painter->setBrush(b);
}