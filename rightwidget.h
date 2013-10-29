//------电子科技大学-计算机组成原理-指令流程模拟运行演示软件------
//本程序根据GPL协议开源，任何组织或个人不得将本程序和/或源码私有化或作为盈利目的使用
//任何对本程序的修改和再编译都必须注明本程序和原作者信息
//本程序原始作者有：杨时雨、黄家垚、曹灿。杨峻欢、戴洋为程序做其它贡献。

#ifndef RIGHTWIDGET_H
#define RIGHTWIDGET_H

#include<QtGui>

class RightWidget:public QWidget{
    Q_OBJECT
public:
    RightWidget(QWidget *parent = 0);
    void setupUi(QWidget *rightwidget);

    QDoubleSpinBox *settime_box;
    QPushButton *buttonQuit;
    QPushButton *buttonStart;
    QPushButton *buttonReset;
    QTextBrowser *textout;

    ~RightWidget();

    QComboBox *combobox1;
    QComboBox *combobox2;
    QComboBox *combobox3;

protected slots:
    void combobox1_changed_to_combobox2(const QString &arg1);
    void combobox1_changed_to_combobox3(const QString &arg1);

private:
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label_timer;
};

#endif // RIGHTWIDGET_H
