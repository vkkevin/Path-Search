#ifndef HELP_MENU_H
#define HELP_MENU_H

#include "ui/core/menuWidget.h"
#include <QString>

class HelpMenu: public MenuWidget
{
    Q_OBJECT

public:
    static QMenu* create();

public:
    HelpMenu(QWidget *parent = nullptr);
    ~HelpMenu();

protected:
    void init();
    void initUi();

signals:
    void menuActionIsTriggered(const QString &menuName, const QString &actionName);

public slots:
    void triggerAction(QAction * action);

};

#endif /* HELP_MENU_H */
