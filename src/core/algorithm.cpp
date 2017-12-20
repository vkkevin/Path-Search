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
    MGraph = NULL;
    MOption = NULL;
    MHeuristic = NULL;

    MDelayTimes = 0;
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
    return MGraph->pathLength(path);
}

void Algorithm::setGraph(Graph *graph)
{
    MGraph = graph;
}

void Algorithm::setOption(Option *option)
{
    MOption = option;
}

/*  TODO: 设置 Heuristic 时需考虑其对算法的适用性 */
void Algorithm::setHeuristic(Heuristic *heuristic)
{
    MHeuristic = heuristic;
    if(MOption == NULL)
        return;
    if(MOption->optionUsability(Option::AllowDiagonal) == Option::Usability &&
            MOption->optionValue(Option::AllowDiagonal) == Option::SELECTED){
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
    MDelayTimes += getSysTimeMicros() - startTime;
#endif
}

void Algorithm::delayUpdate(unsigned int useconds)
{
    mySleep(useconds);
    while(1){
        mySleep(1);
        statusRwlock.lockForRead();
        if(MRunStatus == Run){
            statusRwlock.unlock();
            break;
        }
        statusRwlock.unlock();
    }
    updateGraph();
}

void Algorithm::setRunStatus(Algorithm::RunStatus status)
{
    statusRwlock.lockForWrite();
    MRunStatus = status;
    statusRwlock.unlock();
}

void Algorithm::refurGraph()
{
    emit updateGraph();
}
