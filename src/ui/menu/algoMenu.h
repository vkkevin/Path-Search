#ifndef ALGO_MENU_H
#define ALGO_MENU_H

#include "ui/core/menuWidget.h"

class AlgoMenu: public MenuWidget
{
     Q_OBJECT

public:
    static QMenu* create();

public:
    AlgoMenu(QWidget *parent = nullptr);
    ~AlgoMenu();

protected:
    void initUi();

private:
    QVector<QString> _actionList;
    void initActionList();

signals:
    void menuActionIsTriggered(const QString &menuName, const QString &actionName);

public slots:
    void triggerAction(QAction * action);

};

#endif /* ALGO_MENU_H */
