#include "ui/controlFrame.h"
#include "ui/controlWidget.h"
#include <QDebug>

ControlFrame::ControlFrame(QWidget *parent): QFrame(parent)
{
    MControl = NULL;
//    setMinimumHeight(100);
    setFixedHeight(100);
    setFixedWidth(360);
    setStyleSheet(tr("background-color: #E8E8E8;"));
    setupUi();
    setupConnect();
}


ControlFrame::~ControlFrame()
{

}

void ControlFrame::setControlWidget(ControlWidget *control)
{
    if(MControl != NULL && MControl != control)
        delete MControl;
    if(control == NULL)
        return;
    MControl = control;
    setupConnect();
}

void ControlFrame::searchHasOver()
{
    MControl->searchHasOver();
}

void ControlFrame::setupUi()
{
    setControlWidget(new ControlWidget(this));
}


void ControlFrame::setupConnect()
{
    connect(MControl, SIGNAL(taskIsChecked(const QString &)), this, SLOT(executeTask(const QString &)), Qt::UniqueConnection);
}

void ControlFrame::executeTask(const QString &taskName)
{
    if(taskName != "")
        emit taskIsChecked(taskName);
}

void ControlFrame::refurbishControl()
{
    MControl->refurbishButton();
}
