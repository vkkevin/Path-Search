#include "ui/menus/graphMenu.h"

static const int MAX_ACTION_NUM = 1;
static const QString actionList[MAX_ACTION_NUM] = {
        "Grid Graph"
};

GraphMenu::GraphMenu(QWidget *parent): QMenu(parent)
{
    setTitle(tr("&Graph"));
    initActionList();
    setupUi();
    setupConnect();
}

GraphMenu::~GraphMenu()
{

}

void GraphMenu::setupUi()
{
    for(int i = 0; i < MActionList.size(); i++){
        addAction(MActionList.at(i));
    }
}

void GraphMenu::setupConnect()
{
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(triggerAction(QAction*)));
}

void GraphMenu::initActionList()
{
    for(int i = 0; i < MAX_ACTION_NUM; i++){
            MActionList.push_back(actionList[i]);
    }
}

void GraphMenu::triggerAction(QAction *action)
{
    for(int i = 0; i < MAX_ACTION_NUM; i++){
        if(action->text() == MActionList.at(i)){
            emit menuActionIsTriggered("Graph", action->text());
            return;
        }
    }
}
