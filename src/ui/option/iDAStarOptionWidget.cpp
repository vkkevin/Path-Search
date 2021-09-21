#include "ui/options/iDAStarOptionWidget.h"
#include "core/option.h"
#include "core/heuristic.h"
#include <QBoxLayout>
#include <QDebug>

IDAStarOptionWidget::IDAStarOptionWidget(QString algoName, QWidget *parent)
    : OptionWidget(algoName, parent)
{
    setGeometry(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));
    _option = new Option();
    initOption();
    _heuristic = new Heuristic();
    initUi();
    initConnect();
    _weight->setValue(1);
    _timeLimit->setValue(10);
}

IDAStarOptionWidget::~IDAStarOptionWidget()
{
    delete  _heuristic;
    delete  _option;
}

Option *IDAStarOptionWidget::option()
{
    return _option;
}

Heuristic *IDAStarOptionWidget::heuristic()
{
    return _heuristic;
}

void IDAStarOptionWidget::initUi()
{
    _heuristicGroup = new QGroupBox(tr("Heuristic"), this);
    _heuristicGroup->setMaximumHeight(200);
    _optionGroup = new QGroupBox(tr("Options"), this);
    initHeuristicGroupUi();
    initOptionGroupUi();

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(_algoName);
    mainLayout->addWidget(_heuristicGroup);
    mainLayout->addWidget(_optionGroup);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void IDAStarOptionWidget::initOptionGroupUi()
{
    _allowDiagonal = new QCheckBox(tr("Allow Diagonal"), _optionGroup);
    _allowDiagonal->setCursor(QCursor(Qt::PointingHandCursor));
    _dontCrossCorners = new QCheckBox(tr("Don't Cross Corners"), _optionGroup);
    _dontCrossCorners->setCursor(QCursor(Qt::PointingHandCursor));
    _visualizeRecursion = new QCheckBox(tr("Visualize recursion"), _optionGroup);
    _visualizeRecursion->setCursor(QCursor(Qt::PointingHandCursor));

    _weight = new QSpinBox(_optionGroup);
    _weight->setCursor(QCursor(Qt::PointingHandCursor));
    _weight->setMaximum(99999);
    QLabel *weightLabel = new QLabel("Weight", _optionGroup);
    weightLabel->setCursor(QCursor(Qt::PointingHandCursor));
    weightLabel->setBuddy(_weight);
    QHBoxLayout *weightLayout = new QHBoxLayout();
    weightLayout->addWidget(_weight);
    weightLayout->addWidget(weightLabel);

    _timeLimit = new QSpinBox(_optionGroup);
    _timeLimit->setCursor(QCursor(Qt::PointingHandCursor));
//    MTimeLimit->setMaximum(99);
    QLabel *limitLabel = new QLabel("Seconds limit", _optionGroup);
    limitLabel->setCursor(QCursor(Qt::PointingHandCursor));
    limitLabel->setBuddy(_timeLimit);
    QHBoxLayout *limitLayout = new QHBoxLayout();
    limitLayout->addWidget(_timeLimit);
    limitLayout->addWidget(limitLabel);

    QVBoxLayout *optionLayout = new QVBoxLayout();
    optionLayout->addWidget(_allowDiagonal);
    optionLayout->addWidget(_dontCrossCorners);
    optionLayout->addLayout(weightLayout);
    optionLayout->addLayout(limitLayout);
    optionLayout->addWidget(_visualizeRecursion);

    _optionGroup->setLayout(optionLayout);
}

void IDAStarOptionWidget::initHeuristicGroupUi()
{
    MManhattan = new QRadioButton(tr("manhattan"), _heuristicGroup);
    MManhattan->setCursor(QCursor(Qt::PointingHandCursor));
    MManhattan->setChecked(true);
    MEuclidean = new QRadioButton(tr("euclidean"), _heuristicGroup);
    MEuclidean->setCursor(QCursor(Qt::PointingHandCursor));
    MOctile = new QRadioButton(tr("octile"), _heuristicGroup);
    MOctile->setCursor(QCursor(Qt::PointingHandCursor));
    MChebyshev = new QRadioButton(tr("chebyshev"), _heuristicGroup);
    MChebyshev->setCursor(QCursor(Qt::PointingHandCursor));

    QVBoxLayout *heuristicLayout = new QVBoxLayout();
    heuristicLayout->addWidget(MManhattan);
    heuristicLayout->addWidget(MEuclidean);
    heuristicLayout->addWidget(MOctile);
    heuristicLayout->addWidget(MChebyshev);
    _heuristicGroup->setLayout(heuristicLayout);
}

void IDAStarOptionWidget::initConnect()
{
    connect(MManhattan, SIGNAL(toggled(bool)), this, SLOT(manhattanChecked(bool)));
    connect(MEuclidean, SIGNAL(toggled(bool)), this, SLOT(euclideanChecked(bool)));
    connect(MOctile, SIGNAL(toggled(bool)), this, SLOT(octileChecked(bool)));
    connect(MChebyshev, SIGNAL(toggled(bool)), this, SLOT(chebyshevChecked(bool)));
    connect(_allowDiagonal, SIGNAL(stateChanged(int)), this, SLOT(allowDiagonalStateChanged(int)));
    connect(_visualizeRecursion, SIGNAL(stateChanged(int)), this, SLOT(visualizeRecursionStateChanged(int)));
    connect(_dontCrossCorners, SIGNAL(stateChanged(int)), this, SLOT(dontCrossCornersStateChanged(int)));
    connect(_weight, SIGNAL(valueChanged(int)), this, SLOT(weightValueChanged(int)));
    connect(_timeLimit, SIGNAL(valueChanged(int)), this, SLOT(timelimitValueChanged(int)));
}

void IDAStarOptionWidget::initOption()
{
    _option->setOptionUsability(Option::AllowDiagonal);
    _option->setOptionUsability(Option::VisualizeRecursion);
    _option->setOptionUsability(Option::DontCrossCorners);
    _option->setOptionUsability(Option::Weight);
}

void IDAStarOptionWidget::allowDiagonalStateChanged(int state)
{
    switch(state){
        case 0: _option->setOptionValue(Option::AllowDiagonal, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: _option->setOptionValue(Option::AllowDiagonal, Option::SELECTED); break;
    }
}

void IDAStarOptionWidget::visualizeRecursionStateChanged(int state)
{
    switch(state){
        case 0: _option->setOptionValue(Option::VisualizeRecursion , Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: _option->setOptionValue(Option::VisualizeRecursion, Option::SELECTED); break;
    }
}

void IDAStarOptionWidget::dontCrossCornersStateChanged(int state)
{
    switch(state){
        case 0: _option->setOptionValue(Option::DontCrossCorners, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: _option->setOptionValue(Option::DontCrossCorners, Option::SELECTED); break;
    }
}

void IDAStarOptionWidget::weightValueChanged(int weight)
{
    _option->setOptionValue(Option::Weight, weight);
}

void IDAStarOptionWidget::timelimitValueChanged(int timeLimit)
{
    _option->setOptionValue(Option::SecondsLimit, timeLimit);
}

void IDAStarOptionWidget::manhattanChecked(bool checked)
{
    if(checked){
        _heuristic->setHeuristicType(Heuristic::Manhattan);
    }
}

void IDAStarOptionWidget::euclideanChecked(bool checked)
{
    if(checked){
        _heuristic->setHeuristicType(Heuristic::Euclidean);
    }
}

void IDAStarOptionWidget::octileChecked(bool checked)
{
    if(checked){
        _heuristic->setHeuristicType(Heuristic::Octile);
    }
}

void IDAStarOptionWidget::chebyshevChecked(bool checked)
{
    if(checked){
        _heuristic->setHeuristicType(Heuristic::Chebyshev);
    }
}

