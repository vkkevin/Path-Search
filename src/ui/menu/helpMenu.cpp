#include "ui/menus/helpMenu.h"

HelpMenu::HelpMenu(QWidget *parent): QMenu(parent)
{
    setTitle(tr("&Help"));
    init();
}

HelpMenu::~HelpMenu()
{

}

void HelpMenu::init()
{
    initUi();
    initConnect();
}

void HelpMenu::initUi()
{
    addAction("About");
    addAction("Help");
}

void HelpMenu::initConnect()
{
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(triggerAction(QAction*)));
}

void HelpMenu::triggerAction(QAction *action)
{
    emit menuActionIsTriggered("Help", action->text());
}
