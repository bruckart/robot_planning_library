

#include "MyGraphicsView.h"


#include "DeathStarItem.h"
#include "DroidStartItem.h"
#include "DroidEndItem.h"

#include <iostream>
#include <QAbstractButton>
#include <QGraphicsRectItem>
#include <QStatusBar>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

#include "PathFinder.h"

#include <sstream>


MyGraphicsView::MyGraphicsView(QWidget* parent)
:
    QGraphicsView(parent),
    m_droidStartLocationItem(NULL),
    m_droidEndLocationItem(NULL),
    m_scene(new MyGraphicsScene(this))
{
    // this->ensureVisible(m_scene->sceneRect());
    this->fitInView(
        m_scene->itemsBoundingRect(),
        Qt::KeepAspectRatio);

    setScene(m_scene);

    // cooresponds to the defaults in the main widget
    setFixedSize(400, 300);
    m_scene->setSceneRect(0, 0, 400, 300);
}

MyGraphicsView::~MyGraphicsView()
{
    delete m_droidStartLocationItem;
    delete m_droidEndLocationItem;

    delete m_scene;
}

void MyGraphicsView::loadFile(const QString& filename)
{
    QFile file( filename );
    if (file.open(QIODevice::ReadWrite))
    {
        // clear the scene
        clear();
    
        QTextStream stream(&file);
        QString contents = stream.readAll();

        QStringList lines = contents.split("\n");
    
        double ownshipRadius;

        for (int i = 0; i < lines.size(); ++i)
        {
            QString line = lines.at(i);

            QStringList tokens = line.split(" ");
            if (tokens.at(0) == "scene_size:")
            {
                double sceneWidth = tokens.at(1).toDouble();
                double sceneHeight = tokens.at(2).toDouble();
                m_scene->setSceneRect(0, 0, sceneWidth, sceneHeight);
            }
            else if (tokens.at(0) == "ownship_radius:")
            {
                ownshipRadius = tokens.at(1).toDouble();
            }
            else if (tokens.at(0) == "start_location_item:")
            {
                int startLocationX = tokens.at(1).toInt();
                int startLocationY = tokens.at(2).toInt();
                addStartLocation(startLocationX, startLocationY, ownshipRadius);
            }
            else if (tokens.at(0) == "end_location_item:")
            {
                int endLocationX = tokens.at(1).toInt();
                int endLocationY = tokens.at(2).toInt();
                addEndLocation(endLocationX, endLocationY, ownshipRadius);
            }
            else if (tokens.at(0) == "obstacle:")
            {
                int obsLocationX = tokens.at(1).toInt();
                int obsLocationY = tokens.at(2).toInt();
                int obsRadius    = tokens.at(3).toInt();
                addDeathStar(obsLocationX, obsLocationY, obsRadius);
            }
        }
    }
}

void MyGraphicsView::saveFile(const QString& filename)
{
    QFile file(filename);
    // clear the contents
    file.resize(0);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << "scene_size: " << m_scene->sceneRect().width() << " " << m_scene->sceneRect().height() << "\n"
               << "ownship_radius: " << dynamic_cast<DroidStartItem*>(m_droidStartLocationItem)->radius() << "\n"
               << "start_location_item: " << m_droidStartLocationItem->x() << " " << m_droidStartLocationItem->y() << "\n"
               << "end_location_item: " << m_droidEndLocationItem->x() << " " << m_droidEndLocationItem->y() << "\n";

        // Save each obstacle item with his location and size.
        QList<QGraphicsItem*> items = m_scene->items();
        for (unsigned int i = 0; i < items.size(); ++i)
        {
            QGraphicsItem* item = items.at(i);
            if ((m_droidStartLocationItem == item) || (m_droidEndLocationItem == item)) continue;

            // save the obstacle
            stream << "obstacle: " << item->x() << " " << item->y() << " " << dynamic_cast<DeathStarItem*>(item)->radius() << "\n";
        }
    }
}

void MyGraphicsView::updateSceneWidth(int width)
{
    QRectF sceneRect = m_scene->sceneRect();
    m_scene->setSceneRect(0, 0, width, sceneRect.height());
    setFixedWidth(width);
    clear();
}

void MyGraphicsView::updateSceneHeight(int height)
{
    QRectF sceneRect = m_scene->sceneRect();
    m_scene->setSceneRect(0, 0, sceneRect.width(), height);
    setFixedHeight(height);
    clear();
}

void MyGraphicsView::clear()
{
    // setupMatrix();
    // this->ensureVisible(QRectF(0, 0, 0, 0));
    m_scene->clear();
}

