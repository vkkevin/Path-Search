#include "ui/statsWidget.h"
#include <QBoxLayout>

StatsWidget::StatsWidget(QWidget *parent): QWidget(parent)
{
    setGeometry(QRect(0, 0, parent->width(), parent->height()));
    setupUi();
}

StatsWidget::~StatsWidget()
{

}

void StatsWidget::showResultInfo(double time, double length)
{
    MPathLabel->setText("length: " + QString::number(length, 'g', 4));
    MTimeLabel->setText("time: " + QString::number(time, 'f', 4) + " ms");
}

void StatsWidget::setupUi()
{
    MPathLabel = new QLabel("length: ", this);
    MPathLabel->setMinimumWidth(200);
    MTimeLabel = new QLabel("time:  ms", this);
    MTimeLabel->setMinimumWidth(200);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(MPathLabel);
    mainLayout->addWidget(MTimeLabel);
    mainLayout->addStretch();
    setLayout(mainLayout);
}
