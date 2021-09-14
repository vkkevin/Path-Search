#ifndef __GRAPH_WIDGET_H__
#define __GRAPH_WIDGET_H__

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include "core/graph.h"

class GraphWidget: public QWidget//, virtual public Graph
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);
    virtual ~GraphWidget();
    virtual void clearWalls() = 0;
    virtual void clearPath() = 0;
    virtual Graph *graph() = 0;
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
    QVector<Node *> MPath;
    enum MouseStatus{
        ALLOW,PROHIBIT
    }MMouseStatus;
};

#endif /* __GRAPH_WIDGET_H__ */
