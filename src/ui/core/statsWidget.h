#ifndef STATS_WIDGET_H
#define STATS_WIDGET_H

#include <QWidget>
#include <QLabel>

/* 该类暂时无须虚拟化， 所有算法的结果状态均一致 */
class StatsWidget: public QWidget
{
    Q_OBJECT

public:
    StatsWidget(QWidget *parent = 0);
    ~StatsWidget();
    void showResultInfo(double time, double length);

protected:
    void initUi();

private:
    QLabel *_pathLabel;
    QLabel *_timeLabel;
};

#endif /* STATS_WIDGET_H */
