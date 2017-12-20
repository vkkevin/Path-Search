#include "ui/mainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
//    setGeometry(QRect(300, 80, 1230, 845));
    setFixedSize(QSize(1230, 845));
    setupUi();
    setupConnect();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUi()
{
    mMenuBar = new MenuBar(this);
    setMenuBar(mMenuBar);

    mCentralWidget = new CentralWidget(this);
    setCentralWidget(mCentralWidget);
}

void MainWindow::setupConnect()
{
    connect(mMenuBar, SIGNAL(menuActionIsTriggered(const QString &, const QString &)),
            mCentralWidget, SLOT(responseMenuAction(const QString &, const QString &)));
}
