#ifndef __IDA_STAR_SEARCHER_H__
#define __IDA_STAR_SEARCHER_H__

#include "core/algorithm.h"

class IDAStarSearcher: public Algorithm
{
public:
    IDAStarSearcher();
    ~IDAStarSearcher();
    std::vector<Node *> run();

    Node *search(Node *extNode, double shortcut);
    std::vector<Node *> iDAStarSearch();

    std::vector<Node *> MPath;
    constexpr const static double  Infinity = 0x0ffffff;
    double MStopTime;

};

#endif /* __IDA_STAR_SEARCHER_H__ */
