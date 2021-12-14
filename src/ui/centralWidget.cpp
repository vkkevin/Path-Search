#include "centralWidget.h"
#include "core/commander.h"
#include "ui/graphFrame.h"
#include "ui/optionFrame.h"
#include "ui/controllerFrame.h"
#include "ui/statsFrame.h"
#include <QBoxLayout>
#include <QMessageBox>
#include <QString>
#include <QMetaType>
#include <QDebug>


CentralWidget::CentralWidget(QWidget *parent): QWidget(parent)
{
    qRegisterMetaType< QVector<Node *> >("QVector<Node *>");
    init();
}

CentralWidget::~CentralWidget()
{
    // Finder 无父组件， 析够时需释放资源
    delete _finder;
}

void CentralWidget::init()
{
    //setGeometry(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));
    initUi();
    initConnect();

    /* 初始化算法与地图（缺省算法与地图） */
    responseMenuAction("Algorithm", "A*");
    responseMenuAction("Graph", "Grid Graph");
}

void CentralWidget::initUi()
{
    Commander::instance()->setParent(this);
    _graphFrame = new GraphFrame(this);
    _optionFrame = new OptionFrame(this);
    _controlFrame = new ControllerFrame(this);
    _controlFrame->setFixedSize(360, 100);
    _statsFrame = new StatsFrame(this);
    _statsFrame->setFixedSize(1210, 60);
    _finder = new Finder(this);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(_optionFrame);
    rightLayout->addWidget(_controlFrame);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(_graphFrame);
    topLayout->addLayout(rightLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(_statsFrame);
    mainLayout->setSpacing(5);

    setLayout(mainLayout);
}

void CentralWidget::initConnect()
{
    connect(_controlFrame, SIGNAL(taskIsChecked(const QString &)), this, SLOT(executeTask(const QString &)));
    connect(this, SIGNAL(taskIsChecked(const QString &)), _graphFrame, SLOT(executeTask(const QString &)));
    connect(_optionFrame, SIGNAL(optionChanged(Option *)), this, SLOT(executeOption(Option*)));
    connect(_optionFrame, SIGNAL(heuristicChanged(Heuristic *)), this, SLOT(executeHeuristic(Heuristic*)));
    connect(_graphFrame, SIGNAL(graphChanged(Graph *)), this, SLOT(executeGraph(Graph*)));
    connect(_finder, SIGNAL(hasTasks(const QString &)), this, SLOT(executeFinderTask(const QString &)));
    connect(_finder, SIGNAL(statsUpdate(double,double)), _statsFrame, SLOT(updateStats(double, double)));
    connect(_finder, SIGNAL(showPath(QVector<Node*>)), _graphFrame, SLOT(drawPath(QVector<Node*>)));
}

void CentralWidget::responseMenuAction(const QString menuName, const QString actionName)
{
    if(menuName == "Graph"){
        _finder->terminateSearchingTask();
        executeTask("cancelSearch");
        ((GraphFrame *)_graphFrame)->setGraphWidget(actionName);
    }else if(menuName == "Algorithm"){
        _finder->terminateSearchingTask();
        executeTask("cancelSearch");
        ((ControllerFrame *)_controlFrame)->refurbishController();
        ((OptionFrame *)_optionFrame)->setOptionWidget(actionName);
        // 给 Finder 发送信号， 改变其算法
        _finder->setAlgorithm(actionName);
    }
}

void CentralWidget::executeTask(const QString &taskName)
{
    if(taskName == "startSearch" || taskName == "restartSearch"){
        emit taskIsChecked("clearPath");
        emit taskIsChecked("searchRun");
        _finder->findPath();
    }else if(taskName == "clearWalls" || taskName == "cancelSearch"){
        emit taskIsChecked("searchOver");
        _finder->terminateSearchingTask();
        emit taskIsChecked("clearPath");
        if(taskName == "cancelSearch")
            return;
        emit taskIsChecked("clearWalls");
    }else if(taskName == "clearPath"){
        _finder->terminateSearchingTask();
        emit taskIsChecked(taskName);
    }else if(taskName == "pauseSearch"){
        _finder->pauseFinder();
    }else if(taskName == "resumeSearch"){
        _finder->resumeFinder();
    }else{
        emit taskIsChecked(taskName);
    }
}
void CentralWidget::executeOption(Option *option)
{
    if(option == nullptr)
        return;
    _finder->setOption(option);
}

void CentralWidget::executeHeuristic(Heuristic *heuristic)
{
    if(heuristic == nullptr)
        return;
    _finder->setHeuristic(heuristic);
}

void CentralWidget::executeGraph(Graph *graph)
{
    if(graph == nullptr)
        return;
    _finder->setGraph(graph);
}

void CentralWidget::executeFinderTask(const QString &taskName)
{
    if(taskName == "searchOver")
        ((ControllerFrame *)_controlFrame)->searchHasOver();
    emit taskIsChecked(taskName);
}
