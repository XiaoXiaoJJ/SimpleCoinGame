#ifndef CHOOSELEVELSCENCE_H
#define CHOOSELEVELSCENCE_H
#include"playscene.h"
#include <QMainWindow>

class ChooseLevelScence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScence(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent *event);

    playScene *pScene;

signals:
//点击返回按钮后 抛出自定义信号
    void chooseScenceBack();
};

#endif // CHOOSELEVELSCENCE_H
