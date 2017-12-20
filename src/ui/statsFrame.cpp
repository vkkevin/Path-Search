#include "ui/statsFrame.h"
#include "ui/statsWidget.h"

StatsFrame::StatsFrame(QWidget *parent): QFrame(parent)
{
    MStats = NULL;
    setStyleSheet(tr("background-color: #EBEBEB;"));
    setFixedSize(1210, 60);
    setupUi();
    setupConnect();
}

StatsFrame::~StatsFrame()
{

}

void StatsFrame::setStatsWidget(StatsWidget *stats)
{
    if(MStats != NULL && MStats != stats)
        delete MStats;
    if(stats == NULL)
        return;
    MStats = stats;
    setupConnect();
}

void StatsFrame::setupUi()
{
   setStatsWidget(new StatsWidget(this));
}

void StatsFrame::setupConnect()
{

}

void StatsFrame::updateStats(double time, double length)
{
    MStats->showResultInfo(time, length);
}
