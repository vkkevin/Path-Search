#ifndef __DIJKSTRA_OPTION_WIDGET_H__
#define __DIJKSTRA_OPTION_WIDGET_H__

#include "ui/optionWidget.h"
#include "core/heuristic.h"
#include "core/option.h"
#include <QGroupBox>
#include <QCheckBox>

class DijkstraOptionWidget: public OptionWidget
{
    Q_OBJECT

public:
    DijkstraOptionWidget(QString algoName = "", QWidget *parent = 0);
    ~DijkstraOptionWidget();
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

#endif /* __DIJKSTRA_OPTION_WIDGET_H__ */
