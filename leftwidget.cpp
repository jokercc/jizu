#include"leftwidget.h"
#include"mainwindow.h"
#include"BusRegister.h"
#include<QtGui>

using namespace std;

//MainWidget类，用于绘制指令流程
LeftWidget::LeftWidget(QWidget *parent){
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    label1 = new QLabel(this);
    label2 = new QLabel(this);
    label3 = new QLabel(this);
    label4 = new QLabel(this);

    timer = new QTimer(this);

    //定义传值控件
    label_R0 = new QLabel(this);
    label_R1 = new QLabel(this);
    label_Ma = new QLabel(this);
    label_Mv = new QLabel(this);
    label_M1 = new QLabel(this);
    label_M2 = new QLabel(this);
    label_M3 = new QLabel(this);
    label_M4 = new QLabel(this);

    text_R0 = new QLineEdit(this);
    text_R1 = new QLineEdit(this);
    text_Ma1 = new QLineEdit(this);
    text_Ma2 = new QLineEdit(this);
    text_Ma3 = new QLineEdit(this);
    text_Ma4 = new QLineEdit(this);
    text_Mv1 = new QLineEdit(this);
    text_Mv2 = new QLineEdit(this);
    text_Mv3 = new QLineEdit(this);
    text_Mv4 = new QLineEdit(this);

    head=new node;//设立队列头
    rear=head;//设立队列尾巴
    pointer=head;//浮动指针

    //标记“开始”和“复位”按钮的可用状态
    button_Enabled = true;

    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));

    connect(text_R0,SIGNAL(textEdited(QString)),this,SLOT(text_R0_changed(QString)));
    connect(text_R1,SIGNAL(textEdited(QString)),this,SLOT(text_R1_changed(QString)));
    connect(text_Ma1,SIGNAL(textEdited(QString)),this,SLOT(text_Ma1_changed(QString)));
    connect(text_Ma2,SIGNAL(textEdited(QString)),this,SLOT(text_Ma2_changed(QString)));
    connect(text_Ma3,SIGNAL(textEdited(QString)),this,SLOT(text_Ma3_changed(QString)));
    connect(text_Ma4,SIGNAL(textEdited(QString)),this,SLOT(text_Ma4_changed(QString)));
    connect(text_Mv1,SIGNAL(textEdited(QString)),this,SLOT(text_Mv1_changed(QString)));
    connect(text_Mv2,SIGNAL(textEdited(QString)),this,SLOT(text_Mv2_changed(QString)));
    connect(text_Mv3,SIGNAL(textEdited(QString)),this,SLOT(text_Mv3_changed(QString)));
    connect(text_Mv4,SIGNAL(textEdited(QString)),this,SLOT(text_Mv4_changed(QString)));

    this->setupUi(this);
}

void LeftWidget::setupUi(QWidget *parent){
    //为总线贴标签
    label1->setGeometry(QRect(5,20,60,18));
    label1->setText(tr("地址总线"));
    label2->setGeometry(QRect(5,40,60,18));
    label2->setText(tr("数据总线"));
    label3->setGeometry(QRect(5,60,60,18));
    label3->setText(tr("控制总线"));
    label4->setGeometry(QRect(170,78,60,18));
    label4->setText(tr("内总线"));

    label_R0->setGeometry(QRect(15,345,65,30));
    label_R0->setText(tr("R0寄存器"));
    label_R1->setGeometry(QRect(15,380,65,30));
    label_R1->setText(tr("R1寄存器"));
    label_Ma->setGeometry(QRect(30,480,90,30));
    label_Ma->setText(tr("内存地址"));
    label_Mv->setGeometry(QRect(30,530,90,30));
    label_Mv->setText(tr("相应的值"));
    label_M1->setGeometry(QRect(90,450,90,30));
    label_M1->setText(tr("单元1"));
    label_M2->setGeometry(QRect(190,450,90,30));
    label_M2->setText(tr("单元2"));
    label_M3->setGeometry(QRect(290,450,90,30));
    label_M3->setText(tr("单元3"));
    label_M4->setGeometry(QRect(390,450,90,30));
    label_M4->setText(tr("单元4"));

    text_R0->setGeometry(QRect(90,345,90,30));
    text_R1->setGeometry(QRect(90,380,90,30));
    text_Ma1->setGeometry(QRect(90,480,90,30));
    text_Ma2->setGeometry(QRect(190,480,90,30));
    text_Ma3->setGeometry(QRect(290,480,90,30));
    text_Ma4->setGeometry(QRect(390,480,90,30));
    text_Mv1->setGeometry(QRect(90,530,90,30));
    text_Mv2->setGeometry(QRect(190,530,90,30));
    text_Mv3->setGeometry(QRect(290,530,90,30));
    text_Mv4->setGeometry(QRect(390,530,90,30));
}

