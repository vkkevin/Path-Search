#include "algorithms/breadthFirstSearcher.h"
#include <queue>
#include <ctime>
#include <unistd.h>
#include <iostream>

BreadthFirstSearcher::BreadthFirstSearcher()
{

}

BreadthFirstSearcher::~BreadthFirstSearcher()
{

}

std::vector<Node *> BreadthFirstSearcher::breadthFirstSearch()
{
    std::vector<Node *> neighbor;
    std::vector<Node *> result;

    std::queue<Node *> nodeQue;
    nodeQue.push(MGraph->startNode());
    MGraph->startNode()->setParent(NULL);

    while(!nodeQue.empty()){
        delayUpdate(10000);

        Node *extNode = nodeQue.front();
        nodeQue.pop();
        extNode->setStatus(Node::VISITED);

        if(extNode == MGraph->endNode()){
            return backtrace(MGraph->endNode());
        }

        neighbor = MGraph->getNeighborNodes(extNode, MOption);
        for(unsigned int it = 0; it < neighbor.size(); it++){
            if(((Node *)(neighbor.at(it)))->status() == Node::NONVISITE){
                ((Node *)(neighbor.at(it)))->setParent(extNode);
                ((Node *)(neighbor.at(it)))->setStatus(Node::VISITING);
                nodeQue.push(((Node *)(neighbor.at(it))));
            }
        }
    }

    return result;
}

std::vector<Node *> BreadthFirstSearcher::biBreadthFirstSearch()
{
    std::vector<Node *> result;
    std::vector<Node *> neighbors;
    std::queue<Node *> startNodeQue;
    std::queue<Node *> endNodeQue;
    Node *neighbor;

    startNodeQue.push(MGraph->startNode());
    MGraph->startNode()->setParent(NULL);
    MGraph->startNode()->setBy(Node::BY_START);
    MGraph->startNode()->setStatus(Node::VISITING);

    endNodeQue.push(MGraph->endNode());
    MGraph->endNode()->setParent(NULL);
    MGraph->endNode()->setBy(Node::BY_END);
    MGraph->endNode()->setStatus(Node::VISITING);

    while(!startNodeQue.empty() && !endNodeQue.empty()){
        delayUpdate(10000);

        /* expand start node queue */
        Node *extNode = startNodeQue.front();
        startNodeQue.pop();
        extNode->setStatus(Node::VISITED);

        neighbors = MGraph->getNeighborNodes(extNode, MOption);
        for(unsigned int it = 0; it < neighbors.size(); it++){
            neighbor = neighbors.at(it);

            if(neighbor->status() == Node::VISITED){
                continue;
            }

            if(neighbor->status() == Node::VISITING){
                if(neighbor->by() == Node::BY_END){
                    return biBacktrace(extNode, neighbor);
                }
                continue;
            }

            neighbor->setParent(extNode);
            neighbor->setStatus(Node::VISITING);
            neighbor->setBy(Node::BY_START);
            startNodeQue.push(neighbor);
        }

        /* expand end node queue */
        extNode = endNodeQue.front();
        endNodeQue.pop();
        extNode->setStatus(Node::VISITED);

        neighbors = MGraph->getNeighborNodes(extNode, MOption);
        for(unsigned int it = 0; it < neighbors.size(); it++){
            neighbor = neighbors.at(it);

            if(neighbor->status() == Node::VISITED){
                continue;
            }

            if(neighbor->status() == Node::VISITING){
                if(neighbor->by() == Node::BY_START){
                    return biBacktrace(neighbor, extNode);
                }
                continue;
            }

            neighbor->setParent(extNode);
            neighbor->setStatus(Node::VISITING);
            neighbor->setBy(Node::BY_END);
            endNodeQue.push(neighbor);
        }
    }

    return result;
}

std::vector<Node *> BreadthFirstSearcher::run()
{
    std::vector<Node *> result;
    if(MOption->optionValue(Option::BiDirectional) == Option::SELECTED){
        result = biBreadthFirstSearch();
    }else{
        result = breadthFirstSearch();
    }
    refurGraph();
    return result;
}
