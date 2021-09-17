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
    void initUi();
    void initConnect();

private:
    StatsWidget *_stats;

public slots:
    void updateStats(double time, double length);
};

#endif /* __STATS_FRAME_H__ */
