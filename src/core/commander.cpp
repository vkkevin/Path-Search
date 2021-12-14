#include "commander.h"
#include "core/finder.h"

#include <QMutex>
#include <QMutexLocker>

QMutex Commander::_commander_mtx;
Commander Commander::*_commander = nullptr;

Commander *Commander::instance()
{
    QMutexLocker lock(&_commander_mtx);
    if (_commander == nullptr) {
        _commander = new Commander();
    }
    return _commander;
}

Commander::Commander(QObject *parent): QObject(parent)
{

}

void Commander::changeGraph(const QString &graphName)
{
    _finder->terminateSearchingTask();
    executeTask("cancelSearch");
    ((GraphFrame *)_graphFrame)->setGraphWidget(graphName);
}
