#ifndef BREADTH_FIRST_SEARCHER_H
#define BREADTH_FIRST_SEARCHER_H

#include "core/algorithm.h"

class BreadthFirstSearcher: public Algorithm
{
public:
    BreadthFirstSearcher();
    ~BreadthFirstSearcher();
    std::vector<Node *> run();

    std::vector<Node *> breadthFirstSearch();
    std::vector<Node *> biBreadthFirstSearch();

};

#endif /* BREADTH_FIRST_SEARCHER_H */
