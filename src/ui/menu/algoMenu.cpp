#include "algoMenu.h"
#include "core/algorithm.h"

QMenu *AlgoMenu::create()
{
    return new AlgoMenu();
}

AlgoMenu::AlgoMenu(QWidget *parent): MenuWidget(parent)
{
    setTitle(tr("&Algorithm"));
    initUi();
    initConnect();
}

AlgoMenu::~AlgoMenu()
{

}


void AlgoMenu::initUi()
{
    QVector<QString>::const_iterator it = algoNameList.begin();
    for(; it != algoNameList.end(); ++it){
        addAction(*it);
    }
}

void AlgoMenu::triggerAction(QAction *action)
{
    QVector<QString>::const_iterator it = algoNameList.begin();
    for(; it != algoNameList.end(); ++it){
        if(action->text() == *it){
            emit menuActionIsTriggered("Algorithm", *it);
        }
    }
}
