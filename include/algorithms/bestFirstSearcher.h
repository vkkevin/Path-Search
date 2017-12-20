#ifndef __BEST_FIRST_SEARCHER_H__
#define __BEST_FIRST_SEARCHER_H__

#include "core/algorithm.h"
#include "algorithms/aStarSearcher.h"

class BestFirstSearcher: public AStarSearcher
{
public:
    BestFirstSearcher();
    ~BestFirstSearcher();
    std::vector<Node *> run();
};

#endif /* __BEST_FIRST_SEARCHER_H__ */
