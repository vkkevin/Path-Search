#ifndef __CONTROL_WIDGET_H__
#define __CONTROL_WIDGET_H__

#include <QBoxLayout>
#include <QPushButton>

class ControlWidget: public QWidget
{
    Q_OBJECT

public:
    ControlWidget(QWidget *parent = 0);
    virtual ~ControlWidget();
    void searchHasOver();

protected:
    void setupUi();
    void setupConnect();

protected:
    QPushButton *runButton;
    QPushButton *brackButton;
    QPushButton *clearButton;

signals:
    void taskIsChecked(const QString &taskName);

public slots:
     void onRunButtonClicked();
     void onBreakButtonClicked();
     void onClearButtonClicked();
     void refurbishButton();

     void test(const QString &taskName);
};

#endif /* __CONTROL_WIDGET_H__ */
