


#include "PathFinder.h"
#include "gtest/gtest.h"


// Create a simple one-directional graph for testing purposes.
TEST(PathFinder, SimpleGraph)
{
    // A -> B -> C
    Node* a = new Node('a');
    a->m_distanceFromStart = 0;  // set start node

    Node* b = new Node('b');
    Node* c = new Node('c');
    
    Edge* e1 = new Edge(a, b, 1);
    Edge* e2 = new Edge(b, c, 1);

    PathFinder pf;
    pf.addNode(a);
    pf.addNode(b);
    pf.addNode(c);
    pf.addEdge(e1);
    pf.addEdge(e2);

    pf.computePath();
    // pf.printShortestPathTo(c);

    EXPECT_EQ(c->m_previous, b);
    EXPECT_EQ(b->m_previous, a);
}


// Create a graph which multiple edges with differing weights to test class logic.
TEST(PathFinder, MultiGraph)
{
    //***
    // Nodes:
    //
    //        B ---- D
    //      / |      |  \
    //    A   |      |   F
    //      \ |      |  /
    //        C ---- E
    //
    // Edges/Weights:
    // 
    //            7
    //    2   B ---- D   1
    //      / |      |  \
    //    A   | 1  2 |   F
    //      \ |      |  /
    //    4   C ---- E   5
    //            3
    //
    // From Node F, the shortest path is to D(1), E(2), C(3), B(1), A(2).
    //***

    Node* a = new Node('a');
    a->m_distanceFromStart = 0;
    Node* b = new Node('b');
    Node* c = new Node('c');
    Node* d = new Node('d');
    Node* e = new Node('e');
    Node* f = new Node('f');

    Edge* e1 = new Edge(a, b, 2);
    Edge* e2 = new Edge(a, c, 4);
    Edge* e3 = new Edge(b, c, 1);
    Edge* e4 = new Edge(b, d, 7);
    Edge* e5 = new Edge(c, e, 3);
    Edge* e6 = new Edge(d, e, 2);
    Edge* e7 = new Edge(d, f, 1);
    Edge* e8 = new Edge(e, f, 5);

    PathFinder pf;
    pf.addNode(a);
    pf.addNode(b);
    pf.addNode(c);
    pf.addNode(d);
    pf.addNode(e);
    pf.addNode(f);

    pf.addEdge(e1);
    pf.addEdge(e2);
    pf.addEdge(e3);
    pf.addEdge(e4);
    pf.addEdge(e5);
    pf.addEdge(e6);
    pf.addEdge(e7);
    pf.addEdge(e8);

    
    pf.computePath();
    // f -> d -> e -> c -> b -> a 
    // pf.printShortestPathTo(f);

    EXPECT_EQ(f->m_previous, d);
    EXPECT_EQ(d->m_previous, e);
    EXPECT_EQ(e->m_previous, c);
    EXPECT_EQ(c->m_previous, b);
    EXPECT_EQ(b->m_previous, a);

    EXPECT_EQ(f->m_distanceFromStart, 9);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}