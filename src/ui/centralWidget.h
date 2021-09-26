#ifndef CENTRAL_WIDGET_H
#define CENTRAL_WIDGET_H

#include <QWidget>
#include <QFrame>
#include "core/finder.h"

class CentralWidget: public QWidget
{
    Q_OBJECT

public:
    CentralWidget(QWidget *parent = nullptr);
    ~CentralWidget();

protected:
    void init();
    void initUi();
    void initConnect();

private:
    QFrame *_graphFrame;
    QFrame *_optionFrame;
    QFrame *_controlFrame;
    QFrame *_statsFrame;
    Finder *_finder;

signals:
    void taskIsChecked(const QString &taskName);

public slots:
    void responseMenuAction(const QString menuName, const QString actionName);
    void executeTask(const QString &taskName);
    void executeOption(Option *option);
    void executeHeuristic(Heuristic *heuristic);
    void executeGraph(Graph *graph);
    void executeFinderTask(const QString &taskName);
};

#endif /* CENTRAL_WIDGET_H */
