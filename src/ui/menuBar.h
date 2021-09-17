#ifndef __MENU_BAR_H__
#define __MENU_BAR_H__

#include <QMenuBar>
class MenuBar: public QMenuBar
{
    Q_OBJECT

public:
    MenuBar(QWidget *parent = 0);
    ~MenuBar();

protected:
    void initUi();
    void initConnect();

private:
    QMenu *_graphMenu;
    QMenu *_algoMenu;
    QMenu *_helpMenu;

signals:
    void menuActionIsTriggered(const QString &menuName, const QString &actionName);

public slots:
    void responseMenuAction(const QString &menuName, const QString &actionName);
};

#endif /* __MENU_BAR_H__ */
