#include "algorithms/bestFirstSearcher.h"
#include <queue>
#include <iostream>

BestFirstSearcher::BestFirstSearcher()
{

}

BestFirstSearcher::~BestFirstSearcher()
{

}

std::vector<Node *> BestFirstSearcher::run()
{
    std::vector<Node *> result;
    _option->setOptionUsability(Option::Weight);
    _option->setOptionValue(Option::Weight, 1000000);
    if(_option->optionValue(Option::BiDirectional) == Option::SELECTED){
        result = biAStarSearch();
    }else{
        result = aStarSearch();
    }
    refurGraph();
    return result;
}
