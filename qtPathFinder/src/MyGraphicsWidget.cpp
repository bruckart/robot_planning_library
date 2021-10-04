

#include "MyGraphicsWidget.h"

#include "ObstacleItem.h"
#include "StartLocationItem.h"
#include "EndLocationItem.h"

#include <iostream>
#include <QAbstractButton>
#include <QStatusBar>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>

#include "PathFinder.h"


MyGraphicsWidget::MyGraphicsWidget(QWidget* parent)
:
    QGraphicsView(parent),
    m_startLocationItem(new StartLocationItem(0, 0, 0)),
    m_endLocationItem(new EndLocationItem(0, 0, 0)),
    m_scene(new QGraphicsScene(this))
{
    setScene(m_scene);
}

MyGraphicsWidget::~MyGraphicsWidget()
{
    delete m_startLocationItem;
    delete m_endLocationItem;

    delete m_scene;
}

void MyGraphicsWidget::loadFile(const QString& filename)
{
    std::clog << "MyGraphicsWidget::loadFile()" << std::endl;

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
                addObstacle(obsLocationX, obsLocationY, obsRadius);
            }
        }
    }
}

void MyGraphicsWidget::saveFile(const QString& filename)
{
    std::clog << "MyGraphicsWidget::saveFile()" << std::endl;

    QFile file(filename);
    // clear the contents
    file.resize(0);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << "scene_size: " << m_scene->sceneRect().width() << " " << m_scene->sceneRect().height() << "\n"
               << "ownship_radius: " << dynamic_cast<StartLocationItem*>(m_startLocationItem)->radius() << "\n"
               << "start_location_item: " << m_startLocationItem->x() << " " << m_startLocationItem->y() << "\n"
               << "end_location_item: " << m_endLocationItem->x() << " " << m_endLocationItem->y() << "\n";

        // Save each obstacle item with his location and size.
        QList<QGraphicsItem*> items = m_scene->items();
        for (unsigned int i = 0; i < items.size(); ++i)
        {
            QGraphicsItem* item = items.at(i);
            if ((m_startLocationItem == item) || (m_endLocationItem == item)) continue;

            // save the obstacle
            stream << "obstacle: " << item->x() << " " << item->y() << " " << dynamic_cast<ObstacleItem*>(item)->radius() << "\n";
        }
    }
}
    
void MyGraphicsWidget::updateOwnshipRadius(double radius)
{
    std::clog << "MyGraphicsWidget::updateOwnshipRadius()" << std::endl;

    dynamic_cast<StartLocationItem*>(m_startLocationItem)->setRadius(radius);;
    dynamic_cast<EndLocationItem*>(m_endLocationItem)->setRadius(radius);;

    update();
}


void MyGraphicsWidget::updateSceneSize(qreal width, qreal height)
{
    std::clog << "/// MyGraphicsWidget::updateSceneSize()" << std::endl;
    std::clog << "  width=  " << width << std::endl;
    std::clog << "  height= " << height << std::endl;
    // // m_scene->setSceneRect(0, 0, width, height);
    // m_scene->setSceneRect(0, 0, width, height);
    // // setSceneRect(0, 0, width, height);

    // QRectF sceneRect = m_scene->sceneRect();
    // std::clog << "x1: " << sceneRect.x() << std::endl;
    // std::clog << "y2: " << sceneRect.y() << std::endl;
    // std::clog << "w3: " << sceneRect.width() << std::endl;
    // std::clog << "h4: " << sceneRect.height() << std::endl;

    // m_scene->setSceneRect(0, 0, width, height);
    // setSceneRect(0, 0, width, height);
    // resize(100, 100);
    // setFixedSize(100, 100);

    // resize(width, height);
    // fitInView(0, 0, width, height);
    m_scene->setSceneRect(0, 0, width, height);
    clear();
}

void MyGraphicsWidget::updateSceneWidth(int width)
{
    std::clog << "MyGraphicsWidget::updateSceneWidth()" << std::endl;
    
    QRectF sceneRect = m_scene->sceneRect();
    std::clog << "x1: " << sceneRect.x() << std::endl;
    std::clog << "y2: " << sceneRect.y() << std::endl;
    std::clog << "w3: " << sceneRect.width() << std::endl;
    std::clog << "h4: " << sceneRect.height() << std::endl;

    m_scene->setSceneRect(0, 0, width, sceneRect.height());
    clear();
}
void MyGraphicsWidget::updateSceneHeight(int height)
{
    std::clog << "MyGraphicsWidget::updateSceneHeight()" << std::endl;
    QRectF sceneRect = m_scene->sceneRect();
    std::clog << "x1: " << sceneRect.x() << std::endl;
    std::clog << "y2: " << sceneRect.y() << std::endl;
    std::clog << "w3: " << sceneRect.width() << std::endl;
    std::clog << "h4: " << sceneRect.height() << std::endl;
    m_scene->setSceneRect(0, 0, sceneRect.width(), height);
    clear();
}

