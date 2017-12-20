#include "ui/options/breadthFirstOptionWidget.h"
#include <QBoxLayout>
#include <QDebug>

BreadthFirstOptionWidget::BreadthFirstOptionWidget(QString algoName, QWidget *parent)
    : OptionWidget(algoName, parent)
{
    setGeometry(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));

    MOption = new Option();
    initOption();
    setupUi();
    setupConnect();
}

BreadthFirstOptionWidget::~BreadthFirstOptionWidget()
{
    delete MOption;
}

Option *BreadthFirstOptionWidget::option()
{
    return MOption;
}

Heuristic *BreadthFirstOptionWidget::heuristic()
{
    return NULL;
}

void BreadthFirstOptionWidget::setupUi()
{
    MOptionGroup = new QGroupBox(tr("Options"), this);
    MOptionGroup->setMinimumHeight(200);

    QVBoxLayout *optionLayout = new QVBoxLayout();
    optionLayout->addWidget(MAlgoName);
    optionLayout->addWidget(MOptionGroup);
    optionLayout->addStretch();
    setLayout(optionLayout);
    setupOptionGroupUi();
}

void BreadthFirstOptionWidget::setupOptionGroupUi()
{
    MAllowDiagonal = new QCheckBox(tr("Allow Diagonal"), MOptionGroup);
    MAllowDiagonal->setCursor(QCursor(Qt::PointingHandCursor));
    MBiDirectional = new QCheckBox(tr("Bi-Directional"), MOptionGroup);
    MBiDirectional->setCursor(QCursor(Qt::PointingHandCursor));
    MDontCrossCorners = new QCheckBox(tr("Don't Cross Corners"), MOptionGroup);
    MDontCrossCorners->setCursor(QCursor(Qt::PointingHandCursor));

    QVBoxLayout *optionLayout = new QVBoxLayout();
    optionLayout->addWidget(MAllowDiagonal);
    optionLayout->addWidget(MBiDirectional);
    optionLayout->addWidget(MDontCrossCorners);
    MOptionGroup->setLayout(optionLayout);
}

void BreadthFirstOptionWidget::setupConnect()
{
    connect(MAllowDiagonal, SIGNAL(stateChanged(int)), this, SLOT(allowDiagonalStateChanged(int)));
    connect(MBiDirectional, SIGNAL(stateChanged(int)), this, SLOT(biDirectionalStateChanged(int)));
    connect(MDontCrossCorners, SIGNAL(stateChanged(int)), this, SLOT(dontCrossCornersStateChanged(int)));
}

void BreadthFirstOptionWidget::initOption()
{
    MOption->setOptionUsability(Option::AllowDiagonal);
    MOption->setOptionUsability(Option::BiDirectional);
    MOption->setOptionUsability(Option::DontCrossCorners);
}

void BreadthFirstOptionWidget::allowDiagonalStateChanged(int state)
{
    switch(state){
        case 0: MOption->setOptionValue(Option::AllowDiagonal, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: MOption->setOptionValue(Option::AllowDiagonal, Option::SELECTED); break;
    }
}

void BreadthFirstOptionWidget::biDirectionalStateChanged(int state)
{
    switch(state){
        case 0: MOption->setOptionValue(Option::BiDirectional , Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: MOption->setOptionValue(Option::BiDirectional, Option::SELECTED); break;
    }
}

void BreadthFirstOptionWidget::dontCrossCornersStateChanged(int state)
{
    switch(state){
        case 0: MOption->setOptionValue(Option::DontCrossCorners, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: MOption->setOptionValue(Option::DontCrossCorners, Option::SELECTED); break;
    }
}
