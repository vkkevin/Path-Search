#include "ui/graphs/gridGraphWidget.h"

#include <QPainter>
#include <QGraphicsOpacityEffect>
#include <QDebug>

GridGraphWidget::GridGraphWidget(int weight, int heigth, QWidget *parent): GraphWidget(parent), GridGraph(heigth, weight)
{
    setGeometry(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.9);

    gridTypeIsSelected = GridNode::NOOBSTACLE;
}

GridGraphWidget::~GridGraphWidget()
{

}

void GridGraphWidget::clearWalls()
{
    for(int i = 0; i < GridGraph::height(); i++){
        for(int j = 0; j < GridGraph::width(); j++){
            if(GGraph[i][j].type() != GridNode::START && GGraph[i][j].type() != GridNode::END){
                GGraph[i][j].setType(GridNode::NOOBSTACLE);
            }
        }
    }
    GridGraph::initNodePathStatus();
    update();
}

void GridGraphWidget::clearPath()
{
    GridGraph::initNodePathStatus();
    GraphWidget::MPath.clear();
    update();
}

Graph *GridGraphWidget::graph()
{
    return (GridGraph *)this;
}

void GridGraphWidget::updateGraph()
{
    update();
}

void GridGraphWidget::mousePressEvent(QMouseEvent *event)
{
    if(MMouseStatus == PROHIBIT){
        QWidget::mousePressEvent(event);
        return;
    }
    if(event->button() == Qt::LeftButton){
        int x = event->pos().x() / DEFAULT_RECT_WIDTH;
        int y = event->pos().y() / DEFAULT_RECT_HEIGHT;

        if((x >= 0 && x < GridGraph::height()) && (y >= 0 && y < GridGraph::width()) ){
            gridTypeIsSelected = GGraph[x][y].type();
        }
        update();
    }
    QWidget::mousePressEvent(event);
}

void GridGraphWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(MMouseStatus == PROHIBIT){
        QWidget::mouseMoveEvent(event);
        return;
    }
    if(event->buttons() & Qt::LeftButton){
        int x = event->pos().x() / DEFAULT_RECT_WIDTH;
        int y = event->pos().y() / DEFAULT_RECT_HEIGHT;

        if((x >= 0 && x < GridGraph::height()) && (y >= 0 && y < GridGraph::width())){
            if(gridTypeIsSelected == GridNode::START &&
               GGraph[x][y].type() == GridNode::NOOBSTACLE){
                setStartNode(GridGraph::at(x, y));
            }else if(gridTypeIsSelected == GridNode::END &&
                     GGraph[x][y].type() == GridNode::NOOBSTACLE){
                setEndNode(GridGraph::at(x, y));
            }else if(gridTypeIsSelected == GridNode::OBSTACLE &&
                     GGraph[x][y].type() == GridNode::OBSTACLE){
                GGraph[x][y].setType(GridNode::NOOBSTACLE);
            }else if(gridTypeIsSelected == GridNode::NOOBSTACLE &&
                     GGraph[x][y].type() == GridNode::NOOBSTACLE){
                GGraph[x][y].setType(GridNode::OBSTACLE);
            }
        }
        update();
    }
    QWidget::mouseMoveEvent(event);
}

void GridGraphWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(MMouseStatus == PROHIBIT){
        QWidget::mouseReleaseEvent(event);
        return;
    }
    if(event->button() == Qt::LeftButton){
        int x = event->pos().x() / DEFAULT_RECT_WIDTH;
        int y = event->pos().y() / DEFAULT_RECT_HEIGHT;

        if((x >= 0 && x < GridGraph::height()) && (y >= 0 && y < GridGraph::width())){
            if(gridTypeIsSelected == GridNode::START &&
                    GGraph[x][y].type() == GridNode::NOOBSTACLE){
                setStartNode(GridGraph::at(x, y));
            }else if(gridTypeIsSelected == GridNode::END &&
                     GGraph[x][y].type() == GridNode::NOOBSTACLE){
                setEndNode(GridGraph::at(x, y));
            }else if(gridTypeIsSelected == GridNode::OBSTACLE &&
                     GGraph[x][y].type() == GridNode::OBSTACLE){
                GGraph[x][y].setType(GridNode::NOOBSTACLE);
            }else if(gridTypeIsSelected == GridNode::NOOBSTACLE &&
                     GGraph[x][y].type() == GridNode::NOOBSTACLE){
                GGraph[x][y].setType(GridNode::OBSTACLE);
            }
        }
        gridTypeIsSelected = GridNode::NOOBSTACLE;
        update();
    }
    QWidget::mouseReleaseEvent(event);
}

void GridGraphWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor color;

    for(int i = 0; i < GridGraph::height(); i++){
        for(int j = 0; j < GridGraph::width(); j++){
            if(GGraph[i][j].type() == GridNode::START){
                color = startNodeColor;
            }else if(GGraph[i][j].type() == GridNode::END){
                color = endNodeColor;
            }else if(GGraph[i][j].type() == GridNode::OBSTACLE){
                color = grayNodeColor;
            }else if(GGraph[i][j].type() == GridNode::NOOBSTACLE){
                color = whiteNodeColor;
                if(GGraph[i][j].status() == GridNode::VISITED){
                    color = visitedNodeColor;
                }else if(GGraph[i][j].status() == GridNode::VISITING){
                    color = visitingNodeColor;
                }
            }

            painter.fillRect(QRect(QPoint(GGraph[i][j].x() * DEFAULT_RECT_WIDTH,
                           GGraph[i][j].y() * DEFAULT_RECT_HEIGHT),
                           QSize(DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT)), QColor(color));
        }
    }

    painter.setPen(QPen(Qt::black, 1));
    for(int i = 0; i < GridGraph::height(); i++){
        for(int j = 0; j < GridGraph::width(); j++){
            painter.drawRect(QRect(GridGraph::at(i, j)->x() * DEFAULT_RECT_WIDTH,
                                                      GridGraph::at(i, j)->y() * DEFAULT_RECT_HEIGHT,
                                                       DEFAULT_RECT_WIDTH, DEFAULT_RECT_WIDTH));
        }
    }

    painter.setPen(QPen(Qt::yellow, 3));
    for(int i = 1; i < MPath.size(); i++){
        int x1 =((GridNode *)(MPath.at(i - 1)))->x() * DEFAULT_RECT_WIDTH + DEFAULT_RECT_WIDTH / 2;
        int y1 =((GridNode *)(MPath.at(i - 1)))->y() * DEFAULT_RECT_HEIGHT + DEFAULT_RECT_HEIGHT /2;
        int x2 =((GridNode *)(MPath.at(i)))->x() * DEFAULT_RECT_WIDTH + DEFAULT_RECT_WIDTH / 2;
        int y2 =((GridNode *)(MPath.at(i)))->y() * DEFAULT_RECT_HEIGHT + DEFAULT_RECT_HEIGHT / 2;
        painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
    }

    QWidget::paintEvent(event);
}

