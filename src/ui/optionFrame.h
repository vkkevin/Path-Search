#ifndef OPTION_FRAME_H
#define OPTION_FRAME_H

#include <QFrame>
#include <QLabel>
#include "core/option.h"
#include "ui/core/optionWidget.h"

class OptionFrame: public QFrame
{
    Q_OBJECT

public:
    OptionFrame(QWidget *parent = nullptr);
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

#endif /* OPTION_FRAME_H */
