

#include "MyGrid.h"
#include "QPainter.h"

#include "ui_MyGrid.h"

#include <QDebug.h>
#include <QRandomGenerator>
#include <iostream>


MyGrid::MyGrid(QWidget* parent)
:
    QWidget(parent),
    ui(new Ui::MyGrid),
    m_cells(),
    m_visitedCells(),
    m_startingCell(NULL),
    m_endingCell(NULL),
    m_currentCell(NULL),
    m_timer(new QTimer(this))
{
    ui->setupUi(this);

    setWindowTitle(QString("qtGrid"));
    setFixedSize(200, 200);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);


    // connect(m_timer, &QTimer::timeout, this, &MyGrid::update);



    // Create cells based upon the map size. Each cell represents a 10x10 rectangle
    // on a grid. Iterate through the map through the x (width()) and then y (height()).
    // (0, 0)   (0, 1)
    // (1, 0)   (1, 1)
    // (2, 0)   (2, 1)
    //
    // Note that all cells are initially marked unvisited.
    //... 
    int colNumber = 0; 
    for (int x = 0; x < width(); x += 20)
    {
        int rowNumber = 0;
        for (int y = 0; y < height(); y += 20)
        {
            Cell* cell = new Cell(x, y, 20, 20,
                                  rowNumber, colNumber);
            m_cells.push_back(cell);

            // QPoint pnt(x, y);
            // painter.drawPoint(pnt);

            rowNumber++;
        }

        colNumber++;
    }


    m_startingCell = m_cells.front();
    m_startingCell->setType(Cell::STARTING);
    m_startingCell->setDistanceFromStart(0);

    m_endingCell = m_cells.back();
    m_endingCell->setType(Cell::ENDING);


    // Add obstacles throughout the map scene.
    unsigned int numCells = m_cells.size();
    // qDebug() << "numCells= " << numCells;
    for (unsigned int i = 1; i < numCells-1; ++i)
    {
        bool obs = randomObstruction();
    
        Cell* cell = m_cells.at(i);
        if (obs) cell->setType(Cell::OBSTACLE);
    }

    m_currentCell = m_startingCell;

    // std::clog << "the number of cells: " << m_cells.size() << std::endl;
    // print(std::clog);
}

MyGrid::~MyGrid()
{
    delete ui;

    delete m_timer;
}

std::ostream& MyGrid::print(std::ostream& os) const
{
    os << "MyGrid Contents:\n"
       << "  Number of Cells: " << m_cells.size() << "\n";

    // for (unsigned int i = 0; i < m_cells.size(); ++i)
    // {
    //     Cell* c = m_cells.at(i);
    //     os << "    (" << c->rowNumber() << ", " << c->columnNumber() << ")\n";
    // }
    
    os << std::endl;

    return os;
}

QSize MyGrid::minimumSizeHint() const
{
    return QSize(200, 200);
}

QSize MyGrid::sizeHint() const
{
    return QSize(200, 200);
}

void MyGrid::paintEvent(QPaintEvent * /* event */)
{
    std::clog << "MyGrid::paintEvent() w(" << width() << ") h(" << height() << ")" << std::endl;

    QPainter painter(this);

    std::vector<Cell*>::iterator it;
    for (it = m_cells.begin(); it != m_cells.end(); ++it)
    {
        Cell* cell = (*it);
        cell->display(painter);
    }

    for (it = m_visitedCells.begin(); it != m_visitedCells.end(); ++it)
    {
        Cell* cell = (*it);
        cell->display(painter);
    }

    // Draw a line detailing the shortest path.
    if (m_endingCell->visited())
    {
        std::clog << "The Shortest Path Distance: " << m_endingCell->distanceFromStart() << std::endl;

        QPen pen(QColor(255, 0, 255)); // MAGENTA
        pen.setWidth(3);
        painter.setPen(pen);

        Cell* c = m_endingCell;

        while (c->previous() != NULL)
        {
            painter.drawLine(c->center().x(), c->center().y(), 
                             c->previous()->center().x(), c->previous()->center().y());

            c = c->previous();
        }
    }
}

void MyGrid::keyPressEvent(QKeyEvent* event)
{
    std::clog << "MyGrid::keyPressEvent()" << std::endl;

    // qDebug() << event->key();
    // qDebug() << event->text();

    if (event->text() == " ")
    {
        std::clog << "spacebar is pressed" << std::endl;
        step();
    }

    QWidget::keyPressEvent(event);
}

bool MyGrid::randomObstruction() const
{
    // We want 10% of the cells to be obstructions, so generate a 
    // random number between 0 and 100. If it is less than 20,
    // return true.
    quint32 obs = QRandomGenerator::global()->bounded(0, 100);
    if (obs < 10) return true;

    return false;
}

void MyGrid::step()
{
    std::clog << "MyGrid::step()" << std::endl;


    // Firstly, check that a starting and ending point was specified.
    if ((m_startingCell == NULL) || (m_endingCell == NULL))
    {
        // qDebug() << "The starting and/or ending cells are NULL!";
        return;
    }


    if (m_endingCell->visited())
    {
        std::clog << "The destination cell has been marked visited" << std::endl;
        return;
    }

    // For the current node, consider all of its unvisited neighbours and calculate
    // their tentative distances through the current node. Compare the newly calculated 
    // tentative distance to the current assigned value and assign the smaller one. 
    m_currentCell = smallestCell();
    // std::clog << "the current/smallest cell is at: " << m_currentCell->index().first << ", " << m_currentCell->index().second << std::endl;
    updateUnvisitedNeighbors(m_currentCell);
}

