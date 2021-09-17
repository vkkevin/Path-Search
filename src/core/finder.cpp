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
    _algorithm = NULL;
    _graph = NULL;
    _option = NULL;
    _heuristic = NULL;
    _finderThread = new FinderThread(this);
    _time = 0;
}

Finder::~Finder()
{
    delete _finderThread;
}

/*  此处有 bug
 *  当 algoName 不存在时会造成 MAlgorithm 指针的多次释放
 */
void Finder::setAlgorithm(const QString algoName)
{
    if(_algorithm != NULL){
        disconnect(_algorithm, SIGNAL(updateGraph()), this, SLOT(updateGraph()));
        delete _algorithm;
    }

    if(algoName == "A*"){
        _algorithm = new AStarSearcher();
    }else if(algoName == "IDA*"){
        _algorithm = new IDAStarSearcher();
    }else if(algoName == "Bearch First Search"){
        _algorithm = new BreadthFirstSearcher();
    }else if(algoName == "Best First Search"){
        _algorithm = new BestFirstSearcher();
    }else if(algoName == "Dijkstra"){
        _algorithm = new DijkstraSearcher();
    }

    connect(_algorithm, SIGNAL(updateGraph()), this, SLOT(updateGraph()), Qt::UniqueConnection);
}

/*  此处有 bug
 *  当 type 不存在时会造成 MAlgorithm 指针的多次释放
 */
void Finder::setAlgorithm(Algorithm::AlgorithmType type)
{
    if(_algorithm != NULL){
        disconnect(_algorithm, SIGNAL(updateGraph()), this, SLOT(updateGraph()));
        delete _algorithm;
    }

    switch(type){
        case Algorithm::AStarSearch:   _algorithm = new AStarSearcher();
        case Algorithm::IDAStarSearch:   _algorithm = new IDAStarSearcher();
        case Algorithm::BreadthFirstSearch:   _algorithm = new BreadthFirstSearcher();
        case Algorithm::BestFirstSearch:   _algorithm = new BestFirstSearcher();
        case Algorithm::DijkstraSearch:   _algorithm = new DijkstraSearcher();
        default: break;
    }
    connect(_algorithm, SIGNAL(updateGraph()), this, SLOT(updateGraph()), Qt::UniqueConnection);
}

void Finder::setGraph(Graph *graph)
{
    _graph = graph;
}

void Finder::setOption(Option *option)
{
    if(option == NULL)
        return;
    _option = option;
}

void Finder::setHeuristic(Heuristic *heuristic)
{
    if(heuristic == NULL)
        return;
    _heuristic = heuristic;
}

void Finder::findPath()
{
    terminateSearchingTask();

    if(_graph == NULL){
        qDebug() << "No Graph";
        return;
    }
    _graph->initNodePathStatus();
    _algorithm->setGraph(_graph);

    if(_option != NULL)
        _algorithm->setOption(new Option(*_option));
    else qDebug() << "No Option";

    if(_heuristic != NULL)
        _algorithm->setHeuristic(new Heuristic(*_heuristic));
    else qDebug() << "No Heuristic";

    _algorithm->_delayTimes = 0;
    _time = 0;

    searchRun();
    _finderThread->start();
}

/* 计算运行时间并暂停运行 */
void Finder::pauseFinder()
{
    _algorithm->setRunStatus(Algorithm::Stop);
// 更改结束时间
    MEndTime = getSysTimeMicros();
    _time += ((double)(MEndTime - MStartTime)) / 1000;
}

/* 计算运行时间并继续运行 */
void Finder::resumeFinder()
{
    _algorithm->setRunStatus(Algorithm::Run);
// 更改开始时间
    MStartTime = getSysTimeMicros();
}

/* 计算运行时间并运行 */
void Finder::run()
{
    std::vector<Node *> path;
    MStartTime = getSysTimeMicros();
    path = _algorithm->run();
    MEndTime = getSysTimeMicros();
    _time += ((double)(MEndTime - MStartTime - _algorithm->_delayTimes)) / 1000;
    _path = _path.fromStdVector(path);
    _length = _algorithm->pathLength(path);
    searchOver();
}

/* 该此线程终止方式不安全 */
void Finder::terminateSearchingTask()
{
    if(searchIsRunning()){
        _finderThread->terminate();
        _finderThread->wait();
    }
}

bool Finder::searchIsRunning()
{
    return _finderThread->isRunning();
}

void Finder::updateGraph()
{
    emit hasTasks("updateGraph");
}

void Finder::searchOver()
{
    emit hasTasks("searchOver");
    emit showPath(_path);
    emit statsUpdate(_time, _length);
}

void Finder::searchRun()
{
    _algorithm->setRunStatus(Algorithm::Run);
    emit hasTasks("searchRun");
}

FinderThread::FinderThread(Finder *finder, QObject *parent): QThread(parent)
{
    _finder = finder;
}

FinderThread::~FinderThread()
{
    terminate();
    wait();
}

void FinderThread::run()
{
    _finder->run();
}
