

#include "Cell.h"

#include <limits>
#include <iostream>

Cell::Cell(int x, int y, int width, int height, 
           int rowNumber, int colNumber)
:
    m_rect(x, y, width, height),
    m_center(x + width/2, y + height/2),
    m_rowCol(std::pair<int, int>(rowNumber, colNumber)),
    m_type(OTHER),
    m_distanceFromStart(std::numeric_limits<int>::max()),
    m_visited(false),
    m_previous(NULL)
{
}

Cell::~Cell()
{
}

std::ostream& Cell::print(std::ostream& os) const
{
    os << "Cell ";
    
    // [" << m_rowNumber << ", " << m_colNumber << "]\n"
    //     << "  Rect: (" << m_upperLeftPoint.x()  << ", " << m_upperLeftPoint.y() << ", " << m_lowerRightPoint.x() << ", " << m_lowerRightPoint.y() << ")\n"
    //     << "  Type: " << typeName(m_type) << "\n";

    return os;
}


int Cell::distanceFromStart() const { return m_distanceFromStart; }
void Cell::setDistanceFromStart(int dist) { m_distanceFromStart = dist; }

Cell::Type Cell::type() const { return m_type; }
void Cell::setType(Type type) {  m_type = type; }

std::string Cell::typeName(Type type) const
{
    if (type == 0)
    {
        return "STARTING";
    }
    else if (type == 1)
    {
        return "ENDING";
    }
    else if (type == 2)
    {
        return "OBSTACLE";
    }
    return "VACANT";
}

void Cell::setVisited() { m_visited = true; }
bool Cell::visited() const { return m_visited; } 



void Cell::display(QPainter& painter)
{
    painter.save();

    if (m_type == OBSTACLE)
    {
        QBrush brush(QColor(0, 0, 255)); 
        painter.setBrush(brush);
        painter.drawRect(m_rect);
        painter.restore();
        return;
    }



    // if this is a starting point, outline the cell GREEN if unvisited, and filled
    // if visited.
    if (m_type == STARTING)
    {
        if (m_visited)
        {
            QPen pen;
            pen.setColor(QColor(200, 200, 220));
            painter.setPen(pen);

            QBrush brush(QColor(0, 255, 0));
            painter.setBrush(brush);
            painter.drawRect(m_rect);
        }
        else
        {
            QPen pen(QColor(0, 255, 0));
            pen.setWidth(3);
            painter.setPen(pen);

            QPointF tl = m_rect.topLeft() + QPointF(1, 1);;
            QPointF tr = m_rect.topRight() + QPointF(0, 1);
            QPointF bl = m_rect.bottomLeft() + QPointF(1, 0);
            QPointF br = m_rect.bottomRight();

            painter.drawLine(tl, tr);
            painter.drawLine(tl, bl);
            painter.drawLine(tr, br);
            painter.drawLine(bl, br);
        }
    }
    // if this is a starting point, outline the cell RED if unvisited, and filled
    // if visited.
    else if (m_type == ENDING)
    {
        if (m_visited)
        {
            QBrush brush(QColor(255, 0, 0));
            painter.setBrush(brush);
            painter.drawRect(m_rect);
        }
        else
        {
            QPen pen(QColor(255, 0, 0));
            pen.setWidth(2);
            painter.setPen(pen);

            QPointF tl = m_rect.topLeft() + QPointF(1, 1);;
            QPointF tr = m_rect.topRight() + QPointF(0, 1);
            QPointF bl = m_rect.bottomLeft() + QPointF(1, 0);
            QPointF br = m_rect.bottomRight();

            painter.drawLine(tl, tr);
            painter.drawLine(tl, bl);
            painter.drawLine(tr, br);
            painter.drawLine(bl, br);
        }
    }
    else if (m_type == OTHER)
    {
        // if (m_visited)
        // {


        //     QBrush brush;
        //     brush.setColor(QColor(204, 255, 51));
        //     painter.setBrush(brush);

        //     painter.drawRect(m_rect);
        // }
        // else
        // {
        //     QPen pen;
        //     pen.setColor(QColor(200, 200, 220));
        //     painter.setPen(pen);

        //     QBrush brush;
        //     brush.setColor(QColor(55));
        //     painter.setBrush(brush);

        //     painter.drawRect(m_rect);
        // }

        if (m_visited)
        {
            // This draws the cells in a light grey border.
            QPen pen(QColor(200, 200, 220));
            painter.setPen(pen);

            QBrush brush(QColor(224, 224, 235));
            painter.setBrush(brush);

            painter.drawRect(m_rect);
        }
        else
        {
            QPen pen(QColor(200, 200, 220));
            painter.setPen(pen);

            QBrush brush(QColor(255, 255, 255));
            painter.setBrush(brush);

            painter.drawRect(m_rect);
        }

    }


    if (m_previous)
    {
        QPen pen(QColor(153, 102, 255));
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawLine(m_previous->center(), center());
    }


    // if (m_distanceFromStart < std::numeric_limits<int>::max())
    // {
    //     painter.save();
    //     std::clog << "drawing distnace value: " << m_distanceFromStart << std::endl;
    //     QPen pen;
    //     painter.setPen(pen);

    //     QFont font("Times", 8);
    //     // font.setStyleStrategy(QFont::ForceOutline);
    //     painter.setFont(font);
    //     painter.scale(0.5, 0.5);
    //     painter.drawText(m_center.x(), m_center.y(), QString(m_distanceFromStart));

    // }

    painter.restore();
}