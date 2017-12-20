#include "core/node.h"

Node::Node(int id, Node *parent)
    : NId(id), NDegreeNum(0), NWeight(0)
{
    NParent = parent;
    NStatus = NONVISITE;
    NPType = NOPATH;
}

Node::~Node()
{

}

void Node::setId(int id)
{
    NId = id;
}

int Node::id()
{
    return NId;
}

void Node::setDegreeNumber(int degreeNum)
{
    NDegreeNum = degreeNum;
}

int Node::degreeNumber()
{
    return NDegreeNum;
}

void Node::setWeight(int weight)
{
    NWeight = weight;
}

int Node::weight()
{
    return NWeight;
}

void Node::setStatus(Node::Status status)
{
    NStatus = status;
}

Node::Status Node::status()
{
    return NStatus;
}

void Node::setParent(Node *parent)
{
    NParent = parent;
}

Node *Node::parent()
{
    return NParent;
}

void Node::setBy(Node::By by)
{
    NBy = by;
}

Node::By Node::by()
{
    return NBy;
}

void Node::setPathType(Node::PathType ptype)
{
    NPType = ptype;
}

Node::PathType Node::pathType()
{
    return NPType;
}

