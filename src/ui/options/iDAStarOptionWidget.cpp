#include "ui/options/iDAStarOptionWidget.h"
#include "core/option.h"
#include "core/heuristic.h"
#include <QBoxLayout>
#include <QDebug>

IDAStarOptionWidget::IDAStarOptionWidget(QString algoName, QWidget *parent)
    : OptionWidget(algoName, parent)
{
    setGeometry(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));
    MOption = new Option();
    initOption();
    MHeuristic = new Heuristic();
    setupUi();
    setupConnect();
    MWeight->setValue(1);
    MTimeLimit->setValue(10);
}

IDAStarOptionWidget::~IDAStarOptionWidget()
{
    delete  MHeuristic;
    delete  MOption;
}

Option *IDAStarOptionWidget::option()
{
    return MOption;
}

Heuristic *IDAStarOptionWidget::heuristic()
{
    return MHeuristic;
}

void IDAStarOptionWidget::setupUi()
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

void IDAStarOptionWidget::setupOptionGroupUi()
{
    MAllowDiagonal = new QCheckBox(tr("Allow Diagonal"), MOptionGroup);
    MAllowDiagonal->setCursor(QCursor(Qt::PointingHandCursor));
    MDontCrossCorners = new QCheckBox(tr("Don't Cross Corners"), MOptionGroup);
    MDontCrossCorners->setCursor(QCursor(Qt::PointingHandCursor));
    MVisualizeRecursion = new QCheckBox(tr("Visualize recursion"), MOptionGroup);
    MVisualizeRecursion->setCursor(QCursor(Qt::PointingHandCursor));

    MWeight = new QSpinBox(MOptionGroup);
    MWeight->setCursor(QCursor(Qt::PointingHandCursor));
    MWeight->setMaximum(99999);
    QLabel *weightLabel = new QLabel("Weight", MOptionGroup);
    weightLabel->setCursor(QCursor(Qt::PointingHandCursor));
    weightLabel->setBuddy(MWeight);
    QHBoxLayout *weightLayout = new QHBoxLayout();
    weightLayout->addWidget(MWeight);
    weightLayout->addWidget(weightLabel);

    MTimeLimit = new QSpinBox(MOptionGroup);
    MTimeLimit->setCursor(QCursor(Qt::PointingHandCursor));
//    MTimeLimit->setMaximum(99);
    QLabel *limitLabel = new QLabel("Seconds limit", MOptionGroup);
    limitLabel->setCursor(QCursor(Qt::PointingHandCursor));
    limitLabel->setBuddy(MTimeLimit);
    QHBoxLayout *limitLayout = new QHBoxLayout();
    limitLayout->addWidget(MTimeLimit);
    limitLayout->addWidget(limitLabel);

    QVBoxLayout *optionLayout = new QVBoxLayout();
    optionLayout->addWidget(MAllowDiagonal);
    optionLayout->addWidget(MDontCrossCorners);
    optionLayout->addLayout(weightLayout);
    optionLayout->addLayout(limitLayout);
    optionLayout->addWidget(MVisualizeRecursion);

    MOptionGroup->setLayout(optionLayout);
}

void IDAStarOptionWidget::setupHeuristicGroupUi()
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

void IDAStarOptionWidget::setupConnect()
{
    connect(MManhattan, SIGNAL(toggled(bool)), this, SLOT(manhattanChecked(bool)));
    connect(MEuclidean, SIGNAL(toggled(bool)), this, SLOT(euclideanChecked(bool)));
    connect(MOctile, SIGNAL(toggled(bool)), this, SLOT(octileChecked(bool)));
    connect(MChebyshev, SIGNAL(toggled(bool)), this, SLOT(chebyshevChecked(bool)));
    connect(MAllowDiagonal, SIGNAL(stateChanged(int)), this, SLOT(allowDiagonalStateChanged(int)));
    connect(MVisualizeRecursion, SIGNAL(stateChanged(int)), this, SLOT(visualizeRecursionStateChanged(int)));
    connect(MDontCrossCorners, SIGNAL(stateChanged(int)), this, SLOT(dontCrossCornersStateChanged(int)));
    connect(MWeight, SIGNAL(valueChanged(int)), this, SLOT(weightValueChanged(int)));
    connect(MTimeLimit, SIGNAL(valueChanged(int)), this, SLOT(timelimitValueChanged(int)));
}

void IDAStarOptionWidget::initOption()
{
    MOption->setOptionUsability(Option::AllowDiagonal);
    MOption->setOptionUsability(Option::VisualizeRecursion);
    MOption->setOptionUsability(Option::DontCrossCorners);
    MOption->setOptionUsability(Option::Weight);
}

void IDAStarOptionWidget::allowDiagonalStateChanged(int state)
{
    switch(state){
        case 0: MOption->setOptionValue(Option::AllowDiagonal, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: MOption->setOptionValue(Option::AllowDiagonal, Option::SELECTED); break;
    }
}

void IDAStarOptionWidget::visualizeRecursionStateChanged(int state)
{
    switch(state){
        case 0: MOption->setOptionValue(Option::VisualizeRecursion , Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: MOption->setOptionValue(Option::VisualizeRecursion, Option::SELECTED); break;
    }
}

void IDAStarOptionWidget::dontCrossCornersStateChanged(int state)
{
    switch(state){
        case 0: MOption->setOptionValue(Option::DontCrossCorners, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: MOption->setOptionValue(Option::DontCrossCorners, Option::SELECTED); break;
    }
}

void IDAStarOptionWidget::weightValueChanged(int weight)
{
    MOption->setOptionValue(Option::Weight, weight);
}

void IDAStarOptionWidget::timelimitValueChanged(int timeLimit)
{
    MOption->setOptionValue(Option::SecondsLimit, timeLimit);
}

void IDAStarOptionWidget::manhattanChecked(bool checked)
{
    if(checked){
        MHeuristic->setHeuristicType(Heuristic::Manhattan);
    }
}

void IDAStarOptionWidget::euclideanChecked(bool checked)
{
    if(checked){
        MHeuristic->setHeuristicType(Heuristic::Euclidean);
    }
}

void IDAStarOptionWidget::octileChecked(bool checked)
{
    if(checked){
        MHeuristic->setHeuristicType(Heuristic::Octile);
    }
}

void IDAStarOptionWidget::chebyshevChecked(bool checked)
{
    if(checked){
        MHeuristic->setHeuristicType(Heuristic::Chebyshev);
    }
}