void LeftWidget::paintEvent(QPaintEvent *event){
    //绘制移位器
    QPainter *pSHIFTER = new QPainter(this);
    pSHIFTER->drawRect(80,96,64,30);
    if(shifter.sym==0){
        pSHIFTER->setBrush(Qt::white);
    }
    else if(shifter.sym==1){
        pSHIFTER->setBrush(Qt::green);
    }
    else if(shifter.sym==2){
        pSHIFTER->setBrush(Qt::blue);
    }
    else if(shifter.sym==3){
        pSHIFTER->setBrush(Qt::red);
    }
    else if(shifter.sym==4){
        pSHIFTER->setBrush(Qt::darkYellow);
    }
    pSHIFTER->drawRect(80,96,64,30);
    QPainter *tSHIFTER = new QPainter(this);
    tSHIFTER->drawText(80,96,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("移位器"));
    QPainter *vSHIFTER = new QPainter(this);
    vSHIFTER->drawText(80,126,64,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(shifter.show_ch())));

    //绘制ALU
    QPainter *pALU = new QPainter(this);
    pALU->setRenderHint(QPainter::Antialiasing,true);
    QPolygon polygonALU;
    polygonALU << QPoint(89,153) << QPoint(137,153) << QPoint(168,209) << QPoint(128,209) << QPoint(113,193) << QPoint(97,209) << QPoint(64,209);
    pALU->drawPolygon(polygonALU);
    if(ALU.sym==0){
        pALU->setBrush(Qt::white);
    }
    else if(ALU.sym==1){
        pALU->setBrush(Qt::green);
    }
    else if(ALU.sym==2){
        pALU->setBrush(Qt::blue);
    }
    else if(ALU.sym==3){
        pALU->setBrush(Qt::red);
    }
    else if(ALU.sym==4){
        pALU->setBrush(Qt::darkYellow);
    }
    pALU->drawPolygon(polygonALU);
    QPainter *tALU = new QPainter(this);
    tALU->drawText(64,153,104,56,Qt::AlignHCenter|Qt::AlignVCenter,tr("ALU"));
    QPainter *vALU = new QPainter(this);
    vALU->drawText(64,209,104,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(ALU.show_ch())));

    //绘制选择器A
    QPainter *pA = new QPainter(this);
    pA->drawRect(33,232,64,30);
    if(A.sym==0){
        pA->setBrush(Qt::white);
    }
    else if(A.sym==1){
        pA->setBrush(Qt::green);
    }
    else if(A.sym==2){
        pA->setBrush(Qt::blue);
    }
    else if(A.sym==3){
        pA->setBrush(Qt::red);
    }
    else if(A.sym==4){
        pA->setBrush(Qt::darkYellow);
    }
    pA->drawRect(33,232,64,30);
    QPainter *tA = new QPainter(this);
    tA->drawText(33,232,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("选择器A"));
    QPainter *vA = new QPainter(this);
    vA->drawText(33,262,64,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(A.show_ch())));

    //绘制选择器B
    QPainter *pB = new QPainter(this);
    pB->drawRect(120,232,64,30);
    if(B.sym==0){
        pB->setBrush(Qt::white);
    }
    else if(B.sym==1){
        pB->setBrush(Qt::green);
    }
    else if(B.sym==2){
        pB->setBrush(Qt::blue);
    }
    else if(B.sym==3){
        pB->setBrush(Qt::red);
    }
    else if(B.sym==4){
        pB->setBrush(Qt::darkYellow);
    }
    pB->drawRect(120,232,64,30);
    QPainter *tB = new QPainter(this);
    tB->drawText(120,232,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("选择器B"));
    QPainter *vB = new QPainter(this);
    vB->drawText(120,262,64,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(B.show_ch())));

    //绘制寄存器R0
    QPainter *pR0 = new QPainter(this);
    pR0->drawRect(232,105,64,30);
    if(R0.sym==0){
        pR0->setBrush(Qt::white);
    }
    else if(R0.sym==1){
        pR0->setBrush(Qt::green);
    }
    else if(R0.sym==2){
        pR0->setBrush(Qt::blue);
    }
    else if(R0.sym==3){
        pR0->setBrush(Qt::red);
    }
    else if(R0.sym==4){
        pR0->setBrush(Qt::darkYellow);
    }
    pR0->drawRect(232,105,64,30);
    QPainter *tR0 = new QPainter(this);
    tR0->drawText(232,105,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("R0"));
    QPainter *vR0 = new QPainter(this);
    vR0->drawText(232,135,64,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(R0.show_ch())));

    //绘制寄存器R1
    QPainter *pR1 = new QPainter(this);
    pR1->drawRect(232,165,64,30);
    if(R1.sym==0){
        pR1->setBrush(Qt::white);
    }
    else if(R1.sym==1){
        pR1->setBrush(Qt::green);
    }
    else if(R1.sym==2){
        pR1->setBrush(Qt::blue);
    }
    else if(R1.sym==3){
        pR1->setBrush(Qt::red);
    }
    else if(R1.sym==4){
        pR1->setBrush(Qt::darkYellow);
    }
    pR1->drawRect(232,165,64,30);
    QPainter *tR1 = new QPainter(this);
    tR1->drawText(232,165,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("R1"));
    QPainter *vR1 = new QPainter(this);
    vR1->drawText(232,195,64,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(R1.show_ch())));

    //绘制寄存器R2
    QPainter *pR2 = new QPainter(this);
    pR2->drawRect(232,225,64,30);
    QPainter *tR2 = new QPainter(this);
    tR2->drawText(232,225,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("R2"));

    //绘制寄存器R3
    QPainter *pR3 = new QPainter(this);
    pR3->drawRect(232,285,64,30);
    QPainter *tR3 = new QPainter(this);
    tR3->drawText(232,285,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("R3"));

    //绘制C
    QPainter *pC = new QPainter(this);
    pC->drawRect(232,345,64,30);
    if(C.sym==0){
        pC->setBrush(Qt::white);
    }
    else if(C.sym==1){
        pC->setBrush(Qt::green);
    }
    else if(C.sym==2){
        pC->setBrush(Qt::blue);
    }
    else if(C.sym==3){
        pC->setBrush(Qt::red);
    }
    else if(C.sym==4){
        pC->setBrush(Qt::darkYellow);
    }
    pC->drawRect(232,345,64,30);
    QPainter *tC = new QPainter(this);
    tC->drawText(232,345,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("C"));
    QPainter *vC = new QPainter(this);
    vC->drawText(232,375,64,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(C.show_ch())));

    //绘制D
    QPainter *pD = new QPainter(this);
    pD->drawRect(232,405,64,30);
    if(D.sym==0){
        pD->setBrush(Qt::white);
    }
    else if(D.sym==1){
        pD->setBrush(Qt::green);
    }
    else if(D.sym==2){
        pD->setBrush(Qt::blue);
    }
    else if(D.sym==3){
        pD->setBrush(Qt::red);
    }
    else if(D.sym==4){
        pD->setBrush(Qt::darkYellow);
    }
    pD->drawRect(232,405,64,30);
    QPainter *tD = new QPainter(this);
    tD->drawText(232,405,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("D"));
    QPainter *vD = new QPainter(this);
    vD->drawText(232,435,64,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(D.show_ch())));

    //绘制MAR
    QPainter *pMAR = new QPainter(this);
    pMAR->drawRect(344,105,64,30);
    if(MAR.sym==0){
        pMAR->setBrush(Qt::white);
    }
    else if(MAR.sym==1){
        pMAR->setBrush(Qt::green);
    }
    else if(MAR.sym==2){
        pMAR->setBrush(Qt::blue);
    }
    else if(MAR.sym==3){
        pMAR->setBrush(Qt::red);
    }
    else if(MAR.sym==4){
        pMAR->setBrush(Qt::darkYellow);
    }
    pMAR->drawRect(344,105,64,30);
    QPainter *tMAR = new QPainter(this);
    tMAR->drawText(344,105,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("MAR"));
    QPainter *vMAR = new QPainter(this);
    vMAR->drawText(344,135,64,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(MAR.show_ch())));

    //绘制MDR
    QPainter *pMDR = new QPainter(this);
    pMDR->drawRect(344,165,64,30);
    if(MDR.sym==0){
        pMDR->setBrush(Qt::white);
    }
    else if(MDR.sym==1){
        pMDR->setBrush(Qt::green);
    }
    else if(MDR.sym==2){
        pMDR->setBrush(Qt::blue);
    }
    else if(MDR.sym==3){
        pMDR->setBrush(Qt::red);
    }
    else if(MDR.sym==4){
        pMDR->setBrush(Qt::darkYellow);
    }
    pMDR->drawRect(344,165,64,30);
    QPainter *tMDR = new QPainter(this);
    tMDR->drawText(344,165,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("MDR"));
    QPainter *vMDR = new QPainter(this);
    vMDR->drawText(344,195,64,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(MDR.show_ch())));

    //绘制IR
    QPainter *pIR = new QPainter(this);
    pIR->drawRect(344,225,64,30);
    if(IR.sym==0){
        pIR->setBrush(Qt::white);
    }
    else if(IR.sym==1){
        pIR->setBrush(Qt::green);
    }
    else if(IR.sym==2){
        pIR->setBrush(Qt::blue);
    }
    else if(IR.sym==3){
        pIR->setBrush(Qt::red);
    }
    else if(IR.sym==4){
        pIR->setBrush(Qt::darkYellow);
    }
    pIR->drawRect(344,225,64,30);
    QPainter *tIR = new QPainter(this);
    tIR->drawText(344,225,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("IR"));
    QPainter *vIR = new QPainter(this);
    vIR->drawText(344,255,64,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(IR.show_ch())));

    //绘制PC
    QPainter *pPC = new QPainter(this);
    pPC->drawRect(344,285,64,30);
    if(PC.sym==0){
        pPC->setBrush(Qt::white);
    }
    else if(PC.sym==1){
        pPC->setBrush(Qt::green);
    }
    else if(PC.sym==2){
        pPC->setBrush(Qt::blue);
    }
    else if(PC.sym==3){
        pPC->setBrush(Qt::red);
    }
    else if(PC.sym==4){
        pPC->setBrush(Qt::darkYellow);
    }
    pPC->drawRect(344,285,64,30);
    QPainter *tPC = new QPainter(this);
    tPC->drawText(344,285,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("PC"));
    QPainter *vPC = new QPainter(this);
    vPC->drawText(344,315,64,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(PC.show_ch())));

    //绘制SP
    QPainter *pSP = new QPainter(this);
    pSP->drawRect(344,345,64,30);
    if(SP.sym==0){
        pSP->setBrush(Qt::white);
    }
    else if(SP.sym==1){
        pSP->setBrush(Qt::green);
    }
    else if(SP.sym==2){
        pSP->setBrush(Qt::blue);
    }
    else if(SP.sym==3){
        pSP->setBrush(Qt::red);
    }
    else if(SP.sym==4){
        pSP->setBrush(Qt::darkYellow);
    }
    pSP->drawRect(344,345,64,30);
    QPainter *tSP = new QPainter(this);
    tSP->drawText(344,345,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("SP"));
    QPainter *vSP = new QPainter(this);
    vSP->drawText(344,375,64,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(SP.show_ch())));

    //绘制PSW
    QPainter *pPSW = new QPainter(this);
    pPSW->drawRect(344,405,64,30);
    if(PSW.sym==0){
        pPSW->setBrush(Qt::white);
    }
    else if(PSW.sym==1){
        pPSW->setBrush(Qt::green);
    }
    else if(PSW.sym==2){
        pPSW->setBrush(Qt::blue);
    }
    else if(PSW.sym==3){
        pPSW->setBrush(Qt::red);
    }
    else if(PSW.sym==4){
        pPSW->setBrush(Qt::darkYellow);
    }
    pPSW->drawRect(344,405,64,30);
    QPainter *tPSW = new QPainter(this);
    tPSW->drawText(344,405,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("PSW"));

    //绘制控制逻辑
    QPainter *pCL = new QPainter(this);
    pCL->drawRect(450,264,64,30);
    QPainter *tCL = new QPainter(this);
    tCL->drawText(450,264,64,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("控制逻辑"));

    //绘制主存
    QPainter *pMEM = new QPainter(this);
    pMEM->drawRect(520,113,45,30);
    if(M.sym==0){
        pMEM->setBrush(Qt::white);
    }
    else if(M.sym==1){
        pMEM->setBrush(Qt::green);
    }
    else if(M.sym==2){
        pMEM->setBrush(Qt::blue);
    }
    else if(M.sym==3){
        pMEM->setBrush(Qt::red);
    }
    else if(M.sym==4){
        pMEM->setBrush(Qt::darkYellow);
    }
    pMEM->drawRect(520,113,45,30);
    QPainter *tMEM = new QPainter(this);
    tMEM->drawText(520,113,45,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("主存"));
