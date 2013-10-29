#include"mainwindow.h"
#include<iostream>
#include<QtGui>
using namespace std;

//MainWindow，用于作为本程序的控制窗口。
MainWindow::MainWindow(QWidget *parent){
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    setWindowIcon(QIcon(":/images/icon.png"));

    Wsize = new WindowSize;
    leftwidget = new LeftWidget(this);
    rightwidget = new RightWidget;
    mainlayout = new QHBoxLayout;

    Mtimer = new QTimer(this);

    connect(leftwidget->timer,SIGNAL(timeout()),Mtimer,SIGNAL(timeout()));
    connect(Mtimer,SIGNAL(timeout()),this,SLOT(timeout()));
    connect(rightwidget->combobox1,SIGNAL(activated(QString)),leftwidget,SLOT(combobox1_value_changed(QString)));
    connect(rightwidget->combobox2,SIGNAL(activated(QString)),leftwidget,SLOT(combobox2_value_changed(QString)));
    connect(rightwidget->combobox3,SIGNAL(activated(QString)),leftwidget,SLOT(combobox3_value_changed(QString)));
    connect(rightwidget->settime_box,SIGNAL(valueChanged(double)),leftwidget,SLOT(set_timer(double)));//关联设置定时器
    connect(rightwidget->buttonStart,SIGNAL(clicked()),leftwidget,SLOT(paintStart()));//关联“开始绘图”按钮
    connect(rightwidget->buttonReset,SIGNAL(clicked()),this,SLOT(deleteALL()));//关联“复位”按钮
    connect(rightwidget->buttonQuit,SIGNAL(clicked()),this,SLOT(quit_pressed()));//关联“退出”按钮

    this->setupUi(this);
}

void MainWindow::closeEvent(QCloseEvent *event){
    leftwidget->close();
    rightwidget->close();
    this->close();
    exit(0);
}

void MainWindow::timeout(){
    if(leftwidget->textout_value!=textout_value_old){
        rightwidget->textout->append(leftwidget->textout_value);
        textout_value_old=leftwidget->textout_value;
    }
    if(leftwidget->button_Enabled == true){
        rightwidget->buttonStart->setEnabled(true);
        rightwidget->buttonReset->setEnabled(true);
    }
    else{
        rightwidget->buttonStart->setEnabled(false);
        rightwidget->buttonReset->setEnabled(false);
    }
}

void MainWindow::deleteALL(){
    Mtimer->stop();
    rightwidget->textout->clear();
    rightwidget->combobox2->clear();
    rightwidget->combobox3->clear();
    rightwidget->combobox1->setCurrentIndex(0);
    leftwidget->text_R0->clear();
    leftwidget->text_R1->clear();
    leftwidget->text_Ma1->clear();
    leftwidget->text_Ma2->clear();
    leftwidget->text_Ma3->clear();
    leftwidget->text_Ma4->clear();
    leftwidget->text_Mv1->clear();
    leftwidget->text_Mv2->clear();
    leftwidget->text_Mv3->clear();
    leftwidget->text_Mv4->clear();
}

void MainWindow::quit_pressed(){
    leftwidget->close();
    rightwidget->close();
    this->close();
    exit(0);
}

void MainWindow::setupUi(QWidget *mainwindow){
    setWindowTitle(tr("计算机组成原理课程设计软件"));
    this->setWindowOpacity(0.9);

    Wsize->w=1024;Wsize->h=600;
    this->resize(Wsize->w,Wsize->h);

    mainlayout->addWidget(leftwidget,2);
    mainlayout->addWidget(rightwidget,1);
    this->setLayout(mainlayout);
}

MainWindow::~MainWindow(){
    delete Wsize;
    delete mainlayout;
    delete Mtimer;

    delete this;
}

