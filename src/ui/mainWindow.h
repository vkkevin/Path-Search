#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <QMainWindow>
#include <QMenuBar>
#include <QWidget>
#include "ui/menuBar.h"
#include "ui/centralWidget.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void setupUi();
    void setupConnect();

private:
    MenuBar *mMenuBar;
    CentralWidget *mCentralWidget;
};

#endif /* __MAIN_WINDOW_H__ */
