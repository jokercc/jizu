#include"rightwidget.h"
#include<QtGui>
#include<iostream>

using namespace std;

RightWidget::RightWidget(QWidget *parent){
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    //label0 = new QLabel(this);

    label1 = new QLabel(this);
    combobox1 = new QComboBox(this);
    label2 = new QLabel(this);
    combobox2 = new QComboBox(this);
    label3 = new QLabel(this);
    combobox3 = new QComboBox(this);
    label_timer = new QLabel(this);
    settime_box = new QDoubleSpinBox(this);
    buttonStart = new QPushButton(this);
    buttonReset = new QPushButton(this);
    buttonQuit = new QPushButton(this);
    textout = new QTextBrowser(this);

    this->setupUi(this);
}

void RightWidget::setupUi(QWidget *rightwidget){
    //
    //QLabel *label1;

    label1->setGeometry(QRect(0,24,156,24));
    label1->setText(tr("选择指令"));

    //QComboBox *combobox1;
    combobox1->setGeometry(QRect(168,24,156,24));
    combobox1->addItem(tr("请选择一个指令："));
    combobox1->addItem(tr("--MOV指令--"));
    combobox1->addItem(tr("MOV"));
    combobox1->addItem(tr("--双操作数指令--"));
    combobox1->addItem(tr("ADD"));
    combobox1->addItem(tr("SUB"));
    combobox1->addItem(tr("AND"));
    combobox1->addItem(tr("OR"));
    combobox1->addItem(tr("EOR"));
    combobox1->addItem(tr("--单操作数指令--"));
    combobox1->addItem(tr("COM"));
    combobox1->addItem(tr("NEG"));
    combobox1->addItem(tr("INC"));
    combobox1->addItem(tr("DEC"));
    combobox1->addItem(tr("SL"));
    combobox1->addItem(tr("SR"));
    combobox1->addItem(tr("--转移指令、返回指令--"));
    combobox1->addItem(tr("NJP"));
    combobox1->addItem(tr("JP,RST"));
    combobox1->addItem(tr("--转子指令--"));
    combobox1->addItem(tr("NJSR"));
    combobox1->addItem(tr("JSR"));

    //QLabel *label2;
    label2->setGeometry(QRect(0,64,156,24));
    label2->setText(tr("选择源操作数寻址方式"));

    //QComboBox *combobox2;
    combobox2->setGeometry(QRect(168,64,156,24));

    //QLabel *label3;
    label3->setGeometry(QRect(0,104,156,24));
    label3->setText(tr("选择目的操作数寻址方式"));

    //QComboBox *combobox3;
    combobox3->setGeometry(QRect(168,104,156,24));

    //定时器设置控件的文字标签
    label_timer->setGeometry(QRect(30,158,84,24));
    label_timer->setText(tr("设置延时(s)"));

    //设置定时器
    settime_box->setGeometry(QRect(133,158,84,24));
    settime_box->setRange(0.00,10.00);
    settime_box->setValue(0.50);

    //退出按钮
    buttonQuit->setGeometry(QRect(236,158,84,24));
    buttonQuit->setText(tr("退出程序"));

    //开始绘图按钮
    buttonStart->setGeometry(QRect(30,188,128,24));
    buttonStart->setText(tr("开始绘图"));

    //复位按钮
    buttonReset->setGeometry(QRect(192,188,128,24));
    buttonReset->setText(tr("复位"));

    //指令反馈控件
    textout->setGeometry(QRect(30,242,192,192));

    connect(combobox1,SIGNAL(activated(QString)),this,SLOT(combobox1_changed_to_combobox2(QString)));
    connect(combobox1,SIGNAL(activated(QString)),this,SLOT(combobox1_changed_to_combobox3(QString)));
    connect(buttonStart,SIGNAL(clicked()),textout,SLOT(clear()));
}

