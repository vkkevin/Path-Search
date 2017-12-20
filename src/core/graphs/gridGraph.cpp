#include "core/graphs/gridGraph.h"
#include <iostream>
#include <cmath>

const int GridGraph::Direction[DIRECTION_NUM][2] = {
        {-1, 0}, {-1,-1}, { 0, 1}, {-1, 1},
        { 1, 0}, { 1, 1}, { 0,-1}, { 1,-1}
};

GridGraph::GridGraph()
    : GWidth(DEFAULT_WIDGTH), GHeight(DEFAULT_HEIGHT)
{
    pStartNode = pEndNode = NULL;
    GGraph = new GridNode *[GHeight];
    for(int i = 0; i < GHeight; i++){
        GGraph[i] = new GridNode[GWidth];
    }
    initGraph();
}

GridGraph::GridGraph(int width, int height)
    : GWidth(width), GHeight(height)
{
    pStartNode = pEndNode = NULL;
    GGraph = new GridNode *[GHeight];
    for(int i = 0; i < GHeight; i++){
        GGraph[i] = new GridNode[GWidth];
    }
    initGraph();
}

GridGraph::~GridGraph()
{
//    for(int i = 0; i < GHeight; i++){
//        delete [] GGraph[i];
//    }
//    delete GGraph;
    pStartNode = pEndNode = NULL;
}

void GridGraph::setWidth(int width)
{
    GWidth = width;
}

int GridGraph::width()
{
    return GWidth;
}

void GridGraph::setHeight(int height)
{
    GHeight = height;
}

int GridGraph::height()
{
    return GHeight;
}

GridNode *GridGraph::at(int x, int y)
{
    return &GGraph[x][y];
}

void GridGraph::setStartNode(Node *start)
{
    if(pStartNode != NULL){
        pStartNode->setType(GridNode::NOOBSTACLE);
    }
    pStartNode = (GridNode *)start;
    pStartNode->setType(GridNode::START);
}

GridNode *GridGraph::startNode()
{
    return pStartNode;
}

void GridGraph::setEndNode(Node *end)
{
    if(pEndNode != NULL){
        pEndNode->setType(GridNode::NOOBSTACLE);
    }
    pEndNode = (GridNode *)end;
    pEndNode->setType(GridNode::END);
}

GridNode *GridGraph::endNode()
{
    return pEndNode;
}

Node *GridGraph::nodeById(int id)
{
    for(int i = 0; i < GHeight; i++){
        for(int j = 0; j < GWidth; j++){
            if(GGraph[i][j].id() == id){
                return &GGraph[i][j];
            }
        }
    }
    return NULL;
}

void GridGraph::addNode(Node *node)
{
    if(NULL == node){}
    return;
}

void GridGraph::addEdge(Node *start, Node *end)
{
    if(NULL == start || NULL == end){}
    return;
}

/* 停止使用... */
Node *GridGraph::nextAdjNode(Node *node, Option *option)
{
    GridNode *gnode = (GridNode *)node;
    int x = gnode->x() + Direction[gnode->GNDireIter][0];
    int y = gnode->y() + Direction[gnode->GNDireIter][1];

    int allowValue = 2;
    if(option->optionUsability(Option::AllowDiagonal) &&
            option->optionValue(Option::AllowDiagonal) == Option::SELECTED){
        allowValue = 1;
    }
    gnode->GNDireIter += allowValue;
    if(x >= 0 && x < GHeight && y >= 0 && y < GWidth)
        return &GGraph[x][y];
    return NULL;
}

