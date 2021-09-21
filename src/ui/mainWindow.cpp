#include "ui/mainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    setGeometry(QRect(300, 80, 1230, 845));
    setWindowTitle("Path Search");
//    setFixedSize(QSize(1230, 845));
    initUi();
    initConnect();
}

void MainWindow::initUi()
{
    _menuBar = new MenuBar(this);
    setMenuBar(_menuBar);

    _centralWidget = new CentralWidget(this);
    _centralWidget->setGeometry(QRect(0, 0, width(), height()));
    setCentralWidget(_centralWidget);
}

void MainWindow::initConnect()
{
    connect(_menuBar, SIGNAL(menuActionIsTriggered(const QString &, const QString &)),
            _centralWidget, SLOT(responseMenuAction(const QString &, const QString &)));
}
