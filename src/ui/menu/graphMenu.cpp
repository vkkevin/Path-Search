#include "graphMenu.h"
#include "core/commander.h"

QMenu *GraphMenu::create()
{
    return new GraphMenu();
}

GraphMenu::GraphMenu(QWidget *parent): MenuWidget(parent)
{
    setTitle(tr("&Graph"));
    initUi();
    initConnect();
}

GraphMenu::~GraphMenu()
{

}

void GraphMenu::initUi()
{
    addAction("Grid Graph");
}

void GraphMenu::triggerAction(QAction *action)
{
#if 1
    Commander::instance()->changeGraph(action->text());
#else
    emit menuActionIsTriggered("Graph", action->text());
#endif
}
