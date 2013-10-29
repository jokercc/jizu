//------电子科技大学-计算机组成原理-指令流程模拟运行演示软件------
//本程序根据GPL协议开源，任何组织或个人不得将本程序和/或源码私有化或作为盈利目的使用
//任何对本程序的修改和再编译都必须注明本程序和原作者信息
//本程序原始作者有：杨时雨、黄家垚、曹灿。杨峻欢、戴洋为程序做其它贡献。

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"leftwidget.h"
#include"rightwidget.h"
#include<QtGui>

class WindowSize{
public:
    int w;
    int h;
};

class MainWindow:public QWidget{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);

    void setupUi(QWidget *mainwindow);

    WindowSize* Wsize;
    QTimer *Mtimer;
    QString textout_value_old;

    ~MainWindow();

public slots:
    void timeout();

protected slots:
    virtual void closeEvent(QCloseEvent *event);

protected slots:
    void deleteALL();
    void quit_pressed();

private:
    LeftWidget *leftwidget;
    RightWidget *rightwidget;
    QHBoxLayout *mainlayout;
};


#endif // MAINWINDOW_H

