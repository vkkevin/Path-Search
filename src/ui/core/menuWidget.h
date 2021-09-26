#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QMenu>

typedef QMenu* (*MenuCreateFunc)();

class MenuWidget : public QMenu
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = nullptr);

protected:
    virtual void initConnect();

signals:

public slots:
    virtual void triggerAction(QAction *action) = 0;
};

#endif // MENUWIDGET_H
