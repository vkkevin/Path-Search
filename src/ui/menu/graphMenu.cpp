#include "ui/menus/graphMenu.h"

GraphMenu::GraphMenu(QWidget *parent): QMenu(parent)
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

void GraphMenu::initConnect()
{
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(triggerAction(QAction*)));
}

void GraphMenu::triggerAction(QAction *action)
{
    emit menuActionIsTriggered("Graph", action->text());
}
