#include "statsWidget.h"
#include <QBoxLayout>

StatsWidget::StatsWidget(QWidget *parent): QWidget(parent)
{
    setGeometry(QRect(0, 0, parent->width(), parent->height()));
    initUi();
}

StatsWidget::~StatsWidget()
{

}

void StatsWidget::showResultInfo(double time, double length)
{
    _pathLabel->setText("length: " + QString::number(length, 'g', 4));
    _timeLabel->setText("time: " + QString::number(time, 'f', 4) + " ms");
}

void StatsWidget::initUi()
{
    _pathLabel = new QLabel("length: ", this);
    _pathLabel->setMinimumWidth(200);
    _timeLabel = new QLabel("time:  ms", this);
    _timeLabel->setMinimumWidth(200);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(_pathLabel);
    mainLayout->addWidget(_timeLabel);
    mainLayout->addStretch();
    setLayout(mainLayout);
}
