#ifndef STATS_FRAME_H
#define STATS_FRAME_H

#include <QFrame>
#include "ui/core/statsWidget.h"

class StatsFrame: public QFrame
{
    Q_OBJECT

public:
    StatsFrame(QWidget *parent = nullptr);
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
