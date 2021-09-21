#include "menuBar.h"
#include "ui/menu/graphMenu.h"
#include "ui/menu/algoMenu.h"
#include "ui/menu/helpMenu.h"
#include <QDebug>

MenuBar::MenuBar(QWidget *parent): QMenuBar(parent)
{
    initUi();
    initConnect();
}

MenuBar::~MenuBar()
{

}

void MenuBar::initUi()
{
    _graphMenu = new GraphMenu();
    addMenu(_graphMenu);

    _algoMenu = new AlgoMenu();
    addMenu(_algoMenu);

    _helpMenu = new HelpMenu();
    addMenu(_helpMenu);
}

void MenuBar::initConnect()
{
    connect(_graphMenu, SIGNAL(menuActionIsTriggered(const QString &, const QString &)),
            this, SLOT(responseMenuAction(const QString &,const QString &)));
    connect(_algoMenu, SIGNAL(menuActionIsTriggered(const QString &, const QString &)),
            this, SLOT(responseMenuAction(const QString &,const QString &)));
    connect(_helpMenu, SIGNAL(menuActionIsTriggered(const QString &, const QString &)),
            this, SLOT(responseMenuAction(const QString &,const QString &)));
}

void MenuBar::responseMenuAction(const QString &menuName, const QString &actionName)
{
    if(menuName == "" || actionName == "")
        return;
    emit menuActionIsTriggered(menuName, actionName);
}