void MyGraphicsWidget::clear()
{
    std::clog << "MyGraphicsWidget::clear()" << std::endl;

    // setupMatrix();
    // graphicsView->ensureVisible(QRectF(0, 0, 0, 0));
    m_scene->clear();
}

void MyGraphicsWidget::generate()
{
    std::clog << "MyGraphicsWidget::generate()" << std::endl;

    // Check that the start location and end location are specified.
    bool startLocationInScene = false;
    bool endLocationInScene = false;

    QList<QGraphicsItem*> items = m_scene->items();
    for (unsigned int i = 0; i < items.size(); ++i)
    {
        QGraphicsItem* item = items.at(i);

        if (m_startLocationItem == item)
        {
            startLocationInScene = true;
        }
        else if (m_endLocationItem == item)
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

    PathFinder pf(m_scene->sceneRect().width(),
                  m_scene->sceneRect().height(),
                  dynamic_cast<StartLocationItem*>(m_startLocationItem)->radius());
    
    // Iterate through all the obstacles and add them to pf.
    for (unsigned int i = 0; i < items.size(); ++i)
    {
        QGraphicsItem* item = items.at(i);
        if ((m_startLocationItem == item) || (m_endLocationItem == item)) continue;

        // add the obstacle
        pf.addObstacle(item->x(), item->y(), dynamic_cast<ObstacleItem*>(item)->radius());    
    }

    PathFinder::Path path = pf.generatePath();
    
    // TODO - Draw the path.
    
} 

void MyGraphicsWidget::addStartLocation(int x, int y, int radius)
{
    std::clog << "MyGraphicsWidget::addStartLocation()" << std::endl;

    QList<QGraphicsItem*> items = m_scene->items();
    for (unsigned int i = 0; i < items.size(); ++i)
    {
        QGraphicsItem* item = items.at(i);
        if (m_startLocationItem == item)
        {
            return;
        }
    }

    m_startLocationItem = new StartLocationItem(x, y, radius);
    m_scene->addItem(m_startLocationItem);
}

void MyGraphicsWidget::removeStartLocation()
{
    // if the item is in the scene, remove it.
    QList<QGraphicsItem*> items = m_scene->items();
    for (unsigned int i = 0; i < items.size(); ++i)
    {
        QGraphicsItem* item = items.at(i);
        if (m_startLocationItem == item)
        {
            m_scene->removeItem(m_startLocationItem);
            break;
        }
    }
}
    
void MyGraphicsWidget::addEndLocation(int x, int y, int radius)
{
    std::clog << "MyGraphicsWidget::addEndLocation()" << std::endl;
    
    QList<QGraphicsItem*> items = m_scene->items();
    for (unsigned int i = 0; i < items.size(); ++i)
    {
        QGraphicsItem* item = items.at(i);
        if (m_endLocationItem == item)
        {
            return;
        }
    }

    m_endLocationItem = new EndLocationItem(x, y, radius);
    m_scene->addItem(m_endLocationItem);
}

void MyGraphicsWidget::removeEndLocation()
{
    QList<QGraphicsItem*> items = m_scene->items();
    for (unsigned int i = 0; i < items.size(); ++i)
    {
        QGraphicsItem* item = items.at(i);
        if (m_endLocationItem == item)
        {
            std::clog << "we found the item" << std::endl;

            m_scene->removeItem(m_endLocationItem);
            break;
        }
    }
}

void MyGraphicsWidget::addObstacle(int x, int y, int radius)
{
    std::clog << "MyGraphicsWidget::addObstacle()" << std::endl;

    QGraphicsItem *item = new ObstacleItem(x, y, radius);
    m_scene->addItem(item);
}

void MyGraphicsWidget::keyPressEvent(QKeyEvent* event)
{
    std::clog << "MyGraphicsWidget::keyPressEvent" << std::endl;

    switch (event->key())
    {
        case Qt::Key_Backspace:
            std::clog << "Deleting the item" << std::endl;
            removeSelectedItems();

            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}

void MyGraphicsWidget::removeSelectedItems()
{
    QList<QGraphicsItem*> items = m_scene->selectedItems();
    for (unsigned int i = 0; i < items.size(); ++i)
    {
        QGraphicsItem* item = items.at(i);
        m_scene->removeItem(item);
    }
}
