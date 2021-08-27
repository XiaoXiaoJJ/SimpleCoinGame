#include "mypushbutton.h"
#include<QMessageBox>
#include<QPushButton>
#include<QPropertyAnimation>
//MyPushButton::MyPushButton(QPushButton *parent) : QPushButton(parent)
//{

//}
MyPushButton::MyPushButton(QString normalImg,QString pressImg){
    this->normalImgPath=normalImg;
    this->pressedImgPath=pressImg;
    //pixmap加载图片
    QPixmap pix;
    bool ret=pix.load(normalImgPath);
    if(!ret){
        QString str = QString("图片加载失败 %1").arg(normalImg);
        QMessageBox::warning(this,"警告",str);
        return;
    }
    //设置图片大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
     //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}
void MyPushButton::zoom1(){
    //创建动画对象
        QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
        //设置时间间隔，单位毫秒
        animation1->setDuration(200);
        //创建起始位置
        animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
        //创建结束位置
        animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
        //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果    animation1->setEasingCurve(QEasingCurve::OutBounce);
        //开始执行动画
        animation1->start(QAbstractAnimation::DeleteWhenStopped);
}
void MyPushButton::zoom2(){
    //创建动画对象
        QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
        //设置时间间隔，单位毫秒
        animation1->setDuration(200);
        //创建起始位置
        animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
        //创建结束位置
        animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
        //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果    animation1->setEasingCurve(QEasingCurve::OutBounce);
        //开始执行动画
        animation1->start();
}

//重写鼠标按下
void  MyPushButton::mousePressEvent(QMouseEvent *e){
    //如果按下切换图片的路径不为空的话，要切图
    if(this->pressedImgPath!=""){
        //pixmap加载图片
        QPixmap pix;
        bool ret=pix.load(pressedImgPath);
        if(!ret){
            QString str = QString("图片加载失败 %1").arg(pressedImgPath);
            QMessageBox::warning(this,"警告",str);
            return;
        }
        //设置图片大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
         //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //点击的响应事件抛给父类
    QPushButton::mousePressEvent(e);
}
//重写鼠标释放
void  MyPushButton::mouseReleaseEvent(QMouseEvent *e){
    //如果按下切换图片的路径不为空的话，要切图
    if(this->pressedImgPath!=""){
        //pixmap加载图片
        QPixmap pix;
        bool ret=pix.load(this->normalImgPath);
        if(!ret){
            QString str = QString("图片加载失败 %1").arg(normalImgPath);
            QMessageBox::warning(this,"警告",str);
            return;
        }
        //设置图片大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
         //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //点击的响应事件抛给父类
    QPushButton::mouseReleaseEvent(e);
}
