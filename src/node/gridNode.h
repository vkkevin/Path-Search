#ifndef GRIDNODE_H
#define GRIDNODE_H

#include "core/node.h"

class GridNode: public Node
{
public:
        enum Type{
            START, END, OBSTACLE, NOOBSTACLE
        };

public:
    GridNode(int x = 0, int y = 0);
    ~GridNode();
    void setX(int x);
    int x();
    void setY(int y);
    int y();
    void setType(Type type);
    Type type();
    void setStatus(Status status);
    Status status();
    bool isWalkable();

    int _direIter;

private:
    int _x;
    int _y;
    enum Type _type;

};

#endif /* GRIDNODE_H */
