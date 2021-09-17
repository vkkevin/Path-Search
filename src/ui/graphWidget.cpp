#include "ui/graphWidget.h"
#include <QDebug>

GraphWidget::GraphWidget(QWidget *parent): QWidget(parent)
{
    _path.clear();
    _mouseStatus = ALLOW;
}

GraphWidget::~GraphWidget()
{

}

void GraphWidget::prohibitMouseEvent()
{
    _mouseStatus = PROHIBIT;
}

void GraphWidget::allowMouseEvent()
{
    _mouseStatus = ALLOW;
}

void GraphWidget::drawPath(QVector<Node *> path)
{
    _path = path;
    updateGraph();
}

void GraphWidget::updateGraph()
{
    update();
}
