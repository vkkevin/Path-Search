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
    MOption->setOptionUsability(Option::Weight);
    MOption->setOptionValue(Option::Weight, 0);
    if(MOption->optionValue(Option::BiDirectional) == Option::SELECTED){
        result = biAStarSearch();
    }else{
        result = aStarSearch();
    }
    refurGraph();
    return result;
}
