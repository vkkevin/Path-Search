#ifndef __GRAPH_WIDGET_H__
#define __GRAPH_WIDGET_H__

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include "core/graph.h"

class GraphWidget: public QWidget
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = 0);
    virtual ~GraphWidget();
    virtual void clearWalls() = 0;
    virtual void clearPath() = 0;
    virtual Graph *graph() { return _graph; };
    virtual void prohibitMouseEvent();
    virtual void allowMouseEvent();
    virtual void drawPath(QVector<Node *> path);
    virtual void updateGraph() = 0;

protected:
    virtual void mousePressEvent(QMouseEvent *) = 0;
    virtual void mouseMoveEvent(QMouseEvent *) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *) = 0;
    virtual void paintEvent(QPaintEvent *) = 0;

protected:
    QVector<Node *> _path;
    enum MouseStatus{
        ALLOW,PROHIBIT
    }_mouseStatus;
    Graph *_graph;
};

#endif /* __GRAPH_WIDGET_H__ */