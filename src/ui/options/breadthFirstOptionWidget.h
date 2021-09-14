#ifndef __BREADTH_FIRST_OPTION_WIDGET_H__
#define __BREADTH_FIRST_OPTION_WIDGET_H__

#include "ui/optionWidget.h"
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
    void setupUi();
    void setupOptionGroupUi();
    void setupConnect();
    void initOption();

protected:
    Option *MOption;
    QGroupBox *MOptionGroup;

private:
    QCheckBox *MAllowDiagonal;
    QCheckBox *MBiDirectional;
    QCheckBox *MDontCrossCorners;

public slots:
    void allowDiagonalStateChanged(int state);
    void biDirectionalStateChanged(int state);
    void dontCrossCornersStateChanged(int state);
};

#endif /* __BREADTH_FIRST_OPTION_WIDGET_H__ */