void RightWidget::combobox1_changed_to_combobox2(const QString &arg1){
    if((arg1=="MOV")||(arg1=="ADD")||(arg1=="SUB")||(arg1=="AND")||(arg1=="OR")||(arg1=="EOR")){
        combobox2->clear();
        combobox2->addItem(tr("-请选择一项-"));
        combobox2->addItem(tr("R0"));
        combobox2->addItem(tr("(R0)"));
        combobox2->addItem(tr("-(R0)"));
        combobox2->addItem(tr("(R0)+"));
        combobox2->addItem(tr("@(R0)+"));
        combobox2->addItem(tr("X(R0)"));
    }
    else if(arg1=="COM"||arg1=="NEG"||arg1=="INC"||arg1=="DEC"||arg1=="SL"||arg1=="SR"){
        combobox2->clear();
        combobox2->addItem(tr("-请选择一项-"));
        combobox2->addItem(tr("NULL"));
    }
    else if(arg1=="NJP"||arg1=="JP,RST"){
        combobox2->clear();
        combobox2->addItem(tr("-请选择一项-"));
        combobox2->addItem(tr("NULL"));
    }
    else if(arg1=="NJSR"){
        combobox2->clear();
        combobox2->addItem(tr("-请选择一项-"));
        combobox2->addItem(tr("PC"));
        combobox2->addItem(tr("非PC"));
    }
    else if(arg1=="JSR"){
        combobox2->clear();
        combobox2->addItem(tr("-请选择一项-"));
        combobox2->addItem(tr("R0"));
        combobox2->addItem(tr("(R0)"));
        combobox2->addItem(tr("(R0)+"));
    }
}
void RightWidget::combobox1_changed_to_combobox3(const QString &arg1){
    if((arg1=="MOV")||(arg1=="ADD")||(arg1=="SUB")||(arg1=="AND")||(arg1=="OR")||(arg1=="EOR")){
        combobox3->clear();
        combobox3->addItem(tr("-请选择一项-"));
        combobox3->addItem(tr("R1"));
        combobox3->addItem(tr("(R1)"));
        combobox3->addItem(tr("-(R1)"));
        combobox3->addItem(tr("(R1)+"));
        combobox3->addItem(tr("@(R1)+"));
        combobox3->addItem(tr("X(R1)"));
    }
    else if(arg1=="COM"||arg1=="NEG"||arg1=="INC"||arg1=="DEC"||arg1=="SL"||arg1=="SR"){
        combobox3->clear();
        combobox3->addItem(tr("-请选择一项-"));
        combobox3->addItem(tr("R1"));
        combobox3->addItem(tr("(R1)"));
        combobox3->addItem(tr("-(R1)"));
        combobox3->addItem(tr("(R1)+"));
        combobox3->addItem(tr("@(R1)+"));
        combobox3->addItem(tr("X(R1)"));
    }
    else if(arg1=="NJP"){
        combobox3->clear();
        combobox3->addItem(tr("-请选择一项-"));
        combobox3->addItem(tr("非PC"));
        combobox3->addItem(tr("PC"));
    }
    else if(arg1=="JP,RST"){
        combobox3->clear();
        combobox3->addItem(tr("-请选择一项-"));
        combobox3->addItem(tr("SKP"));
        combobox3->addItem(tr("R1"));
        combobox3->addItem(tr("(R1)"));
        combobox3->addItem(tr("(R1)+"));
        combobox3->addItem(tr("X(PC)"));
    }
    else if(arg1=="NJSR"){
        combobox3->clear();
        combobox3->addItem(tr("-请选择一项-"));
        combobox3->addItem(tr("NULL"));

    }
    else if(arg1=="JSR"){
        combobox3->clear();
        combobox3->addItem(tr("-请选择一项-"));
        combobox3->addItem(tr("NULL"));
    }
}


RightWidget::~RightWidget(){
    delete label1;
    delete combobox1;
    delete label2;
    delete combobox2;
    delete label3;
    delete combobox3;
    delete label_timer;
    delete settime_box;
    delete buttonStart;
    delete buttonReset;
    delete buttonQuit;
    delete textout;

    delete this;
}