void MyGrid::updateUnvisitedNeighbors(Cell* currentCell)
{
    std::clog << "MyGrid::updateUnvisitedNeighbors" << std::endl;
    
    std::vector<Cell*> adjacentCells;

    std::pair<int, int> cellIndex = currentCell->index();
    int currentRow = cellIndex.first;
    int currentCol = cellIndex.second;

    std::clog << "Current Cell Index: " << currentRow << " , " << currentCol << std::endl;

    std::pair<int, int> upperLeftIndex = std::make_pair(currentRow-1, currentCol-1);
    std::pair<int, int> upperMiddleIndex = std::make_pair(currentRow-1, currentCol);
    std::pair<int, int> upperRightIndex = std::make_pair(currentRow-1, currentCol+1);
    
    std::pair<int, int> leftIndex = std::make_pair(currentRow, currentCol-1);
    std::pair<int, int> rightIndex = std::make_pair(currentRow, currentCol+1);

    std::pair<int, int> lowerLeftIndex = std::make_pair(currentRow+1, currentCol-1);
    std::pair<int, int> lowerMiddleIndex = std::make_pair(currentRow+1, currentCol);
    std::pair<int, int> lowerRightIndex = std::make_pair(currentRow+1, currentCol+1);


    std::vector<std::pair<int, int> > adjacentIndices;
    adjacentIndices.push_back(upperLeftIndex);
    adjacentIndices.push_back(upperMiddleIndex);
    adjacentIndices.push_back(upperRightIndex);
    adjacentIndices.push_back(leftIndex);
    adjacentIndices.push_back(rightIndex);
    adjacentIndices.push_back(lowerLeftIndex);
    adjacentIndices.push_back(lowerMiddleIndex);
    adjacentIndices.push_back(lowerRightIndex);

    if (adjacentIndices.size() == 0)
    {
        std::clog << "No adjacent cells were found for index [" << currentRow << ", " << currentCol << "]!" << std::endl;
    }

    std::vector<Cell*>::const_iterator it;
    // Iterate through all the unvisited cells and return the adjacent cells.
    for (it = m_cells.begin(); it != m_cells.end(); ++it)
    {
        Cell* otherCell = (*it);
    
        // ignore yourself
        if (otherCell == currentCell ) continue;

        // ignore obstacles
        if (otherCell->type() == Cell::OBSTACLE) continue;

        // only query unvisited cells (they will be removed)
        // if (otherCell->visited()) continue;
    
        int otherCellRowNumber = otherCell->index().first; // otherCell->rowNumber();
        int otherCellColNumber = otherCell->index().second; // columnNumber();

        // std::clog << "otherCell Row/Col: " << otherCellRowNumber << ", " << otherCellColNumber << std::endl;

        // If the cell exceeds the map size, skip it and continue.
        if ((otherCellRowNumber < 0) || (otherCellRowNumber > height())) continue;
        if ((otherCellColNumber < 0) || (otherCellColNumber > width())) continue;

        for (int i = 0; i < adjacentIndices.size(); ++i)
        {
            int adjRow = adjacentIndices.at(i).first;
            int adjCol = adjacentIndices.at(i).second;

            if ((otherCellRowNumber == adjRow) && (otherCellColNumber == adjCol))
            {
                adjacentCells.push_back(otherCell);
            }
        }
    }
    std::clog << "the number of adjacent cells is " << adjacentCells.size() << std::endl;


    // Iterate through the adjacent cells and update their distance.
    for (it = adjacentCells.begin(); it != adjacentCells.end(); ++it)
    {
        Cell* adjacentCell = *it;

        double dist = distanceBetween(currentCell, *it) + currentCell->distanceFromStart();
        // std::clog << "The distance between the cell is: " << dist << std::endl;

        if (dist < adjacentCell->distanceFromStart())
        {
            adjacentCell->setDistanceFromStart(dist);
            adjacentCell->setPrevious(currentCell);
        }
    }

    // Remove the current node from the unvisited set.
    currentCell->setVisited();

    std::clog << "Removing the selected cell from the vector" << std::endl;
    std::clog << "before " << m_cells.size() << std::endl;
    for (it = m_cells.begin(); it != m_cells.end(); ++it)
    {
        Cell* cell = (*it);
        if (cell == currentCell)
        {
            m_visitedCells.push_back(cell);
            m_cells.erase(it);
            break;
        }
    }
    std::clog << "after " << m_cells.size() << std::endl;


    update();
}

double MyGrid::distanceBetween(Cell* c1, Cell* c2)
{
    return sqrt(pow(c1->center().x() - c2->center().x(), 2) + pow(c1->center().y() - c2->center().y(), 2));
}

Cell* MyGrid::smallestCell()
{
//     if (m_cells.empty()) return NULL;

    int smallestPosition = 0;

    Cell* smallestCell = m_cells.front();
    for (int i = 1; i < m_cells.size(); ++i)
    {
        Cell* cell = m_cells.at(i);
        if (cell->distanceFromStart() < smallestCell->distanceFromStart())
        {
            smallestCell = cell;
            smallestPosition = i;
        }
    }

    // Remove that cell from the vector of cells.
    // m_cells.erase(m_cells.begin() + smallestPosition);
    return smallestCell;
}
