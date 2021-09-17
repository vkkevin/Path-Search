#include "ui/statsFrame.h"
#include "ui/statsWidget.h"

StatsFrame::StatsFrame(QWidget *parent): QFrame(parent)
{
    _stats = NULL;
    setStyleSheet(tr("background-color: #EBEBEB;"));
    initUi();
    initConnect();
}

StatsFrame::~StatsFrame()
{

}

void StatsFrame::setStatsWidget(StatsWidget *stats)
{
    if(_stats != NULL && _stats != stats)
        delete _stats;
    if(stats == NULL)
        return;
    _stats = stats;
    initConnect();
}

void StatsFrame::initUi()
{
   setStatsWidget(new StatsWidget(this));
}

void StatsFrame::initConnect()
{

}

void StatsFrame::updateStats(double time, double length)
{
    _stats->showResultInfo(time, length);
}
