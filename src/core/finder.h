#ifndef __FINDER_H__
#define __FINDER_H__

#include <QObject>
#include <QVector>
#include <QTime>
#include <QThread>
#include "graph.h"
#include "algorithm.h"
#include "option.h"
#include "heuristic.h"

class FinderThread;

class Finder: public QObject
{
    Q_OBJECT
    friend class FinderThread;
public:
    Finder(QObject *parent = 0);
    ~Finder();
    void setAlgorithm(const QString algoName);
    void setAlgorithm(Algorithm::AlgorithmType type);
    void setGraph(Graph *graph);
    void setOption(Option *option);
    void setHeuristic(Heuristic *heuristic);

    void findPath();
    void pauseFinder();
    void resumeFinder();
protected:
    void run();

private:
    Graph *MGraph;
    Algorithm *MAlgorithm;
    Option *MOption;
    Heuristic *MHeuristic;

    QVector<Node *> MPath;
    double MTime;
    double MLength;

    FinderThread *MFinderThread;

public:
    void terminateSearchingTask();
    bool searchIsRunning();

signals:
    void hasTasks(const QString &taskName);
    void statsUpdate(double time, double length);
    void showPath(QVector<Node *> path);

protected slots:
    void updateGraph();
    void searchOver();
    void searchRun();
};


class FinderThread: public QThread
{
    Q_OBJECT
public:
    FinderThread(Finder *finder, QObject *parent = 0);
    ~FinderThread();
protected:
    void run();
private:
    Finder *MFinder;
};

#endif /* __FINDER_H__ */
