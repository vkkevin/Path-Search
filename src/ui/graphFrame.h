#ifndef __GRAPH_FRAME_H__
#define __GRAPH_FRAME_H__

#include <QFrame>
#include "ui/graphWidget.h"
#include "core/graph.h"

class GraphFrame: public QFrame
{
    Q_OBJECT

public:
    GraphFrame(QWidget *parent = 0);
    ~GraphFrame();
    void setGraphWidget(GraphWidget *graph);
    void setGraphWidget(const QString &graphName);
    Graph *graph();

protected:
    void setupUi();
    void setupConnect();

private:
    GraphWidget *MGraph;

signals:
    void graphChanged(Graph *graph);

public slots:
    void executeTask(const QString &taskName);
    void executeGraph(Graph *graph);
    void drawPath(QVector<Node *> path);
};

#endif /* __GRAPH_FRAME_H__ */
