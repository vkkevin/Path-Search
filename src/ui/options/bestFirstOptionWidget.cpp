#include "ui/options/bestFirstOptionWidget.h"
#include "core/option.h"
#include "core/heuristic.h"
#include <QBoxLayout>
#include <QDebug>

BestFirstOptionWidget::BestFirstOptionWidget(QString algoName, QWidget *parent)
    : OptionWidget(algoName, parent)
{
    setGeometry(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));
    MOption = new Option();
    initOption();
    MHeuristic = new Heuristic();
    setupUi();
    setupConnect();
}

BestFirstOptionWidget::~BestFirstOptionWidget()
{
    delete  MHeuristic;
    delete  MOption;
}

Option *BestFirstOptionWidget::option()
{
    return MOption;
}

Heuristic *BestFirstOptionWidget::heuristic()
{
    return MHeuristic;
}

void BestFirstOptionWidget::setupUi()
{
    MHeuristicGroup = new QGroupBox(tr("Heuristic"), this);
    MHeuristicGroup->setMaximumHeight(200);
    MOptionGroup = new QGroupBox(tr("Options"), this);
    setupHeuristicGroupUi();
    setupOptionGroupUi();

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(MAlgoName);
    mainLayout->addWidget(MHeuristicGroup);
    mainLayout->addWidget(MOptionGroup);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void BestFirstOptionWidget::setupOptionGroupUi()
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

void BestFirstOptionWidget::setupHeuristicGroupUi()
{
    MManhattan = new QRadioButton(tr("manhattan"), MHeuristicGroup);
    MManhattan->setCursor(QCursor(Qt::PointingHandCursor));
    MManhattan->setChecked(true);
    MEuclidean = new QRadioButton(tr("euclidean"), MHeuristicGroup);
    MEuclidean->setCursor(QCursor(Qt::PointingHandCursor));
    MOctile = new QRadioButton(tr("octile"), MHeuristicGroup);
    MOctile->setCursor(QCursor(Qt::PointingHandCursor));
    MChebyshev = new QRadioButton(tr("chebyshev"), MHeuristicGroup);
    MChebyshev->setCursor(QCursor(Qt::PointingHandCursor));

    QVBoxLayout *heuristicLayout = new QVBoxLayout();
    heuristicLayout->addWidget(MManhattan);
    heuristicLayout->addWidget(MEuclidean);
    heuristicLayout->addWidget(MOctile);
    heuristicLayout->addWidget(MChebyshev);
    MHeuristicGroup->setLayout(heuristicLayout);
}

void BestFirstOptionWidget::setupConnect()
{
    connect(MManhattan, SIGNAL(toggled(bool)), this, SLOT(manhattanChecked(bool)));
    connect(MEuclidean, SIGNAL(toggled(bool)), this, SLOT(euclideanChecked(bool)));
    connect(MOctile, SIGNAL(toggled(bool)), this, SLOT(octileChecked(bool)));
    connect(MChebyshev, SIGNAL(toggled(bool)), this, SLOT(chebyshevChecked(bool)));
    connect(MAllowDiagonal, SIGNAL(stateChanged(int)), this, SLOT(allowDiagonalStateChanged(int)));
    connect(MBiDirectional, SIGNAL(stateChanged(int)), this, SLOT(biDirectionalStateChanged(int)));
    connect(MDontCrossCorners, SIGNAL(stateChanged(int)), this, SLOT(dontCrossCornersStateChanged(int)));
}

void BestFirstOptionWidget::initOption()
{
    MOption->setOptionUsability(Option::AllowDiagonal);
    MOption->setOptionUsability(Option::BiDirectional);
    MOption->setOptionUsability(Option::DontCrossCorners);
    MOption->setOptionUsability(Option::Weight);
}

void BestFirstOptionWidget::allowDiagonalStateChanged(int state)
{
    switch(state){
        case 0: MOption->setOptionValue(Option::AllowDiagonal, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: MOption->setOptionValue(Option::AllowDiagonal, Option::SELECTED); break;
    }
}

void BestFirstOptionWidget::biDirectionalStateChanged(int state)
{
    switch(state){
        case 0: MOption->setOptionValue(Option::BiDirectional , Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: MOption->setOptionValue(Option::BiDirectional, Option::SELECTED); break;
    }
}

void BestFirstOptionWidget::dontCrossCornersStateChanged(int state)
{
    switch(state){
        case 0: MOption->setOptionValue(Option::DontCrossCorners, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: MOption->setOptionValue(Option::DontCrossCorners, Option::SELECTED); break;
    }
}

void BestFirstOptionWidget::manhattanChecked(bool checked)
{
    if(checked){
        MHeuristic->setHeuristicType(Heuristic::Manhattan);
    }
}

void BestFirstOptionWidget::euclideanChecked(bool checked)
{
    if(checked){
        MHeuristic->setHeuristicType(Heuristic::Euclidean);
    }
}

void BestFirstOptionWidget::octileChecked(bool checked)
{
    if(checked){
        MHeuristic->setHeuristicType(Heuristic::Octile);
    }
}

void BestFirstOptionWidget::chebyshevChecked(bool checked)
{
    if(checked){
        MHeuristic->setHeuristicType(Heuristic::Chebyshev);
    }
}

