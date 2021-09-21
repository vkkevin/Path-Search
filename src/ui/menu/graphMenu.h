#ifndef __GRAPH_MENU_H__
#define __GRAPH_MENU_H__

#include <QMenu>

class GraphMenu: public QMenu
{
    Q_OBJECT

public:
    GraphMenu(QWidget *parent = nullptr);
    ~GraphMenu();

protected:
    void initUi();
    void initConnect();

signals:
    void menuActionIsTriggered(const QString &menuName, const QString &actionName);

public slots:
    void triggerAction(QAction * action);

};

#endif /* __GRAPH_MENU_H__ */
