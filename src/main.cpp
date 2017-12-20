#include <QApplication>
#include "ui/mainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("path.ico"));
    MainWindow w;
    w.setWindowTitle("Find Path");
    w.show();

    return app.exec();
}
