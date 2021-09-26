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
    _menus.reserve(menuCreaters.size());
    QVector<MenuCreateFunc>::iterator it = menuCreaters.begin();
    for (; it != menuCreaters.end(); ++it) {
        QMenu *menu = (*it)();
        addMenu(menu);
        _menus.push_back(menu);
    }
}

void MenuBar::initConnect()
{
    QVector<QMenu*>::iterator it = _menus.begin();
    for (; it != _menus.end(); ++it) {
        connect(*it, SIGNAL(menuActionIsTriggered(const QString &, const QString &)),
                this, SLOT(responseMenuAction(const QString &,const QString &)));
    }
}

void MenuBar::responseMenuAction(const QString &menuName, const QString &actionName)
{
    if(menuName == "" || actionName == "")
        return;
    emit menuActionIsTriggered(menuName, actionName);
}
