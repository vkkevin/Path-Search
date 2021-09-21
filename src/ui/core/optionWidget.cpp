#include "optionWidget.h"

OptionWidget::OptionWidget(QString algoName, QWidget *parent): QWidget(parent)
{
    _algoName = new QLabel(algoName);
    _algoName->setMaximumHeight(30);
}

OptionWidget::~OptionWidget()
{

}

void OptionWidget::setAlgoName(QString algoName)
{
    _algoName->setText(algoName);
}

QString OptionWidget::algoName()
{
    return _algoName->text();
}
