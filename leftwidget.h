//------电子科技大学-计算机组成原理-指令流程模拟运行演示软件------
//本程序根据GPL协议开源，任何组织或个人不得将本程序和/或源码私有化或作为盈利目的使用
//任何对本程序的修改和再编译都必须注明本程序和原作者信息
//本程序原始作者有：杨时雨、黄家垚、曹灿。杨峻欢、戴洋为程序做其它贡献。

#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include<QtGui>
#include<iostream>
using namespace std;


QString s2q(const string &s);
string q2s(const QString &s);

class LeftWidget:public QWidget{
    Q_OBJECT
public:
    LeftWidget(QWidget *parent = 0);
    void setupUi(QWidget *leftwidget);

    //设定QT定时器，用于全局定时
    QTimer *timer;

    //存放要传递给右边控件的文字输出
    QString textout_value;

    //定义传值控件
    QLineEdit *text_R0;
    QLineEdit *text_R1;
    QLineEdit *text_Ma1;
    QLineEdit *text_Ma2;
    QLineEdit *text_Ma3;
    QLineEdit *text_Ma4;
    QLineEdit *text_Mv1;
    QLineEdit *text_Mv2;
    QLineEdit *text_Mv3;
    QLineEdit *text_Mv4;

    bool button_Enabled;

    ~LeftWidget();

public slots:
    void timeout();

protected:
    void paintEvent(QPaintEvent *event);

protected slots:
    void combobox1_value_changed(const QString &arg1);
    void combobox2_value_changed(const QString &arg1);
    void combobox3_value_changed(const QString &arg1);
    void paintStart();
    void deleteALL();
    void set_timer(double time_changed);

private:
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;

    QLabel *label_R0;
    QLabel *label_R1;
    QLabel *label_Ma;
    QLabel *label_Mv;
    QLabel *label_M1;
    QLabel *label_M2;
    QLabel *label_M3;
    QLabel *label_M4;

private slots:
    void text_R0_changed(const QString &arg1);
    void text_R1_changed(const QString &arg1);
    void text_Ma1_changed(const QString &arg1);
    void text_Ma2_changed(const QString &arg1);
    void text_Ma3_changed(const QString &arg1);
    void text_Ma4_changed(const QString &arg1);
    void text_Mv1_changed(const QString &arg1);
    void text_Mv2_changed(const QString &arg1);
    void text_Mv3_changed(const QString &arg1);
    void text_Mv4_changed(const QString &arg1);

};

#endif // LEFTWIDGET_H
