#include "playscene.h"
#include<QDebug>
#include<QMenu>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<QString>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
//playScene::playScene(QWidget *parent) : QMainWindow(parent)
//{

//}
playScene::playScene(int levelIndex){
    this->levelIndex=levelIndex;

    this->setFixedSize(320,588);
       //设置图标
       this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
       //设置标题
       this->setWindowTitle("翻金币");

       //创建菜单栏
       QMenuBar * bar = this->menuBar();
       this->setMenuBar(bar);
       //创建开始菜单
       QMenu * startMenu = bar->addMenu("开始");
       //创建按钮菜单项
       QAction * quitAction = startMenu->addAction("退出");
       //点击退出 退出游戏
       connect(quitAction,&QAction::triggered,[=](){this->close();});
       //返回按钮音效
       QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
       //翻金币音效
       QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
       //胜利按钮音效
       QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);
       //返回按钮
       MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

       backBtn->setParent(this);

       backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

       connect(backBtn,&MyPushButton::clicked,[=](){
           backSound->play();
           //延时发送返回信号
           QTimer::singleShot(500,this,[=](){
               emit this->chooseScenceBack();
           });
       });
       //创建用户选择的关卡的标签
       //当前关卡标题
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str = QString("Level:%1").arg(this->levelIndex);
     qDebug()<<"用户选择的是"<<this->levelIndex<<"关";
    label->setText(str);
    label->setGeometry(QRect(20, this->height() - 50,140, 50)); //设置大小和位置

    dataConfig config;
    //初始化二维数组
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }
    //胜利图片
    QLabel* winLabel = new QLabel;
   QPixmap tmpPix;
   tmpPix.load(":/res/LevelCompletedDialogBg.png");
   winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
   winLabel->setPixmap(tmpPix);
   winLabel->setParent(this);
   winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());


    //创建金币的背景图片
      for(int i = 0 ; i < 4;i++)
      {
          for(int j = 0 ; j < 4; j++)
          {
             //绘制背景图片
              QLabel* label = new QLabel;
              QPixmap pix;
              pix.load(":/res/BoardNode.png");
              label->setGeometry(0,0,pix.width(),pix.height());
              label->setPixmap(pix);
              label->setParent(this);
              label->move(57 + i*pix.width(),200+j*pix.height());

              QString str;
              if(this->gameArray[i][j]==1){
                  str=":/res/Coin0001.png";
              }else{
                  str=":/res/Coin0008.png";
              }
               //创建金币
              MyCoin *coin=new MyCoin(str);
              coin->setParent(this);
              coin->move(59 + i*pix.width(),204+j*pix.height());

              coin->posX=i;
              coin->posY=j;
              coin->flag=this->gameArray[i][j];

              //将金币放到二维数组中
              coinBtn[i][j] = coin;

                //监听点击按钮信号
              connect(coin,&MyCoin::clicked,[=](){
                  for(int i = 0 ; i < 4;i++)
                  {
                      for(int j = 0 ; j < 4; j++)
                      {
                         coinBtn[i][j]->isWin=true;
                      }
                  }
                  //开启翻金币音效
                  flipSound->play();
              //qDebug() << "点击的位置： x = " <<  coin->posX << " y = " << coin->posY ;
              coin->changeFlag();
              //同步二维数组，如果以后有需求，可以用数组还原
              gameArray[i][j] = gameArray[i][j] == 0 ? 1 : 0; //数组内部记录的标志同步修改
              //翻转周围硬币
              QTimer::singleShot(300, this,[=](){
                  if(coin->posX+1 <=3)
                  {
                    coinBtn[coin->posX+1][coin->posY]->changeFlag();
                    gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                  }
                  if(coin->posX-1>=0)
                  {
                    coinBtn[coin->posX-1][coin->posY]->changeFlag();
                    gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY]== 0 ? 1 : 0;
                  }
                  if(coin->posY+1<=3)
                  {
                   coinBtn[coin->posX][coin->posY+1]->changeFlag();
                   gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                  }
                  if(coin->posY-1>=0)
                  {
                   coinBtn[coin->posX][coin->posY-1]->changeFlag();
                   gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                  }
                  for(int i = 0 ; i < 4;i++)
                  {
                      for(int j = 0 ; j < 4; j++)
                      {
                         coinBtn[i][j]->isWin=false;
                      }
                  }
                  //判断是否胜利
                  this->isWin = true;
                  for(int i = 0 ; i < 4;i++)
                  {
                      for(int j = 0 ; j < 4; j++)
                      {
                          //qDebug() << coinBtn[i][j]->flag ;
                          if( coinBtn[i][j]->flag == false)
                          {
                              this->isWin = false;
                              break;
                          }
                      }
                  }


                  //如果isWin依然是true，代表胜利了！
                  if(this->isWin){
                    qDebug() << "胜利";
                    //开启胜利音效
                    QTimer::singleShot(800,this,[=](){
                         winSound->play();
                    });

                    for(int i = 0 ; i < 4;i++)
                    {
                        for(int j = 0 ; j < 4; j++)
                        {
                           coinBtn[i][j]->isWin=true;
                        }
                    }
                  //将胜利的图片做一个动画
                    if(this->isWin){
                       qDebug() << "胜利";
                       QPropertyAnimation * animation1 =  new QPropertyAnimation(winLabel,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+134,winLabel->width(),winLabel->height()));
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start(QAbstractAnimation::DeleteWhenStopped);
                        }
                     }
                    });
                });
          }
      }
}

//重写绘图事件
void playScene::paintEvent(QPaintEvent *){
   //加载背景
   QPainter painter(this);
   QPixmap pix;
   pix.load(":/res/PlayLevelSceneBg.png");
   painter.drawPixmap(0,0,this->width(),this->height(),pix);

   //加载标题
   pix.load(":/res/Title.png");
   pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
   painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);
}
