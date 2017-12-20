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
    MOption->setOptionUsability(Option::Weight);
    MOption->setOptionValue(Option::Weight, 1000000);
    if(MOption->optionValue(Option::BiDirectional) == Option::SELECTED){
        result = biAStarSearch();
    }else{
        result = aStarSearch();
    }
    refurGraph();
    return result;
}
