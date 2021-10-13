
#ifndef CELL_H
#define CELL_H

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include <cmath>

#include <iostream>



//***
// A cell represents a entry in the 2D grid. It can be identified as the start
// point, end point, or an obstacle. 
//***
class Cell
{
public:

    enum Type
    {
        STARTING,
        ENDING,
        OBSTACLE,
        OTHER
    };

    Cell(int x, int y,
         int width, int height,
         int rowNumber,
         int colNumber);

    ~Cell();

    std::pair<int, int> index() const
    {
        return m_rowCol;
    }


    Cell* previous()
    {
        return m_previous; 
    }

    void setPrevious(Cell* cell)
    {
        m_previous = cell;
    }

    // This method returns the distance from the starting node.
    int distanceFromStart() const;
    void setDistanceFromStart(int dist);

    // double distanceFromCell(Cell* cell) const
    // {
    //     // qDebug() << "m_center:       " << m_center;
    //     // qDebug() << "other m_center: " << cell->center();

    //     return sqrt(pow(m_center.x() - cell->center().x(), 2) + pow(m_center.y() - cell->center().y(), 2));
    //     // return 0.0;
    // }

    QPoint center() const
    {
        return m_center;
    }

    Type type() const;
    void setType(Type type);

    std::string typeName(Type type) const;

    void setVisited();
    bool visited() const;

    void display(QPainter& painter);

    std::ostream& print(std::ostream& os) const;

private:

    QRect m_rect;

    QPoint m_center;

    std::pair<int, int> m_rowCol;

    Type m_type;

    bool m_visited;

    int m_distanceFromStart;

    // Cell* m_start;
    Cell* m_previous;
};


inline std::ostream& operator<<(std::ostream& os, const Cell& g)
{
    return g.print(os);
}

#endif // CELL_H
