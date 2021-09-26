#ifndef BREADTH_FIRST_OPTION_WIDGET_H
#define BREADTH_FIRST_OPTION_WIDGET_H

#include "ui/core/optionWidget.h"
#include "core/heuristic.h"
#include "core/option.h"
#include <QGroupBox>
#include <QCheckBox>

class BreadthFirstOptionWidget: public OptionWidget
{
    Q_OBJECT

public:
    BreadthFirstOptionWidget(QString algoName = "", QWidget *parent = 0);
    ~BreadthFirstOptionWidget();
    Option *option();
    Heuristic *heuristic();

protected:
    void initUi();
    void initOptionGroupUi();
    void initConnect();
    void initOption();

protected:
    Option *_option;
    QGroupBox *_optionGroup;

private:
    QCheckBox *_allowDiagonal;
    QCheckBox *_biDirectional;
    QCheckBox *_dontCrossCorners;

public slots:
    void allowDiagonalStateChanged(int state);
    void biDirectionalStateChanged(int state);
    void dontCrossCornersStateChanged(int state);
};

#endif /* BREADTH_FIRST_OPTION_WIDGET_H */
