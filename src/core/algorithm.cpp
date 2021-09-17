#include "core/algorithm.h"
#include <QTime>
#include <QtGlobal>

#ifdef Q_OS_LINUX
    #include <unistd.h>
#elif defined (Q_OS_WIN32)
    #include <windows.h>
#endif

Algorithm::Algorithm(QObject *parent): QObject(parent)
{
    _graph = NULL;
    _option = NULL;
    _heuristic = NULL;

    _delayTimes = 0;
}

Algorithm::~Algorithm()
{

}

vector<Node *> Algorithm::backtrace(Node *endNode)
{
    std::vector<Node *> nodes;
    while(endNode != NULL){
        nodes.push_back(endNode);
        endNode->setPathType(Node::PATH);
        endNode = endNode->parent();
    }
    std::reverse(nodes.begin(), nodes.end());
    return nodes;
}

vector<Node *> Algorithm::biBacktrace(Node *startNode, Node *endNode)
{
    std::vector<Node *> pathS = backtrace(startNode);
    std::vector<Node *> pathE = backtrace(endNode);
    std::reverse(pathE.begin(), pathE.end());
    pathS.insert(pathS.end(), pathE.begin(), pathE.end());
    return pathS;
}

double Algorithm::pathLength(vector<Node *> path)
{
    return _graph->pathLength(path);
}

void Algorithm::setGraph(Graph *graph)
{
    _graph = graph;
}

void Algorithm::setOption(Option *option)
{
    _option = option;
}

/*  TODO: 设置 Heuristic 时需考虑其对算法的适用性 */
void Algorithm::setHeuristic(Heuristic *heuristic)
{
    _heuristic = heuristic;
    if(_option == NULL)
        return;
    if(_option->optionUsability(Option::AllowDiagonal) == Option::Usability &&
            _option->optionValue(Option::AllowDiagonal) == Option::SELECTED){
        if(heuristic->heuristicType() == Heuristic::Manhattan){
//            MHeuristic->setHeuristicType(Heuristic::Octile);
        }
    }else{
//        if(heuristic->heuristicType() == Heuristic::Octile)
//            MHeuristic->setHeuristicType(Heuristic::Manhattan);
    }
}

void Algorithm::mySleep(unsigned int useconds)
{
#ifdef Q_OS_LINUX
    double startTime = getSysTimeMicros();
    usleep(useconds);
    MDelayTimes += getSysTimeMicros() - startTime;
#elif defined (Q_OS_WIN32)
    double startTime = getSysTimeMicros();
    Sleep(useconds / 1000);
    _delayTimes += getSysTimeMicros() - startTime;
#endif
}

void Algorithm::delayUpdate(unsigned int useconds)
{
    mySleep(useconds);
    while(1){
        mySleep(1);
        _statusRwlock.lockForRead();
        if(_runStatus == Run){
            _statusRwlock.unlock();
            break;
        }
        _statusRwlock.unlock();
    }
    updateGraph();
}

void Algorithm::setRunStatus(Algorithm::RunStatus status)
{
    _statusRwlock.lockForWrite();
    _runStatus = status;
    _statusRwlock.unlock();
}

void Algorithm::refurGraph()
{
    emit updateGraph();
}