void MyGraphicsView::generatePath()
{
    // Check that the start location and end location are specified.
    bool startLocationInScene = false;
    bool endLocationInScene = false;

    QList<QGraphicsItem*> items = m_scene->items();
    for (unsigned int i = 0; i < items.size(); ++i)
    {
        QGraphicsItem* item = items.at(i);

        if (m_droidStartLocationItem == item)
        {
            startLocationInScene = true;
        }
        else if (m_droidEndLocationItem == item)
        {
            endLocationInScene = true;
        }

        if (startLocationInScene && endLocationInScene) break;
    }

    if (!startLocationInScene)
    {
        int ret = QMessageBox::warning(
                    this, 
                    tr("qtPathFinder"),
                    tr("The start location has not been specified!\n"
                       "Please specify a start and end location before path generation."),
                    QMessageBox::Ok);
        return;
    }
    if (!endLocationInScene)
    {
        int ret = QMessageBox::warning(
                    this, 
                    tr("qtPathFinder"),
                    tr("The end location has not been specified!\n"
                       "Please specify a start and end location before path generation."),
                    QMessageBox::Ok);
        return;
    }

    PathFinder pf;
    //***
    // Algorithmic Approach:
    // Overlay QGraphicsRectItems throughout the scene to determine if it collides 
    // with a death stars. If so, remove it from the data structure. Use the 
    // DroidStartItem QPoint to find which QGraphicsRectItem represents the starting 
    // node and the ending node. After all the nodes and edges are specified, call 
    // the following: 
    // 
    // pf.computePath();
    // pf.printShortestPathTo(lastNode);
    // 
    // The lastNode contains a pointer to the previous node, which traces back
    // to the BB-8 starting position. In this manner, we are using QGraphicsRectItems
    // to detect collions, so that we know which nodes not to instantiate.
    //
    // Lastly, plot the path on the scene by drawing a line from the center of the
    // cooresponding QGraphicsRectItem.
    //***

    int columnIndex = 0;
    int bbRadius = dynamic_cast<DroidStartItem*>(m_droidStartLocationItem)->radius();

    QPoint bbStartPos(m_droidStartLocationItem->x() + bbRadius, m_droidStartLocationItem->y() + bbRadius);
    QPoint bbEndPos(m_droidEndLocationItem->x()     + bbRadius, m_droidEndLocationItem->y() + bbRadius);

    QString startNodeIndexName;
    QString endNodeIndexName;

    QMap<QString, QRect> indexRectMap;

    // Specify the cell size as the BB-8 diameter (radius*2).
    int gridSize = bbRadius * 2;
    for (int x = 0; x < m_scene->width(); x+= gridSize)
    {
        int rowIndex = 0;
        for (int y = 0; y < m_scene->height(); y+=gridSize)
        {
            QGraphicsRectItem* rectItem = m_scene->addRect(x, y, x+gridSize, y+gridSize);

            std::stringstream ss;
            ss << columnIndex << " " << rowIndex;
            QString indexName(QString::fromStdString(ss.str()));

            QRect rect(x, y, x+gridSize, y+gridSize);
        
            if (rect.contains(bbStartPos))
            {
                startNodeIndexName = indexName;
                // Node* n = new Node("s");
            }
            else if (rect.contains(bbEndPos))
            {
                endNodeIndexName = indexName;
                // Node* e = new Node("e");
            }

            // Check whether a death star exists in this cell.
            bool deathStarIntersectsCell = false;
            QList<QGraphicsItem*> items = m_scene->items();
            for (unsigned int i = 0; i < items.size(); ++i)
            {
                QGraphicsItem* item = items.at(i);

                if (m_droidStartLocationItem == item) continue;
                else if (m_droidEndLocationItem == item) continue;

                QRectF deathStarRect = item->boundingRect();
                if (deathStarRect.intersects(rect))
                {
                    deathStarIntersectsCell = true;
                    break;
                }
            }

            if (!deathStarIntersectsCell)
            {
                indexRectMap[indexName] = rect;
            } 

            rowIndex++;
        }
        columnIndex++;
    }

    // Iterate through the map containing all the cells.
    // std::clog << "size of the map is:" << indexRectMap.size() << std::endl;

    QMap<QString, QRect>::const_iterator i = indexRectMap.constBegin();
    while (i != indexRectMap.constEnd())
    {
        std::clog << i.key().toStdString() << std::endl; // cout << i.key() << ": " << i.value() << Qt::endl;
        ++i;
    }
} 

void MyGraphicsView::addStartLocation(int x, int y, int radius)
{
    QList<QGraphicsItem*> items = m_scene->items();
    for (unsigned int i = 0; i < items.size(); ++i)
    {
        QGraphicsItem* item = items.at(i);
        if (m_droidStartLocationItem == item)
        {
            return;
        }
    }
    m_droidStartLocationItem = new DroidStartItem(x, y, radius);
    m_scene->addItem(m_droidStartLocationItem);
}
    
void MyGraphicsView::addEndLocation(int x, int y, int radius)
{
    QList<QGraphicsItem*> items = m_scene->items();
    for (unsigned int i = 0; i < items.size(); ++i)
    {
        QGraphicsItem* item = items.at(i);
        if (m_droidEndLocationItem == item)
        {
            qDebug() << "The DroidEndItem is already in the scene.";
            return;
        }
    }
    m_droidEndLocationItem = new DroidEndItem(x, y, radius);
    m_scene->addItem(m_droidEndLocationItem);
}

void MyGraphicsView::addDeathStar(int x, int y, int radius)
{
    QGraphicsItem *item = new DeathStarItem(x, y, radius);
    m_scene->addItem(item);
}

void MyGraphicsView::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Backspace:
            removeSelectedItems();

            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}

void MyGraphicsView::removeSelectedItems()
{
    QList<QGraphicsItem*> items = m_scene->selectedItems();
    for (unsigned int i = 0; i < items.size(); ++i)
    {
        QGraphicsItem* item = items.at(i);
        m_scene->removeItem(item);
    }
}
