#include "algorithms/iDAStarSearcher.h"
#include <queue>

IDAStarSearcher::IDAStarSearcher()
{
    MStopTime = 0;
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

    extNode->MHeuristicWeight.h = MOption->optionValue(Option::Weight) * MHeuristic->run(
                    MGraph->distanceHorizontal(extNode, MGraph->endNode()),
                    MGraph->distanceVertical(extNode, MGraph->endNode()));
    extNode->MHeuristicWeight.f = extNode->MHeuristicWeight.g + extNode->MHeuristicWeight.h;

    if(getSysTimeMicros() > MStopTime){
        return NULL;
    }

    if(extNode->MHeuristicWeight.f > shortcut){
        return extNode;
    }

    if(extNode == MGraph->endNode()){
        MPath.push_back(extNode);
        return extNode;
    }
    neighbors = MGraph->getNeighborNodes(extNode, MOption);
    std::sort(neighbors.begin(), neighbors.end(), comp);

    double min = Infinity;
    for(unsigned int it = 0; it < neighbors.size(); it++){
        double delayTime = getSysTimeMicros();
        delayUpdate(3000);
        delayTime = getSysTimeMicros() - delayTime;
        MStopTime += delayTime;

        neighbor = (Node *)(neighbors.at(it));
        if(neighbor->weight() == 1)
            continue;
        neighbor->setWeight(1);
        if(MOption->optionValue(Option::VisualizeRecursion) == Option::SELECTED){
            neighbor->setStatus(Node::VISITED);
        }
        neighbor->MHeuristicWeight.g = extNode->MHeuristicWeight.g + MGraph->distance(extNode, neighbor);
        MPath.push_back(neighbor);

        endNode = search(neighbor, shortcut);

        if(endNode == NULL){
            return NULL;
        }

        if(endNode == MGraph->endNode()){
            return endNode;
        }

        if(endNode->MHeuristicWeight.f < min){
            min = endNode->MHeuristicWeight.f;
        }

        MPath.pop_back();
        neighbor->setWeight(0);
        if(MOption->optionValue(Option::VisualizeRecursion) == Option::SELECTED){
            neighbor->setStatus(Node::NONVISITE);
        }
    }
    extNode->MHeuristicWeight.f = min;
    return extNode;
}

std::vector<Node *> IDAStarSearcher::iDAStarSearch()
{
    double shortcut = MHeuristic->run(
                MGraph->distanceHorizontal(MGraph->startNode(), MGraph->endNode()),
                MGraph->distanceVertical(MGraph->startNode(), MGraph->endNode()));
    MGraph->startNode()->setWeight(1);
    if(MOption->optionValue(Option::VisualizeRecursion) == Option::SELECTED){
        MGraph->startNode()->setStatus(Node::VISITED);
    }
    MGraph->startNode()->MHeuristicWeight.g = 0;
    MPath.push_back(MGraph->startNode());

    MStopTime = getSysTimeMicros() + MOption->optionValue(Option::SecondsLimit) * 1000000;
    for(long long j = 0; true; j++){
        Node *endNode = search(MGraph->startNode(), shortcut);
        if(endNode == NULL){
            MPath.clear();
            return MPath;
        }

        if(endNode == MGraph->endNode()){
            return MPath;
        }
        shortcut = (endNode->MHeuristicWeight.f > shortcut + 0.5?endNode->MHeuristicWeight.f:shortcut + 0.5);
    }

    MPath.clear();
    return MPath;
}

std::vector<Node *> IDAStarSearcher::run()
{
    heuristic = MHeuristic;
    graph = MGraph;
    std::vector<Node *> result;
    MPath.clear();
    iDAStarSearch();
    result = MPath;
    MPath.clear();
    refurGraph();
    return result;
}
