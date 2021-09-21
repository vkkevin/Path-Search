#ifndef HELP_MENU_H
#define HELP_MENU_H

#include <QMenu>
#include <QString>

class HelpMenu: public QMenu
{
    Q_OBJECT

public:
    HelpMenu(QWidget *parent = nullptr);
    ~HelpMenu();

protected:
    void init();
    void initUi();
    void initConnect();

signals:
    void menuActionIsTriggered(const QString &menuName, const QString &actionName);

public slots:
    void triggerAction(QAction * action);

};

#endif /* HELP_MENU_H */
