#ifndef IDA_STAR_SEARCHER_H
#define IDA_STAR_SEARCHER_H

#include "core/algorithm.h"

class IDAStarSearcher: public Algorithm
{
public:
    IDAStarSearcher();
    ~IDAStarSearcher();
    std::vector<Node *> run();

    Node *search(Node *extNode, double shortcut);
    std::vector<Node *> iDAStarSearch();

    constexpr const static double  Infinity = 0x0ffffff;
    std::vector<Node *> _path;
    double _stopTime;

};

#endif /* IDA_STAR_SEARCHER_H */
