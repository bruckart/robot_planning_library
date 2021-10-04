



#include <iostream>
#include <vector>

// At the minimum the library should include the following abilities:
// ● Take the initial parameters of map size(M x N) and robot radius.
// ● Add obstacles to the current map using as a parameter a list of circular obstacles, with
// each having a center location and radius.
// ● Create the best safe path given a start and end location on the current map, taking into
// consideration the robot radius.
// ● Save the current map to a file.
// ● Load a map from a file.
  
// ● Visualize a map and path to the screen.

class Waypoint;
class Obstacle;

class PathFinder
{
public:

    PathFinder(unsigned int mapWidth,
               unsigned int mapHeight,
               unsigned int robotRadius);
    ~PathFinder();

    void setStartLocation(unsigned int x,
                          unsigned int y);

    void setEndLocation(unsigned int x,
                        unsigned int y);


    void addObstacle(unsigned int x,
                     unsigned int y, 
                     unsigned int radius);

    typedef std::vector<Waypoint> Path;
    PathFinder::Path generatePath();

private:
    unsigned int m_mapWidth;
    unsigned int m_mapHeight;

    unsigned int m_robotRadius;
    
    std::pair<unsigned int, unsigned int> m_startLocation;
    std::pair<unsigned int, unsigned int> m_endLocation;

    std::vector<Obstacle> m_obstacles;

    std::vector<Waypoint> m_path;
};

class Waypoint
{
public:
    Waypoint(unsigned int x, unsigned int y)
    :
        m_x(x),
        m_y(y)
    {
    }
    ~Waypoint()
    {
    }
    unsigned int getX() const { return m_x; }
    unsigned int getY() const { return m_y; }

private:
    unsigned int m_x;
    unsigned int m_y;
};

class Obstacle
{
public:
    Obstacle(unsigned int x, 
             unsigned int y, 
             unsigned int radius)
    :
        m_x(x),
        m_y(y),
        m_radius(radius)
    {
    }

    ~Obstacle() {}

private:
    unsigned int m_x;
    unsigned int m_y;
    unsigned int m_radius;
};
