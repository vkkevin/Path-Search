#ifndef __HELP_MENU_H__
#define __HELP_MENU_H__

#include <QMenu>
#include <QString>

class HelpMenu: public QMenu
{
    Q_OBJECT

public:
    HelpMenu(QWidget *parent = 0);
    ~HelpMenu();

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

#endif /* __HELP_MENU_H__ */
