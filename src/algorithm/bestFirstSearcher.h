#ifndef BEST_FIRST_SEARCHER_H
#define BEST_FIRST_SEARCHER_H

#include "core/algorithm.h"
#include "aStarSearcher.h"

class BestFirstSearcher: public AStarSearcher
{
public:
    BestFirstSearcher();
    ~BestFirstSearcher();
    std::vector<Node *> run();
};

#endif /* BEST_FIRST_SEARCHER_H */
