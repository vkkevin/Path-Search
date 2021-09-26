#ifndef OPTION_WIDGET_H
#define OPTION_WIDGET_H

#include <QWidget>
#include <QLabel>
#include "core/option.h"
#include "core/heuristic.h"

class OptionWidget: public QWidget
{
    Q_OBJECT

public:
    OptionWidget(QString algoName = "",QWidget *parent = 0);
    ~OptionWidget();
    virtual void setAlgoName(QString algoName);
    virtual QString algoName();
    virtual Option *option() = 0;
    virtual Heuristic *heuristic() = 0;

    /* 该语句可删除 选项组件不在该层改变 */
//signals:
//    void optionChanged(Option *option);
//    void heuristicChanged(Heuristic *heuristic);

protected:
    QLabel *_algoName;

};


#endif /* OPTION_WIDGET_H */
