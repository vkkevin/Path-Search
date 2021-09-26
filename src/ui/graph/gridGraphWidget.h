#ifndef GRID_GRAPH_WIDGET_H
#define GRID_GRAPH_WIDGET_H

#include <QtGlobal>
#include "ui/core/graphWidget.h"
#include "graph/gridGraph.h"

/*
 * Graph display color
 */
static QColor startNodeColor = QColor(QRgb(0x00dd00));
static QColor endNodeColor = QColor(QRgb(0xee4400));
//static QColor pathNodeColor = QColor(Qt::yellow);
static QColor visitedNodeColor = QColor(QRgb(0xafeeee));
static QColor visitingNodeColor = QColor(QRgb(0x98fb98));
static QColor grayNodeColor = QColor(QRgb(0x808080));
static QColor whiteNodeColor = QColor(QRgb(0xffffff));

class GridGraphWidget: public GraphWidget
{
    Q_OBJECT

public:
    GridGraphWidget(int width, int height, QWidget *parent = nullptr);
    virtual ~GridGraphWidget();
    void clearWalls();
    void clearPath();
    Graph *graph();
    void updateGraph();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    static const int DEFAULT_RECT_WIDTH = 30;
    static const int DEFAULT_RECT_HEIGHT = 30;
    enum GridNode::Type _gridTypeIsSelected;
    GridGraph _gridgraph;
};


#endif /* GRID_GRAPH_WIDGET_H */
