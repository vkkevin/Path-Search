#include "ui/controllerFrame.h"
#include "ui/controllerWidget.h"
#include <QDebug>

ControllerFrame::ControllerFrame(QWidget *parent): QFrame(parent)
{
    _controller = NULL;
//    setMinimumHeight(100);
    setFixedSize(360, 100);
    setStyleSheet(tr("background-color: #E8E8E8;"));
    initUi();
    initConnect();
}


ControllerFrame::~ControllerFrame()
{

}

void ControllerFrame::setControllerWidget(ControllerWidget *controller)
{
    if(_controller != NULL && _controller != controller)
        delete _controller;
    if(controller == NULL)
        return;
    _controller = controller;
    initConnect();
}

void ControllerFrame::searchHasOver()
{
    _controller->searchHasOver();
}

void ControllerFrame::initUi()
{
    ControllerWidget* controller = new ControllerWidget(this);
    controller->setGeometry(QRect(0, 0, width(), height()));
    setControllerWidget(controller);
}


void ControllerFrame::initConnect()
{
    connect(_controller, SIGNAL(taskIsChecked(const QString &)), this, SLOT(executeTask(const QString &)), Qt::UniqueConnection);
}

void ControllerFrame::executeTask(const QString &taskName)
{
    if(taskName != "")
        emit taskIsChecked(taskName);
}

void ControllerFrame::refurbishController()
{
    _controller->refurbishButton();
}
