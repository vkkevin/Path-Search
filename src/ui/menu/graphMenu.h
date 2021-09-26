#ifndef GRAPH_MENU_H
#define GRAPH_MENU_H

#include "ui/core/menuWidget.h"

class GraphMenu: public MenuWidget
{
    Q_OBJECT

public:
    static QMenu* create();

public:
    GraphMenu(QWidget *parent = nullptr);
    ~GraphMenu();

protected:
    void initUi();

signals:
    void menuActionIsTriggered(const QString &menuName, const QString &actionName);

public slots:
    void triggerAction(QAction * action);

};

#endif /* GRAPH_MENU_H */
