#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>
#include <QMutex>
#include "core/finder.h"

class Commander: public QObject
{
    Q_OBJECT
public:
    static Commander* instance();
    Commander(Commander& right) = delete;
    Commander& operator= (Commander& right) = delete;

public:
    void bindFinder(Finder* finder);

    // change 开头的方法表示改变其对应组件
    void changeGraph(const QString &graphName);
    void changeAlgorithm();

    // refresh 开头的方法表示刷新对应 ui
    void refreshGraph();

    // update 表示更新数据
    void updateStats();

private:
    Commander(QObject *parent = nullptr);

private:
    static QMutex _commander_mtx;
    static Commander *_commander;
};

#endif // COMMANDER_H
