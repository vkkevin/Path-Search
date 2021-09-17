#ifndef __OPTION_FRAME_H__
#define __OPTION_FRAME_H__

#include <QFrame>
#include <QLabel>
#include "core/option.h"
#include "ui/optionWidget.h"

class OptionFrame: public QFrame
{
    Q_OBJECT

public:
    OptionFrame(QWidget *parent = 0);
    ~OptionFrame();
    void setOptionWidget(OptionWidget *option);
    void setOptionWidget(const QString &optionName);
    Option *option();
    Heuristic *heuristic();

protected:
    void initUi();
    void initConnect();

private:
    OptionWidget *_option;

signals:
    void optionChanged(Option *option);
    void heuristicChanged(Heuristic *heuristic);

public slots:
    void executeOption(Option *option);
    void executeHeuristic(Heuristic *heuristic);
};

#endif /* __OPTION_FRAME_H__ */
