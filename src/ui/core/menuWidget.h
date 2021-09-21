#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    static MenuWidget* create();

public:
    explicit MenuWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MENUWIDGET_H
