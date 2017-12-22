#include "ui/centralWidget.h"
#include "ui/graphFrame.h"
#include "ui/optionFrame.h"
#include "ui/controlFrame.h"
#include "ui/statsFrame.h"
#include <QBoxLayout>
#include <QMessageBox>
#include <QString>
#include <QMetaType>
#include <QDebug>

const char *helpMessage[][2] = {
    {"About", "<p>版本: v1.0</p>"
                     "<p>原创: <a href='http://qiao.github.io/PathFinding.js/visual/'>PathFinding</a>（灵感源）</p>"
                     "<p>特别感谢: <a href='https://github.com/qiao'>Xueqiao (Joe) Xu</a></p>"
                     "<p>项目地址: <a href='https://github.com/ckkcoder'>github</a></p>"
                     ""},
    {"Help", "<h2>Instructions</h2>"
     "<p>Click within the <font color='grey'>white</font> grid and drag your mouse to draw obstacles. </p>"
     "<p>Drag the <font color='green'>green</font> node to set the start position. </p>"
     "<p>Drag the <font color='red'>red</font> node to set the end position. </p>"
     "<p>Choose an algorithm from the top menu. </p>"
     "<p>Click \"Start Search\" in the lower-right corner to start the animation.</p>"}
};

CentralWidget::CentralWidget(QWidget *parent): QWidget(parent)
{
    qRegisterMetaType< QVector<Node *> >("QVector<Node *>");
    setGeometry(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));
    setupUi();
    setupConnect();

    /* 初始化算法与地图（缺省算法与地图） */
    responseMenuAction("Algorithm", "A*");
    responseMenuAction("Graph", "Grid Graph");
}

CentralWidget::~CentralWidget()
{
    // Finder 无父组件， 析够时需释放资源
    delete MFinder;
}

void CentralWidget::setupUi()
{
    MGraphFrame = new GraphFrame(this);
    MOptionFrame = new OptionFrame(this);
    MControlFrame = new ControlFrame(this);
    MStatsFrame = new StatsFrame(this);
    MFinder = new Finder(this);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(MOptionFrame);
    rightLayout->addWidget(MControlFrame);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(MGraphFrame);
    topLayout->addLayout(rightLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(MStatsFrame);
    mainLayout->setSpacing(5);

    setLayout(mainLayout);
}

void CentralWidget::setupConnect()
{
    connect(MControlFrame, SIGNAL(taskIsChecked(const QString &)), this, SLOT(executeTask(const QString &)));
    connect(this, SIGNAL(taskIsChecked(const QString &)), MGraphFrame, SLOT(executeTask(const QString &)));
    connect(MOptionFrame, SIGNAL(optionChanged(Option *)), this, SLOT(executeOption(Option*)));
    connect(MOptionFrame, SIGNAL(heuristicChanged(Heuristic *)), this, SLOT(executeHeuristic(Heuristic*)));
    connect(MGraphFrame, SIGNAL(graphChanged(Graph *)), this, SLOT(executeGraph(Graph*)));
    connect(MFinder, SIGNAL(hasTasks(const QString &)), this, SLOT(executeFinderTask(const QString &)));
    connect(MFinder, SIGNAL(statsUpdate(double,double)), MStatsFrame, SLOT(updateStats(double, double)));
    connect(MFinder, SIGNAL(showPath(QVector<Node*>)), MGraphFrame, SLOT(drawPath(QVector<Node*>)));
}

void CentralWidget::responseMenuAction(const QString menuName, const QString actionName)
{
    if(menuName == "Graph"){
        MFinder->terminateSearchingTask();
        executeTask("cancelSearch");
        ((GraphFrame *)MGraphFrame)->setGraphWidget(actionName);
    }else if(menuName == "Algorithm"){
        MFinder->terminateSearchingTask();
        executeTask("cancelSearch");
        ((ControlFrame *)MControlFrame)->refurbishControl();
        ((OptionFrame *)MOptionFrame)->setOptionWidget(actionName);
        // 给 Finder 发送信号， 改变其算法
        MFinder->setAlgorithm(actionName);
    }else if(menuName == "Help"){
        if(actionName == "About"){
            QMessageBox::about(this, QObject::trUtf8(helpMessage[0][0]), QObject::trUtf8(helpMessage[0][1]));
        }else if(actionName == "Help"){
            QMessageBox::about(this, helpMessage[1][0], helpMessage[1][1]);
        }
    }
}

void CentralWidget::executeTask(const QString &taskName)
{
    if(taskName == "startSearch" || taskName == "restartSearch"){
        emit taskIsChecked("clearPath");
        emit taskIsChecked("searchRun");
        MFinder->findPath();
    }else if(taskName == "clearWalls" || taskName == "cancelSearch"){
        emit taskIsChecked("searchOver");
        MFinder->terminateSearchingTask();
        emit taskIsChecked("clearPath");
        if(taskName == "cancelSearch")
            return;
        emit taskIsChecked("clearWalls");
    }else if(taskName == "clearPath"){
        MFinder->terminateSearchingTask();
        emit taskIsChecked(taskName);
    }else if(taskName == "pauseSearch"){
        MFinder->pauseFinder();
    }else if(taskName == "resumeSearch"){
        MFinder->resumeFinder();
    }else{
        emit taskIsChecked(taskName);
    }
}
void CentralWidget::executeOption(Option *option)
{
    if(option == NULL)
        return;
    MFinder->setOption(option);
}

void CentralWidget::executeHeuristic(Heuristic *heuristic)
{
    if(heuristic == NULL)
        return;
    MFinder->setHeuristic(heuristic);
}

void CentralWidget::executeGraph(Graph *graph)
{
    if(graph == NULL)
        return;
    MFinder->setGraph(graph);
}

void CentralWidget::executeFinderTask(const QString &taskName)
{
    if(taskName == "searchOver")
        ((ControlFrame *)MControlFrame)->searchHasOver();
    emit taskIsChecked(taskName);
}
