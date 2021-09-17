#include "ui/controllerWidget.h"
#include <QDebug>

ControllerWidget::ControllerWidget(QWidget *parent): QWidget(parent)
{
    setGeometry(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));
    initUi();
    initConnect();
}

ControllerWidget::~ControllerWidget()
{

}

void ControllerWidget::searchHasOver()
{
    _brackButton->setText(tr("Clear\nPath"));
}

void ControllerWidget::refurbishButton()
{
    _runButton->setText(tr("Start\nSearch"));
    _brackButton->setText(tr("Pause\nSearch"));
    _brackButton->setEnabled(false);
    _clearButton->setText(tr("Clear\nWalls"));
}

void ControllerWidget::initUi()
{
    _runButton = new QPushButton(this);
    _runButton->setText(tr("Start\nSearch"));
    _runButton->setMinimumSize(110, 80);
    _runButton->setStyleSheet(tr("background-color: white;"));
    _runButton->setCursor(QCursor(Qt::PointingHandCursor));

    _brackButton = new QPushButton(this);
    _brackButton->setText(tr("Pause\nSearch"));
    _brackButton->setMinimumSize(110, 80);
    _brackButton->setStyleSheet(tr("background-color: white;"));
    _brackButton->setEnabled(false);
    _brackButton->setCursor(QCursor(Qt::PointingHandCursor));

    _clearButton = new QPushButton(this);
    _clearButton->setText(tr("Clear\nWalls"));
    _clearButton->setMinimumSize(110, 80);
    _clearButton->setStyleSheet(tr("background-color: white;"));
    _clearButton->setCursor(QCursor(Qt::PointingHandCursor));

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(_runButton);
    mainLayout->addStretch();
    mainLayout->addWidget(_brackButton);
    mainLayout->addStretch();
    mainLayout->addWidget(_clearButton);
    setLayout(mainLayout);
}

void ControllerWidget::initConnect()
{
    connect(_runButton, SIGNAL(clicked()), this, SLOT(onRunButtonClicked()));
    connect(_brackButton, SIGNAL(clicked()), this, SLOT(onBreakButtonClicked()));
    connect(_clearButton, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));
//    connect(this, SIGNAL(taskIsChecked(const QString &)), this, SLOT(test(const QString &)));
}

void ControllerWidget::onRunButtonClicked()
{
    if(_runButton->text() == "Start\nSearch"){
        _runButton->setText("Restart\nSearch");
        _brackButton->setEnabled(true);
        emit taskIsChecked("startSearch");
    }else if(_runButton->text() == "Restart\nSearch"){
        _brackButton->setText("Pause\nSearch");
        emit taskIsChecked("restartSearch");
    }else if(_runButton->text() == "Resume\nSearch"){
        _runButton->setText("Restart\nSearch");
        _brackButton->setText("Pause\nSearch");
        emit taskIsChecked("resumeSearch");
    }
}

void ControllerWidget::onBreakButtonClicked()
{
    if(_brackButton->text() == "Pause\nSearch"){
        _brackButton->setText("Cancel\nSearch");
        _runButton->setText("Resume\nSearch");
        emit taskIsChecked("pauseSearch");
    }else if(_brackButton->text() == "Cancel\nSearch"){
        _brackButton->setText("Pause\nSearch");
        _brackButton->setEnabled(false);
        _runButton->setText("Start\nSearch");
        emit taskIsChecked("cancelSearch");
    }else if(_brackButton->text() == "Clear\nPath"){
        _brackButton->setText("Pause\nSearch");
        _brackButton->setEnabled(false);
        _runButton->setText("Start\nSearch");
        emit taskIsChecked("clearPath");
    }
}

void ControllerWidget::onClearButtonClicked()
{
    if(_clearButton->text() == "Clear\nWalls"){
        _brackButton->setText("Pause\nSearch");
        _brackButton->setEnabled(false);
        _runButton->setText("Start\nSearch");
        emit taskIsChecked("clearWalls");
    }
}

void ControllerWidget::test(const QString &taskName)
{
    qDebug() << "test control " << taskName;
}
