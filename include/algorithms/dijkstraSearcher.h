#ifndef __DIJKSTRA_SEARCHER_H__
#define __DIJKSTRA_SEARCHER_H__

#include "core/algorithm.h"
#include "algorithms/aStarSearcher.h"

class DijkstraSearcher: public AStarSearcher
{
public:
    DijkstraSearcher();
    ~DijkstraSearcher();
    std::vector<Node *> run();
};

#endif /* __DIJKSTRA_SEARCHER_H__ */
