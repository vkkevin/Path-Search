#include "ui/menus/algoMenu.h"
#include "core/algorithm.h"

AlgoMenu::AlgoMenu(QWidget *parent): QMenu(parent)
{
    setTitle(tr("&Algorithm"));
    initActionList();
    initUi();
    initConnect();
}

AlgoMenu::~AlgoMenu()
{

}


void AlgoMenu::initUi()
{
    for(int i = 0; i < _actionList.size(); i++){
        addAction(_actionList.at(i));
    }
}

void AlgoMenu::initConnect()
{
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(triggerAction(QAction*)));
}

void AlgoMenu::initActionList()
{
    for(int i = 0; i < MAX_ALGO_NUM; i++){
            _actionList.push_back(algoNameList[i]);
    }
}

void AlgoMenu::triggerAction(QAction *action)
{
    for(int i = 0; i < MAX_ALGO_NUM; i++){
        if(action->text() == _actionList.at(i)){
            emit menuActionIsTriggered("Algorithm", action->text());
        }
    }
}
