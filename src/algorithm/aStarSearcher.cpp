#include "aStarSearcher.h"
#include <queue>
#include <ctime>
#include <unistd.h>
#include <iostream>

AStarSearcher::AStarSearcher()
{

}

AStarSearcher::~AStarSearcher()
{

}

std::vector<Node *> AStarSearcher::aStarSearch()
{
    std::vector<Node *> result;
    Node *neighbor, *extNode;
    std::vector<Node *> neighbors;
    myPriorityQueue<Node *, std::vector<Node *>, cmp> nodeHeap;

    extNode = _graph->startNode();
    extNode->setStatus(Node::VISITING);
    extNode->setParent(NULL);
    extNode->_heuristicWeight.f = extNode->_heuristicWeight.g = 0;
    nodeHeap.push(extNode);

    while(!nodeHeap.empty()){
        delayUpdate(10000);
        extNode = nodeHeap.top();
        nodeHeap.pop();
        extNode->setStatus(Node::VISITED);

        if(extNode == _graph->endNode()){
            return backtrace(extNode);
        }

        neighbors = _graph->getNeighborNodes(extNode,_option);
        for(unsigned int it = 0; it < neighbors.size(); it++){
            neighbor = (Node *)(neighbors.at(it));

            if(neighbor->status() == Node::VISITED){
                continue;
            }

            double ng = extNode->_heuristicWeight.g + _graph->distance(neighbor, extNode);

            if(neighbor->status() == Node::NONVISITE || ng < neighbor->_heuristicWeight.g){
                neighbor->_heuristicWeight.g = ng;
                if(neighbor->status() == Node::NONVISITE){
                    neighbor->_heuristicWeight.h = _option->optionValue(Option::Weight) * _heuristic->run(
                            _graph->distanceHorizontal(neighbor, _graph->endNode()),
                                _graph->distanceVertical(neighbor, _graph->endNode()));
                }
                neighbor->_heuristicWeight.f = neighbor->_heuristicWeight.g + neighbor->_heuristicWeight.h;
                neighbor->setParent(extNode);

                if(neighbor->status() == Node::NONVISITE){
                    neighbor->setStatus(Node::VISITING);
                    nodeHeap.push(neighbor);
                }else{
                    nodeHeap.updateItem(neighbor);
                }
            }
        }   //  end for each neighbor
    }

    return result;
}

std::vector<Node *> AStarSearcher::biAStarSearch()
{
    std::vector<Node *> result;
    Node *neighbor, *extNode;
    std::vector<Node *> neighbors;
    myPriorityQueue<Node *, std::vector<Node *>, cmp> startNodeHeap;
    myPriorityQueue<Node *, std::vector<Node *>, cmp> endNodeHeap;

    extNode = _graph->startNode();
    extNode->setStatus(Node::VISITING);
    extNode->setBy(Node::BY_START);
    extNode->setParent(NULL);
    extNode->_heuristicWeight.f = extNode->_heuristicWeight.g = 0;
    startNodeHeap.push(extNode);

    extNode = _graph->endNode();
    extNode->setBy(Node::BY_END);
    extNode->setStatus(Node::VISITING);
    extNode->setParent(NULL);
    extNode->_heuristicWeight.f = extNode->_heuristicWeight.g = 0;
    endNodeHeap.push(extNode);

    while(!startNodeHeap.empty() && !endNodeHeap.empty()){
        delayUpdate(10000);

        /* expand start node heap */
        extNode = startNodeHeap.top();
        startNodeHeap.pop();
        extNode->setStatus(Node::VISITED);

        neighbors = _graph->getNeighborNodes(extNode,_option);
        for(unsigned int it = 0; it < neighbors.size(); it++){
            neighbor = (Node *)(neighbors.at(it));

            if(neighbor->status() == Node::VISITED){
                continue;
            }

            if(neighbor->status() == Node::VISITING){
                if(neighbor->by() == Node::BY_END){
                    return biBacktrace(extNode, neighbor);
                }
            }

            double ng = extNode->_heuristicWeight.g + _graph->distance(neighbor, extNode);

            if(neighbor->status() == Node::NONVISITE || ng < neighbor->_heuristicWeight.g){
                neighbor->_heuristicWeight.g = ng;
                if(neighbor->status() == Node::NONVISITE){
                    neighbor->_heuristicWeight.h = _option->optionValue(Option::Weight) * _heuristic->run(
                            _graph->distanceHorizontal(neighbor, _graph->endNode()),
                                _graph->distanceVertical(neighbor, _graph->endNode()));
                }
                neighbor->_heuristicWeight.f = neighbor->_heuristicWeight.g + neighbor->_heuristicWeight.h;
                neighbor->setParent(extNode);

                if(neighbor->status() == Node::NONVISITE){
                    neighbor->setStatus(Node::VISITING);
                    neighbor->setBy(Node::BY_START);
                    startNodeHeap.push(neighbor);
                }else{
                    startNodeHeap.updateItem(neighbor);
                }
            }
        }   //  end for each neighbor by start


        /* expand end node heap */
        extNode = endNodeHeap.top();
        endNodeHeap.pop();
        extNode->setStatus(Node::VISITED);

        neighbors = _graph->getNeighborNodes(extNode,_option);
        for(unsigned int it = 0; it < neighbors.size(); it++){
            neighbor = (Node *)(neighbors.at(it));

            if(neighbor->status() == Node::VISITED){
                continue;
            }

            if(neighbor->status() == Node::VISITING){
                if(neighbor->by() == Node::BY_START){
                    return biBacktrace(neighbor, extNode);
                }
            }

            double ng = extNode->_heuristicWeight.g + _graph->distance(neighbor, extNode);

            if(neighbor->status() == Node::NONVISITE || ng < neighbor->_heuristicWeight.g){
                neighbor->_heuristicWeight.g = ng;
                if(neighbor->status() == Node::NONVISITE){
                    neighbor->_heuristicWeight.h = _option->optionValue(Option::Weight) * _heuristic->run(
                            _graph->distanceHorizontal(_graph->startNode(), neighbor),
                                _graph->distanceVertical(_graph->startNode(), neighbor));
                }
                neighbor->_heuristicWeight.f = neighbor->_heuristicWeight.g + neighbor->_heuristicWeight.h;
                neighbor->setParent(extNode);

                if(neighbor->status() == Node::NONVISITE){
                    neighbor->setStatus(Node::VISITING);
                    neighbor->setBy(Node::BY_END);
                    endNodeHeap.push(neighbor);
                }else{
                    endNodeHeap.updateItem(neighbor);
                }
            }
        }   //  end for each neighbor by end
    }

    return result;
}

std::vector<Node *> AStarSearcher::run()
{
    std::vector<Node *> result;
    if(_option->optionValue(Option::BiDirectional) == Option::SELECTED){
        result = biAStarSearch();
    }else{
        result = aStarSearch();
    }
    refurGraph();
    return result;
}

template <class T, class Container, class Compare>
void myPriorityQueue<T, Container, Compare>::updateItem(T &val)
{
    std::vector<Node *>::iterator nit = std::find(priority_queue<T, Container, Compare>::c.begin(),
                                                  priority_queue<T, Container, Compare>::c.end(), val);
    if(nit != priority_queue<T, Container, Compare>::c.end()){
        priority_queue<T, Container, Compare>::c.erase(nit);
        priority_queue<T, Container, Compare>::push(val);
    }
}
