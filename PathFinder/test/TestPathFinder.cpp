


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
    EXPECT_EQ(1, 1);

    PathFinder pf(100, 100, 10);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}