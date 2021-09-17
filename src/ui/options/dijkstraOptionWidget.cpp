#include "ui/options/dijkstraOptionWidget.h"
#include <QBoxLayout>
#include <QDebug>

DijkstraOptionWidget::DijkstraOptionWidget(QString algoName, QWidget *parent)
    : OptionWidget(algoName, parent)
{
    setGeometry(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));

    _option = new Option();
    initOption();
    initUi();
    initConnect();
}

DijkstraOptionWidget::~DijkstraOptionWidget()
{
    delete _option;
}

Option *DijkstraOptionWidget::option()
{
    return _option;
}

Heuristic *DijkstraOptionWidget::heuristic()
{
    return NULL;
}

void DijkstraOptionWidget::initUi()
{
    _optionGroup = new QGroupBox(tr("Options"), this);
    _optionGroup->setMinimumHeight(200);

    QVBoxLayout *optionLayout = new QVBoxLayout();
    optionLayout->addWidget(_algoName);
    optionLayout->addWidget(_optionGroup);
    optionLayout->addStretch();
    setLayout(optionLayout);
    initOptionGroupUi();
}

void DijkstraOptionWidget::initOptionGroupUi()
{
    _allowDiagonal = new QCheckBox(tr("Allow Diagonal"), _optionGroup);
    _allowDiagonal->setCursor(QCursor(Qt::PointingHandCursor));
    _biDirectional = new QCheckBox(tr("Bi-Directional"), _optionGroup);
    _biDirectional->setCursor(QCursor(Qt::PointingHandCursor));
    _dontCrossCorners = new QCheckBox(tr("Don't Cross Corners"), _optionGroup);
    _dontCrossCorners->setCursor(QCursor(Qt::PointingHandCursor));

    QVBoxLayout *optionLayout = new QVBoxLayout();
    optionLayout->addWidget(_allowDiagonal);
    optionLayout->addWidget(_biDirectional);
    optionLayout->addWidget(_dontCrossCorners);
    _optionGroup->setLayout(optionLayout);
}

void DijkstraOptionWidget::initConnect()
{
    connect(_allowDiagonal, SIGNAL(stateChanged(int)), this, SLOT(allowDiagonalStateChanged(int)));
    connect(_biDirectional, SIGNAL(stateChanged(int)), this, SLOT(biDirectionalStateChanged(int)));
    connect(_dontCrossCorners, SIGNAL(stateChanged(int)), this, SLOT(dontCrossCornersStateChanged(int)));
}

void DijkstraOptionWidget::initOption()
{
    _option->setOptionUsability(Option::AllowDiagonal);
    _option->setOptionUsability(Option::BiDirectional);
    _option->setOptionUsability(Option::DontCrossCorners);
}

void DijkstraOptionWidget::allowDiagonalStateChanged(int state)
{
    switch(state){
        case 0: _option->setOptionValue(Option::AllowDiagonal, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: _option->setOptionValue(Option::AllowDiagonal, Option::SELECTED); break;
    }
}

void DijkstraOptionWidget::biDirectionalStateChanged(int state)
{
    switch(state){
        case 0: _option->setOptionValue(Option::BiDirectional , Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: _option->setOptionValue(Option::BiDirectional, Option::SELECTED); break;
    }
}

void DijkstraOptionWidget::dontCrossCornersStateChanged(int state)
{
    switch(state){
        case 0: _option->setOptionValue(Option::DontCrossCorners, Option::UNSELECTED); break;
        case 1: qDebug() << state;break;
        case 2: _option->setOptionValue(Option::DontCrossCorners, Option::SELECTED); break;
    }
}
