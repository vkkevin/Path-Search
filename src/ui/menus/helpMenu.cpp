#include "ui/menus/helpMenu.h"

static const int MAX_ACTION_NUM = 2;
static const QString actionList[MAX_ACTION_NUM] = {
        "About", "Help"
};

HelpMenu::HelpMenu(QWidget *parent): QMenu(parent)
{
    setTitle(tr("&Help"));
    initActionList();
    initUi();
    initConnect();
}

HelpMenu::~HelpMenu()
{

}

void HelpMenu::initUi()
{
    for(int i = 0; i < _actionList.size(); i++){
        addAction(_actionList.at(i));
    }
}

void HelpMenu::initConnect()
{
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(triggerAction(QAction*)));
}

void HelpMenu::initActionList()
{
    for(int i = 0; i < MAX_ACTION_NUM; i++){
            _actionList.push_back(actionList[i]);
    }
}

void HelpMenu::triggerAction(QAction *action)
{
    for(int i = 0; i < MAX_ACTION_NUM; i++){
        if(action->text() == _actionList.at(i)){
            emit menuActionIsTriggered("Help", action->text());
            return;
        }
    }
}
