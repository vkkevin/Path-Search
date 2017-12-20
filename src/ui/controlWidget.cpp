#include "ui/controlWidget.h"
#include <QDebug>

ControlWidget::ControlWidget(QWidget *parent): QWidget(parent)
{
    setGeometry(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));
    setupUi();
    setupConnect();
}

ControlWidget::~ControlWidget()
{

}

void ControlWidget::searchHasOver()
{
    brackButton->setText(tr("Clear\nPath"));
}

void ControlWidget::refurbishButton()
{
    runButton->setText(tr("Start\nSearch"));
    brackButton->setText(tr("Pause\nSearch"));
    brackButton->setEnabled(false);
    clearButton->setText(tr("Clear\nWalls"));
}

void ControlWidget::setupUi()
{
    runButton = new QPushButton(this);
    runButton->setText(tr("Start\nSearch"));
    runButton->setMinimumSize(110, 80);
    runButton->setStyleSheet(tr("background-color: white;"));
    runButton->setCursor(QCursor(Qt::PointingHandCursor));

    brackButton = new QPushButton(this);
    brackButton->setText(tr("Pause\nSearch"));
    brackButton->setMinimumSize(110, 80);
    brackButton->setStyleSheet(tr("background-color: white;"));
    brackButton->setEnabled(false);
    brackButton->setCursor(QCursor(Qt::PointingHandCursor));

    clearButton = new QPushButton(this);
    clearButton->setText(tr("Clear\nWalls"));
    clearButton->setMinimumSize(110, 80);
    clearButton->setStyleSheet(tr("background-color: white;"));
    clearButton->setCursor(QCursor(Qt::PointingHandCursor));

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(runButton);
    mainLayout->addStretch();
    mainLayout->addWidget(brackButton);
    mainLayout->addStretch();
    mainLayout->addWidget(clearButton);
    setLayout(mainLayout);
}

void ControlWidget::setupConnect()
{
    connect(runButton, SIGNAL(clicked()), this, SLOT(onRunButtonClicked()));
    connect(brackButton, SIGNAL(clicked()), this, SLOT(onBreakButtonClicked()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));
//    connect(this, SIGNAL(taskIsChecked(const QString &)), this, SLOT(test(const QString &)));
}

void ControlWidget::onRunButtonClicked()
{
    if(runButton->text() == "Start\nSearch"){
        runButton->setText("Restart\nSearch");
        brackButton->setEnabled(true);
        emit taskIsChecked("startSearch");
    }else if(runButton->text() == "Restart\nSearch"){
        brackButton->setText("Pause\nSearch");
        emit taskIsChecked("restartSearch");
    }else if(runButton->text() == "Resume\nSearch"){
        runButton->setText("Restart\nSearch");
        brackButton->setText("Pause\nSearch");
        emit taskIsChecked("resumeSearch");
    }
}

void ControlWidget::onBreakButtonClicked()
{
    if(brackButton->text() == "Pause\nSearch"){
        brackButton->setText("Cancel\nSearch");
        runButton->setText("Resume\nSearch");
        emit taskIsChecked("pauseSearch");
    }else if(brackButton->text() == "Cancel\nSearch"){
        brackButton->setText("Pause\nSearch");
        brackButton->setEnabled(false);
        runButton->setText("Start\nSearch");
        emit taskIsChecked("cancelSearch");
    }else if(brackButton->text() == "Clear\nPath"){
        brackButton->setText("Pause\nSearch");
        brackButton->setEnabled(false);
        runButton->setText("Start\nSearch");
        emit taskIsChecked("clearPath");
    }
}

void ControlWidget::onClearButtonClicked()
{
    if(clearButton->text() == "Clear\nWalls"){
        brackButton->setText("Pause\nSearch");
        brackButton->setEnabled(false);
        runButton->setText("Start\nSearch");
        emit taskIsChecked("clearWalls");
    }
}

void ControlWidget::test(const QString &taskName)
{
    qDebug() << "test control " << taskName;
}
