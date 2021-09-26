#include "gridNode.h"

GridNode::GridNode(int x, int y)
    : _x(x), _y(y)
{
    _direIter = 0;
    setDegreeNumber(8);
}

GridNode::~GridNode()
{

}

void GridNode::setX(int x)
{
    _x = x;
}

int GridNode::x()
{
    return _x;
}

void GridNode::setY(int y)
{
    _y = y;
}

int GridNode::y()
{
    return _y;
}

void GridNode::setType(GridNode::Type type)
{
    _type = type;
}

GridNode::Type GridNode::type()
{
    return _type;
}

void GridNode::setStatus(GridNode::Status status)
{
    _status = status;
}

GridNode::Status GridNode::status()
{
    return _status;
}

bool GridNode::isWalkable()
{
    if(_type != OBSTACLE)
        return true;
    return false;
}
