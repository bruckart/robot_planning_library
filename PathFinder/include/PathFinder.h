

#ifndef PATHFINDER_H
#define PATHFINDER_H


#include <iostream>
#include <vector>
#include <limits>


class Node;
class Edge;

//***
// This class computes the shortest path utilizing Dijkstra's Algorithm. In order to 
// use this class, the user needs to specify a graph through a series of nodes and 
// edges. Once specified, the algorithm iterates through the nodes and computes the
// distance value based upon the edges. Please see the unit test for more usage
// examples.
//
// The method printShortestPathTo(Node* node) will print out the shortest path
// to the specific node. All nodes contain a pointer to the previous node, which
// can be traversed in order to determine the shortest path.
//***
class PathFinder
{
public:

    PathFinder();
    ~PathFinder();

    // This method adds a node, in the graph.
    void addNode(Node* node);

    // This method adds an edge which connects 2 nodes and speciies a distance.
    void addEdge(Edge* edge);

    // This method iterates through the graph and computes the shortest path. 
    // Upon completion, it prints the shortest path.
    void computePath();

    // This method 
    void printShortestPathTo(Node* node);

private:

    std::vector<Node*> m_nodes;
    std::vector<Edge*> m_edges;


    // This method returns the smallest node in the graph. Note that for the first
    // itertion, this is the "start node" which is specified with a distnace from
    // start of 0.
    Node* extractSmallestNode(std::vector<Node*>& nodes);

    // This method returns the adjacent nodes to the specified node via
    // the edges that are still in in the collection.
    std::vector<Node*>* adjacentRemainingNodes(Node* node);

    int distanceBetween(Node* node1, Node* node2);

    bool contains(std::vector<Node*>& nodes, Node* node);

};


class Node
{
public:
    Node(std::string name)
    :
        m_name(name),
        m_previous(NULL),
        m_distanceFromStart(std::numeric_limits<int>::max()) 
    {
    }

    std::string  m_name;
    Node*        m_previous;
    int          m_distanceFromStart;
};


class Edge 
{
public:
    Edge(Node* node1, Node* node2, int distance)
    : 
        m_node1(node1),
        m_node2(node2),
        m_distance(distance)
    {
    }

    bool connects(Node* node1, Node* node2)
    {
        return ((node1 == this->m_node1 && node2 == this->m_node2) ||
                (node1 == this->m_node2 && node2 == this->m_node1));
    }

    Node* m_node1;
    Node* m_node2;
    int   m_distance;
};

#endif // PATHFINDER_H
