#ifndef CONTROL_FRAME_H
#define CONTROL_FRAME_H

#include <QFrame>
#include "ui/core/controllerWidget.h"

class ControllerFrame: public QFrame
{
    Q_OBJECT

public:
    ControllerFrame(QWidget *parent = nullptr);
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
