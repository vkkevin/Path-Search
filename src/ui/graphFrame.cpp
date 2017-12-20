#include "ui/graphFrame.h"
#include "ui/graphs/gridGraphWidget.h"
#include <QDebug>

GraphFrame::GraphFrame(QWidget *parent): QFrame(parent)
{
    MGraph = NULL;
    setMinimumSize(QSize(845, 725));
    setStyleSheet(tr("background-color: White;"));
    setupUi();
    setupConnect();
}


GraphFrame::~GraphFrame()
{

}

void GraphFrame::setGraphWidget(GraphWidget *graph)
{
    if(MGraph != NULL && MGraph != graph)
        delete MGraph;
    if(graph == NULL)
        return;
    MGraph = graph;
    MGraph->show();
    setupConnect();
    executeGraph((Graph *)(MGraph->graph()));
}

void GraphFrame::setGraphWidget(const QString &graphName)
{
    if(graphName == "Grid Graph"){
        setGraphWidget((GraphWidget *)(new GridGraphWidget(28, 24, this)));
    }
}

Graph *GraphFrame::graph()
{
    return (Graph *)(MGraph->graph());
}


void GraphFrame::setupUi()
{
    setGraphWidget("Grid Graph");
}


void GraphFrame::setupConnect()
{

}

void GraphFrame::executeTask(const QString &taskName)
{
    if(taskName == "clearWalls"){
        MGraph->clearWalls();
        MGraph->allowMouseEvent();
    }else if(taskName == "updateGraph"){
        MGraph->update();
    }else if(taskName == "clearPath"){
        MGraph->clearPath();
        MGraph->allowMouseEvent();
    }else if(taskName == "searchRun"){
        MGraph->prohibitMouseEvent();
    }else if(taskName == "searchOver"){
        MGraph->allowMouseEvent();
    }
}

void GraphFrame::executeGraph(Graph *graph)
{
    emit graphChanged(graph);
}

void GraphFrame::drawPath(QVector<Node *> path)
{
    MGraph->drawPath(path);
    MGraph->updateGraph();
}
