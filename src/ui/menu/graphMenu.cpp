#include "graphMenu.h"

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
    emit menuActionIsTriggered("Graph", action->text());
}
