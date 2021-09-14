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
    void setupUi();
    void setupOptionGroupUi();
    void setupHeuristicGroupUi();
    void setupConnect();
    void initOption();

protected:
    Option *MOption;
    QGroupBox *MOptionGroup;
    Heuristic *MHeuristic;
    QGroupBox *MHeuristicGroup;

private:
    QRadioButton *MManhattan;
    QRadioButton *MEuclidean;
    QRadioButton *MOctile;
    QRadioButton *MChebyshev;

    QCheckBox *MAllowDiagonal;
    QCheckBox *MBiDirectional;
    QCheckBox *MDontCrossCorners;
    QSpinBox *MWeight;

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
