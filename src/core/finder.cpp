#include "core/finder.h"
#include "algorithms/aStarSearcher.h"
#include "algorithms/iDAStarSearcher.h"
#include "algorithms/breadthFirstSearcher.h"
#include "algorithms/bestFirstSearcher.h"
#include "algorithms/dijkstraSearcher.h"
#include <QtGlobal>

#ifdef Q_OS_LINUX
    #include <sys/time.h>
#elif defined(Q_OS_WIN32)
    #include <windows.h>
#endif
#include <QDebug>

static double MStartTime = 0;
static double MEndTime = 0;

/* 获取系统当前时间（微秒） */
double getSysTimeMicros()
{
#ifdef Q_OS_LINUX
    timeval tv;
    gettimeofday(&tv, 0);
    return (double)((int64_t)tv.tv_sec * 1000000 + (int64_t)tv.tv_usec);
#elif defined(Q_OS_WIN32)
// 从1601年1月1日0:0:0:000到1970年1月1日0:0:0:000的时间(单位100ns)
#define EPOCHFILETIME   (116444736000000000UL)
    FILETIME ft;
    LARGE_INTEGER li;
    double tt = 0;
    GetSystemTimeAsFileTime(&ft);
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    // 从1970年1月1日0:0:0:000到现在的微秒数(UTC时间)
    tt = ((double)(li.QuadPart - EPOCHFILETIME)) / 10;
    return tt;
#endif
    return 0;
}

Finder::Finder(QObject *parent): QObject(parent)
{
    MAlgorithm = NULL;
    MGraph = NULL;
    MOption = NULL;
    MHeuristic = NULL;
    MFinderThread = new FinderThread(this);
    MTime = 0;
}

Finder::~Finder()
{
    delete MFinderThread;
}

/*  此处有 bug
 *  当 algoName 不存在时会造成 MAlgorithm 指针的多次释放
 */
void Finder::setAlgorithm(const QString algoName)
{
    if(MAlgorithm != NULL){
        disconnect(MAlgorithm, SIGNAL(updateGraph()), this, SLOT(updateGraph()));
        delete MAlgorithm;
    }

    if(algoName == "A*"){
        MAlgorithm = new AStarSearcher();
    }else if(algoName == "IDA*"){
        MAlgorithm = new IDAStarSearcher();
    }else if(algoName == "Bearch First Search"){
        MAlgorithm = new BreadthFirstSearcher();
    }else if(algoName == "Best First Search"){
        MAlgorithm = new BestFirstSearcher();
    }else if(algoName == "Dijkstra"){
        MAlgorithm = new DijkstraSearcher();
    }

    connect(MAlgorithm, SIGNAL(updateGraph()), this, SLOT(updateGraph()), Qt::UniqueConnection);
}

/*  此处有 bug
 *  当 type 不存在时会造成 MAlgorithm 指针的多次释放
 */
void Finder::setAlgorithm(Algorithm::AlgorithmType type)
{
    if(MAlgorithm != NULL){
        disconnect(MAlgorithm, SIGNAL(updateGraph()), this, SLOT(updateGraph()));
        delete MAlgorithm;
    }

    switch(type){
        case Algorithm::AStarSearch:   MAlgorithm = new AStarSearcher();
        case Algorithm::IDAStarSearch:   MAlgorithm = new IDAStarSearcher();
        case Algorithm::BreadthFirstSearch:   MAlgorithm = new BreadthFirstSearcher();
        case Algorithm::BestFirstSearch:   MAlgorithm = new BestFirstSearcher();
        case Algorithm::DijkstraSearch:   MAlgorithm = new DijkstraSearcher();
        default: break;
    }
    connect(MAlgorithm, SIGNAL(updateGraph()), this, SLOT(updateGraph()), Qt::UniqueConnection);
}

void Finder::setGraph(Graph *graph)
{
    MGraph = graph;
}

void Finder::setOption(Option *option)
{
    if(option == NULL)
        return;
    MOption = option;
}

void Finder::setHeuristic(Heuristic *heuristic)
{
    if(heuristic == NULL)
        return;
    MHeuristic = heuristic;
}

void Finder::findPath()
{
    terminateSearchingTask();

    if(MGraph == NULL){
        qDebug() << "No Graph";
        return;
    }
    MGraph->initNodePathStatus();
    MAlgorithm->setGraph(MGraph);

    if(MOption != NULL)
        MAlgorithm->setOption(new Option(*MOption));
    else qDebug() << "No Option";

    if(MHeuristic != NULL)
        MAlgorithm->setHeuristic(new Heuristic(*MHeuristic));
    else qDebug() << "No Heuristic";

    MAlgorithm->MDelayTimes = 0;
    MTime = 0;

    searchRun();
    MFinderThread->start();
}

/* 计算运行时间并暂停运行 */
void Finder::pauseFinder()
{
    MAlgorithm->setRunStatus(Algorithm::Stop);
// 更改结束时间
    MEndTime = getSysTimeMicros();
    MTime += ((double)(MEndTime - MStartTime)) / 1000;
}

/* 计算运行时间并继续运行 */
void Finder::resumeFinder()
{
    MAlgorithm->setRunStatus(Algorithm::Run);
// 更改开始时间
    MStartTime = getSysTimeMicros();
}

/* 计算运行时间并运行 */
void Finder::run()
{
    std::vector<Node *> path;
    MStartTime = getSysTimeMicros();
    path = MAlgorithm->run();
    MEndTime = getSysTimeMicros();
    MTime += ((double)(MEndTime - MStartTime - MAlgorithm->MDelayTimes)) / 1000;
    MPath = MPath.fromStdVector(path);
    MLength = MAlgorithm->pathLength(path);
    searchOver();
}

/* 该此线程终止方式不安全 */
void Finder::terminateSearchingTask()
{
    if(searchIsRunning()){
        MFinderThread->terminate();
        MFinderThread->wait();
    }
}

bool Finder::searchIsRunning()
{
    return MFinderThread->isRunning();
}

void Finder::updateGraph()
{
    emit hasTasks("updateGraph");
}

void Finder::searchOver()
{
    emit hasTasks("searchOver");
    emit showPath(MPath);
    emit statsUpdate(MTime, MLength);
}

void Finder::searchRun()
{
    MAlgorithm->setRunStatus(Algorithm::Run);
    emit hasTasks("searchRun");
}

FinderThread::FinderThread(Finder *finder, QObject *parent): QThread(parent)
{
    MFinder = finder;
}

FinderThread::~FinderThread()
{
    terminate();
    wait();
}

void FinderThread::run()
{
    MFinder->run();
}