//    QPainter *vMEM = new QPainter(this);
//    vMEM->drawText(520,143,45,18,Qt::AlignHCenter|Qt::AlignVCenter,tr(sy_binary_to_hex(M.show_ch())));

    //绘制接口
    QPainter *pIF = new QPainter(this);
    pIF->drawRect(600,113,45,30);
    QPainter *tIF = new QPainter(this);
    tIF->drawText(600,113,45,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("接口"));

    //绘制I/O
    QPainter *pIO = new QPainter(this);
    pIO->drawRect(600,168,45,30);
    QPainter *tIO = new QPainter(this);
    tIO->drawText(600,168,45,30,Qt::AlignHCenter|Qt::AlignVCenter,tr("I/O"));

    //先绘制所有的线条
    QPainter *plines = new QPainter(this);
    plines->setRenderHint(QPainter::Antialiasing,true);
    plines->setPen(Qt::gray);
    QLine line[38];
    line[0].setPoints(QPoint(80,33),QPoint(700,33));//地址总线
    line[1].setPoints(QPoint(80,41),QPoint(700,41));//数据总线
    line[2].setPoints(QPoint(80,49),QPoint(700,49));//控制总线
    line[3].setPoints(QPoint(64,209),QPoint(64,232));//出选择器A
    line[4].setPoints(QPoint(168,209),QPoint(168,232));//出选择器B
    line[5].setPoints(QPoint(113,154),QPoint(113,126));//出ALU
    line[6].setPoints(QPoint(113,96),QPoint(113,73));//内总线（出移位器）
    line[7].setPoints(QPoint(113,73),QPoint(321,73));//内总线
    line[8].setPoints(QPoint(321,73),QPoint(321,450));//内总线（接寄存器）
    line[9].setPoints(QPoint(296,113),QPoint(321,113));//R0
    line[10].setPoints(QPoint(296,175),QPoint(321,175));//R1
    line[11].setPoints(QPoint(296,235),QPoint(321,235));//R2
    line[12].setPoints(QPoint(296,295),QPoint(321,295));//R3
    line[13].setPoints(QPoint(296,355),QPoint(321,355));//C
    line[14].setPoints(QPoint(296,415),QPoint(321,415));//D
    line[15].setPoints(QPoint(321,121),QPoint(344,121));//MAR
    line[16].setPoints(QPoint(321,181),QPoint(344,181));//MDR
    line[17].setPoints(QPoint(321,241),QPoint(344,241));//IR
    line[18].setPoints(QPoint(321,301),QPoint(344,301));//PC
    line[19].setPoints(QPoint(321,361),QPoint(344,361));//SP
    line[20].setPoints(QPoint(321,421),QPoint(344,421));//PSW
    line[21].setPoints(QPoint(408,121),QPoint(426,121));//出MAR
    line[22].setPoints(QPoint(408,181),QPoint(434,181));//出MDR
    line[23].setPoints(QPoint(408,241),QPoint(441,241));//出IR
    line[24].setPoints(QPoint(426,121),QPoint(426,33));//MAR to ADDBUS
    line[25].setPoints(QPoint(434,181),QPoint(434,41));//MDR to DATABUS
    line[26].setPoints(QPoint(441,241),QPoint(441,41));//IR to DATABUS
    line[27].setPoints(QPoint(483,264),QPoint(483,49));//CL to CTRLBUS
    line[28].setPoints(QPoint(532,113),QPoint(532,33));//MEM to ADDBUS
    line[29].setPoints(QPoint(543,113),QPoint(543,41));//MEM to DATABUS
    line[30].setPoints(QPoint(554,113),QPoint(554,49));//MEM to CTRLBUS
    line[31].setPoints(QPoint(611,113),QPoint(611,33));//IF to ADDBUS
    line[32].setPoints(QPoint(622,113),QPoint(622,41));//IF to DATABUS
    line[33].setPoints(QPoint(633,113),QPoint(633,49));//IF to CTRLBUS
    line[34].setPoints(QPoint(622,168),QPoint(622,143));//I/O to IF
    line[35].setPoints(QPoint(70,29),QPoint(80,33));//地址总线延长
    line[36].setPoints(QPoint(70,49),QPoint(80,41));//数据总线延长
    line[37].setPoints(QPoint(70,69),QPoint(80,49));//控制总线延长
    plines->drawLines(line,38);

    //绘制高亮总线
    QPainter *pA2ALU = new QPainter(this);  //选择器A到ALU高亮
    pA2ALU->setRenderHint(QPainter::Antialiasing,true);
    QLine lA2ALU;
    lA2ALU.setPoints(QPoint(64,209),QPoint(64,232));
    if(A.sym==0){
        pA2ALU->setPen(Qt::gray);
    }
    else{
        pA2ALU->setPen(Qt::red);
    }
    pA2ALU->drawLine(lA2ALU);
    //华丽分界线
    QPainter *pB2ALU = new QPainter(this);  //选择器B到ALU高亮
    pB2ALU->setRenderHint(QPainter::Antialiasing,true);
    QLine lB2ALU;
    lB2ALU.setPoints(QPoint(168,209),QPoint(168,232));
    if(B.sym==0){
        pB2ALU->setPen(Qt::gray);
    }
    else{
        pB2ALU->setPen(Qt::red);
    }
    pB2ALU->drawLine(lB2ALU);
    //华丽分界线
    QPainter *pALU2shifter = new QPainter(this); //ALU到移位器高亮
    pALU2shifter->setRenderHint(QPainter::Antialiasing,true);
    QLine lALU2shifter;
    lALU2shifter.setPoints(QPoint(113,154),QPoint(113,126));
    if(shifter.sym==0){
        pALU2shifter->setPen(Qt::gray);
    }
    else{
        pALU2shifter->setPen(Qt::red);
    }
    pALU2shifter->drawLine(lALU2shifter);
    //华丽分界线
    QPainter *pInnerbus = new QPainter(this);   //内总线高亮
    pInnerbus->setRenderHint(QPainter::Antialiasing,true);
    QLine lInnerbus[2];
    lInnerbus[0].setPoints(QPoint(113,73),QPoint(321,73));
    lInnerbus[1].setPoints(QPoint(321,73),QPoint(321,450));
    if(innerbus.sym==0){
        pInnerbus->setPen(Qt::gray);
    }
    else{
        pInnerbus->setPen(Qt::red);
    }
    pInnerbus->drawLines(lInnerbus,2);
    //华丽分界线
    QPainter *pI2shifter = new QPainter(this); //内总线到移位器高亮
    pI2shifter->setRenderHint(QPainter::Antialiasing,true);
    QLine lI2shifter;
    lI2shifter.setPoints(QPoint(113,96),QPoint(113,73));
    if(innerbus.sym==0 || shifter.sym==0){
        pI2shifter->setPen(Qt::gray);
    }
    else{
        pI2shifter->setPen(Qt::red);
    }
    pI2shifter->drawLine(lI2shifter);
    //华丽分界线
    QPainter *pI2R0 = new QPainter(this); //内总线到R0高亮
    pI2R0->setRenderHint(QPainter::Antialiasing,true);
    QLine lI2R0;
    lI2R0.setPoints(QPoint(296,113),QPoint(321,113));
    if(innerbus.sym==0 || R0.sym==0){
        pI2R0->setPen(Qt::gray);
    }
    else{
        pI2R0->setPen(Qt::red);
    }
    pI2R0->drawLine(lI2R0);
    //华丽分界线
    QPainter *pI2R1 = new QPainter(this); //内总线到R1高亮
    pI2R1->setRenderHint(QPainter::Antialiasing,true);
    QLine lI2R1;
    lI2R1.setPoints(QPoint(296,175),QPoint(321,175));
    if(innerbus.sym==0 || R1.sym==0){
        pI2R1->setPen(Qt::gray);
    }
    else{
        pI2R1->setPen(Qt::red);
    }
    pI2R1->drawLine(lI2R1);
    //华丽分界线
    QPainter *pI2C = new QPainter(this); //内总线到C高亮
    pI2C->setRenderHint(QPainter::Antialiasing,true);
    QLine lI2C;
    lI2C.setPoints(QPoint(296,355),QPoint(321,355));
    if(innerbus.sym==0 || C.sym==0){
        pI2C->setPen(Qt::gray);
    }
    else{
        pI2C->setPen(Qt::red);
    }
    pI2C->drawLine(lI2C);
    //华丽分界线
    QPainter *pI2D = new QPainter(this); //内总线到D高亮
    pI2D->setRenderHint(QPainter::Antialiasing,true);
    QLine lI2D;
    lI2D.setPoints(QPoint(296,415),QPoint(321,415));
    if(innerbus.sym==0 || D.sym==0){
        pI2D->setPen(Qt::gray);
    }
    else{
        pI2D->setPen(Qt::red);
    }
    pI2D->drawLine(lI2D);
    //华丽分界线
    QPainter *pI2MAR = new QPainter(this); //内总线到MAR高亮
    pI2MAR->setRenderHint(QPainter::Antialiasing,true);
    QLine lI2MAR;
    lI2MAR.setPoints(QPoint(321,121),QPoint(344,121));
    if(innerbus.sym==0 || MAR.sym==0){
        pI2MAR->setPen(Qt::gray);
    }
    else{
        pI2MAR->setPen(Qt::red);
    }
    pI2MAR->drawLine(lI2MAR);
    //华丽分界线
    QPainter *pI2MDR = new QPainter(this); //内总线到MDR高亮
    pI2MDR->setRenderHint(QPainter::Antialiasing,true);
    QLine lI2MDR;
    lI2MDR.setPoints(QPoint(321,181),QPoint(344,181));
    if(innerbus.sym==0 || MDR.sym==0){
        pI2MDR->setPen(Qt::gray);
    }
    else{
        pI2MDR->setPen(Qt::red);
    }
    pI2MDR->drawLine(lI2MDR);
    //华丽分界线
    QPainter *pI2IR = new QPainter(this); //内总线到IR高亮
    pI2IR->setRenderHint(QPainter::Antialiasing,true);
    QLine lI2IR;
    lI2IR.setPoints(QPoint(321,241),QPoint(344,241));
    if(innerbus.sym==0 || IR.sym==0){
        pI2IR->setPen(Qt::gray);
    }
    else{
        pI2IR->setPen(Qt::red);
    }
    pI2IR->drawLine(lI2IR);
    //华丽分界线
    QPainter *pI2PC = new QPainter(this); //内总线到PC高亮
    pI2PC->setRenderHint(QPainter::Antialiasing,true);
    QLine lI2PC;
    lI2PC.setPoints(QPoint(321,301),QPoint(344,301));
    if(innerbus.sym==0 || PC.sym==0){
        pI2PC->setPen(Qt::gray);
    }
    else{
        pI2PC->setPen(Qt::red);
    }
    pI2PC->drawLine(lI2PC);
    //华丽分界线
    QPainter *pI2SP = new QPainter(this); //内总线到SP高亮
    pI2SP->setRenderHint(QPainter::Antialiasing,true);
    QLine lI2SP;
    lI2SP.setPoints(QPoint(321,361),QPoint(344,361));
    if(innerbus.sym==0 || SP.sym==0){
        pI2SP->setPen(Qt::gray);
    }
    else{
        pI2SP->setPen(Qt::red);
    }
    pI2SP->drawLine(lI2SP);
    //华丽分界线
    QPainter *pI2PSW = new QPainter(this); //内总线到PSW高亮
    pI2PSW->setRenderHint(QPainter::Antialiasing,true);
    QLine lI2PSW;
    lI2PSW.setPoints(QPoint(321,421),QPoint(344,421));
    if(innerbus.sym==0 || PSW.sym==0){
        pI2PSW->setPen(Qt::gray);
    }
    else{
        pI2PSW->setPen(Qt::red);
    }
    pI2PSW->drawLine(lI2PSW);
    //华丽分界线
    QPainter *pMAR2MEM = new QPainter(this);   //MAR到内存高亮
    pMAR2MEM->setRenderHint(QPainter::Antialiasing,true);
    QLine lMAR2MEM[4];
    lMAR2MEM[0].setPoints(QPoint(408,121),QPoint(426,121));
    lMAR2MEM[1].setPoints(QPoint(426,121),QPoint(426,33));
    lMAR2MEM[2].setPoints(QPoint(426,33),QPoint(532,33));
    lMAR2MEM[3].setPoints(QPoint(532,113),QPoint(532,33));
    if(MAR.sym==0 || M.sym==0){
        pMAR2MEM->setPen(Qt::gray);
    }
    else{
        pMAR2MEM->setPen(Qt::red);
    }
    pMAR2MEM->drawLines(lMAR2MEM,4);
    //华丽分界线
    QPainter *pMDR2MEM = new QPainter(this);   //MDR到内存高亮
    pMDR2MEM->setRenderHint(QPainter::Antialiasing,true);
    QLine lMDR2MEM[4];
    lMDR2MEM[0].setPoints(QPoint(408,181),QPoint(434,181));
    lMDR2MEM[1].setPoints(QPoint(434,181),QPoint(434,41));
    lMDR2MEM[2].setPoints(QPoint(434,41),QPoint(543,41));
    lMDR2MEM[3].setPoints(QPoint(543,113),QPoint(543,41));
    if(MDR.sym==0 || M.sym==0){
        pMDR2MEM->setPen(Qt::gray);
    }
    else{
        pMDR2MEM->setPen(Qt::red);
    }
    pMDR2MEM->drawLines(lMDR2MEM,4);
    //绘制高亮总线

    this->update();

    //delete所有指针
    delete pSHIFTER; delete tSHIFTER; delete vSHIFTER;
    delete pALU; delete tALU; delete vALU;
    delete pA; delete tA; delete vA; delete pB; delete tB; delete vB;
    delete pR0; delete tR0; delete vR0; delete pR1; delete tR1; delete vR1;
    delete pR2; delete pR3;
    delete pC; delete tC; delete vC; delete pD; delete tD; delete vD;
    delete pMAR; delete tMAR; delete vMAR; delete pMDR; delete tMDR; delete vMDR;
    delete pIR; delete tIR; delete vIR; delete pPC; delete tPC; delete vPC;
    delete pSP; delete tSP; delete vSP; delete pPSW; delete tPSW;
    delete pCL; delete tCL; delete pMEM; delete tMEM; //delete vMEM;
    delete pIF; delete tIF; delete pIO; delete tIO;
    delete plines;

    //delete总线高亮
    delete pA2ALU; delete pB2ALU;
    delete pALU2shifter; delete pI2shifter;
    delete pInnerbus;
    delete pI2R0; delete pI2R1; delete pI2C; delete pI2D;
    delete pI2MAR; delete pI2MDR; delete pI2IR; delete pI2PC; delete pI2SP; delete pI2PSW;
    delete pMAR2MEM; delete pMDR2MEM;

    QWidget::paintEvent(event);
}

