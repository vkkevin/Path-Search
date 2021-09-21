#ifndef __IDA_STAR_OPTION_WIDGET_H__
#define __IDA_STAR_OPTION_WIDGET_H__

#include "ui/optionWidget.h"
#include <QRadioButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>
class Option;
class Heuristic;

class IDAStarOptionWidget: public OptionWidget
{
    Q_OBJECT

public:
    IDAStarOptionWidget(QString algoName, QWidget *parent = 0);
    ~IDAStarOptionWidget();
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
    QRadioButton *MManhattan;
    QRadioButton *MEuclidean;
    QRadioButton *MOctile;
    QRadioButton *MChebyshev;

    QCheckBox *_allowDiagonal;
    QCheckBox *_visualizeRecursion;
    QCheckBox *_dontCrossCorners;
    QSpinBox *_weight;
    QSpinBox *_timeLimit;

public slots:
    void allowDiagonalStateChanged(int state);
    void visualizeRecursionStateChanged(int state);
    void dontCrossCornersStateChanged(int state);
    void weightValueChanged(int weight);
    void timelimitValueChanged(int timeLimit);
    void manhattanChecked(bool checked);
    void euclideanChecked(bool checked);
    void octileChecked(bool checked);
    void chebyshevChecked(bool checked);

};

#endif /* __IDA_STAR_OPTION_WIDGET_H__ */
