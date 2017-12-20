#include "ui/menuBar.h"
#include "ui/menus/graphMenu.h"
#include "ui/menus/algoMenu.h"
#include "ui/menus/helpMenu.h"
#include <QDebug>

MenuBar::MenuBar(QWidget *parent): QMenuBar(parent)
{
    setupUi();
    setupConnect();
}

MenuBar::~MenuBar()
{

}

void MenuBar::setupUi()
{
    MGraphMenu = new GraphMenu();
    addMenu(MGraphMenu);

    MAlgoMenu = new AlgoMenu();
    addMenu(MAlgoMenu);

    MHelpMenu = new HelpMenu();
    addMenu(MHelpMenu);
}

void MenuBar::setupConnect()
{
    connect(MGraphMenu, SIGNAL(menuActionIsTriggered(const QString &, const QString &)),
            this, SLOT(responseMenuAction(const QString &,const QString &)));
    connect(MAlgoMenu, SIGNAL(menuActionIsTriggered(const QString &, const QString &)),
            this, SLOT(responseMenuAction(const QString &,const QString &)));
    connect(MHelpMenu, SIGNAL(menuActionIsTriggered(const QString &, const QString &)),
            this, SLOT(responseMenuAction(const QString &,const QString &)));
}

void MenuBar::responseMenuAction(const QString &menuName, const QString &actionName)
{
    if(menuName == "" || actionName == "")
        return;
    emit menuActionIsTriggered(menuName, actionName);
}
