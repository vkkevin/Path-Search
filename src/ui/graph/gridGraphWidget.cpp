#include "gridGraphWidget.h"

#include <QPainter>
#include <QGraphicsOpacityEffect>
#include <QDebug>

GridGraphWidget::GridGraphWidget(int width, int height, QWidget *parent)
    : GraphWidget(parent),
      _gridgraph(width, height)
{
    setGeometry(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.9);

    _gridTypeIsSelected = GridNode::NOOBSTACLE;

//    _gridgraph.setWidth(weight);
//    _gridgraph.setHeight(heigth);
    _graph = &_gridgraph;
}

GridGraphWidget::~GridGraphWidget()
{

}

void GridGraphWidget::clearWalls()
{
    _gridgraph.clearWalls();
    update();
}

void GridGraphWidget::clearPath()
{
    _gridgraph.clearPath();
    GraphWidget::_path.clear();
    update();
}

Graph *GridGraphWidget::graph()
{
    return _graph;
}

void GridGraphWidget::updateGraph()
{
    update();
}

void GridGraphWidget::mousePressEvent(QMouseEvent *event)
{
    if(_mouseStatus == PROHIBIT){
        QWidget::mousePressEvent(event);
        return;
    }
    if(event->button() == Qt::LeftButton){
        int x = event->pos().x() / DEFAULT_RECT_WIDTH;
        int y = event->pos().y() / DEFAULT_RECT_HEIGHT;

        if((x >= 0 && x < _gridgraph.height()) && (y >= 0 && y < _gridgraph.width()) ){
            _gridTypeIsSelected = _gridgraph.at(x, y)->type();
        }
        update();
    }
    QWidget::mousePressEvent(event);
}

void GridGraphWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(_mouseStatus == PROHIBIT){
        QWidget::mouseMoveEvent(event);
        return;
    }
    if(event->buttons() & Qt::LeftButton){
        int x = event->pos().x() / DEFAULT_RECT_WIDTH;
        int y = event->pos().y() / DEFAULT_RECT_HEIGHT;

        if((x >= 0 && x < _gridgraph.height()) && (y >= 0 && y < _gridgraph.width())){
            if(_gridTypeIsSelected == GridNode::START &&
                    _gridgraph.at(x, y)->type() == GridNode::NOOBSTACLE){
                _gridgraph.setStartNode(_gridgraph.at(x, y));
            }else if(_gridTypeIsSelected == GridNode::END &&
                    _gridgraph.at(x, y)->type() == GridNode::NOOBSTACLE){
                _gridgraph.setEndNode(_gridgraph.at(x, y));
            }else if(_gridTypeIsSelected == GridNode::OBSTACLE &&
                    _gridgraph.at(x, y)->type() == GridNode::OBSTACLE){
                _gridgraph.at(x, y)->setType(GridNode::NOOBSTACLE);
            }else if(_gridTypeIsSelected == GridNode::NOOBSTACLE &&
                    _gridgraph.at(x, y)->type() == GridNode::NOOBSTACLE){
                _gridgraph.at(x, y)->setType(GridNode::OBSTACLE);
            }
        }
        update();
    }
    QWidget::mouseMoveEvent(event);
}

void GridGraphWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(_mouseStatus == PROHIBIT){
        QWidget::mouseReleaseEvent(event);
        return;
    }
    if(event->button() == Qt::LeftButton){
        int x = event->pos().x() / DEFAULT_RECT_WIDTH;
        int y = event->pos().y() / DEFAULT_RECT_HEIGHT;

        if((x >= 0 && x < _gridgraph.height()) && (y >= 0 && y < _gridgraph.width())){
            if(_gridTypeIsSelected == GridNode::START &&
                    _gridgraph.at(x, y)->type() == GridNode::NOOBSTACLE){
                _gridgraph.setStartNode(_gridgraph.at(x, y));
            }else if(_gridTypeIsSelected == GridNode::END &&
                     _gridgraph.at(x, y)->type() == GridNode::NOOBSTACLE){
                _gridgraph.setEndNode(_gridgraph.at(x, y));
            }else if(_gridTypeIsSelected == GridNode::OBSTACLE &&
                     _gridgraph.at(x, y)->type() == GridNode::OBSTACLE){
                _gridgraph.at(x, y)->setType(GridNode::NOOBSTACLE);
            }else if(_gridTypeIsSelected == GridNode::NOOBSTACLE &&
                     _gridgraph.at(x, y)->type() == GridNode::NOOBSTACLE){
                _gridgraph.at(x, y)->setType(GridNode::OBSTACLE);
            }
        }
        _gridTypeIsSelected = GridNode::NOOBSTACLE;
        update();
    }
    QWidget::mouseReleaseEvent(event);
}

void GridGraphWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor color;

    for(int i = 0; i < _gridgraph.height(); i++){
        for(int j = 0; j < _gridgraph.width(); j++){
            if(_gridgraph.at(i, j)->type() == GridNode::START){
                color = startNodeColor;
            }else if(_gridgraph.at(i, j)->type() == GridNode::END){
                color = endNodeColor;
            }else if(_gridgraph.at(i, j)->type() == GridNode::OBSTACLE){
                color = grayNodeColor;
            }else if(_gridgraph.at(i, j)->type() == GridNode::NOOBSTACLE){
                color = whiteNodeColor;
                if(_gridgraph.at(i, j)->status() == GridNode::VISITED){
                    color = visitedNodeColor;
                }else if(_gridgraph.at(i, j)->status() == GridNode::VISITING){
                    color = visitingNodeColor;
                }
            }

            painter.fillRect(QRect(QPoint(_gridgraph.at(i, j)->x() * DEFAULT_RECT_WIDTH,
                           _gridgraph.at(i, j)->y() * DEFAULT_RECT_HEIGHT),
                           QSize(DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT)), QColor(color));
        }
    }

    painter.setPen(QPen(Qt::black, 1));
    for(int i = 0; i < _gridgraph.height(); i++){
        for(int j = 0; j < _gridgraph.width(); j++){
            painter.drawRect(QRect(_gridgraph.at(i, j)->x() * DEFAULT_RECT_WIDTH,
                                                      _gridgraph.at(i, j)->y() * DEFAULT_RECT_HEIGHT,
                                                       DEFAULT_RECT_WIDTH, DEFAULT_RECT_WIDTH));
        }
    }

    painter.setPen(QPen(Qt::yellow, 3));
    for(int i = 1; i < _path.size(); i++){
        int x1 =((GridNode *)(_path.at(i - 1)))->x() * DEFAULT_RECT_WIDTH + DEFAULT_RECT_WIDTH / 2;
        int y1 =((GridNode *)(_path.at(i - 1)))->y() * DEFAULT_RECT_HEIGHT + DEFAULT_RECT_HEIGHT /2;
        int x2 =((GridNode *)(_path.at(i)))->x() * DEFAULT_RECT_WIDTH + DEFAULT_RECT_WIDTH / 2;
        int y2 =((GridNode *)(_path.at(i)))->y() * DEFAULT_RECT_HEIGHT + DEFAULT_RECT_HEIGHT / 2;
        painter.drawLine(QPoint(x1, y1), QPoint(x2, y2));
    }

    QWidget::paintEvent(event);
}

