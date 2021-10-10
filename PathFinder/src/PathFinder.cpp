

#include "PathFinder.h"


PathFinder::PathFinder()
:
    m_nodes(),
    m_edges()
{
}

PathFinder::~PathFinder()
{
}

void PathFinder::addNode(Node* node)
{
    m_nodes.push_back(node);
}

void PathFinder::addEdge(Edge* edge)
{
    m_edges.push_back(edge);
}

void PathFinder::computePath()
{
    while (m_nodes.size() > 0)
    {
        Node* smallestNode = extractSmallestNode(m_nodes);

        std::vector<Node*>* adjacentNodes = 
            adjacentRemainingNodes(smallestNode);

        const int size = adjacentNodes->size();
        for (int i = 0; i < size; ++i)
        {
            Node* adjacentNode = adjacentNodes->at(i);

            int distance = distanceBetween(smallestNode, adjacentNode) + 
                smallestNode->m_distanceFromStart;

            if (distance < adjacentNode->m_distanceFromStart)
            {
                adjacentNode->m_distanceFromStart = distance;
                adjacentNode->m_previous = smallestNode;
            }
        }
        delete adjacentNodes;
    }
}

Node* PathFinder::extractSmallestNode(std::vector<Node*>& nodes)
{
    int size = nodes.size();
    if (size == 0) return NULL;

    int smallestPosition = 0;
    Node* smallest = nodes.at(0);
    for (int i = 1; i < size; ++i)
    {
        Node* current = nodes.at(i);
        if (current->m_distanceFromStart < smallest->m_distanceFromStart)
        {
            smallest = current;
            smallestPosition = i;
        }
    }
    
    nodes.erase(nodes.begin() + smallestPosition);
    return smallest;
}

std::vector<Node*>* PathFinder::adjacentRemainingNodes(Node* node)
{
    std::vector<Node*>* adjacentNodes = new std::vector<Node*>();

    const int size = m_edges.size();
    for (int i = 0; i < size; ++i)
    {
        Edge* edge = m_edges.at(i);
        Node* adjacent = NULL;
    
        if (edge->m_node1 == node)
        {
            adjacent = edge->m_node2;
        } 
        else if (edge->m_node2 == node)
        {
            adjacent = edge->m_node1;
        }

        if (adjacent && contains(m_nodes, adjacent))
        {
            adjacentNodes->push_back(adjacent);
        }
    }
    return adjacentNodes;
}

// Iterate through all the edges and find the edge that connects the 2 specified nodes.
int PathFinder::distanceBetween(Node* node1, Node* node2)
{
    const int size = m_edges.size();
    for (int i = 0; i < size; ++i)
    {
        Edge* edge = m_edges.at(i);

        if (edge->connects(node1, node2))
        {
            return edge->m_distance;
        }
    }

    std::clog << "No edge was found between the 2 specified nodes!" << std::endl;
    return -1;  // should never happen
}


// Does the 'nodes' vector contain 'node'
bool PathFinder::contains(std::vector<Node*>& nodes, Node* node)
{
    const int size = m_nodes.size();
    for (int i = 0; i < size; ++i)
    {
        if (node == nodes.at(i))
        {
            return true;
        }
    }
    return false;
}

void PathFinder::printShortestPathTo(Node* destination)
{
    Node* previous = destination;
    std::clog << "Distance from start: " << destination->m_distanceFromStart << std::endl;
    while (previous)
    {
        std::clog << previous->m_id << " "; 
        previous = previous->m_previous;
    }
    std::clog << std::endl;
}
