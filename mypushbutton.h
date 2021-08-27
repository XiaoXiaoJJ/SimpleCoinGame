#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);
    //normalImg 代表正常显示的图片
    //pressImg  代表按下后显示的图片，默认为空
    MyPushButton(QString normalImg,QString pressImg = "");

    QString normalImgPath;  //默认显示图片路径
    QString pressedImgPath; //按下后显示图片路径
    //向下弹起
    void zoom1();
    //向上弹起
   void zoom2();

   //重写鼠标按下
   void mousePressEvent(QMouseEvent *e);
   //重写鼠标释放
   void mouseReleaseEvent(QMouseEvent *e);

signals:

};

#endif // MYPUSHBUTTON_H
