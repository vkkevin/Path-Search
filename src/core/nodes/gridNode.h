#ifndef __GRIDNODE_H__
#define __GRIDNODE_H__

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

    int GNDireIter;

private:
    int GNX;
    int GNY;
    enum Type GNType;

};

#endif /* __GRIDNODE_H__ */
