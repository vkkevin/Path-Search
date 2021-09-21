#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "node.h"
#include "option.h"
using std::vector;

class Graph
{
public:
    enum GraphType{
        GridGraph
    };

public:
    Graph();
    virtual ~Graph();
    virtual void addNode(Node *node) = 0;
    virtual void addEdge(Node *start, Node *end) = 0;
    virtual Node* nodeById(int id) = 0;
    virtual void setStartNode(Node *start) = 0;
    virtual Node *startNode() = 0;
    virtual void setEndNode(Node *end) = 0;
    virtual Node *endNode() = 0;
    virtual Node *nextAdjNode(Node *node, Option *option) = 0;
    virtual vector<Node *> getNeighborNodes(Node *node, Option *option) = 0;
    virtual double distance(Node *nodeA, Node *nodeB) = 0;
    virtual double distanceHorizontal(Node *nodeA, Node *nodeB) = 0;
    virtual double distanceVertical(Node *nodeA, Node *nodeB) = 0;
    virtual bool isWalkable(Node *node) = 0;
    virtual void initNodePathStatus() = 0;
    virtual double pathLength(vector<Node *> path) = 0;

    virtual void clearWalls() = 0;
    virtual void clearPath() = 0;
};

#endif /* GRAPH_H */
