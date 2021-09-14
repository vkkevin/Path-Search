#ifndef __A_STAR_SEARCHER_H__
#define __A_STAR_SEARCHER_H__

#include "core/algorithm.h"
#include <queue>
using std::priority_queue;

template <class T, class Container, class Compare>
class myPriorityQueue: public priority_queue<T, Container, Compare>
{
public:
    myPriorityQueue(): priority_queue<T, Container, Compare>() {}
    ~myPriorityQueue() {}
    void updateItem(T &val);

};

struct cmp{
    bool operator()(Node *nodeA, Node *nodeB){
        return nodeA->MHeuristicWeight.f > nodeB->MHeuristicWeight.f;
    }
};

class AStarSearcher: public Algorithm
{
public:
    AStarSearcher();
    ~AStarSearcher();
    std::vector<Node *> run();

    std::vector<Node *> aStarSearch();
    std::vector<Node *> biAStarSearch();
};

#endif /* __A_STAR_SEARCHER_H__ */