void LeftWidget::combobox1_value_changed(const QString &arg1){
    combobox1_value = q2s(arg1);
}

void LeftWidget::combobox2_value_changed(const QString &arg1){
    combobox2_value = q2s(arg1);
}

void LeftWidget::combobox3_value_changed(const QString &arg1){
    combobox3_value = q2s(arg1);
}

void LeftWidget::set_timer(double time_changed){
    the_time = time_changed;
    the_time_ms = the_time*1000;
}

void LeftWidget::paintStart(){
    button_Enabled = false;
    program_start(combobox1_value,combobox3_value,combobox2_value);
    all_zero(1);
    timer->start(the_time_ms);
    this->update();
}

void LeftWidget::deleteALL(){
    timer->stop();
    all_zero(1);
    text_R0->clear();
    text_R1->clear();
    text_Ma1->clear();
    text_Ma2->clear();
    text_Ma3->clear();
    text_Ma4->clear();
    text_Mv1->clear();
    text_Mv2->clear();
    text_Mv3->clear();
    text_Mv4->clear();
    if(pointer->next==NULL){
        Free_quene();
    }
    this->update();
}

void LeftWidget::timeout(){
    cout<<pointer->name<<":"<<pointer->value<<" color;"<<pointer->color<<endl;
    timer->stop();

    string *tmp;
    tmp = new string;
    *tmp = sy_binary_to_hex(M.MM[3].ch);
    text_Mv1->setText(s2q(*tmp));
    *tmp = sy_binary_to_hex(M.MM[4].ch);
    text_Mv2->setText(s2q(*tmp));
    *tmp = sy_binary_to_hex(M.MM[5].ch);
    text_Mv3->setText(s2q(*tmp));
    *tmp = sy_binary_to_hex(M.MM[6].ch);
    text_Mv4->setText(s2q(*tmp));
    delete tmp;

    if(pointer->name=="ZERO"){
        all_zero();
    }
    else if(pointer->name=="STDTET"){
        textout_value = s2q(pointer->Procedure);
    }
    else if(pointer->name=="ALU"){
        ALU.get_color(pointer->color);
        ALU.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="shifter"){
        shifter.get_color(pointer->color);
        shifter.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="A"){
        A.get_color(pointer->color);
        A.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="B"){
        B.get_color(pointer->color);
        B.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="R0"){
        R0.get_color(pointer->color);
        R0.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="R1"){
        R1.get_color(pointer->color);
        R1.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="C"){
        C.get_color(pointer->color);
        C.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="D"){
        D.get_color(pointer->color);
        D.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="MAR"){
        MAR.get_color(pointer->color);
        MAR.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="MDR"){
        MDR.get_color(pointer->color);
        MDR.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="IR"){
        IR.get_color(pointer->color);
        IR.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="PC"){
        PC.get_color(pointer->color);
        PC.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="M"){
        M.get_color(pointer->color);
        M.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="SP"){
        SP.get_color(pointer->color);
        SP.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="PSW"){
        PSW.get_color(pointer->color);
        PSW.get_ch(sy_hex_to_binary(pointer->value));
    }
    else if(pointer->name=="innerbus"){
        innerbus.get_color(pointer->color);
        innerbus.get_ch(sy_hex_to_binary(pointer->value));
    }

    this->update();
    if(pointer->next!=NULL){
        pointer=pointer->next;
        timer->start(the_time_ms);
    }
    else{
        Free_quene();
        textout_value = "Finished";
        button_Enabled = true;
    }
}

