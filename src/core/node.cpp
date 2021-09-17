#include "core/node.h"

Node::Node(int id, Node *parent)
    : _id(id), _degreeNum(0), _weight(0)
{
    _parent = parent;
    _status = NONVISITE;
    _pathType = NOPATH;
}

Node::~Node()
{

}

void Node::setId(int id)
{
    _id = id;
}

int Node::id()
{
    return _id;
}

void Node::setDegreeNumber(int degreeNum)
{
    _degreeNum = degreeNum;
}

int Node::degreeNumber()
{
    return _degreeNum;
}

void Node::setWeight(int weight)
{
    _weight = weight;
}

int Node::weight()
{
    return _weight;
}

void Node::setStatus(Node::Status status)
{
    _status = status;
}

Node::Status Node::status()
{
    return _status;
}

void Node::setParent(Node *parent)
{
    _parent = parent;
}

Node *Node::parent()
{
    return _parent;
}

void Node::setBy(Node::By by)
{
    _by = by;
}

Node::By Node::by()
{
    return _by;
}

void Node::setPathType(Node::PathType ptype)
{
    _pathType = ptype;
}

Node::PathType Node::pathType()
{
    return _pathType;
}

