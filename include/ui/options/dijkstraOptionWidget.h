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

#endif /* __DIJKSTRA_OPTION_WIDGET_H__ */
