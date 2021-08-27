#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include<QTimer>
#include"mypushbutton.h"
#include<QSound>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //主场景基本配置
    this->setWindowTitle("翻金币小游戏");

    this->setFixedSize(320,588);

    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //点击开始中的退出  实现关闭游戏
    connect(ui->actionquit,&QAction::triggered,[=](){
       this->close();
    });

    //开始按钮音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);

    //创建出选择关卡的场景
    chooseScence = new ChooseLevelScence;

    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
        startBtn->setParent(this);
        startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //监听返回关卡场景中的返回按钮自定义信号
        connect(chooseScence,&ChooseLevelScence::chooseScenceBack,[=](){
           chooseScence->hide();
           this->setGeometry(chooseScence->geometry());
           this->show();
        });
        connect(startBtn,&MyPushButton::clicked,[=](){

            startSound->play(); //开始音效
            //做延时操作
                startBtn->zoom1(); //向下跳跃
                startBtn->zoom2(); //向上跳跃
                //延时0.5秒后   进入场景
                QTimer::singleShot(500,this,[=](){
                    this->hide();//自身隐藏
                    //设置选择关卡场景出现的位置
                    chooseScence->setGeometry(this->geometry());
                    chooseScence->show();//选择关卡场景的显示
                });
            });

}

//利用绘图时间  绘制背景
void MainScene::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    // 加载标题
    pix.load(":/res/Title.png");

    pix = pix.scaled(pix.width() * 0.5,pix.height() * 0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);


}

MainScene::~MainScene()
{
    delete ui;
}

