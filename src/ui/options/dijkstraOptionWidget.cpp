#include "ui/options/dijkstraOptionWidget.h"
#include <QBoxLayout>
#include <QDebug>

DijkstraOptionWidget::DijkstraOptionWidget(QString algoName, QWidget *parent)
    : OptionWidget(algoName, parent)
{
    setGeometry(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));

    MOption = new Option();
    initOption();
    setupUi();
    setupConnect();
}

DijkstraOptionWidget::~DijkstraOptionWidget()
{
    delete MOption;
}

Option *DijkstraOptionWidget::option()
{
    return MOption;
}

Heuristic *DijkstraOptionWidget::heuristic()
{
    return NULL;
}

void DijkstraOptionWidget::setupUi()
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

void DijkstraOptionWidget::setupOptionGroupUi()
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

void DijkstraOptionWidget::setupConnect()
{
    connect(MAllowDiagonal, SIGNAL(stateChanged(int)), this, SLOT(allowDiagonalStateChanged(int)));
    connect(MBiDirectional, SIGNAL(stateChanged(int)), this, SLOT(biDirectionalStateChanged(int)));
    connect(MDontCrossCorners, SIGNAL(stateChanged(int)), this, SLOT(dontCrossCornersStateChanged(int)));
}

void DijkstraOptionWidget::initOption()
{
    MOption->setOptionUsability(Option::AllowDiagonal);
    MOption->setOptionUsability(Option::BiDirectional);
    MOption->setOptionUsability(Option::DontCrossCorners);
}

void DijkstraOptionWidget::allowDiagonalStateChanged(int state)
{
    switch(state){
        case 0: MOption->setOptionValue(Option::AllowDiagonal, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: MOption->setOptionValue(Option::AllowDiagonal, Option::SELECTED); break;
    }
}

void DijkstraOptionWidget::biDirectionalStateChanged(int state)
{
    switch(state){
        case 0: MOption->setOptionValue(Option::BiDirectional , Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: MOption->setOptionValue(Option::BiDirectional, Option::SELECTED); break;
    }
}

void DijkstraOptionWidget::dontCrossCornersStateChanged(int state)
{
    switch(state){
        case 0: MOption->setOptionValue(Option::DontCrossCorners, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: MOption->setOptionValue(Option::DontCrossCorners, Option::SELECTED); break;
    }
}
