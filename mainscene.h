#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include"chooselevelscence.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();


    //维护选择关卡的指针
    ChooseLevelScence *chooseScence;

private:
    Ui::MainScene *ui;
    //利用绘图时间  绘制背景
    void paintEvent(QPaintEvent *event);
};
#endif // MAINSCENE_H
