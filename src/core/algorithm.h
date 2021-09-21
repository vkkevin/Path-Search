#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#include "node.h"
#include "graph.h"
#include "option.h"
#include "heuristic.h"
#include <QObject>
#include <QReadWriteLock>
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

double getSysTimeMicros();

static const int MAX_ALGO_NUM = 5;
static const QString algoNameList[MAX_ALGO_NUM] = {
    "A*","IDA*","Bearch First Search","Best First Search","Dijkstra"
    //TODO: 添加算法名并在 Algorithm类 中添加其类型
};

class Algorithm: public QObject
{
    Q_OBJECT

public:
    enum AlgorithmType{
        AStarSearch = 0,
        IDAStarSearch,
        BreadthFirstSearch,
        BestFirstSearch,
        DijkstraSearch
    };

    Algorithm(QObject *parent = nullptr);
    virtual ~Algorithm();

    virtual vector<Node *> run() = 0;
    virtual vector<Node *> backtrace(Node *endNode);
    virtual vector<Node *> biBacktrace(Node *startNode, Node *endNode);
    virtual double pathLength(vector<Node *> path);

    virtual void setGraph(Graph *graph);
    virtual void setOption(Option *option);
    virtual void setHeuristic(Heuristic *heuristic);
    void mySleep(unsigned int useconds);

    friend class Finder;
protected:
    Graph *_graph;
    Option *_option;
    Heuristic *_heuristic;

    void delayUpdate(unsigned int useconds);

private:
    enum RunStatus{
        Run,Stop
    };
    RunStatus _runStatus;
    QReadWriteLock _statusRwlock;
    void setRunStatus(RunStatus status);
    unsigned int _delayTimes;

signals:
    void updateGraph();

public:
    void refurGraph();
};


#endif /* __ALGORITHM_H__ */
