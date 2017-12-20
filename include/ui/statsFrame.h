#ifndef __STATS_FRAME_H__
#define __STATS_FRAME_H__

#include <QFrame>
#include "ui/statsWidget.h"

class StatsFrame: public QFrame
{
    Q_OBJECT

public:
    StatsFrame(QWidget *parent = 0);
    ~StatsFrame();
    void setStatsWidget(StatsWidget *stats);

protected:
    void setupUi();
    void setupConnect();

private:
    StatsWidget *MStats;

public slots:
    void updateStats(double time, double length);
};

#endif /* __STATS_FRAME_H__ */
