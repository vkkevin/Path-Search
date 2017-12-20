#include "ui/optionFrame.h"
#include "ui/options/aStarOptionWidget.h"
#include "ui/options/iDAStarOptionWidget.h"
#include "ui/options/breadthFirstOptionWidget.h"
#include "ui/options/bestFirstOptionWidget.h"
#include "ui/options/dijkstraOptionWidget.h"
#include <QDebug>

OptionFrame::OptionFrame(QWidget *parent): QFrame(parent)
{
    MOption = NULL;
    setMinimumHeight(625);
//    setMaximumWidth(360);
    setFixedWidth(360);
    setStyleSheet(tr("background-color: #E8E8E8;"));
    setupUi();
    setupConnect();
}

OptionFrame::~OptionFrame()
{

}

void OptionFrame::setOptionWidget(OptionWidget *option)
{
    if(MOption != NULL && MOption != option)
        delete MOption;
    if(option == NULL)
        return;
    MOption = option;
    MOption->show();
    setupConnect();
    executeOption(MOption->option());
    executeHeuristic(MOption->heuristic());
}

/* optionName <==> algoName */
void OptionFrame::setOptionWidget(const QString &optionName)
{
    if(optionName == "A*"){
        setOptionWidget(new AStarOptionWidget(optionName, this));
    }else if(optionName == "IDA*"){
        setOptionWidget(new IDAStarOptionWidget(optionName, this));
    }else if(optionName == "Bearch First Search"){
        setOptionWidget(new BreadthFirstOptionWidget(optionName, this));
    }else if(optionName == "Best First Search"){
        setOptionWidget(new BestFirstOptionWidget(optionName, this));
    }else if(optionName == "Dijkstra"){
        setOptionWidget(new DijkstraOptionWidget(optionName, this));
    }
    MOption->setAlgoName(optionName);
}

Option *OptionFrame::option()
{
    return MOption->option();
}

Heuristic *OptionFrame::heuristic()
{
    return MOption->heuristic();
}

void OptionFrame::setupUi()
{
    setOptionWidget("Bearch First Search");
}


void OptionFrame::setupConnect()
{

}

void OptionFrame::executeOption(Option *option)
{
    emit optionChanged(option);
}

void OptionFrame::executeHeuristic(Heuristic *heuristic)
{
    emit heuristicChanged(heuristic);
}
