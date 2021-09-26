#include "ui/graphFrame.h"
#include "ui/graph/gridGraphWidget.h"
#include <QDebug>

GraphFrame::GraphFrame(QWidget *parent)
    : QFrame(parent),
      _graph(NULL)
{
    init();
}


GraphFrame::~GraphFrame()
{

}

void GraphFrame::setGraphWidget(GraphWidget *graph)
{
    if(_graph != NULL && _graph != graph)
        delete _graph;
    if(graph == NULL)
        return;
    _graph = graph;
    _graph->show();
    initConnect();
    executeGraph((Graph *)(_graph->graph()));
}

void GraphFrame::setGraphWidget(const QString &graphName)
{
    if(graphName == "Grid Graph"){
        setGraphWidget((GraphWidget *)(new GridGraphWidget(28, 24, this)));
    }
}

Graph *GraphFrame::graph()
{
    return (Graph *)(_graph->graph());
}

void GraphFrame::init()
{
    setMinimumSize(QSize(845, 725));
    setStyleSheet(tr("background-color: White;"));
    initUi();
    initConnect();
}


void GraphFrame::initUi()
{
    setGraphWidget("Grid Graph");
}


void GraphFrame::initConnect()
{

}

void GraphFrame::executeTask(const QString &taskName)
{
    if(taskName == "clearWalls"){
        _graph->clearWalls();
        _graph->allowMouseEvent();
    }else if(taskName == "updateGraph"){
        _graph->update();
    }else if(taskName == "clearPath"){
        _graph->clearPath();
        _graph->allowMouseEvent();
    }else if(taskName == "searchRun"){
        _graph->prohibitMouseEvent();
    }else if(taskName == "searchOver"){
        _graph->allowMouseEvent();
    }
}

void GraphFrame::executeGraph(Graph *graph)
{
    emit graphChanged(graph);
}

void GraphFrame::drawPath(QVector<Node *> path)
{
    _graph->drawPath(path);
    _graph->updateGraph();
}
