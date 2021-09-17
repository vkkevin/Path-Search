#ifndef __BEST_FIRST_OPTION_WIDGET_H__
#define __BEST_FIRST_OPTION_WIDGET_H__

#include "ui/optionWidget.h"
#include <QRadioButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>
class Option;
class Heuristic;

class BestFirstOptionWidget: public OptionWidget
{
    Q_OBJECT

public:
    BestFirstOptionWidget(QString algoName, QWidget *parent = 0);
    ~BestFirstOptionWidget();
    Option *option();
    Heuristic *heuristic();

protected:
    void initUi();
    void initOptionGroupUi();
    void initHeuristicGroupUi();
    void initConnect();
    void initOption();

protected:
    Option *_option;
    QGroupBox *_optionGroup;
    Heuristic *_heuristic;
    QGroupBox *_heuristicGroup;

private:
    QRadioButton *_manhattan;
    QRadioButton *_euclidean;
    QRadioButton *_octile;
    QRadioButton *_chebyshev;

    QCheckBox *_allowDiagonal;
    QCheckBox *_biDirectional;
    QCheckBox *_dontCrossCorners;

public slots:
    void allowDiagonalStateChanged(int state);
    void biDirectionalStateChanged(int state);
    void dontCrossCornersStateChanged(int state);
    void manhattanChecked(bool checked);
    void euclideanChecked(bool checked);
    void octileChecked(bool checked);
    void chebyshevChecked(bool checked);

};


#endif /* __BEST_FIRST_OPTION_WIDGET_H__ */
