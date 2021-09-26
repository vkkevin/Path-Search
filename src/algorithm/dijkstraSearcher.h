#ifndef DIJKSTRA_SEARCHER_H
#define DIJKSTRA_SEARCHER_H

#include "core/algorithm.h"
#include "aStarSearcher.h"

class DijkstraSearcher: public AStarSearcher
{
public:
    DijkstraSearcher();
    ~DijkstraSearcher();
    std::vector<Node *> run();
};

#endif /* DIJKSTRA_SEARCHER_H */
