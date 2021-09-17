#include "algorithms/iDAStarSearcher.h"
#include <queue>

IDAStarSearcher::IDAStarSearcher()
{
    _stopTime = 0;
}

IDAStarSearcher::~IDAStarSearcher()
{

}

static Heuristic *heuristic;
static Graph *graph;

bool comp(Node *nodeA, Node *nodeB)
{
    int da = heuristic->run(graph->distanceHorizontal(nodeA, graph->endNode()),
                             graph->distanceVertical(nodeA, graph->endNode()));
    int db = heuristic->run(graph->distanceHorizontal(nodeB, graph->endNode()),
                             graph->distanceVertical(nodeB, graph->endNode()));
    return da < db;
}

Node *IDAStarSearcher::search(Node *extNode, double shortcut)
{
    Node *neighbor, *endNode;
    std::vector<Node *> neighbors;

    extNode->_heuristicWeight.h = _option->optionValue(Option::Weight) * _heuristic->run(
                    _graph->distanceHorizontal(extNode, _graph->endNode()),
                    _graph->distanceVertical(extNode, _graph->endNode()));
    extNode->_heuristicWeight.f = extNode->_heuristicWeight.g + extNode->_heuristicWeight.h;

    if(getSysTimeMicros() > _stopTime){
        return NULL;
    }

    if(extNode->_heuristicWeight.f > shortcut){
        return extNode;
    }

    if(extNode == _graph->endNode()){
        _path.push_back(extNode);
        return extNode;
    }
    neighbors = _graph->getNeighborNodes(extNode, _option);
    std::sort(neighbors.begin(), neighbors.end(), comp);

    double min = Infinity;
    for(unsigned int it = 0; it < neighbors.size(); it++){
        double delayTime = getSysTimeMicros();
        delayUpdate(3000);
        delayTime = getSysTimeMicros() - delayTime;
        _stopTime += delayTime;

        neighbor = (Node *)(neighbors.at(it));
        if(neighbor->weight() == 1)
            continue;
        neighbor->setWeight(1);
        if(_option->optionValue(Option::VisualizeRecursion) == Option::SELECTED){
            neighbor->setStatus(Node::VISITED);
        }
        neighbor->_heuristicWeight.g = extNode->_heuristicWeight.g + _graph->distance(extNode, neighbor);
        _path.push_back(neighbor);

        endNode = search(neighbor, shortcut);

        if(endNode == NULL){
            return NULL;
        }

        if(endNode == _graph->endNode()){
            return endNode;
        }

        if(endNode->_heuristicWeight.f < min){
            min = endNode->_heuristicWeight.f;
        }

        _path.pop_back();
        neighbor->setWeight(0);
        if(_option->optionValue(Option::VisualizeRecursion) == Option::SELECTED){
            neighbor->setStatus(Node::NONVISITE);
        }
    }
    extNode->_heuristicWeight.f = min;
    return extNode;
}

std::vector<Node *> IDAStarSearcher::iDAStarSearch()
{
    double shortcut = _heuristic->run(
                _graph->distanceHorizontal(_graph->startNode(), _graph->endNode()),
                _graph->distanceVertical(_graph->startNode(), _graph->endNode()));
    _graph->startNode()->setWeight(1);
    if(_option->optionValue(Option::VisualizeRecursion) == Option::SELECTED){
        _graph->startNode()->setStatus(Node::VISITED);
    }
    _graph->startNode()->_heuristicWeight.g = 0;
    _path.push_back(_graph->startNode());

    _stopTime = getSysTimeMicros() + _option->optionValue(Option::SecondsLimit) * 1000000;
    for(long long j = 0; true; j++){
        Node *endNode = search(_graph->startNode(), shortcut);
        if(endNode == NULL){
            _path.clear();
            return _path;
        }

        if(endNode == _graph->endNode()){
            return _path;
        }
        shortcut = (endNode->_heuristicWeight.f > shortcut + 0.5?endNode->_heuristicWeight.f:shortcut + 0.5);
    }

    _path.clear();
    return _path;
}

std::vector<Node *> IDAStarSearcher::run()
{
    heuristic = _heuristic;
    graph = _graph;
    std::vector<Node *> result;
    _path.clear();
    iDAStarSearch();
    result = _path;
    _path.clear();
    refurGraph();
    return result;
}
