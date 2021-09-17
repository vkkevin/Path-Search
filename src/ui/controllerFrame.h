#ifndef __CONTROL_FRAME_H__
#define __CONTROL_FRAME_H__

#include <QFrame>
#include "ui/controllerWidget.h"

class ControllerFrame: public QFrame
{
    Q_OBJECT

public:
    ControllerFrame(QWidget *parent = 0);
    ~ControllerFrame();
    void setControllerWidget(ControllerWidget *controller);
    void searchHasOver();

protected:
    void initUi();
    void initConnect();

private:
    ControllerWidget *_controller;

signals:
    void taskIsChecked(const QString &taskName);

public slots:
    void executeTask(const QString &taskName);
    void refurbishController();
};

#endif /* __CONTROL_FRAME_H__ */
