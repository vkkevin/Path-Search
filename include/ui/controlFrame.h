#ifndef __CONTROL_FRAME_H__
#define __CONTROL_FRAME_H__

#include <QFrame>
#include "ui/controlWidget.h"

class ControlFrame: public QFrame
{
    Q_OBJECT

public:
    ControlFrame(QWidget *parent = 0);
    ~ControlFrame();
    void setControlWidget(ControlWidget *control);
    void searchHasOver();

protected:
    void setupUi();
    void setupConnect();

private:
    ControlWidget *MControl;

signals:
    void taskIsChecked(const QString &taskName);

public slots:
    void executeTask(const QString &taskName);
    void refurbishControl();
};

#endif /* __CONTROL_FRAME_H__ */
