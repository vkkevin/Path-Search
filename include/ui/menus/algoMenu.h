#ifndef __ALGO_MENU_H__
#define __ALGO_MENU_H__

#include <QMenu>

class AlgoMenu: public QMenu
{
     Q_OBJECT

public:
    AlgoMenu(QWidget *parent = 0);
    ~AlgoMenu();

protected:
    void setupUi();
    void setupConnect();

private:
    QVector<QString> MActionList;
    void initActionList();

signals:
    void menuActionIsTriggered(const QString &menuName, const QString &actionName);

public slots:
    void triggerAction(QAction * action);

};

#endif /* __ALGO_MENU_H__ */
