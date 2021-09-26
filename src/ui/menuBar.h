#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <QMenuBar>
#include "ui/menu/algoMenu.h"
#include "ui/menu/graphMenu.h"
#include "ui/menu/helpMenu.h"

static QVector<MenuCreateFunc> menuCreaters = {
    AlgoMenu::create,
    GraphMenu::create,
    HelpMenu::create
};

class MenuBar: public QMenuBar
{
    Q_OBJECT

public:
    MenuBar(QWidget *parent = nullptr);
    ~MenuBar();

protected:
    void initUi();
    void initConnect();

private:
    QVector<QMenu*> _menus;

signals:
    void menuActionIsTriggered(const QString &menuName, const QString &actionName);

public slots:
    void responseMenuAction(const QString &menuName, const QString &actionName);
};

#endif /* MENU_BAR_H */
