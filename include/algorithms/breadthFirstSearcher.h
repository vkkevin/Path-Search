#ifndef __BREADTH_FIRST_SEARCHER_H__
#define __BREADTH_FIRST_SEARCHER_H__

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

#endif /* __BREADTH_FIRST_SEARCHER_H__ */
