#include "helpMenu.h"
#include <QMessageBox>
#include <QMap>
#include <QString>

QMap<QString, QString> helpMessage = {
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


QMenu *HelpMenu::create()
{
    return new HelpMenu();
}

HelpMenu::HelpMenu(QWidget *parent): MenuWidget(parent)
{
    setTitle(tr("&Help"));
    init();
}

HelpMenu::~HelpMenu()
{

}

void HelpMenu::init()
{
    initUi();
    initConnect();
}

void HelpMenu::initUi()
{
    QMap<QString, QString>::const_iterator it = helpMessage.begin();
    for (; it != helpMessage.end(); ++it) {
        addAction(it.key());
    }
}

void HelpMenu::triggerAction(QAction *action)
{
#if 1
    QMap<QString, QString>::const_iterator it = helpMessage.find(action->text());
    if (it != helpMessage.end()) {
        QMessageBox::about(this, it.key(), it.value());
    }
#else
    emit menuActionIsTriggered("Help", action->text());
#endif
}
