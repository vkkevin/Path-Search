#ifndef ALGO_MENU_H
#define ALGO_MENU_H

#include <QMenu>

class AlgoMenu: public QMenu
{
     Q_OBJECT

public:
    AlgoMenu(QWidget *parent = nullptr);
    ~AlgoMenu();

protected:
    void initUi();
    void initConnect();

private:
    QVector<QString> _actionList;
    void initActionList();

signals:
    void menuActionIsTriggered(const QString &menuName, const QString &actionName);

public slots:
    void triggerAction(QAction * action);

};

#endif /* ALGO_MENU_H */
