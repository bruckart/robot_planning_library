

#include "PathFinder.h"

PathFinder::PathFinder(unsigned int mapWidth,
                       unsigned int mapHeight,
                       unsigned int robotRadius)
:
    m_mapWidth(mapWidth),
    m_mapHeight(mapHeight),
    m_robotRadius(robotRadius),
    m_obstacles(),
    m_startLocation(),
    m_endLocation()
{
}

PathFinder::~PathFinder()
{
}

void PathFinder::setStartLocation(unsigned int x,
                                  unsigned int y)
{
    m_startLocation.first = x;
    m_startLocation.second = y;
}

void PathFinder::setEndLocation(unsigned int x,
                                unsigned int y)
{
    m_endLocation.first = x;
    m_endLocation.second = y;
}

void PathFinder::addObstacle(unsigned int x,
                             unsigned int y, 
                             unsigned int radius)
{
    Obstacle o(x, y, radius);
    m_obstacles.push_back(o);
}

void PathFinder::addObstacle(const Obstacle& obstacle)
{
    m_obstacles.push_back(obstacle);
}

PathFinder::Path PathFinder::generatePath()
{
    // Check that the start location and the end location
    // are specified.
    Path p;

    https://stackoverflow.com/questions/5303538/algorithm-to-find-the-shortest-path-with-obstacles

    
    std::clog << "start point" << m_startLocation.first << ", " << m_startLocation.second << std::endl;
    std::clog << "end point" << m_endLocation.first << ", " << m_endLocation.second << std::endl;

    // Create a grid encompassing these 2 points.
    




    return p;
}
