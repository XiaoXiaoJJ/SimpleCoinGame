#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<mycoin.h>
class playScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit playScene(QWidget *parent = nullptr);
    playScene(int levelIndex);
    //具体选择的关卡号
    int levelIndex;
    //重写绘图事件
    void  paintEvent(QPaintEvent *);
    //记录当前关卡的二维数组
    int gameArray[4][4];
    MyCoin * coinBtn[4][4]; //金币按钮数组
     bool isWin = true; //是否胜利
signals:
    //点击返回按钮后 抛出自定义信号
    void chooseScenceBack();
};

#endif // PLAYSCENE_H
