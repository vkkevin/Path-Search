#include "ui/menus/algoMenu.h"
#include "core/algorithm.h"

AlgoMenu::AlgoMenu(QWidget *parent): QMenu(parent)
{
    setTitle(tr("&Algorithm"));
    initActionList();
    setupUi();
    setupConnect();
}

AlgoMenu::~AlgoMenu()
{

}


void AlgoMenu::setupUi()
{
    for(int i = 0; i < MActionList.size(); i++){
        addAction(MActionList.at(i));
    }
}

void AlgoMenu::setupConnect()
{
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(triggerAction(QAction*)));
}

void AlgoMenu::initActionList()
{
    for(int i = 0; i < MAX_ALGO_NUM; i++){
            MActionList.push_back(algoNameList[i]);
    }
}

void AlgoMenu::triggerAction(QAction *action)
{
    for(int i = 0; i < MAX_ALGO_NUM; i++){
        if(action->text() == MActionList.at(i)){
            emit menuActionIsTriggered("Algorithm", action->text());
        }
    }
}
