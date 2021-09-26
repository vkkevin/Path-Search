#ifndef GRAPH_FRAME_H
#define GRAPH_FRAME_H

#include <QFrame>
#include "ui/core/graphWidget.h"
#include "core/graph.h"

class GraphFrame: public QFrame
{
    Q_OBJECT

public:
    GraphFrame(QWidget *parent = nullptr);
    ~GraphFrame();
    void setGraphWidget(GraphWidget *graph);
    void setGraphWidget(const QString &graphName);
    Graph *graph();

protected:
    void init();
    void initUi();
    void initConnect();

private:
    GraphWidget *_graph;

signals:
    void graphChanged(Graph *graph);

public slots:
    void executeTask(const QString &taskName);
    void executeGraph(Graph *graph);
    void drawPath(QVector<Node *> path);
};

#endif /* GRAPH_FRAME_H */
