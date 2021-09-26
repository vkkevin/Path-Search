#include "menuWidget.h"

MenuWidget::MenuWidget(QWidget *parent) : QMenu(parent)
{

}

void MenuWidget::initConnect()
{
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(triggerAction(QAction*)));
}
