#include "ui/options/aStarOptionWidget.h"
#include "core/option.h"
#include "core/heuristic.h"
#include <QBoxLayout>
#include <QDebug>

AStarOptionWidget::AStarOptionWidget(QString algoName, QWidget *parent)
    : OptionWidget(algoName, parent)
{
    setGeometry(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));
    _option = new Option();
    initOption();
    _heuristic = new Heuristic();
    initUi();
    initConnect();
    _manhattan->setChecked(true);
    _weight->setValue(1);
}

AStarOptionWidget::~AStarOptionWidget()
{
    delete  _heuristic;
    delete  _option;
}

Option *AStarOptionWidget::option()
{
    return _option;
}

Heuristic *AStarOptionWidget::heuristic()
{
    return _heuristic;
}

void AStarOptionWidget::initUi()
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

void AStarOptionWidget::initOptionGroupUi()
{
    _allowDiagonal = new QCheckBox(tr("Allow Diagonal"), _optionGroup);
    _allowDiagonal->setCursor(QCursor(Qt::PointingHandCursor));
    _biDirectional = new QCheckBox(tr("Bi-Directional"), _optionGroup);
    _biDirectional->setCursor(QCursor(Qt::PointingHandCursor));
    _dontCrossCorners = new QCheckBox(tr("Don't Cross Corners"), _optionGroup);
    _dontCrossCorners->setCursor(QCursor(Qt::PointingHandCursor));
    _weight = new QSpinBox(_optionGroup);
    _weight->setCursor(QCursor(Qt::PointingHandCursor));
    _weight->setMaximum(99999);
    QLabel *weightLabel = new QLabel("Weight", _optionGroup);
    weightLabel->setCursor(QCursor(Qt::PointingHandCursor));
    weightLabel->setBuddy(_weight);

    QHBoxLayout *weightLayout = new QHBoxLayout();
    weightLayout->addWidget(_weight);
    weightLayout->addWidget(weightLabel);

    QVBoxLayout *optionLayout = new QVBoxLayout();
    optionLayout->addWidget(_allowDiagonal);
    optionLayout->addWidget(_biDirectional);
    optionLayout->addWidget(_dontCrossCorners);
    optionLayout->addLayout(weightLayout);

    _optionGroup->setLayout(optionLayout);
}

void AStarOptionWidget::initHeuristicGroupUi()
{
    _manhattan = new QRadioButton(tr("manhattan"), _heuristicGroup);
    _manhattan->setCursor(QCursor(Qt::PointingHandCursor));
    _euclidean = new QRadioButton(tr("euclidean"), _heuristicGroup);
    _euclidean->setCursor(QCursor(Qt::PointingHandCursor));
    _octile = new QRadioButton(tr("octile"), _heuristicGroup);
    _octile->setCursor(QCursor(Qt::PointingHandCursor));
    _chebyshev = new QRadioButton(tr("chebyshev"), _heuristicGroup);
    _chebyshev->setCursor(QCursor(Qt::PointingHandCursor));

    QVBoxLayout *heuristicLayout = new QVBoxLayout();
    heuristicLayout->addWidget(_manhattan);
    heuristicLayout->addWidget(_euclidean);
    heuristicLayout->addWidget(_octile);
    heuristicLayout->addWidget(_chebyshev);
    _heuristicGroup->setLayout(heuristicLayout);
}

void AStarOptionWidget::initConnect()
{
    connect(_manhattan, SIGNAL(toggled(bool)), this, SLOT(manhattanChecked(bool)));
    connect(_euclidean, SIGNAL(toggled(bool)), this, SLOT(euclideanChecked(bool)));
    connect(_octile, SIGNAL(toggled(bool)), this, SLOT(octileChecked(bool)));
    connect(_chebyshev, SIGNAL(toggled(bool)), this, SLOT(chebyshevChecked(bool)));
    connect(_allowDiagonal, SIGNAL(stateChanged(int)), this, SLOT(allowDiagonalStateChanged(int)));
    connect(_biDirectional, SIGNAL(stateChanged(int)), this, SLOT(biDirectionalStateChanged(int)));
    connect(_dontCrossCorners, SIGNAL(stateChanged(int)), this, SLOT(dontCrossCornersStateChanged(int)));
    connect(_weight, SIGNAL(valueChanged(int)), this, SLOT(weightValueChanged(int)));
}

void AStarOptionWidget::initOption()
{
    _option->setOptionUsability(Option::AllowDiagonal);
    _option->setOptionUsability(Option::BiDirectional);
    _option->setOptionUsability(Option::DontCrossCorners);
    _option->setOptionUsability(Option::Weight);
}

void AStarOptionWidget::allowDiagonalStateChanged(int state)
{
    switch(state){
        case 0: _option->setOptionValue(Option::AllowDiagonal, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: _option->setOptionValue(Option::AllowDiagonal, Option::SELECTED); break;
    }
}

void AStarOptionWidget::biDirectionalStateChanged(int state)
{
    switch(state){
        case 0: _option->setOptionValue(Option::BiDirectional , Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: _option->setOptionValue(Option::BiDirectional, Option::SELECTED); break;
    }
}

void AStarOptionWidget::dontCrossCornersStateChanged(int state)
{
    switch(state){
        case 0: _option->setOptionValue(Option::DontCrossCorners, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: _option->setOptionValue(Option::DontCrossCorners, Option::SELECTED); break;
    }
}

void AStarOptionWidget::weightValueChanged(int weight)
{
    _option->setOptionValue(Option::Weight, weight);
}

void AStarOptionWidget::manhattanChecked(bool checked)
{
    if(checked){
        _heuristic->setHeuristicType(Heuristic::Manhattan);
    }
}

void AStarOptionWidget::euclideanChecked(bool checked)
{
    if(checked){
        _heuristic->setHeuristicType(Heuristic::Euclidean);
    }
}

void AStarOptionWidget::octileChecked(bool checked)
{
    if(checked){
        _heuristic->setHeuristicType(Heuristic::Octile);
    }
}

void AStarOptionWidget::chebyshevChecked(bool checked)
{
    if(checked){
        _heuristic->setHeuristicType(Heuristic::Chebyshev);
    }
}

