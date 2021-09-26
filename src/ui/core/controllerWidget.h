#ifndef CONTROL_WIDGET_H
#define CONTROL_WIDGET_H

#include <QBoxLayout>
#include <QPushButton>

class ControllerWidget: public QWidget
{
    Q_OBJECT

public:
    ControllerWidget(QWidget *parent = 0);
    virtual ~ControllerWidget();
    void searchHasOver();

protected:
    void initUi();
    void initConnect();

protected:
    QPushButton *_runButton;
    QPushButton *_brackButton;
    QPushButton *_clearButton;

signals:
    void taskIsChecked(const QString &taskName);

public slots:
     void onRunButtonClicked();
     void onBreakButtonClicked();
     void onClearButtonClicked();
     void refurbishButton();

     void test(const QString &taskName);
};

#endif /* CONTROL_WIDGET_H */
