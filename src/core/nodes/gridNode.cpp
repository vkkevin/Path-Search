#include "core/nodes/gridNode.h"

GridNode::GridNode(int x, int y)
    : GNX(x), GNY(y)
{
    GNDireIter = 0;
    setDegreeNumber(8);
}

GridNode::~GridNode()
{

}

void GridNode::setX(int x)
{
    GNX = x;
}

int GridNode::x()
{
    return GNX;
}

void GridNode::setY(int y)
{
    GNY = y;
}

int GridNode::y()
{
    return GNY;
}

void GridNode::setType(GridNode::Type type)
{
    GNType = type;
}

GridNode::Type GridNode::type()
{
    return GNType;
}

void GridNode::setStatus(GridNode::Status status)
{
    NStatus = status;
}

GridNode::Status GridNode::status()
{
    return NStatus;
}

bool GridNode::isWalkable()
{
    if(GNType != OBSTACLE)
        return true;
    return false;
}
