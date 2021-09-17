#include "ui/menus/graphMenu.h"

static const int MAX_ACTION_NUM = 1;
static const QString actionList[MAX_ACTION_NUM] = {
        "Grid Graph"
};

GraphMenu::GraphMenu(QWidget *parent): QMenu(parent)
{
    setTitle(tr("&Graph"));
    initActionList();
    initUi();
    initConnect();
}

GraphMenu::~GraphMenu()
{

}

void GraphMenu::initUi()
{
    for(int i = 0; i < _actionList.size(); i++){
        addAction(_actionList.at(i));
    }
}

void GraphMenu::initConnect()
{
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(triggerAction(QAction*)));
}

void GraphMenu::initActionList()
{
    for(int i = 0; i < MAX_ACTION_NUM; i++){
            _actionList.push_back(actionList[i]);
    }
}

void GraphMenu::triggerAction(QAction *action)
{
    for(int i = 0; i < MAX_ACTION_NUM; i++){
        if(action->text() == _actionList.at(i)){
            emit menuActionIsTriggered("Graph", action->text());
            return;
        }
    }
}