void LeftWidget::text_R0_changed(const QString &arg1){
    char *temp;
    temp = new char[5];
    strcpy(temp,q2s(arg1).c_str());
    R0.get_ch(sy_hex_to_binary(temp));
    delete temp;
}

void LeftWidget::text_R1_changed(const QString &arg1){
    char *temp;
    temp = new char[5];
    strcpy(temp,q2s(arg1).c_str());
    R1.get_ch(sy_hex_to_binary(temp));
    delete temp;
}

void LeftWidget::text_Ma1_changed(const QString &arg1){
    char *temp;
    temp = new char[5];
    strcpy(temp,q2s(arg1).c_str());
    strcpy(M.MM[3].address,(sy_hex_to_binary(temp)));
    delete temp;
}

void LeftWidget::text_Ma2_changed(const QString &arg1){
    char *temp;
    temp = new char[5];
    strcpy(temp,q2s(arg1).c_str());
    strcpy(M.MM[4].address,(sy_hex_to_binary(temp)));
    delete temp;
}

void LeftWidget::text_Ma3_changed(const QString &arg1){
    char *temp;
    temp = new char[5];
    strcpy(temp,q2s(arg1).c_str());
    strcpy(M.MM[5].address,(sy_hex_to_binary(temp)));
    delete temp;
}

