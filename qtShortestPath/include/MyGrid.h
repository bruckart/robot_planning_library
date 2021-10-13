


#ifndef MYGRID_H
#define MYGRID_H

#include "Cell.h"

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>

#include <ostream>


namespace Ui
{
    class MyGrid;
}


// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm



class MyGrid : public QWidget
{
    Q_OBJECT

public:

    MyGrid(QWidget* parent=0);
    virtual ~MyGrid();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    // This method prints the overall grid in ASCII format.
    std::ostream& print(std::ostream& os) const;

protected:

    void paintEvent(QPaintEvent* event) override;

    virtual void keyPressEvent(QKeyEvent * event) override;

public slots:

    // void update();

private:

    // void simulate();

    // This method returns true/false randomly.
    bool randomObstruction() const;

    void step();

    void updateUnvisitedNeighbors(Cell* currentCell);

    double distanceBetween(Cell* cell1, Cell* cell2);



    Cell* smallestCell();

    // std::vector<Cell*> adjacentCells(Cell* cell) const;

    // This method 
    // double distance(Cell* c1, Cell* c2) const;

    Ui::MyGrid* ui;

    // The vector of unvisited cells. Once visited, it is removed and 
    // placed in the vectof of visited cells.
    std::vector<Cell*> m_cells;

    std::vector<Cell*> m_visitedCells;


    Cell* m_startingCell;
    Cell* m_endingCell;

    Cell* m_currentCell;

    QTimer* m_timer;
};

inline std::ostream& operator<<(std::ostream& os, const MyGrid& g)
{
    return g.print(os);
}



// class Cell 



#endif // MYGRID_H
