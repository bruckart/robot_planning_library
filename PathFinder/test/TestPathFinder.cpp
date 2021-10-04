


#include "PathFinder.h"
#include "gtest/gtest.h"

class TestPathFinder : public ::testing::Test
{
public:
    TestPathFinder()
    {
    }
    ~TestPathFinder()
    {
    }

    virtual void SetUp()
    {
        std::cout << "SetUp called." << std::endl;
    }

    virtual void TearDown()
    {
        std::cout << "TearDown called." << std::endl;
    }
private:


};


TEST(PathFinder, PathFinderInit)
{
    // EXPECT_EQ(1, 1);

    PathFinder pf(100, 100, 10);
    pf.setStartLocation(0, 0);
    pf.setEndLocation(100, 100);

    pf.addObstacle(50, 50, 10);

    // typedef std::vector<Waypoint> > Path;

    PathFinder::Path path = pf.generatePath();

    std::clog << "number of waypoints returned= " << path.size() << std::endl;
    std::vector<Waypoint>::const_iterator iter;
    for (iter = path.begin(); iter != path.end(); ++iter)
    {
        Waypoint wp = *iter;
        std::clog << "WP: " << wp.getX() << ", " << wp.getY() << std::endl;
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}