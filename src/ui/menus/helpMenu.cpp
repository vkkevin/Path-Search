#include "ui/menus/helpMenu.h"

static const int MAX_ACTION_NUM = 2;
static const QString actionList[MAX_ACTION_NUM] = {
        "About", "Help"
};

HelpMenu::HelpMenu(QWidget *parent): QMenu(parent)
{
    setTitle(tr("&Help"));
    initActionList();
    setupUi();
    setupConnect();
}

HelpMenu::~HelpMenu()
{

}

void HelpMenu::setupUi()
{
    for(int i = 0; i < MActionList.size(); i++){
        addAction(MActionList.at(i));
    }
}

void HelpMenu::setupConnect()
{
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(triggerAction(QAction*)));
}

void HelpMenu::initActionList()
{
    for(int i = 0; i < MAX_ACTION_NUM; i++){
            MActionList.push_back(actionList[i]);
    }
}

void HelpMenu::triggerAction(QAction *action)
{
    for(int i = 0; i < MAX_ACTION_NUM; i++){
        if(action->text() == MActionList.at(i)){
            emit menuActionIsTriggered("Help", action->text());
            return;
        }
    }
}
