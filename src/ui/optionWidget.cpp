#include "ui/optionWidget.h"

OptionWidget::OptionWidget(QString algoName, QWidget *parent): QWidget(parent)
{
    MAlgoName = new QLabel(algoName);
    MAlgoName->setMaximumHeight(30);
}

OptionWidget::~OptionWidget()
{

}

void OptionWidget::setAlgoName(QString algoName)
{
    MAlgoName->setText(algoName);
}

QString OptionWidget::algoName()
{
    return MAlgoName->text();
}
