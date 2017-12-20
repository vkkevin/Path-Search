#ifndef __NODE_H__
#define __NODE_H__

class Node
{
public:
    enum Status{
        VISITED,                // 已访问
        VISITING,               // 正在访问
        NONVISITE,           //  未访问
    };

    enum By{
        BY_START,
        BY_END
    };

    enum PathType{
        NOPATH,
        PATH
    };

public:
    Node(int id = 0, Node *parent = 0);
    virtual ~Node();
    virtual void setId(int id);
    virtual int id();
    virtual void setDegreeNumber(int degreeNum);
    virtual int degreeNumber();
    virtual void setWeight(int weight);
    virtual int weight();
    virtual void setStatus(Status status);
    virtual Status status();
    virtual void setParent(Node *parent);
    virtual Node *parent();
    virtual bool isWalkable() = 0;
    virtual void setBy(enum By by);
    virtual By by();
    virtual void setPathType(PathType ptype);
    virtual PathType pathType();

public:
    struct heuristicWeight{
        double f, g, h;
    }MHeuristicWeight;

protected:
    int NId;
    int NDegreeNum;
    int NWeight;
    enum Status NStatus;
    Node *NParent;
    enum By NBy;
    enum PathType NPType;
    int NPathId;
};

#endif /* __NODE_H__ */
