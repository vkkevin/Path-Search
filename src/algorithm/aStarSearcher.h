#ifndef A_STAR_SEARCHER_H
#define A_STAR_SEARCHER_H

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
        return nodeA->_heuristicWeight.f > nodeB->_heuristicWeight.f;
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

#endif /* A_STAR_SEARCHER_H */
