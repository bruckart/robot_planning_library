

#include "PathFinder.h"

PathFinder::PathFinder(unsigned int mapWidth,
                       unsigned int mapHeight,
                       unsigned int robotRadius)
:
    m_mapWidth(mapWidth),
    m_mapHeight(mapHeight),
    m_robotRadius(robotRadius),
    m_obstacles()
{
}

PathFinder::~PathFinder()
{
}

void PathFinder::addObstacle(unsigned int x,
                             unsigned int y, 
                             unsigned int radius)
{
    Obstacle o(x, y, radius);
    // o.x = x;
    // o.y = y;
    // o.radius = radius;
    m_obstacles.push_back(o);
}



void PathFinder::addObstacle(const Obstacle& obstacle)
{
    m_obstacles.push_back(obstacle);
}

PathFinder::Path PathFinder::getPath()
{
    Path p;

    return p;
}

void PathFinder::saveMap(const std::string filename)
{
}

void PathFinder::loadMap(const std::string filename)
{
}