void LeftWidget::text_Ma4_changed(const QString &arg1){
    char *temp;
    temp = new char[5];
    strcpy(temp,q2s(arg1).c_str());
    strcpy(M.MM[6].address,(sy_hex_to_binary(temp)));
    delete temp;
}

void LeftWidget::text_Mv1_changed(const QString &arg1){
    char *temp;
    temp = new char[5];
    strcpy(temp,q2s(arg1).c_str());
    strcpy(M.MM[3].ch,(sy_hex_to_binary(temp)));
    delete temp;
}

void LeftWidget::text_Mv2_changed(const QString &arg1){
    char *temp;
    temp = new char[5];
    strcpy(temp,q2s(arg1).c_str());
    strcpy(M.MM[4].ch,(sy_hex_to_binary(temp)));
    delete temp;
}

void LeftWidget::text_Mv3_changed(const QString &arg1){
    char *temp;
    temp = new char[5];
    strcpy(temp,q2s(arg1).c_str());
    strcpy(M.MM[5].ch,(sy_hex_to_binary(temp)));
    delete temp;
}

void LeftWidget::text_Mv4_changed(const QString &arg1){
    char *temp;
    temp = new char[5];
    strcpy(temp,q2s(arg1).c_str());
    strcpy(M.MM[6].ch,(sy_hex_to_binary(temp)));
    delete temp;
}

LeftWidget::~LeftWidget(){
    delete label1;
    delete label2;
    delete label3;
    delete label4;
    delete timer;
    delete label_R0;
    delete label_R1;
    delete label_Ma;
    delete label_Mv ;
    delete label_M1;
    delete label_M2;
    delete label_M3;
    delete label_M4;
    delete text_R0;
    delete text_R1;
    delete text_Ma1;
    delete text_Ma2;
    delete text_Ma3;
    delete text_Ma4;
    delete text_Mv1;
    delete text_Mv2;
    delete text_Mv3;
    delete text_Mv4;
    delete head;

    delete this;
}


QString s2q(const string &s){
    return QString(QString::fromLocal8Bit(s.c_str()));
}
string q2s(const QString &s){
    return string((const char *)s.toLocal8Bit());
}
