#ifndef GRIDGRAPH_H
#define GRIDGRAPH_H

#include "core/graph.h"
#include "node/gridNode.h"

class GridGraph: public Graph
{
public:
    const static int DIRECTION_NUM = 8;
    const static int Direction[DIRECTION_NUM][2];

public:
    GridGraph();
    GridGraph(int width, int height);
    virtual ~GridGraph();
    void setWidth(int width);
    int width();
    void setHeight(int height);
    int height();
    GridNode *at(int x, int y);
    void setStartNode(Node *start);
    GridNode *startNode();
    void setEndNode(Node *end);
    GridNode *endNode();

    Node *nodeById(int id);
    void addNode(Node *node);
    void addEdge(Node *start, Node *end);
    std::vector<Node *> getNeighborNodes(Node *node, Option *option);
    GridNode *getNodeAt(int x, int y);
    double distance(Node *nodeA, Node *nodeB);
    double distanceHorizontal(Node *nodeA, Node *nodeB);
    double distanceVertical(Node *nodeA, Node *nodeB);
    bool isInside(Node *node);
    bool isWalkable(Node *node);
    void initNodePathStatus();
    double pathLength(vector<Node *> path);

       /* 停止使用... */
    Node *nextAdjNode(Node *node, Option *option);

    void clearWalls();
    void clearPath();

protected:
    void initGraph();
    GridNode **_graph;

private:
    static const int DEFAULT_WIDGTH = 20;
    static const int DEFAULT_HEIGHT = 20;
    int _width;
    int _height;
    GridNode *_startNode;
    GridNode *_endNode;
};

#endif /* GRIDGRAPH_H */
