#include "ui/optionFrame.h"
#include "ui/options/aStarOptionWidget.h"
#include "ui/options/iDAStarOptionWidget.h"
#include "ui/options/breadthFirstOptionWidget.h"
#include "ui/options/bestFirstOptionWidget.h"
#include "ui/options/dijkstraOptionWidget.h"
#include <QDebug>

OptionFrame::OptionFrame(QWidget *parent): QFrame(parent)
{
    _option = NULL;
    setMinimumHeight(625);
//    setMaximumWidth(360);
    setFixedWidth(360);
    setStyleSheet(tr("background-color: #E8E8E8;"));
    initUi();
    initConnect();
}

OptionFrame::~OptionFrame()
{

}

void OptionFrame::setOptionWidget(OptionWidget *option)
{
    if(_option != NULL && _option != option)
        delete _option;
    if(option == NULL)
        return;
    _option = option;
    _option->show();
    initConnect();
    executeOption(_option->option());
    executeHeuristic(_option->heuristic());
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
    _option->setAlgoName(optionName);
}

Option *OptionFrame::option()
{
    return _option->option();
}

Heuristic *OptionFrame::heuristic()
{
    return _option->heuristic();
}

void OptionFrame::initUi()
{
    setOptionWidget("Bearch First Search");
}


void OptionFrame::initConnect()
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
