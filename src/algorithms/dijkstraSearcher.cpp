#include "algorithms/dijkstraSearcher.h"
#include <queue>
#include <iostream>

DijkstraSearcher::DijkstraSearcher()
{

}

DijkstraSearcher::~DijkstraSearcher()
{

}

std::vector<Node *> DijkstraSearcher::run()
{
    std::vector<Node *> result;
    Algorithm::setHeuristic(new Heuristic());
    _option->setOptionUsability(Option::Weight);
    _option->setOptionValue(Option::Weight, 0);
    if(_option->optionValue(Option::BiDirectional) == Option::SELECTED){
        result = biAStarSearch();
    }else{
        result = aStarSearch();
    }
    refurGraph();
    return result;
}
