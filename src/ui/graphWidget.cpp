#include "ui/graphWidget.h"
#include <QDebug>

GraphWidget::GraphWidget(QWidget *parent): QWidget(parent)
{
    MPath.clear();
    MMouseStatus = ALLOW;
}

GraphWidget::~GraphWidget()
{

}

void GraphWidget::prohibitMouseEvent()
{
    MMouseStatus = PROHIBIT;
}

void GraphWidget::allowMouseEvent()
{
    MMouseStatus = ALLOW;
}

void GraphWidget::drawPath(QVector<Node *> path)
{
    MPath = path;
    updateGraph();
}

void GraphWidget::updateGraph()
{
    update();
}