std::vector<Node *> GridGraph::getNeighborNodes(Node *node, Option *option)
{
    GridNode *gnode = (GridNode *)node;
    GridNode *extNode;
    std::vector<Node *> neighbor;
    bool vertical[DIRECTION_NUM / 2] = {false, false, false, false};
    bool diagonal[DIRECTION_NUM / 2] = {false, false, false, false};

    for(int i = 0; i < DIRECTION_NUM; i += 2){
        extNode = getNodeAt(gnode->x() + Direction[i][0], gnode->y() + Direction[i][1]);
        if(isWalkable(extNode)){
            neighbor.push_back(extNode);
            vertical[i / 2] = true;
        }
    }

    if(option != NULL){
        if(option->optionUsability(Option::AllowDiagonal) &&
                option->optionValue(Option::AllowDiagonal)){
            if(option->optionUsability(Option::DontCrossCorners) &&
                    option->optionValue(Option::DontCrossCorners)){
                diagonal[0] = vertical[3] && vertical[0];
                diagonal[1] = vertical[0] && vertical[1];
                diagonal[2] = vertical[1] && vertical[2];
                diagonal[3] = vertical[2] && vertical[3];
            }else{
                diagonal[0] = vertical[3] || vertical[0];
                diagonal[1] = vertical[0] || vertical[1];
                diagonal[2] = vertical[1] || vertical[2];
                diagonal[3] = vertical[2] || vertical[3];
            }
        }else{
            return neighbor;
        }
    }else{
        return neighbor;
    }

    for(int i = 1; i < DIRECTION_NUM; i += 2){
        extNode = getNodeAt(gnode->x() + Direction[i][0], gnode->y() + Direction[i][1]);
        if(diagonal[i / 2] && isWalkable(extNode)){
            neighbor.push_back(extNode);
        }
    }

    return neighbor;
}

GridNode *GridGraph::getNodeAt(int x, int y)
{
    if(x >= 0 && x < GHeight && y >= 0 && y < GWidth)
        return &GGraph[x][y];
    return NULL;
}

double GridGraph::distance(Node *nodeA, Node *nodeB)
{
    int x1 = ((GridNode *)nodeA)->x();
    int y1 = ((GridNode *)nodeA)->y();
    int x2 = ((GridNode *)nodeB)->x();
    int y2 = ((GridNode *)nodeB)->y();
    return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double GridGraph::distanceHorizontal(Node *nodeA, Node *nodeB)
{
    int x1 = ((GridNode *)nodeA)->x();
    int x2 = ((GridNode *)nodeB)->x();
    return std::fabs(x1 - x2);
}

double GridGraph::distanceVertical(Node *nodeA, Node *nodeB)
{
    int y1 = ((GridNode *)nodeA)->y();
    int y2 = ((GridNode *)nodeB)->y();
    return std::fabs(y1 - y2);
}

bool GridGraph::isInside(Node *node)
{
    int x = ((GridNode *)node)->x();
    int y = ((GridNode *)node)->y();
    return (x >= 0 && x < GHeight && y >= 0 && y < GWidth);
}

bool GridGraph::isWalkable(Node *node)
{
    GridNode *gnode = (GridNode *)node;
    if(gnode == NULL)
        return false;
    if(gnode->isWalkable() && isInside(gnode))
        return true;
    return false;
}

void GridGraph::initNodePathStatus()
{
    for(int i = 0; i < GHeight; i++){
        for(int j = 0; j < GWidth; j++){
            GGraph[i][j].setStatus(Node::NONVISITE);
            GGraph[i][j].setPathType(Node::NOPATH);
            GGraph[i][j].GNDireIter = 0;
            GGraph[i][j].setWeight(0);
            GGraph[i][j].setBy((Node::By)-1);
        }
    }
}

double GridGraph::pathLength(std::vector<Node *> path)
{
    GridNode *n1, *n2;
    double dx, dy, sum = 0;

    for(unsigned int i = 1; i < path.size(); i++){
        n1 = (GridNode *)path.at(i - 1);
        n2 = (GridNode *)path.at(i);
        dx = n1->x() - n2->x();
        dy = n1->y() - n2->y();
        sum += std::sqrt(dx * dx + dy * dy);
    }
    return sum;
}

void GridGraph::initGraph()
{
    for(int i = 0; i < GHeight; i++){
        for(int j = 0; j < GWidth; j++){
            GGraph[i][j].setX(i);
            GGraph[i][j].setY(j);
            GGraph[i][j].setType(GridNode::NOOBSTACLE);
        }
    }
    setStartNode(&GGraph[0][0]);
    setEndNode(&GGraph[0][1]);
}
