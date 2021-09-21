#ifndef __A_STAR_OPTION_WIDGET_H__
#define __A_STAR_OPTION_WIDGET_H__

#include "ui/optionWidget.h"
#include <QRadioButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>
class Option;
class Heuristic;

class AStarOptionWidget: public OptionWidget
{
    Q_OBJECT

public:
    AStarOptionWidget(QString algoName, QWidget *parent = 0);
    ~AStarOptionWidget();
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
    QSpinBox *_weight;

public slots:
    void allowDiagonalStateChanged(int state);
    void biDirectionalStateChanged(int state);
    void dontCrossCornersStateChanged(int state);
    void weightValueChanged(int weight);
    void manhattanChecked(bool checked);
    void euclideanChecked(bool checked);
    void octileChecked(bool checked);
    void chebyshevChecked(bool checked);

};

#endif /* __A_STAR_OPTION_WIDGET_H__ */
