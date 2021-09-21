#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QWidget>
#include "ui/menuBar.h"
#include "ui/centralWidget.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void init();
    void initUi();
    void initConnect();

private:
    MenuBar *_menuBar;
    CentralWidget *_centralWidget;
};

#endif /* MAIN_WINDOW_H */
