#include "chooselevelscence.h"
#include<QMenuBar>
#include<QMenu>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<QSound>
#include"playscene.h"
ChooseLevelScence::ChooseLevelScence(QWidget *parent) : QMainWindow(parent)
{
    //菜单栏
    QMenuBar *bar = menuBar();
    //菜单
    QMenu *startMenu = bar->addMenu("开始");
    //菜单项
    QAction *quictAction = startMenu->addAction("退出");
    connect(quictAction,&QAction::triggered,[=](){
       this->close();
    });

    //窗口大小
    this->setWindowTitle("选择关卡场景");

    this->setFixedSize(320,588);

    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //选中关卡音效
     QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
   //返回按钮音效
     QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

    backBtn->setParent(this);

    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&MyPushButton::clicked,[=](){

        //播放返回按钮音效
        backSound->play();

        //延时发送返回信号
        QTimer::singleShot(500,this,[=](){
            emit this->chooseScenceBack();
        });

    });
    pScene=nullptr;
    //创建20个选择关卡的小按钮
    for(int i=0;i<20;i++){
        MyPushButton *menubtn =new MyPushButton(":/res/LevelIcon.png");
        menubtn->setParent(this);
        menubtn->move(25+(i%4)*70,130+(i/4)*70);
        connect(menubtn,&MyPushButton::clicked,[=](){
            chooseSound->play();//开始播放音效
            pScene =new playScene(i+1);
            this->hide();
            this->pScene->setGeometry(this->geometry());
            this->pScene->show();
          //监听游戏场景中的返回按钮  进行游戏画面切换
            connect(this->pScene,&playScene::chooseScenceBack,[=](){
                this->setGeometry(this->pScene->geometry());
                delete pScene;
                pScene=nullptr;
                this->show();
            });

        });
        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menubtn->width(),menubtn->height());
        label->setText(QString::number(i+1));
        label->move(25+(i%4)*70,130+(i/4)*70);
        //设置居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        // 设置鼠标穿透属性 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

//重写绘图事件
void ChooseLevelScence::paintEvent(QPaintEvent *event){
    //画家
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    // 加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
